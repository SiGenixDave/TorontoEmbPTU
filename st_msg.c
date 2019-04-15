/*****************************************************************************
 *
 * .b
 *   Copyright (C) 2001 Bombardier Transportation (Holdings) USA Inc.
 *
 * Project:      Pittsburgh LRV Propulsion
 *
 * File Name:    st_msg.c
 *
 * Subsystem:    VCU: Self Test
 *
 * Procedures:   Write_st_cmd_buf
 *               Read_st_resp_buf
 *               Write_st_resp_buf
 *               Respond_brief
 *               Respond_detailed
 *               Respond_counter
 *               Respond_special
 *               Respond_interactive
 *
 * .b
 *
 * History:
 *   Jun 8 2001 Vipin Sapra @ Bombardier
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
/*  Grab all of the compiler #pragma's.                                     */
#ifdef __cplusplus
extern "C" {
#endif

#include "myWrapper.h"
#include "fltinfo.h"
//#include "rts_api.h"

//#include "st_dd.h"
#include "st_def.h"
#include "st_var.h"

extern UINT_32 getSTControlFlag();
extern void setSTAbortTestFlag(UINT_16 aFlag);
extern UINT_16 getSTMode();
extern UINT_16 getSTItem();
void Log_st_event(UINT_16, UINT_16, UINT_32, UINT_32, UINT_32, UINT_32, UINT_32,
		UINT_32, UINT_32, UINT_32, UINT_32, UINT_32);

/*****************************************************************************
 *
 * .b
 * Procedure Name: Write_st_cmd_buf
 *
 * Abstract:
 *   This function writes the PTU Self-test command into the local buffer.
 *
 * INPUTS:
 *   Globals:
 *     None
 *
 *   Procedure Parameters:
 *     UINT_8 *buffer, Pointer to the Command
 *     UINT_16 length, Command Data Length
 *
 * OUTPUTS:
 *   Globals:
 *     None
 *
 *   Returned Values:
 *     None
 *
 * Functional Description:
 *   This function writes the PTU self-test command into the local circular
 *   command buffer of size ST_CMD_BUFFER_SIZE. This command buffer acts as a
 *   shared memory between the PTU and the Self-test task. The PTU Task writes
 *   the received command. Self-test task acts as per the command appropriately.
 *
 *   cmd_buf.index_in != cmd_buf.index_out indicates pending commands.
 *   cmd_buf.index_in == cmd_buf.index_out indicates no new commands
 *   or buffer full.
 *
 *   While writing, the PTU task takes care that it does not overwrite the
 *   command, which is not read by the Self-test task.
 *   In case the command buffer is full, the event is logged and all the pending
 *   commands are purged. The current Self-test session is aborted.
 *   If the command is Update List (ST_CMD_UPDT_LIST), the user-defined list is
 *   copied.
 *
 *   A check is made to ensure that the length of self-test list provided by PTU
 *   matches the number of bytes received.
 *
 *   A check is made to ensure the number of User defined tests does not
 *   exceed the list size. The number of User defined tests are limited to
 *   ST_MAX_USRDEF_LIST_SIZE.
 *
 *   Note that the PTU and Self-test task time are different
 *
 * .b
 *
 * History:
 *   Jun 8 2001 Vipin Sapra @ Bombardier
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
void Write_st_cmd_buf(UINT_8 *buffer, UINT_16 length) {
	struct st_cmd_str *cmd;
	UINT_16 i, cmd_buf_index_out;

	cmd = (struct st_cmd_str *) buffer;

	/* Write the command */
	st_cmd_buf[cmd_buf.index_in].id = cmd->id;
	st_cmd_buf[cmd_buf.index_in].xy_info = cmd->xy_info;
	st_cmd_buf[cmd_buf.index_in].data = cmd->data;


	/* Debug */
	if (cmd->id != ST_CMD_UPDT_MODE) {
		Log_st_event(Engineering, ST_E_WRITE_ST_CMD_BUF, cmd->id, cmd->xy_info,
				cmd->data, cmd_buf.index_in, cmd_buf.index_out, 0, 0, 0, 0, 0);
	}

	/* Update User-defined List */
	if (st_cmd_buf[cmd_buf.index_in].id == ST_CMD_UPDT_LIST) {
		/* Check for User defined Test-list Length Mismatch */
		if (length
				!= (sizeof(struct st_cmd_str) - sizeof(cmd->usrdef_test_id)
						+ (st_cmd_buf[cmd_buf.index_in].data
								* (sizeof(cmd->usrdef_test_id)
										/ ST_MAX_USRDEF_LIST_SIZE)))) {
			/* Ignore the User-defined list */
			st_cmd_buf[cmd_buf.index_in].data = 0;

			/* User defined Test-list Length Mismatch */
			Log_st_event(Engineering, ST_E_USRDEF_LIST_LENGTH_MISMATCH,
					st_cmd_buf[cmd_buf.index_in].id,
					st_cmd_buf[cmd_buf.index_in].xy_info,
					st_cmd_buf[cmd_buf.index_in].data, length, 0, 0, 0, 0, 0,
					0);
		}

		if (st_cmd_buf[cmd_buf.index_in].data > (ST_MAX_USRDEF_LIST_SIZE - 1)) {
			/* Allow the last for ST_NULL, the list terminator */
			st_cmd_buf[cmd_buf.index_in].data = ST_MAX_USRDEF_LIST_SIZE - 1;

			/* Number of User defined tests exceeds the list size */
			Log_st_event(Engineering, ST_E_USRDEF_LIST_EXCEEDS_SIZE,
					st_cmd_buf[cmd_buf.index_in].id,
					st_cmd_buf[cmd_buf.index_in].xy_info,
					st_cmd_buf[cmd_buf.index_in].data, length, 0, 0, 0, 0, 0,
					0);
		}

		/* Copy the User-defined list */

		for (i = 0; i < st_cmd_buf[cmd_buf.index_in].data; i++) {
			st_cmd_buf[cmd_buf.index_in].usrdef_test_id[i] =
					cmd->usrdef_test_id[i];
		}

		st_cmd_buf[cmd_buf.index_in].usrdef_test_id[i] = ST_NULL;

	}

	/* Save the index_out, in case the PTU task is pre-empted */
	cmd_buf_index_out = cmd_buf.index_out;

	/* Update the index for next write and Wrap around if required */
	cmd_buf.index_in++;
	cmd_buf.index_in %= ST_CMD_BUFFER_SIZE;

	if (cmd_buf.index_in == cmd_buf_index_out) {
		/* Keeping stg.cmd_buf.index_in == stg.cmd_buf.index_out purges the
		 existing commands */

		/* Log event - PTU Command Buffer Full */
		Log_st_event(Engineering, ST_E_COMMAND_BUF_FULL, cmd->id, cmd->xy_info,
				cmd->data, cmd_buf.index_in, cmd_buf_index_out, 0, 0, 0, 0, 0);

		/* Abort Self-test */
		//DAS setSTAbortTestFlag(ST_ABORT_CMD_BUF_FULL);
	}

	ProcessPtuCommand(st_cmd_buf[cmd_buf.index_out].id, st_cmd_buf[cmd_buf.index_out].data);


    cmd_buf.index_out++;
    cmd_buf.index_out %= ST_CMD_BUFFER_SIZE;

}

UINT_8 testExecute;
void ProcessPtuCommand(UINT_8 commandId, UINT16 commandData) {
    //#[ operation ProcessPtuCommand()
    UINT_16 i;
    UINT_16 tempFlag;
    UINT_16 listComplete;

    printf("ST: Write_st_cmd_buf(): id = %d : data = %d\n",commandId, commandData);

    switch (commandId)
    {
        case ST_CMD_UPDT_MODE:  //Update Self-test User mode
            //itsASelfTestMgr->setUser_mode(command.data);
            //printf("Mode Update\n");
            break;

        case ST_CMD_SEL_LIST: //Select predetermined list
            switch (commandData)
            {
                case PTU_LIST_LOGIC:
                    //DAS itsASelfTestMgr->setMode(ST_MODE_LTEST);
                    printf("Logic List Selected\n");
                    break;

                case PTU_LIST_INTERACTIVE:
                    //DASitsASelfTestMgr->setMode(ST_MODE_ITEST);
                    printf("Interactive List Selected\n");
                    break;

                case PTU_LIST_POWER:
                    //itsASelfTestMgr->setMode(ST_MODE_PTEST);
                    printf("Power List Selected\n");
                    break;

                default: //PTU LIst not supported
                    printf("Unknown List\n");
                    //itsStEventLogger->LogPtuEvents(ST_E_LIST_NOT_SUPPORTED, aCmd->id, aCmd->xy_info, aCmd->data, 0, 0, 0 );
                    break;
            }
            break;

        case ST_CMD_EXECUTE_LIST:  //Execute Self-test
            //DAS itsASelfTestMgr->opStEnter();
            testExecute = TRUE;
            printf("Execute Command\n");
            break;

        case ST_CMD_ABORT_SEQ: // Abort sequence
        case ST_CMD_ABORT_SES: // Abort session
            //DAS tempFlag = itsASelfTestMgr->getAbortTestFlag();
            //DAS itsASelfTestMgr->setAbortTestFlag(tempFlag |= ST_ABORT_SES_PTU);
            //DAS itsASelfTestMgr->opStAbortSes();
            printf("Abort %d\n",commandId);
            break;

        case ST_CMD_ACK_MSG:
            break;

        // the operator acknowledges to continue the interactive test
        case ST_CMD_OPRTR_ACK:
            //DAS itsASelfTestMgr->Continue();
            //printf("Operator Ack\n");
            break;

        case ST_CMD_UPDT_LOOP_CNT:  // Update the Self-test loop count
            //DAS itsASelfTestMgr->setMaxLoopCount(command.data);
            printf("Loop: %d\n",commandData);
            break;

        case ST_CMD_ENTER_ST:  //enter self test
            resp_buf.index_in = 0;
            resp_buf.index_out = 0;
            Respond_special(ST_SPECIAL_ENTER);
            break;

        case ST_CMD_EXIT_ST: // Exit Self-test
            Respond_special(ST_SPECIAL_EXIT);
            break;

        case ST_CMD_UPDT_LIST: //update user defined test list
            //DAS itsASelfTestMgr->setMode(ST_MODE_USRDEF_TEST);
            //DAS itsASelfTestMgr->ClearUserDefList();
            printf("User Def List\n");

            for(i = 0; i < ST_MAX_USRDEF_LIST_SIZE; i++)
            {
                //DAS listComplete = itsASelfTestMgr->AddToUserDefList(st_cmd_buf[cmd_buf.index_out].usrdef_test_id[i]);

                if (listComplete == (UINT_16)FALSE)
                {
                    break;
                }
            }
            break;

        default:  // PTU Command Invalid
            //itsStEventLogger->LogPtuEvents(ST_E_INVALID_USRDEF_LIST, aCmd->id, aCmd->xy_info, aCmd->data, 0, 0, 0 );
            break;
     }



    //#]
}



/*****************************************************************************
 *
 * .b
 * Procedure Name: Read_st_resp_buf
 *
 * Abstract:
 *   PTU task uses this function to read the Self-test response from the
 *   local self-test response buffer.
 *
 * INPUTS:
 *   Globals:
 *     None
 *
 *   Procedure Parameters:
 *     UINT_8 *buffer, Pointer to the Response
 *     UINT_16 *length, Pointer to the Response Data Length
 *
 * OUTPUTS:
 *   Globals:
 *     None
 *
 *   Returned Values:
 *     UINT_16
 *     TRUE:  A new Self-test response is available.
 *     FALSE: No new Self-test response is available.
 *
 * Functional Description:
 *   PTU task uses this function to read the Self-test response from the local
 *   self-test response buffer. This response buffer acts as a shared memory
 *   between the PTU and the Self-test task.
 *
 *   If there is a new Self-test response available, then the next-in-the-line
 *   response is copied into the buffer for PTU task to send to the PTU.
 *
 *   A TRUE value is returned if a new Self-test response is available.
 *   A FALSE value is returned if no new Self-test response is available.
 *
 * .b
 *
 * History:
 *   Jun 8 2001 Vipin Sapra @ Bombardier
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
UINT_16 Read_st_resp_buf(UINT_8 *buffer, UINT_16 *length) {
	struct st_resp_str *resp;
	UINT_16 ret_val = FALSE;
	UINT_16 i;

	resp = (struct st_resp_str *) buffer;

	/* Read the Self-test response, if present in queue */
	if (resp_buf.index_out != resp_buf.index_in) {
		/* Read the response */
		resp->Valid = st_resp_buf[resp_buf.index_out].Valid;
		resp->msg_mode = st_resp_buf[resp_buf.index_out].msg_mode;
		resp->set_info = st_resp_buf[resp_buf.index_out].set_info;
		resp->test_id = st_resp_buf[resp_buf.index_out].test_id;
		resp->flags = st_resp_buf[resp_buf.index_out].flags;

		if (resp->msg_mode == ST_MSG_MODE_COUNTER) { /* Result Type 2 */
			resp->result.type2.version =
					st_resp_buf[resp_buf.index_out].result.type2.version;
			resp->result.type2.test_result =
					st_resp_buf[resp_buf.index_out].result.type2.test_result;
			resp->result.type2.loop_count =
					st_resp_buf[resp_buf.index_out].result.type2.loop_count;
			resp->result.type2.num_of_failures =
					st_resp_buf[resp_buf.index_out].result.type2.num_of_failures;

				/* Debug */
				Log_st_event(Engineering, ST_E_READ_ST_RESP_BUF, resp->msg_mode,
						resp->set_info, resp->test_id,
						resp->result.type2.version,
						resp->result.type2.test_result,
						resp->result.type2.loop_count,
						resp->result.type2.num_of_failures, resp->flags,
						resp_buf.index_in, resp_buf.index_out);
		} else { /* Result Type 1 */
			resp->result.type1.version =
					st_resp_buf[resp_buf.index_out].result.type1.version;
			resp->result.type1.test_case =
					st_resp_buf[resp_buf.index_out].result.type1.test_case;
			resp->result.type1.num_of_vars =
					st_resp_buf[resp_buf.index_out].result.type1.num_of_vars;
			resp->result.type1.test_result =
					st_resp_buf[resp_buf.index_out].result.type1.test_result;

			/* Copy supporting Response data variables */
			if (resp->result.type1.num_of_vars) {
				for (i = 0; i < resp->result.type1.num_of_vars; i++) {
					resp->st_resp_vars[i].var =
							st_resp_buf[resp_buf.index_out].st_resp_vars[i].var;
					resp->st_resp_vars[i].type =
							st_resp_buf[resp_buf.index_out].st_resp_vars[i].type;
					resp->st_resp_vars[i].tag =
							st_resp_buf[resp_buf.index_out].st_resp_vars[i].tag;
				}
			}

				/* Debug */
				Log_st_event(Engineering, ST_E_READ_ST_RESP_BUF, resp->msg_mode,
						resp->set_info, resp->test_id,
						resp->result.type1.version,
						resp->result.type1.test_case,
						resp->result.type1.num_of_vars,
						resp->result.type1.test_result, resp->flags,
						resp_buf.index_in, resp_buf.index_out);
		}

		/* Update the index for next read and Wrap around if required */
		resp_buf.index_out++;
		resp_buf.index_out %= ST_RESP_BUFFER_SIZE;

		/* Get the response length */
		*length = (UINT_16) sizeof(struct st_resp_str);

		ret_val = TRUE;
	}

	return ret_val;
}

/*****************************************************************************
 *
 * .b
 * Procedure Name: Write_st_resp_buf
 *
 * Abstract:
 *   This function writes the Self-test response into the local buffer for the
 *   PTU task to read.
 *
 * INPUTS:
 *   Globals:
 *     None
 *
 *   Procedure Parameters:
 *     UINT_8 *buffer, Pointer to the Response
 *
 * OUTPUTS:
 *   Globals:
 *     None
 *
 *   Returned Values:
 *     None
 *
 * Functional Description:
 *   This function writes the Self-test response into the local circular response
 *   buffer of size ST_RESP_BUFFER_SIZE for the PTU task to read. This response
 *   buffer acts as a shared memory between the PTU and the Self-test task.
 *   The Self-test Task writes the response.
 *
 *   resp_buf.index_in != resp_buf.index_out indicates response is available.
 *   resp_buf.index_in == resp_buf.index_out indicates no new responses
 *   or buffer full.
 *
 *   While writing, the Self-test task takes care that it does not overwrite the
 *   response, which is not read by the PTU task.
 *   In case the response buffer is full, the event is logged and all the
 *   existing responses are purged. The current Self-test session is aborted.
 *
 *   Note that the PTU and Self-test task time are different
 *
 * .b
 *
 * History:
 *   Jun 8 2001 Vipin Sapra @ Bombardier
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
void Write_st_resp_buf(UINT_8 *buffer) {
	struct st_resp_str *resp;
	UINT_16 i, resp_buf_index_out;

	resp = (struct st_resp_str *) buffer;

	/* Write the response */
	st_resp_buf[resp_buf.index_in].Valid = resp->Valid;
	st_resp_buf[resp_buf.index_in].msg_mode = resp->msg_mode;
	st_resp_buf[resp_buf.index_in].set_info = resp->set_info;
	st_resp_buf[resp_buf.index_in].test_id = resp->test_id;
	st_resp_buf[resp_buf.index_in].flags = resp->flags;

	if (resp->msg_mode == ST_MSG_MODE_COUNTER) { /* Result Type 2 */
		st_resp_buf[resp_buf.index_in].result.type2.version =
				resp->result.type2.version;
		st_resp_buf[resp_buf.index_in].result.type2.test_result =
				resp->result.type2.test_result;
		st_resp_buf[resp_buf.index_in].result.type2.loop_count =
				resp->result.type2.loop_count;
		st_resp_buf[resp_buf.index_in].result.type2.num_of_failures =
				resp->result.type2.num_of_failures;
	} else { /* Result Type 1 */
		st_resp_buf[resp_buf.index_in].result.type1.version =
				resp->result.type1.version;
		st_resp_buf[resp_buf.index_in].result.type1.test_case =
				resp->result.type1.test_case;
		st_resp_buf[resp_buf.index_in].result.type1.num_of_vars =
				resp->result.type1.num_of_vars;
		st_resp_buf[resp_buf.index_in].result.type1.test_result =
				resp->result.type1.test_result;

		if (resp->result.type1.num_of_vars) {
			/* Copy supporting Response data variables */
			for (i = 0; i < resp->result.type1.num_of_vars; i++) {
				st_resp_buf[resp_buf.index_in].st_resp_vars[i].var =
						resp->st_resp_vars[i].var;
				st_resp_buf[resp_buf.index_in].st_resp_vars[i].type =
						resp->st_resp_vars[i].type;
				st_resp_buf[resp_buf.index_in].st_resp_vars[i].tag =
						resp->st_resp_vars[i].tag;
			}
		}
	}

	/* Save the index_out, in case the PTU task is pre-empted */
	resp_buf_index_out = resp_buf.index_out;

	/* Update the index for next write and Wrap around if required */
	resp_buf.index_in++;
	resp_buf.index_in %= ST_RESP_BUFFER_SIZE;

	if (resp_buf.index_in == resp_buf_index_out) {
		/* Keeping stg.resp_buf.index_in == stg.resp_buf.index_out purges the
		 existing responses */

		/* Log event - Self-test Response Buffer Full */
		if (resp->msg_mode == ST_MSG_MODE_COUNTER) { /* Result Type 2 */
			Log_st_event(Engineering, ST_E_RESPONSE_BUF_FULL, resp->Valid,
					resp->msg_mode, resp->set_info, resp->test_id,
					resp->result.type2.version, resp->result.type2.test_result,
					resp->result.type2.loop_count,
					resp->result.type2.num_of_failures, resp->flags, 0);
		} else {
			Log_st_event(Engineering, ST_E_RESPONSE_BUF_FULL, resp->Valid,
					resp->msg_mode, resp->set_info, resp->test_id,
					resp->result.type1.version, resp->result.type1.test_case,
					resp->result.type1.num_of_vars,
					resp->result.type1.test_result, resp->flags, 0);
		}

		/* Abort Self-test */
		//DAS setSTAbortTestFlag(ST_ABORT_RESP_BUF_FULL);
	}

		/* Debug */
		if (resp->msg_mode == ST_MSG_MODE_COUNTER) { /* Result Type 2 */
			Log_st_event(Engineering, ST_E_WRITE_ST_RESP_BUF, resp->msg_mode,
					resp->set_info, resp->test_id, resp->result.type2.version,
					resp->result.type2.test_result,
					resp->result.type2.loop_count,
					resp->result.type2.num_of_failures, resp->flags,
					resp_buf.index_in, resp_buf_index_out);
		} else {
			Log_st_event(Engineering, ST_E_WRITE_ST_RESP_BUF, resp->msg_mode,
					resp->set_info, resp->test_id, resp->result.type1.version,
					resp->result.type1.test_case,
					resp->result.type1.num_of_vars,
					resp->result.type1.test_result, resp->flags,
					resp_buf.index_in, resp_buf_index_out);
		}
}

/*****************************************************************************
 *
 * .b
 * Procedure Name: Respond_brief
 *
 * Abstract:
 *   This function assembles a Brief Response for the PTU and writes into the
 *   Self-test response buffer.
 *
 * INPUTS:
 *   Globals:
 *     None
 *
 *   Procedure Parameters:
 *     UINT_16 index, Index value pointing to the addressed test
 *
 * OUTPUTS:
 *   Globals:
 *     None
 *
 *   Returned Values:
 *     None
 *
 * Functional Description:
 *   This function assembles a Brief Response for the PTU and writes into the
 *   Self-test response buffer.
 *
 *   This is used if response message mode is ST_MSG_MODE_BRIEF
 *
 * .b
 *
 * History:
 *   Jun 8 2001 Vipin Sapra @ Bombardier
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
void Respond_brief(UINT_16 test_id, UINT_16 composite_result) {
	struct st_resp_str resp;

	/* Do not send any response if Internal Requested Self-test is in progress */
//  if (getSTMode() != ST_MODE_REQ_TEST)
//  {
	/* Assemble and write the Self-test response */
	resp.Valid = 0;
	resp.msg_mode = ST_MSG_MODE_BRIEF;
	resp.set_info = 0;
	resp.test_id = test_id;
	resp.result.type1.version = 0;
	resp.result.type1.test_case = 0;
	resp.result.type1.num_of_vars = 0;
	resp.result.type1.test_result = composite_result;
	resp.flags = 0;
	Write_st_resp_buf((UINT_8 *) &resp);
//  }
}

/*****************************************************************************
 *
 * .b
 * Procedure Name: Respond_detailed
 *
 * Abstract:
 *   This function assembles a Detailed Response for the PTU and writes into the
 *   Self-test response buffer.
 *
 * INPUTS:
 *   Globals:
 *     None
 *
 *   Procedure Parameters:
 *     UINT_16 index, Index value pointing to the addressed test
 *
 * OUTPUTS:
 *   Globals:
 *     None
 *
 *   Returned Values:
 *     None
 *
 * Functional Description:
 *   This function assembles a Detailed Response for the PTU and writes into the
 *   Self-test response buffer.
 *
 *   This is used if response message mode is ST_MSG_MODE_DETAILED
 *
 * .b
 *
 * History:
 *   Jun 8 2001 Vipin Sapra @ Bombardier
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
void Respond_detailed(UINT_16 test_id, UINT_16 composite_result) {
	struct st_resp_str resp;

	/* Do not send any response if Internal Requested Self-test is in progress */
//  if (getSTMode() != ST_MODE_REQ_TEST)
//  {
	/* Assemble and write the Self-test response */
	resp.Valid = 0;
	resp.msg_mode = ST_MSG_MODE_DETAILED;
	resp.set_info = 0;
	resp.test_id = test_id;
	resp.result.type1.version = 0;
	resp.result.type1.test_case = 0;
	resp.result.type1.num_of_vars = 0;
	resp.result.type1.test_result = composite_result;
	resp.flags = 0;
	Write_st_resp_buf((UINT_8 *) &resp);
//  }
}

/*****************************************************************************
 *
 * .b
 * Procedure Name: Respond_counter
 *
 * Abstract:
 *   This function assembles a Counter Response for the PTU and writes into the
 *   Self-test response buffer.
 *
 * INPUTS:
 *   Globals:
 *     None
 *
 *   Procedure Parameters:
 *     UINT_16 index, Index value pointing to the addressed test
 *
 * OUTPUTS:
 *   Globals:
 *     None
 *
 *   Returned Values:
 *     None
 *
 * Functional Description:
 *   This function assembles a Counter Response for the PTU and writes into the
 *   Self-test response buffer.
 *
 *   This is used if response message mode is ST_MSG_MODE_COUNTER
 *
 * .b
 *
 * History:
 *   Jun 8 2001 Vipin Sapra @ Bombardier
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
void Respond_counter(UINT_16 test_id, UINT_16 composite_result) {
	struct st_resp_str resp;

	/* Do not send any response if Internal Requested Self-test is in progress */
//  if (getSTMode() != ST_MODE_REQ_TEST)
//  {
	/* Assemble and write the Self-test response */
	resp.Valid = 0;
	resp.msg_mode = ST_MSG_MODE_COUNTER;
	resp.set_info = 0;
	resp.test_id = test_id;
	resp.result.type2.version = 0;
	resp.result.type2.test_result = composite_result;
	resp.result.type2.loop_count = 0;
	resp.result.type2.num_of_failures = 0;
	resp.flags = 0;
	Write_st_resp_buf((UINT_8 *) &resp);
//  }
}

/*****************************************************************************
 *
 * .b
 * Procedure Name: Respond_special
 *
 * Abstract:
 *   This function assembles a Special Response for the PTU and writes into the
 *   Self-test response buffer.
 *
 * INPUTS:
 *   Globals:
 *     None
 *
 *   Procedure Parameters:
 *     UINT_16 message_id, The Special Message ID being sent
 *
 * OUTPUTS:
 *   Globals:
 *     None
 *
 *   Returned Values:
 *     None
 *
 * Functional Description:
 *   This function assembles a Special Response for the PTU and writes into the
 *   Self-test response buffer.
 *
 *   This is used to send a special message with message mode as
 *   ST_MSG_MODE_SPECIAL. The possible messages are:
 *
 *   Enter Self-test
 *   Do not Enter Self-test
 *   Self-test Completed
 *   Self-test Aborted
 *   Exit Self-test
 *   Internally Requested Self-test Completed
 *
 * .b
 *
 * History:
 *   Jun 8 2001 Vipin Sapra @ Bombardier
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
void Respond_special(UINT_16 message_id) {
	struct st_resp_str resp;

	/* Do not send any response if Internal Requested Self-test is in progress */
//  if (getSTMode() != ST_MODE_REQ_TEST)
//  {
	/* Assemble and write the Self-test response */
	resp.Valid = 0;
	resp.msg_mode = ST_MSG_MODE_SPECIAL;
	resp.set_info = 0;
	resp.test_id = message_id;
	resp.result.type1.version = 0;
	resp.result.type1.test_case = 1;
	resp.result.type1.num_of_vars = 0;
	resp.result.type1.test_result = ST_GO;
	resp.flags = 0;
	Write_st_resp_buf((UINT_8 *) &resp);
//  }
}

/*****************************************************************************
 *
 * .b
 * Procedure Name: Respond_interactive
 *
 * Abstract:
 *   This function assembles a Interactive Response for the PTU and writes into
 *   the Self-test response buffer.
 *
 * INPUTS:
 *   Globals:
 *     None
 *
 *   Procedure Parameters:
 *     UINT_16 index, Index value pointing to the addressed test
 *     const INT_8 *fmt, Pointer to the data format string
 *     UINT_32 data1 ... data10, Possibly 10 data items
 *
 * OUTPUTS:
 *   Globals:
 *     None
 *
 *   Returned Values:
 *     None
 *
 * Functional Description:
 *   This function assembles a Interactive Response for the PTU and writes into
 *   the Self-test response buffer.
 *
 *   This is used if response message mode is ST_MSG_MODE_INTERACTIVE
 *
 *   10 data items are supported with the format describing them. The data items
 *   are written along with the main response into the buffer.
 *
 * .b
 *
 * History:
 *   Jun 8 2001 Vipin Sapra @ Bombardier
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
void Respond_interactive(UINT_16 test_id, UINT_16 composite_result,
		const INT_8 *fmt, UINT_32 data1, UINT_32 data2, UINT_32 data3,
		UINT_32 data4, UINT_32 data5, UINT_32 data6, UINT_32 data7,
		UINT_32 data8, UINT_32 data9, UINT_32 data10) {
	struct st_resp_str resp;
	INT_8 tag[10];
	UINT_16 state = 0;
	UINT_16 quit = FALSE;
	UINT_16 tag_index = 0;
	UINT_16 data_index = 0;
	/* Match array size with the number of maximum parameters supported */
	UINT_32 data_item[10];

	//MySleep(400);

	/* Do not send any response if Internal Requested Self-test is in progress */
	/* PTU cannot handle a fast response rate - Slow it down */
	if (resp_buf.index_out == resp_buf.index_in) {
//    if (getSTMode() != ST_MODE_REQ_TEST)
//    {
		/* Move it into an array - Easier to work with */
		/* Match array size with the number of maximum parameters supported */
		data_item[0] = data1;
		data_item[1] = data2;
		data_item[2] = data3;
		data_item[3] = data4;
		data_item[4] = data5;
		data_item[5] = data6;
		data_item[6] = data7;
		data_item[7] = data8;
		data_item[8] = data9;
		data_item[9] = data10;

		/* Assemble and write the Self-test response */
		resp.Valid = 0;
		resp.msg_mode = ST_MSG_MODE_INTERACTIVE;
		resp.set_info = 0;
		resp.test_id = test_id;
		resp.result.type1.version = 0;
		resp.result.type1.test_case = 1;
		resp.result.type1.num_of_vars = 0;
		resp.result.type1.test_result = composite_result;
		resp.flags = 0;

		while (!quit) {
			switch (state) {
			case 0: /* Looking for '%' */
				switch (*fmt) {
				case '\0': /* Null */
					quit = TRUE;
					break;

				case '%': /* Delimiter */
					state++;
					break;

				default:
					break;
				}
				break;

			case 1: /* Found '%' - Get data according to the type */
				switch (*fmt) {
				case '\0': /* Null */
					quit = TRUE;
					break;

				case 'c': /* 8 bit data */
				case 'J': /* 8 bit data string */
				case 'd': /* 16 bit data */
				case 'x': /* 16 bit hex data */
				case 'l': /* 32 bit data */
					resp.st_resp_vars[resp.result.type1.num_of_vars].var =
							data_item[data_index];
					data_index++;
					resp.st_resp_vars[resp.result.type1.num_of_vars].type = 0;
					state++;
					break;

				default: /* Unsupported data */
					state = 0;
					break;
				}
				break;

			case 2: /* Get tag */
				switch (*fmt) {
				case '\0': /* Null */
					quit = TRUE;
				case ' ': /* Delimiter */
					tag[tag_index] = '\0';
					resp.st_resp_vars[resp.result.type1.num_of_vars].tag =
							(UINT_8) atoi(tag);
					tag_index = 0;
					state = 0;
					resp.result.type1.num_of_vars++;
					if (resp.result.type1.num_of_vars >= ST_NUM_OF_RESP_VARS) { /* Maximum ST_NUM_OF_RESP_VARS, No more */
						resp.result.type1.num_of_vars = ST_NUM_OF_RESP_VARS;
						quit = TRUE;
					}
					break;

				default:
					tag[tag_index] = *fmt;
					tag_index++;
					/* if (tag_index >= 10) Error: Increase tag array size */
					break;
				}
				break;

			default:
				state = 0;
				break;
			}

			fmt++; /* Get the next char of the format string */
		}
		Write_st_resp_buf((UINT_8 *) &resp);
		//}
	}
}

/*****************************************************************************
 *
 * .b
 * Procedure Name: Log_st_event
 *
 * Abstract:
 *   This function logs the event in the PTU event log.
 *
 * INPUTS:
 *   Globals:
 *     None
 *
 *   Procedure Parameters:
 *     UINT_16 log, Specifies the log type where the event is logged
 *     UINT_16 event, The event being logged
 *     UINT_32 data1 ... data10, Possible 10 supporting data items logged along
 *
 * OUTPUTS:
 *   Globals:
 *     None
 *
 *   Returned Values:
 *     None
 *
 * Functional Description:
 *   This function logs the event in the specified PTU event log.
 *
 * .b
 *
 * History:
 *   Mar 5 2001 Vipin Sapra @ ADtranz, PGH
 *     Created.
 *
 * Revision:
 *
 *****************************************************************************/
void Log_st_event(UINT_16 log, UINT_16 event, UINT_32 data1, UINT_32 data2,
		UINT_32 data3, UINT_32 data4, UINT_32 data5, UINT_32 data6,
		UINT_32 data7, UINT_32 data8, UINT_32 data9, UINT_32 data10) {
#if 0 
	UINT_16 event_log=log;
	UINT_16 event_data_size=0;

	/* Pointer to the event data prolog */
	struct prolog_str
	{
		FAULTPACKETPROLOG
	}*prolog;

	/* Union of the event data pack structures */
	union event_d
	{
		struct e_semaphore_invalid_str e_semaphore_invalid;
		struct e_list_not_supported_str e_list_not_supported;
		struct e_command_invalid_str e_command_invalid;
		struct e_command_buf_full_str e_command_buf_full;
		struct e_response_buf_full1_str e_response_buf_full1;
		struct e_response_buf_full2_str e_response_buf_full2;
		struct e_execution_invalid_str e_execution_invalid;
		struct e_session_abort_str e_session_abort;
		struct e_test_unknown_str e_test_unknown;
		struct e_abort_initial_str e_abort_initial;
		struct e_restore_fail_str e_restore_fail;
		struct e_usrdef_list_exceeds_size_str e_usrdef_list_exceeds_size;
		struct e_usrdef_list_length_mismatch_str e_usrdef_list_length_mismatch;
		struct e_invalid_usrdef_list_str e_invalid_usrdef_list;
		struct e_null_str e_null;
		struct e_analon_bist_fail_str e_analon_bist_fail;
		struct e_req_test_fail_str e_req_test_fail;
		struct e_ptest_fail_str e_ptest_fail;
		struct e_debug_command_buf_str e_debug_command_buf;
		struct e_debug_response_buf1_str e_debug_response_buf1;
		struct e_debug_response_buf2_str e_debug_response_buf2;
		struct e_debug_generic_str e_debug_generic;
		struct e_unknown_str e_unknown;
	}event_data;

	prolog = (struct prolog_str *) &event_data;
	prolog->loggerid = ST_FAULT;

	/* Assemble the Event and its supporting data */
	switch (event)
	{
		case ST_E_SEMAPHORE_INVALID: /* Self-test Task Semaphore Invalid */
		event_data.e_semaphore_invalid.task_to_ctr = data1;
		event_data.e_semaphore_invalid.faultid = E_SEMAPHORE_INVALID;
		event_data_size = sizeof(struct e_semaphore_invalid_str);
		break;

		case ST_E_LIST_NOT_SUPPORTED: /* PTU List Not Supported */
		event_data.e_list_not_supported.cmnd_id = data1;
		event_data.e_list_not_supported.xy_info = data2;
		event_data.e_list_not_supported.data = data3;
		event_data.e_list_not_supported.faultid = E_LIST_NOT_SUPPORTED;
		event_data_size = sizeof(struct e_list_not_supported_str);
		break;

		case ST_E_COMMAND_INVALID: /* PTU Command Invalid */
		event_data.e_command_invalid.cmnd_id = data1;
		event_data.e_command_invalid.xy_info = data2;
		event_data.e_command_invalid.data = data3;
		event_data.e_command_invalid.faultid = E_COMMAND_INVALID;
		event_data_size = sizeof(struct e_command_invalid_str);
		break;

		case ST_E_COMMAND_BUF_FULL: /* PTU Command Buffer Full */
		event_data.e_command_buf_full.cmnd_id = data1;
		event_data.e_command_buf_full.xy_info = data2;
		event_data.e_command_buf_full.data = data3;
		event_data.e_command_buf_full.index_in = data4;
		event_data.e_command_buf_full.index_out = data5;
		event_data.e_command_buf_full.faultid = E_COMMAND_BUF_FULL;
		event_data_size = sizeof(struct e_command_buf_full_str);
		break;

		case ST_E_RESPONSE_BUF_FULL: /* Self-test Response Buffer Full */
		event_data.e_response_buf_full1.Valid =
		event_data.e_response_buf_full2.Valid = data1;
		event_data.e_response_buf_full1.msg_mode =
		event_data.e_response_buf_full2.msg_mode = data2;
		event_data.e_response_buf_full1.set_info =
		event_data.e_response_buf_full2.set_info = data3;
		event_data.e_response_buf_full1.resp_id =
		event_data.e_response_buf_full2.resp_id = data4;

		if (event_data.e_response_buf_full1.msg_mode == ST_MSG_MODE_COUNTER)
		{ /* Result Type 2 */
			event_data.e_response_buf_full2.version = data5;
			event_data.e_response_buf_full2.test_result = data6;
			event_data.e_response_buf_full2.loop_count = data7;
			event_data.e_response_buf_full2.num_of_failures = data8;
			event_data.e_response_buf_full2.faultid = E_RESPONSE_BUF_FULL2;
			event_data_size = sizeof(struct e_response_buf_full2_str);
		}
		else
		{ /* Result Type 1 */
			event_data.e_response_buf_full1.version = data5;
			event_data.e_response_buf_full1.test_case = data6;
			event_data.e_response_buf_full1.num_of_vars = data7;
			event_data.e_response_buf_full1.test_result = data8;
			event_data.e_response_buf_full1.faultid = E_RESPONSE_BUF_FULL1;
			event_data_size = sizeof(struct e_response_buf_full1_str);
		}
		event_data.e_response_buf_full1.flags =
		event_data.e_response_buf_full2.flags = data9;
		break;

		case ST_E_EXECUTION_INVALID: /* Execution Request Invalid */
		event_data.e_execution_invalid.execute_test_flag = data1;
		event_data.e_execution_invalid.faultid = E_EXECUTION_INVALID;
		event_data_size = sizeof(struct e_execution_invalid_str);
		break;

		case ST_E_SESSION_ABORT: /* Session Aborted due to Abort Flag */
		event_data.e_session_abort.abort_test_flag = data1;
		event_data.e_session_abort.zero_speed_flag = data2;
		event_data.e_session_abort.mode_request_safe_status = data3;
		event_data.e_session_abort.rate_request = data4;
		event_data.e_session_abort.mot_st_mode = data5;
		event_data.e_session_abort.tach_st_mode = data6;
		event_data.e_session_abort.vpm_st_mode = data7;
		event_data.e_session_abort.ici_st_mode = data8;
		event_data.e_session_abort.analon_st_mode = data9;
		event_data.e_session_abort.nm_st_mode = data10;
		event_data.e_session_abort.faultid = E_SESSION_ABORT;
		event_data_size = sizeof(struct e_session_abort_str);
		break;

		case ST_E_TEST_UNKNOWN: /* Test Unknown */
		event_data.e_test_unknown.unknown_test_id = data1;
		event_data.e_test_unknown.faultid = E_TEST_UNKNOWN;
		event_data_size = sizeof(struct e_test_unknown_str);
		break;

		case ST_E_ABORT_INITIAL: /* Could not Enter Self-Test mode */
		event_data.e_abort_initial.zero_speed_flag = data1;
		event_data.e_abort_initial.mode_request_safe_status = data2;
		event_data.e_abort_initial.rate_request = data3;
		event_data.e_abort_initial.mot_st_mode = data4;
		event_data.e_abort_initial.tach_st_mode = data5;
		event_data.e_abort_initial.vpm_st_mode = data6;
		event_data.e_abort_initial.ici_st_mode = data7;
		event_data.e_abort_initial.analon_st_mode = data8;
		event_data.e_abort_initial.nm_st_mode = data9;
		event_data.e_abort_initial.faultid = E_ABORT_INITIAL;
		event_data_size = sizeof(struct e_abort_initial_str);
		break;

		case ST_E_RESTORE_FAIL: /* Could not Restore Normal mode */
		event_data.e_restore_fail.restore_item_failed = data1;
		event_data.e_restore_fail.mot_st_mode = data2;
		event_data.e_restore_fail.tach_st_mode = data3;
		event_data.e_restore_fail.vpm_st_mode = data4;
		event_data.e_restore_fail.ici_st_mode = data5;
		event_data.e_restore_fail.analon_st_mode = data6;
		event_data.e_restore_fail.nm_st_mode = data7;
		event_data.e_restore_fail.faultid = E_RESTORE_FAIL;
		event_data_size = sizeof(struct e_restore_fail_str);
		break;

		/* Number of User defined tests exceeds the list size */
		case ST_E_USRDEF_LIST_EXCEEDS_SIZE:
		event_data.e_usrdef_list_exceeds_size.cmnd_id = data1;
		event_data.e_usrdef_list_exceeds_size.xy_info = data2;
		event_data.e_usrdef_list_exceeds_size.data = data3;
		event_data.e_usrdef_list_exceeds_size.length = data4;
		event_data.e_usrdef_list_exceeds_size.faultid = E_USRDEF_LIST_EXCEEDS_SIZE;
		event_data_size = sizeof(struct e_usrdef_list_exceeds_size_str);
		break;

		/* User defined Test-list Length Mismatch */
		case ST_E_USRDEF_LIST_LENGTH_MISMATCH:
		event_data.e_usrdef_list_length_mismatch.cmnd_id = data1;
		event_data.e_usrdef_list_length_mismatch.xy_info = data2;
		event_data.e_usrdef_list_length_mismatch.data = data3;
		event_data.e_usrdef_list_length_mismatch.length = data4;
		event_data.e_usrdef_list_length_mismatch.faultid =
		E_USRDEF_LIST_LENGTH_MISMATCH;
		event_data_size = sizeof(struct e_usrdef_list_length_mismatch_str);
		break;

		case ST_E_INVALID_USRDEF_LIST: /* Invalid User defined test list */
		event_data.e_invalid_usrdef_list.cmnd_id = data1;
		event_data.e_invalid_usrdef_list.xy_info = data2;
		event_data.e_invalid_usrdef_list.data = data3;
		event_data.e_invalid_usrdef_list.invalid_test_id = data4;
		event_data.e_invalid_usrdef_list.faultid = E_INVALID_USRDEF_LIST;
		event_data_size = sizeof(struct e_invalid_usrdef_list_str);
		break;

		case ST_E_NULL: /* Test not supported */
		event_data.e_null.test_id = data1;
		event_data.e_null.faultid = E_NULL;
		event_data_size = sizeof(struct e_null_str);
		break;

		case ST_E_ANALON_BIST_FAIL:
		event_data.e_analon_bist_fail.analon_result = data1;
		event_data.e_analon_bist_fail.faultid = E_ANALON_BIST_FAIL;
		event_data_size = sizeof(struct e_analon_bist_fail_str);
		break;

		case ST_E_REQ_TEST_FAIL:
		event_data.e_req_test_fail.failed_test = data1;
		event_data.e_req_test_fail.total_tests = data2;
		event_data.e_req_test_fail.faultid = E_REQ_TEST_FAIL;
		event_data_size = sizeof(struct e_req_test_fail_str);
		break;

		case ST_E_PTEST_FAIL:
		event_data.e_ptest_fail.test_id = data1;
		event_data.e_ptest_fail.item = data2;
		event_data.e_ptest_fail.pct_number = data3;
		event_data.e_ptest_fail.pct_result1 = data4;
		event_data.e_ptest_fail.pct_result2 = data5;
		event_data.e_ptest_fail.pct_result3 = data6;
		event_data.e_ptest_fail.pct_result4 = data7;
		event_data.e_ptest_fail.pct_result5 = data8;
		event_data.e_ptest_fail.pct_result6 = data9;
		event_data.e_ptest_fail.pct_result7 = data10;
		event_data.e_ptest_fail.faultid = E_PTEST_FAIL;
		event_data_size = sizeof(struct e_ptest_fail_str);
		break;

		case ST_E_WRITE_ST_CMD_BUF: /* Write PTU Command Buffer */
		case ST_E_READ_ST_CMD_BUF: /* Read PTU Command Buffer */
		event_data.e_debug_command_buf.cmnd_id = data1;
		event_data.e_debug_command_buf.xy_info = data2;
		event_data.e_debug_command_buf.data = data3;
		event_data.e_debug_command_buf.index_in = data4;
		event_data.e_debug_command_buf.index_out = data5;
		if (event == ST_E_WRITE_ST_CMD_BUF)
		{
			event_data.e_debug_command_buf.faultid = E_WRITE_ST_CMD_BUF;
		}
		else
		{
			event_data.e_debug_command_buf.faultid = E_READ_ST_CMD_BUF;
		}
		event_data_size = sizeof(struct e_debug_command_buf_str);
		break;

		case ST_E_WRITE_ST_RESP_BUF: /* Write Self-test Response Buffer */
		case ST_E_READ_ST_RESP_BUF: /* Read Self-test Response Buffer */
		event_data.e_debug_response_buf1.msg_mode =
		event_data.e_debug_response_buf2.msg_mode = data1;
		event_data.e_debug_response_buf1.set_info =
		event_data.e_debug_response_buf2.set_info = data2;
		event_data.e_debug_response_buf1.resp_id =
		event_data.e_debug_response_buf2.resp_id = data3;
		if (event_data.e_debug_response_buf1.msg_mode == ST_MSG_MODE_COUNTER)
		{ /* Result Type 2 */
			event_data.e_debug_response_buf2.version = data4;
			event_data.e_debug_response_buf2.test_result = data5;
			event_data.e_debug_response_buf2.loop_count = data6;
			event_data.e_debug_response_buf2.num_of_failures = data7;
			if (event == ST_E_WRITE_ST_RESP_BUF)
			{
				event_data.e_debug_response_buf2.faultid = E_WRITE_ST_RESP_BUF2;
			}
			else
			{
				event_data.e_debug_response_buf2.faultid = E_READ_ST_RESP_BUF2;
			}
			event_data_size = sizeof(struct e_debug_response_buf2_str);
		}
		else
		{ /* Result Type 1 */
			event_data.e_debug_response_buf1.version = data4;
			event_data.e_debug_response_buf1.test_case = data5;
			event_data.e_debug_response_buf1.num_of_vars = data6;
			event_data.e_debug_response_buf1.test_result = data7;
			if (event == ST_E_WRITE_ST_RESP_BUF)
			{
				event_data.e_debug_response_buf1.faultid = E_WRITE_ST_RESP_BUF1;
			}
			else
			{
				event_data.e_debug_response_buf1.faultid = E_READ_ST_RESP_BUF1;
			}
			event_data_size = sizeof(struct e_debug_response_buf1_str);
		}
		event_data.e_debug_response_buf1.flags =
		event_data.e_debug_response_buf2.flags = data8;
		event_data.e_debug_response_buf1.index_in =
		event_data.e_debug_response_buf2.index_in = data9;
		event_data.e_debug_response_buf1.index_out =
		event_data.e_debug_response_buf2.index_out = data10;
		break;

		case ST_E_DEBUG_GENERIC:
		event_data.e_debug_generic.debug_data1 = data1;
		event_data.e_debug_generic.debug_data2 = data2;
		event_data.e_debug_generic.debug_data3 = data3;
		event_data.e_debug_generic.debug_data4 = data4;
		event_data.e_debug_generic.debug_data5 = data5;
		event_data.e_debug_generic.debug_data6 = data6;
		event_data.e_debug_generic.debug_data7 = data7;
		event_data.e_debug_generic.debug_data8 = data8;
		event_data.e_debug_generic.debug_data9 = data9;
		event_data.e_debug_generic.debug_data10 = data10;
		event_data.e_debug_generic.faultid = E_DEBUG_GENERIC;
		event_data_size = sizeof(struct e_debug_generic_str);
		break;

		default: /* Unknown event */
		event_data.e_unknown.event = event;
		event_data.e_unknown.faultid = E_UNKNOWN;
		event_data_size = sizeof(struct e_unknown_str);
		break;
	}

	/* Check if PTU has completed initialization */
	LogFault(event_log, (struct minfaultpacket_t *) &event_data,
			(UINT_16) event_data_size);
#endif
}

#ifdef __cplusplus
}
#endif

