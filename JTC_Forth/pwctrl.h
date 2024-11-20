/*============================================================================*/
/*						  L a b W i n d o w s / C V I						  */
/*----------------------------------------------------------------------------*/
/*	  Copyright (c) National Instruments 1987-2020.	 All Rights Reserved.	  */
/*----------------------------------------------------------------------------*/
/*																			  */
/* Title:		pwctrl.h													  */
/* Purpose:		implements password controls								  */
/*																			  */
/*============================================================================*/

#ifndef PASSWORD_CTRL_HEADER
#define PASSWORD_CTRL_HEADER

#include <cvidef.h>
#include "toolbox.h"

#ifdef __cplusplus
	extern "C" {
#endif


#define ATTR_PASSWORD_MAX_LENGTH	   1000
#define ATTR_PASSWORD_VAL			   1001
#define ATTR_PASSWORD_MASK_CHARACTER   1002

#define MAX_POSSIBLE_PASSWORD_LENGTH	(255 * MAX_UTF8_BYTES_IN_ANSI_CHAR)

int CVIFUNC PasswordCtrl_CreateAnsi(int panel, const char *label, int top, int left);
int CVIFUNC PasswordCtrl_CreateUtf8(int panel, const char *label, int top, int left);
int CVIFUNC PasswordCtrl_ConvertFromString(int panel, int stringCtrl);
int CVIFUNC PasswordCtrl_RevertToString(int panel, int control);
int CVIFUNC_C PasswordCtrl_SetAttributeAnsi(int panel, int passwordCtrl, int attribute, ...);
int CVIFUNC_C PasswordCtrl_SetAttributeUtf8(int panel, int passwordCtrl, int attribute, ...);
int CVIFUNC PasswordCtrl_GetAttributeAnsi(int panel, int passwordCtrl, int attribute, void *value);
int CVIFUNC PasswordCtrl_GetAttributeUtf8(int panel, int passwordCtrl, int attribute, void *value);

#ifdef CVI_UTF8
#define PasswordCtrl_Create PasswordCtrl_CreateUtf8
#define PasswordCtrl_SetAttribute PasswordCtrl_SetAttributeUtf8
#define PasswordCtrl_GetAttribute PasswordCtrl_GetAttributeUtf8
#else
#define PasswordCtrl_Create PasswordCtrl_CreateAnsi
#define PasswordCtrl_SetAttribute PasswordCtrl_SetAttributeAnsi
#define PasswordCtrl_GetAttribute PasswordCtrl_GetAttributeAnsi
#endif

#ifdef __cplusplus
	}
#endif

#endif /* PASSWORD_CTRL_HEADER */

