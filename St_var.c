/*****************************************************************************
*
* .b
*   Copyright (C) 2001 DaimlerChrysler Rail Systems (North America) Inc.
*   Copyright (C) 2001 Bombardier Transportation (Holdings) USA Inc.
*
* Project:      Pittsburgh LRV Propulsion
*
* File Name:    st_var.c
*
* Subsystem:    VCU: Self Test
*
* Procedures:   None
*
* .b
*
* History:
*   Mar 5 2001 Vipin Sapra @ ADtranz
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

#include "st_var.h"
//DAS #include "st_dd.h"


/* PTU Command Buffer - From PTU to ST */
struct st_cmd_str st_cmd_buf[ST_CMD_BUFFER_SIZE];
struct st_buffer_index_str cmd_buf;

/* ST Response Buffer - From ST to PTU */
struct st_resp_str st_resp_buf[ST_RESP_BUFFER_SIZE];
struct st_buffer_index_str resp_buf;

#if 0
/* Default Logic and Passive Tests' list */
UINT_16 st_list_logic[] =
{
  ST_NULL
};

/* Default Interacive Tests' list */
UINT_16 st_list_interactive[] =
{
  ST_MC,
  ST_NULL
};

/* Default Power Tests' list */
UINT_16 st_list_power[] =
{
  ST_NULL
};

/* User-defined Self-Test list space */
UINT_16 st_list_usrdef[ST_MAX_USRDEF_LIST_SIZE] =
{
  ST_NULL
};


/* Pointers to the various Self-test list */
/* Note: Keep the sequence same as the ST_LIST_XXX definitions */
UINT_16 *st_test_list[] =
{
  st_list_logic,       /* ST_LIST_REQUEST     - 0 */
  st_list_logic,       /* ST_LIST_LOGIC       - 1 */
  st_list_interactive, /* ST_LIST_INTERACTIVE - 2 */
  st_list_power,       /* ST_LIST_POWER       - 3 */
  st_list_usrdef,      /* ST_LIST_USRDEF      - 4 */
};


#endif

#ifdef __cplusplus
}
#endif
