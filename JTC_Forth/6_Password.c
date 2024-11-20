#include "windows.h"
#include "pwctrl.h"
#include <userint.h>
#include "6_Password.h"
#include "A_Global.h"

void 	Check_Password(void)
{
	SetCtrlVal(pw, PW_PASSWORD, "");
	DisplayPanel(pw);
	InstallPopup(pw);
}

int CVICALLBACK Cb_Ok (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	char 	InputPassword[MAX_PW_CHARS + 1] = {0,};
	int 	Master = 0, User = 0, a = 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			PasswordCtrl_GetAttribute(panel, PW_PASSWORD, ATTR_PASSWORD_VAL, InputPassword);
			SetCtrlVal(panel, PW_PASSWORD, "");
			
			//Master Password
			if(CompareStrings (InputPassword, 0, MASTER_PW, 0, 0) == 0)
			{
				Master = 1;		
			}
			else if(CompareStrings (InputPassword, 0, UserPassword, 0, 0) == 0)
			{
				User = 1;
			}
			else
			{
				if(PwMain)
				{
					SetCtrlVal(mainpanel, MAIN_MODEL_NAME, ModelNo);
				}
				MessagePopup("Password Error", "Incorrect Password\nCheck Password Again");
				RemovePopup(0);
				HidePanel(panel);
				PwMain = PwCali = PwSetup = PwModel = 0;
				ActivePanel = mainpanel;
				return 0;
			}
			
			if(Master || User)
			{
				RemovePopup(0);
				if(PwMain)
				{
					GetCtrlVal(mainpanel, MAIN_MODEL_NAME, &a);
					ChangeModel(a);
//					CallCtrlCallback(modelpanel, MODEL_LIST_MODEL, EVENT_MARK_STATE_CHANGE, 1, a, NULL);
				}
				else if(PwSetup)
				{
					LogUpdate("Display : Program Setup");
					DisplayPanel(setuppanel);
					InstallPopup(setuppanel);
					ActivePanel = setuppanel;
				}
				else if(PwCali)
				{
					LogUpdate("Display : Calibration");
					DisplayPanel(calpanel);
					InstallPopup(calpanel);
					ActivePanel = calpanel;
				}
				else if(PwModel)
				{
					LogUpdate("Display : Model Setup");
					DisplayPanel(modelpanel);
					InstallPopup(modelpanel);
					ActivePanel = modelpanel;
				}
				HidePanel(panel);
				PwMain = PwCali = PwSetup = PwModel = 0;
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Cancel (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(PwMain)
			{
				SetCtrlVal(mainpanel, MAIN_MODEL_NAME, ModelNo);
			}
			RemovePopup(0);
			HidePanel(panel);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_PwPanel (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	char	temp[24] = {0,};
	char 	InputPassword[MAX_PW_CHARS + 1] = {0,};
	int 	Master = 0, User = 0;
	
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		case EVENT_KEYPRESS:
			// ALT + A ~ Z 			: 131169 ~ 131194
			// CTL + A ~ Z 			: 262209 ~ 262234
			// ALT + SHIFT + A ~ Z	: 196673 ~ 196698
			// CTL + SHIFT + A ~ Z	: 327745 ~ 327770
			// CTL + ALT : NO WORKS
			// ENTER				: 1280
			switch(eventData1)	
			{
				case 1280:
					CallCtrlCallback(pw, PW_OK, EVENT_COMMIT, 0, 0, 0);
					break;
				case 327760:	// CTL + SHIFT + P
					sprintf(temp, "Password : %s", UserPassword);
					SetCtrlAttribute(panel, PW_PASSWORD, ATTR_LABEL_TEXT, temp);
					ResetTimer(pw, PW_TIMER_PW);
					SetCtrlAttribute(pw, PW_TIMER_PW, ATTR_ENABLED, 1);
					break;
				case 327747:	// CTL + SHIFT + C
					PasswordCtrl_GetAttribute(panel, PW_PASSWORD, ATTR_PASSWORD_VAL, InputPassword);
					SetCtrlVal(panel, PW_PASSWORD, "");
					
					if(CompareStrings (InputPassword, 0, MASTER_PW, 0, 0) == 0)
						Master = 1;
					else if(CompareStrings (InputPassword, 0, UserPassword, 0, 0) == 0)
						User = 1;	
					if(Master || User) 
					{
						if(VAL_GENERIC_POPUP_BTN1 == 
						GenericMessagePopup("Change Password", "Input New Password", "Change", "Cancel", "", temp, 23, 1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN2))
						{
							temp[10] = 0;
							memset(UserPassword, 0, sizeof(UserPassword));
							strcpy(UserPassword, temp);
							SetRegUserPw();
						}
					}
					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Timer_Pw (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(pw, PW_PASSWORD, ATTR_LABEL_TEXT, "Password :");
			SetCtrlAttribute(pw, PW_TIMER_PW, ATTR_ENABLED, 0);

			break;
	}
	return 0;
}
