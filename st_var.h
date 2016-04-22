/*****************************************************************************
*
* .b
*   Copyright (C) 2001 Bombardier Transportation (Holdings) USA Inc.
*
* Project:      Pittsburgh LRV Propulsion
*
* File Name:    st_var.h
*
* Subsystem:    VCU: Self Test
*
* Abstract:     This file contains Self-test Task Variable definitions.
*
* .b
*
* History:
*   Sept 24 2001 Vipin Sapra @ Bombardier
*     Created.
*
* Revision:
*  13 Dec 2002 JEP @ Bombardier
*   SCR062 Passive Discharge Power Test always fails
*   Added UINT_16 st_calibration_enable to structure st_global_str to allow
*   self-test to disable DCU calibration during self-test.
*
*  27 July 2009 AET @ Bombardier
*	added __attribute__((packed)) to structure definitions, needed for 
*	PTU communication on the VCUC
*	increased response buffer size
*
*****************************************************************************/
#ifndef _ST_VAR_H_
#define _ST_VAR_H_

#include "myWrapper.h"

/* Structure and Type Declarations */

/* Self-test Null Test */
#define ST_NULL                        0

/* Command / Message Buffer size */
#define ST_CMD_BUFFER_SIZE             (UINT_16)10
#define ST_RESP_BUFFER_SIZE            (UINT_16)20
/* Self-test data array sizes */
#define ST_NUM_OF_TESTS                56
#define ST_MAX_USRDEF_LIST_SIZE        ST_NUM_OF_TESTS
#define ST_NUM_OF_RESP_VARS            16

struct st_cmd_str /* Self-test Command structure */
{
  UINT_8 id;      /* Command ID */
  UINT_8 xy_info; /* A | B | Both trucks */
  UINT_16 data;   /* Command Data */
  UINT_16 usrdef_test_id[ST_MAX_USRDEF_LIST_SIZE]; /* User defined Test IDs */
}__attribute__ ((packed));

struct st_result_type1_str {
  UINT_8  version;
  UINT_8  test_case;
  UINT_8  num_of_vars;
  UINT_8  test_result;
}__attribute__ ((packed));

struct st_result_type2_str {
  UINT_8  version;
  UINT_8  test_result;
  UINT_16  loop_count;
  UINT_16  num_of_failures;
}__attribute__ ((packed));

union st_result_str
{
  struct st_result_type1_str type1;
  struct st_result_type2_str type2;
}__attribute__ ((packed));

/* Self-test response variable structure */
struct st_resp_var_str
{
  UINT_32 var; /* Variable */
  UINT_8 tag;  /* Tag sent to the PTU */
  UINT_8 type; /* Variable type: 8, 16, 32 bit */
}__attribute__ ((packed));

struct st_resp_str
{
  UINT_8  Valid;
  UINT_8  msg_mode; /* Mode for test message generation */
  UINT_16 set_info; /* A | B | Both trucks */
  UINT_16 test_id;
  union   st_result_str result; /* Test results */
  UINT_32 flags;
  UINT_8  reserved[4]; /* reserved */
  struct st_resp_var_str st_resp_vars[ST_NUM_OF_RESP_VARS]; /* Data Variables */
}__attribute__ ((packed));

struct st_buffer_index_str
{
  UINT_16 index_in;
  UINT_16 index_out;
}__attribute__ ((packed));


/* External Variable Declarations */
/* PTU Command Buffer - From PTU to ST */
extern struct st_cmd_str st_cmd_buf[ST_CMD_BUFFER_SIZE];
extern struct st_buffer_index_str cmd_buf;

/* ST Response Buffer - From ST to PTU */
extern struct st_resp_str st_resp_buf[ST_RESP_BUFFER_SIZE];
extern struct st_buffer_index_str resp_buf;

#if 0
/* User-defined Self-Test list space */
extern UINT_16 st_list_usrdef[ST_MAX_USRDEF_LIST_SIZE];

/* Pointers to the various Self-test list */
/* Note: Keep the sequence same as the ST_LIST_XXX definitions */
extern UINT_16 *st_test_list[];
#endif

/* Functions in st_msg.c */
void Write_st_cmd_buf (UINT_8 *buffer, UINT_16 length);
UINT_16 Read_st_resp_buf (UINT_8 *buffer, UINT_16 *length);
void Write_st_resp_buf (UINT_8 *buffer);
void Respond_brief (UINT_16 test_id, UINT_16 composite_result);
void Respond_detailed (UINT_16 test_id, UINT_16 composite_result);
void Respond_counter (UINT_16 test_id, UINT_16 composite_result);
void Respond_special (UINT_16 message_id);
void Respond_interactive (UINT_16 test_id, UINT_16 composite_result, 
						  const INT_8 *fmt, UINT_32 data1,
                          UINT_32 data2, UINT_32 data3, UINT_32 data4,
                          UINT_32 data5, UINT_32 data6, UINT_32 data7,
                          UINT_32 data8, UINT_32 data9, UINT_32 data10);

/* Functions in st_ltest.c */
UINT_16 Null_test (UINT_16 index);

/* Functions in st_itest.c */
UINT_16 Allowed_to_test (void);


#endif
