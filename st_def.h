/*****************************************************************************
*
* .b
*   Copyright (C) 2001 DaimlerChrysler Rail Systems (North America) Inc.
*   Copyright (C) 2001 Bombardier Transportation (Holdings) USA Inc.
*
* Project:      Pittsburgh LRV Propulsion
*
* File Name:    st_def.h
*
* Subsystem:    VCU: Self Test
*
* Abstract:     This file contains Self-test Task Data definitions.
*
* .b
*
* History:
*   Mar 5 2001 Vipin Sapra @ ADtranz
*     Created.
*
* Revision:
*   23 Jul 2002 JEP @ Bombardier
*     Modified MODE_REQUEST_SAFE to include RQST_PANIC_EBRAKE as a valid
*     operator mode request to conduct self-test.
*   25 Nov 2002 JEP @ Bombardier
*     SCR 59 - Restore Conditions Self-test always fails.
*     Modified RESTORE_CHK_MASK from 0x000f to 0x0007.
*
*****************************************************************************/
#ifndef _ST_DEF_H_
#define _ST_DEF_H_

/* Debug Enable bit positions */
#define ST_CTRL_EXE_SELF_TEST          0x00000001
#define ST_CTRL_EXE_USER_DEF_LIST      0x00000002
#define ST_DEBUG_READ_CMD_BUF          0x00010000
#define ST_DEBUG_WRITE_CMD_BUF         0x00020000
#define ST_DEBUG_READ_RESP_BUF         0x00040000
#define ST_DEBUG_WRITE_RESP_BUF        0x00080000
#define ST_DEBUG_GENERIC               0x00100000
#define ST_DEBUG_ENABLE                0x00000000

/* Count values for various timings */
#define ST_TASK_TIME                   15 /* 15 ms */
#define ST_SEMA_TIMEOUT                20 /* 20 ms */
#define ST_15MS                        (UINT_32)(15 / ST_TASK_TIME)
#define ST_105MS                       (UINT_32)(105 / ST_TASK_TIME)
#define ST_150MS                       (UINT_32)(150 / ST_TASK_TIME)
#define ST_210MS                       (UINT_32)(210 / ST_TASK_TIME)
#define ST_300MS                       (UINT_32)(300 / ST_TASK_TIME)
#define ST_1005MS                      (UINT_32)(1005 / ST_TASK_TIME)
#define ST_1995MS                      (UINT_32)(1995 / ST_TASK_TIME)
#define ST_3000MS                      (UINT_32)(3000 / ST_TASK_TIME)
#define ST_4995MS                      (UINT_32)(4995 / ST_TASK_TIME)
#define ST_7995MS                      (UINT_32)(7995 / ST_TASK_TIME)
#define ST_15SEC                       (UINT_32)(15 * 1000 / ST_TASK_TIME)
#define ST_30SEC                       (UINT_32)(30 * 1000 / ST_TASK_TIME)
#define ST_1MIN                        (UINT_32)(1 * 60 * 1000 / ST_TASK_TIME)
#define ST_5MIN                        (UINT_32)(5 * 60 * 1000 / ST_TASK_TIME)
#define ST_10MIN                       (UINT_32)(10 * 60 * 1000 / ST_TASK_TIME)
#define ST_15MIN                       (UINT_32)(15 * 60 * 1000 / ST_TASK_TIME)
#define ST_30MIN                       (UINT_32)(30 * 60 * 1000 / ST_TASK_TIME)
#define ST_MAX_TASK_TO_COUNT           ST_1005MS
#define ST_DATA_SAMPLE_SIZE            4
#define ST_MAX_SES_TIMEOUT_COUNT       ST_5MIN

/* Self-test Events */
#define ST_E_SEMAPHORE_INVALID             0
#define ST_E_LIST_NOT_SUPPORTED            1
#define ST_E_COMMAND_INVALID               2
#define ST_E_COMMAND_BUF_FULL              3
#define ST_E_RESPONSE_BUF_FULL             4
#define ST_E_EXECUTION_INVALID             5
#define ST_E_SESSION_ABORT                 6
#define ST_E_TEST_UNKNOWN                  7
#define ST_E_ABORT_INITIAL                 8
#define ST_E_RESTORE_FAIL                  9
#define ST_E_USRDEF_LIST_EXCEEDS_SIZE     10
#define ST_E_USRDEF_LIST_LENGTH_MISMATCH  11
#define ST_E_INVALID_USRDEF_LIST          12
#define ST_E_NULL                         13
#define ST_E_ANALON_BIST_FAIL             14
#define ST_E_REQ_TEST_FAIL                15
#define ST_E_PTEST_FAIL                   16
/* Debug Self-test Events */
#define ST_E_DEBUG_GENERIC                17
#define ST_E_WRITE_ST_CMD_BUF             18
#define ST_E_READ_ST_CMD_BUF              19
#define ST_E_WRITE_ST_RESP_BUF            20
#define ST_E_READ_ST_RESP_BUF             21

/* PTU Self-test Commands */
#define ST_CMD_UPDT_MODE               0  /* Update Self-test User mode */
#define ST_CMD_SEL_LIST                1  /* Select predetermined list */
#define ST_CMD_EXECUTE_LIST            2  /* Execute self-test */
#define ST_CMD_UPDT_LIST               3  /* Update user defined list */
#define ST_CMD_ABORT_SEQ               4  /* Abort test sequence */
#define ST_CMD_ABORT_SES               5  /* Abort test session */
#define ST_CMD_ACK_MSG                 6  /* Acknowledge message */
#define ST_CMD_OPRTR_ACK               7  /* Operator acknowledge */
#define ST_CMD_UPDT_LOOP_CNT           8  /* Update loop count */
#define ST_CMD_ENTER_ST                9  /* Enter Self-test */
#define ST_CMD_EXIT_ST                 10 /* Exit Self-test */

/* Self-test Message Modes */
#define ST_MSG_MODE_BRIEF              1
#define ST_MSG_MODE_DETAILED           2
#define ST_MSG_MODE_COUNTER            3
#define ST_MSG_MODE_SPECIAL            4
#define ST_MSG_MODE_INTERACTIVE        5

/* Special Self-test Message ID */
#define ST_SPECIAL_ENTER               1 /* Enter Self-test */
#define ST_SPECIAL_NO_ENTER            2 /* Do not Enter Self-test */
#define ST_SPECIAL_TEST_COMPLETE       3 /* Self-test Completed */
#define ST_SPECIAL_TEST_ABORTED        4 /* Self-test Aborted */
#define ST_SPECIAL_EXIT                5 /* Exit Self-test */
#define ST_SPECIAL_INT_TEST_COMPLETE   6 /* Internally Requested Self-test */
                                         /* Complete */

/* Self-test User Modes */
#define ST_USER_HIGH_LEVEL             0
#define ST_USER_SUPERVISOR             1
#define ST_USER_ENG_MODE_1             2
#define ST_USER_ENG_MODE_2             3
#define ST_USER_ENG_MODE_3             4
#define ST_USER_ENG_MODE_4             5
#define ST_USER_POWER_UP               6
#define ST_USER_PUSH_BUTTON            7
#define ST_USER_NETWORK                8

/* PTU Self-test Lists */
#define PTU_LIST_LOGIC                 0
#define PTU_LIST_INTERACTIVE           1
#define PTU_LIST_POWER                 2

/* Self-test Operational Modes */
#define ST_MODE_REQ_TEST               0
#define ST_MODE_LTEST                  1
#define ST_MODE_ITEST                  2
#define ST_MODE_PTEST                  3
#define ST_MODE_USRDEF_TEST            4

/* Self-test Lists */
#define ST_LIST_REQUEST                0
#define ST_LIST_LOGIC                  1
#define ST_LIST_INTERACTIVE            2
#define ST_LIST_POWER                  3
#define ST_LIST_USRDEF                 4
#define ST_LIST_INITIAL                5
#define ST_LIST_FINAL                  6

/* Self-test Task States */
#define ST_STATE_IDLE                  0
#define ST_STATE_START                 1
#define ST_STATE_RUN                   2
#define ST_STATE_EXIT                  3

/* Self-test Execution Status */
#define ST_STATUS_INACTIVE             0
#define ST_STATUS_ACTIVE               1
#define ST_STATUS_IN_PROGRESS          2

/* Self-test Execution State */
#define ST_NOT_DONE                    1
#define ST_DONE                        2

/* Self-test Result */
#define ST_GO                          1 /* Passed */
#define ST_NOGO                        2 /* Failed */
#define ST_ABORT                       3

/* Test Item on Hold bit */
#define ST_HOLD_ON                     0x8000

/* Execute Test Flag definitions */
#define ST_EXEC_REQ_TEST               0x0001
#define ST_EXEC_PTU_TEST               0x0002

/* Abort Test Flag definitions */
#define ST_ABORT_SAFE_CHK_FAILURE      0x0001
#define ST_ABORT_MOT_FAIL              0x0002
#define ST_ABORT_TACH_FAIL             0x0004
#define ST_ABORT_VM_FAIL               0x0008
#define ST_ABORT_ICI_FAIL              0x0010
#define ST_ABORT_ANALON_FAIL           0x0020
#define ST_ABORT_NM_FAIL               0x0040
/* #define ST_ABORT_TR_FAIL               0x0080 **/
#define ST_ABORT_INITIAL               0x0100
#define ST_ABORT_SES_PTU               0x0200
#define ST_ABORT_EXIT_ST               0x0400
#define ST_ABORT_SES_TIMEOUT           0x0800
#define ST_ABORT_CMD_BUF_FULL          0x1000
#define ST_ABORT_RESP_BUF_FULL         0x2000
#define ST_ABORT_SESSION_MASK          0x3FFF
#define ST_ABORT_BACKGROUND_MASK       0x08FF

/* Case # to handle Common Faults */
#define ST_COMMON_FAULT_HANDLER_CASE   100

/* VCU Requests */
#define ST_VCU_REQ_NORMAL              0
#define ST_VCU_REQ_SELFTEST            1

/* VCU Status */
#define ST_VCU_MODE_NORMAL             0
#define ST_VCU_MODE_SELFTEST           1

/* Analon Requests */
#define ST_ANALON_REQ_NORMAL           0x0000
#define ST_ANALON_REQ_SELFTEST         0x1111
#define ST_ANALON_REQ_REFRESH          0xEFEF
#define ST_ANALON_BIST_EXECUTE         0xEAEA
#define ST_ANALON_BIST_EXIT            0xABAB

/* Analon Status */
#define ST_ANALON_MODE_NORMAL          0x0000
#define ST_ANALON_MODE_SELFTEST        0x1111
#define ST_ANALON_STATUS_WAIT          0x1111
#define ST_ANALON_STATUS_IN_PROGRESS   0xEAEA
#define ST_ANALON_STATUS_COMPLETE      0xCCCC

/* No-motion Requests */
#define ST_NM_REQ_NORMAL               0
#define ST_NM_REQ_SELFTEST             1

/* No-motion Status */
#define ST_NM_MODE_NORMAL              0
#define ST_NM_MODE_SELFTEST            1

/* Self-test DCU Power Circuit Test Parameter Sets */
#define ST_DCU_PCT_PAR_SET_TRAIN       1
#define ST_DCU_PCT_PAR_SET_PRODUCTION  2
#define ST_DCU_PCT_PAR_SET_OTHER       3

/* Test limits */
#define ST_MAX_NO_POWER_VLINE          40
#define ST_MAX_NO_POWER_VLINK          40
#define ST_MIN_PSV_ILINE              -20
#define ST_MAX_PSV_ILINE               20
#define ST_MIN_PSV_IRET               -20
#define ST_MAX_PSV_IRET                20
#define ST_MIN_PSV_VBAT                17
#define ST_MAX_PSV_VBAT                33

/* Evaluate results masks */
#define RESTORE_CHK_MASK               0x0007

extern void Log_st_event (UINT_16, UINT_16, UINT_32, UINT_32,
                   UINT_32, UINT_32, UINT_32, UINT_32,
                   UINT_32, UINT_32, UINT_32, UINT_32);


#endif
