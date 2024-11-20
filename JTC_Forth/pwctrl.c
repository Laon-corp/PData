/*============================================================================*/
/*						  L a b W i n d o w s / C V I						  */
/*----------------------------------------------------------------------------*/
/*	  Copyright (c) National Instruments 1987-2020.	 All Rights Reserved.	  */
/*----------------------------------------------------------------------------*/
/*																			  */
/* Title:		pwctrl.c													  */
/* Purpose:		implements password controls								  */
/*																			  */
/*============================================================================*/

#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include <formatio.h>
#include "toolbox.h"
#include "pwctrl.h"


#define DEFAULT_MASK_CHARACTER  '*'
#define PASSWORD_CTRL_TYPE      "Password Control"

#undef PasswordCtrl_Create
#undef PasswordCtrl_SetAttribute
#undef PasswordCtrl_GetAttribute

typedef struct
	{
	int                 panel;
	int                 ctrl;
	int                 maxPasswordLength;
	int                 valid;                                    /* Tells if the lock is good. */
	CmtThreadLockHandle	lockHandle;
	} *PasswordInfo;

static int  CreatePasswordInfo(int panel, int ctrl, PasswordInfo *newPasswordInfo, int *pLocked);
static void DiscardPasswordInfo(PasswordInfo passwordInfo, int *pLocked);
static int PasswordCtrl_SetAttributeWithEncoding(int panel, int passwordCtrl, int attribute, va_list args, int encoding);
static int PasswordCtrl_GetAttributeWithEncoding(int panel, int passwordCtrl, int attribute, void *value, int encoding);

int  CVICALLBACK PasswordCtrl_Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


/*****************************************************************************************/

int CVIFUNC PasswordCtrl_CreateAnsi(int panel, const char *label, int top, int left)
{
	int stringCtrl;
	int error  = 0;

	errChk(stringCtrl = NewCtrlAnsi (panel, CTRL_STRING, label, top, left));

	error = PasswordCtrl_ConvertFromString(panel, stringCtrl);

Error:
	if (error < 0)
		DiscardCtrl(panel, stringCtrl);
	return error;
}

/*****************************************************************************************/

int CVIFUNC PasswordCtrl_CreateUtf8(int panel, const char *label, int top, int left)
{
	int stringCtrl;
	int error  = 0;

	errChk(stringCtrl = NewCtrlUtf8 (panel, CTRL_STRING, label, top, left));

	error = PasswordCtrl_ConvertFromString(panel, stringCtrl);

Error:
	if (error < 0)
		DiscardCtrl(panel, stringCtrl);
	return error;
}

/*****************************************************************************************/

int CVIFUNC PasswordCtrl_Create(int panel, const char *label, int top, int left)
{
	return PasswordCtrl_CreateAnsi(panel, label, top, left);
}

/*****************************************************************************************/

static int PasswordCtrl_ConvertFromString(int panel, int stringCtrl)
{
	int             error = UIENoError;
	PasswordInfo    pwInfo = 0;
	int             locked = FALSE;

	errChk( CreatePasswordInfo(panel, stringCtrl, &pwInfo, &locked));       /* Creates and gets the lock. */

	errChk( SetCtrlAttribute(panel, stringCtrl, ATTR_ENABLE_CHARACTER_MASKING, 1));

	errChk( PasswordCtrl_SetAttributeUtf8(panel, stringCtrl, ATTR_PASSWORD_MASK_CHARACTER, DEFAULT_MASK_CHARACTER));
	errChk( PasswordCtrl_SetAttributeUtf8(panel, stringCtrl, ATTR_PASSWORD_MAX_LENGTH, MAX_POSSIBLE_PASSWORD_LENGTH));

Error:
	if (error < 0)
		DiscardPasswordInfo(pwInfo, &locked);                               /* Releases and deletes the lock. */
	else if (locked)
		CmtReleaseLock(pwInfo->lockHandle);

	return (error < 0) ? error : stringCtrl;
}

/*****************************************************************************************/

int CVIFUNC PasswordCtrl_RevertToString(int panel, int control)
{
	int             error = UIENoError;
	int 			locked = FALSE;
	PasswordInfo    pwInfo = 0;

	errChk( SetCtrlAttribute(panel, control, ATTR_ENABLE_CHARACTER_MASKING, 0));

	errChk( GetChainedCallbackData(panel, control, PASSWORD_CTRL_TYPE, (void **)&pwInfo));
	if (!pwInfo->valid)
		errChk(UIEInvalidControlId);

	DiscardPasswordInfo(pwInfo, &locked);                               /* Releases and deletes the lock. */
Error:
	return (error < 0) ? error : control;
}

/*****************************************************************************************/

static int CreatePasswordInfo(int panel, int ctrl, PasswordInfo *newPasswordInfo, int *pLocked)
{
	int             error = UIENoError;
	PasswordInfo    pwInfo = 0;
	int             locked = FALSE;

	nullChk(pwInfo = (PasswordInfo)calloc(sizeof(*pwInfo), 1));
	errChk( CmtNewLock(NULL, 0, &pwInfo->lockHandle) );
	errChk( CmtGetLock(pwInfo->lockHandle) );
	locked = TRUE;
	pwInfo->valid = TRUE;

	pwInfo->panel = panel;
	pwInfo->ctrl = ctrl;

	errChk( ChainCtrlCallback(panel, ctrl, PasswordCtrl_Callback, (void *)pwInfo, PASSWORD_CTRL_TYPE));

	if (newPasswordInfo)
		*newPasswordInfo = pwInfo;

Error:
	/* Do not release lock, calling function still needs it to be locked. */
	if (error < 0)
		{
		if (newPasswordInfo)
			*newPasswordInfo = 0;
		}

	*pLocked = locked;
	return error;
}

/*****************************************************************************************/

static void DiscardPasswordInfo(PasswordInfo passwordInfo, int *pLocked)
{
	if (passwordInfo && passwordInfo->valid)
		{
		passwordInfo->valid = FALSE;
		if (!(*pLocked))
			CmtGetLock(passwordInfo->lockHandle);		/* Want to make sure the lock is not owned by another thread. */

		CmtReleaseLock(passwordInfo->lockHandle);

		*pLocked = FALSE;
		CmtDiscardLock(passwordInfo->lockHandle);
		UnchainCtrlCallback(passwordInfo->panel, passwordInfo->ctrl, PASSWORD_CTRL_TYPE);
		free(passwordInfo);
		}
}

/*****************************************************************************************/

int CVIFUNC_C PasswordCtrl_SetAttributeAnsi(int panel, int passwordCtrl, int attribute, ...)
{
	int     retVal;
	va_list args = NULL;

	va_start(args, attribute);
	retVal = PasswordCtrl_SetAttributeWithEncoding(panel, passwordCtrl, attribute, args, VAL_ANSI_ENCODING);
	va_end(args);

	return retVal;
}

/*****************************************************************************************/

int CVIFUNC_C PasswordCtrl_SetAttributeUtf8(int panel, int passwordCtrl, int attribute, ...)
{
	int     retVal;
	va_list args = NULL;

	va_start(args, attribute);
	retVal = PasswordCtrl_SetAttributeWithEncoding(panel, passwordCtrl, attribute, args, VAL_UTF8_ENCODING);
	va_end(args);

	return retVal;
}
/*****************************************************************************************/

int CVIFUNC_C PasswordCtrl_SetAttribute(int panel, int passwordCtrl, int attribute, ...)
{
	int     retVal;
	va_list args = NULL;

	va_start(args, attribute);
	retVal = PasswordCtrl_SetAttributeAnsi(panel, passwordCtrl, attribute, args);
	va_end(args);

	return retVal;
}

/*****************************************************************************************/

static int PasswordCtrl_SetAttributeWithEncoding(int panel, int passwordCtrl, int attribute, va_list args, int encoding)
{
	int             error = UIENoError;
	PasswordInfo    pwInfo = 0;
	int             locked = FALSE;
	int             maskCharacter;

	errChk( GetChainedCallbackData(panel, passwordCtrl, PASSWORD_CTRL_TYPE, (void **)&pwInfo));

	if (!pwInfo->valid)
		errChk(UIEInvalidControlId);

	errChk( CmtGetLock(pwInfo->lockHandle) );
	locked = TRUE;

	switch (attribute)
		{
		case ATTR_PASSWORD_MAX_LENGTH:
			pwInfo->maxPasswordLength = va_arg(args, int);

			if (pwInfo->maxPasswordLength < 0)
				pwInfo->maxPasswordLength = 0;
			else
			if (pwInfo->maxPasswordLength > MAX_POSSIBLE_PASSWORD_LENGTH)
				pwInfo->maxPasswordLength = MAX_POSSIBLE_PASSWORD_LENGTH;

			errChk( PasswordCtrl_SetAttributeUtf8(panel, passwordCtrl, ATTR_PASSWORD_VAL, ""));
			errChk( SetCtrlAttribute(panel, passwordCtrl, ATTR_MAX_ENTRY_LENGTH, pwInfo->maxPasswordLength));
			break;
		case ATTR_PASSWORD_VAL:
			{
			char    *newPasswordVal = (char *)va_arg(args, char *);

				if (!newPasswordVal)
					newPasswordVal = "";

				if (encoding == VAL_ANSI_ENCODING) {
					errChk( SetCtrlAttributeAnsi(panel, passwordCtrl, ATTR_CTRL_VAL, newPasswordVal));
				} else {
					errChk( SetCtrlAttributeUtf8(panel, passwordCtrl, ATTR_CTRL_VAL, newPasswordVal));
				}
			}
			break;
		case ATTR_PASSWORD_MASK_CHARACTER:
			maskCharacter = (char) va_arg(args, int);
			if (maskCharacter == 0)
				maskCharacter = DEFAULT_MASK_CHARACTER;
			errChk( SetCtrlAttribute(panel, passwordCtrl, ATTR_MASK_CHARACTER, (int)maskCharacter));
			break;
		default:
			errChk(UIEInvalidAttribute);
			break;
		}

Error:
	if (locked)
		CmtReleaseLock(pwInfo->lockHandle);
	return error;
}

/*****************************************************************************************/

int CVIFUNC PasswordCtrl_GetAttributeAnsi(int panel, int passwordCtrl, int attribute, void *value)
{
	return PasswordCtrl_GetAttributeWithEncoding(panel, passwordCtrl, attribute, value, VAL_ANSI_ENCODING);
}

/*****************************************************************************************/

int CVIFUNC PasswordCtrl_GetAttributeUtf8(int panel, int passwordCtrl, int attribute, void *value)
{
	return PasswordCtrl_GetAttributeWithEncoding(panel, passwordCtrl, attribute, value, VAL_UTF8_ENCODING);
}

/*****************************************************************************************/

int CVIFUNC PasswordCtrl_GetAttribute(int panel, int passwordCtrl, int attribute, void *value)
{
	return PasswordCtrl_GetAttributeAnsi(panel, passwordCtrl, attribute, value);
}

/*****************************************************************************************/

static int PasswordCtrl_GetAttributeWithEncoding(int panel, int passwordCtrl, int attribute, void *value, int encoding)
{
	int             error = UIENoError;
	PasswordInfo    pwInfo = 0;
	int             locked = FALSE;
	int				maskCharacter;

	if (!value)
		errChk(UIENullPointerPassed);

	errChk( GetChainedCallbackData(panel, passwordCtrl, PASSWORD_CTRL_TYPE, (void **)&pwInfo));

	if (!pwInfo->valid)
		errChk(UIEInvalidControlId);

	errChk( CmtGetLock(pwInfo->lockHandle) );
	locked = TRUE;

	switch (attribute)
		{
		case ATTR_PASSWORD_MAX_LENGTH:
			*(int *)value = pwInfo->maxPasswordLength;
			 break;
		case ATTR_PASSWORD_VAL:
			if (value) {
				if (encoding == VAL_ANSI_ENCODING) {
					errChk( GetCtrlValAnsi(panel, passwordCtrl, value));
				} else {
					errChk( GetCtrlValUtf8(panel, passwordCtrl, value));
				}
			}
			break;
		case ATTR_PASSWORD_MASK_CHARACTER:
			errChk(GetCtrlAttribute(panel, passwordCtrl, ATTR_MASK_CHARACTER, &maskCharacter));
			*(char *)value = (char) maskCharacter;
			break;
		default:
			errChk(UIEInvalidAttribute);
			break;
		}

Error:
	if (locked)
		CmtReleaseLock(pwInfo->lockHandle);
	return error;
}

/*****************************************************************************************/

int  CVICALLBACK PasswordCtrl_Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	PasswordInfo    pwInfo = (PasswordInfo)callbackData;
	int             locked = FALSE;

	if (!pwInfo->valid)
		return 0;

	CmtGetLock(pwInfo->lockHandle);
	locked = TRUE;

	switch (event)
		{
		case EVENT_DISCARD:
			DiscardPasswordInfo(pwInfo, &locked);    /* Releases and deletes the lock. */
			break;
		}

	if (locked)
		CmtReleaseLock(pwInfo->lockHandle);
	return 0;
}
