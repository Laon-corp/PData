#include <userint.h>
#include "0_Main.h"
#include <windows.h>
#include "pwctrl.h"
#include "A_Global.h"

int main (int argc, char *argv[])
{
	int	thereIsAnother;
	
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */

	if (CheckForDuplicateAppInstance (ACTIVATE_OTHER_INSTANCE, &thereIsAnother) < 0)
		return -1; /* out of memory */
	
	if (thereIsAnother)
		return 0; /* prevent duplicate instance */

	//Check Hdd Id
//	if(GetRegHdd() < 0)
//		return 0;
	
	//Check Used Days
//	if(GetRegUsedDays() < 0)
//		return 0;
	
	if ((mainpanel = LoadPanel (0, "0_Main.uir", MAIN)) < 0)
		return -1;
	if ((modelpanel = LoadPanel(0, "1_Model.uir", MODEL)) < 0)
		return -1;
	if ((resultpanel = LoadPanel(0, "2_Result.uir", RESULT)) < 0)
		return -1;
	if ((setuppanel = LoadPanel(0, "3_Setup.uir", SETUP)) < 0)
		return -1;
	if ((portpanel = LoadPanel(0, "3_Setup.uir", PORTPANEL)) < 0)
		return -1;
	if ((calpanel = LoadPanel(0, "4_Calibration.uir", CALPANEL)) < 0)
		return -1;
	if ((keypad = LoadPanel(0, "5_Keypad.uir", KEYPAD)) < 0)
		return -1;
	if ((pw = LoadPanel(0, "6_Password.uir", PW)) < 0)
		return -1;
	
	//mainpanel
	GetPanelHandleFromTabPage(mainpanel, MAIN_TAB, 0, &tab_auto);
	GetPanelHandleFromTabPage(mainpanel, MAIN_TAB, 1, &tab_manual);
	GetPanelHandleFromTabPage(mainpanel, MAIN_TAB, 2, &tab_zeroset);
	GetPanelHandleFromTabPage(mainpanel, MAIN_TAB, 3, &tab_table);
	GetPanelHandleFromTabPage(mainpanel, MAIN_TAB, 4, &tab_graph);
	GetPanelHandleFromTabPage(mainpanel, MAIN_TAB, 5, &tab_history);
	GetPanelHandleFromTabPage(mainpanel, MAIN_TAB, 6, &tab_io);
	
	SetCtrlAttribute(mainpanel, MAIN_TAB, ATTR_TABS_VISIBLE, 0);
	
	//modelpanel
	GetPanelHandleFromTabPage(modelpanel, MODEL_TAB, 0, &model_tab_Meas);
	GetPanelHandleFromTabPage(modelpanel, MODEL_TAB, 1, &model_tab_Calc);
	GetPanelHandleFromTabPage(modelpanel, MODEL_TAB, 2, &model_tab_Mark);

	// Password Control Handle
	Password_Control_Handle = PasswordCtrl_ConvertFromString (pw, PW_PASSWORD);					
	PasswordCtrl_SetAttribute(pw, Password_Control_Handle, ATTR_PASSWORD_MASK_CHARACTER, '*');
	PasswordCtrl_SetAttribute(pw, Password_Control_Handle, ATTR_PASSWORD_MAX_LENGTH, MAX_PW_CHARS);

	//Init System
	GetDateTime();
	InitSystem();

	InitPlcErrStr();
	InitIO();
	//InitManuSol();
	
	GetRegUserPw();
	
	ResetSpcData();	
		
	GetCurrShift();
	OldShift = CurrShift;
	LoadModel();
	
	LogUpdate("Program Start");
	//Thread
	WhileLoopFlag = 1;
	ThreadInit();
	LogUpdate("Thread Initialized success");

	//Amp Comm
	LoadCali();
	LogUpdate("Calibration Initialized success");

	
	
	numAmp = 2;
	if( !AmpPortOpen() )
		
	//GetAmpParameter(); 	
	//AmpStart(1);

	//Plc Comm
	PlcInit();
	LogUpdate("Plc Initialized success");

	//241016 마킹기 사용 시 주석 MarkInit 해제
	//Mark Comm
	//MarkInit();
	
	//Set Default Tab Page
	MainButton(0);
	SetActiveTabPage(mainpanel,		MAIN_TAB,	0);
	SetActiveTabPage(modelpanel,	MODEL_TAB,	0);
	
	SetMouseCursor(VAL_DEFAULT_CURSOR); 
	
	FuncDBConnect();	
	
	DisplayPanel (mainpanel);
	
	SetCtrlAttribute(tab_auto, TAB_AUTO_MEAS_TIMER_1, ATTR_INTERVAL, MEAS_TIME*1.0);
	SetCtrlAttribute(tab_auto, TAB_AUTO_MEAS_TIMER_2, ATTR_INTERVAL, MEAS_TIME*1.0);
	SetCtrlAttribute(tab_auto, TAB_AUTO_MEAS_TIMER_3, ATTR_INTERVAL, MEAS_TIME*1.0);
	SetCtrlAttribute(tab_auto, TAB_AUTO_MEAS_TIMER_4, ATTR_INTERVAL, MEAS_TIME*1.0);
	
	SetCtrlAttribute(tab_manual, TAB_MANU_MANU_TIMER_1, ATTR_INTERVAL, MEAS_TIME*1.0);
	SetCtrlAttribute(tab_manual, TAB_MANU_MANU_TIMER_2, ATTR_INTERVAL, MEAS_TIME*1.0);
	SetCtrlAttribute(tab_manual, TAB_MANU_MANU_TIMER_3, ATTR_INTERVAL, MEAS_TIME*1.0);
	SetCtrlAttribute(tab_manual, TAB_MANU_MANU_TIMER_4, ATTR_INTERVAL, MEAS_TIME*1.0);
	
	SetCtrlAttribute(tab_zeroset, TAB_ZERO_ZERO_TIMER_1, ATTR_INTERVAL, MEAS_TIME*1.0);
	SetCtrlAttribute(tab_zeroset, TAB_ZERO_ZERO_TIMER_2, ATTR_INTERVAL, MEAS_TIME*1.0);
	SetCtrlAttribute(tab_zeroset, TAB_ZERO_ZERO_TIMER_3, ATTR_INTERVAL, MEAS_TIME*1.0);
	SetCtrlAttribute(tab_zeroset, TAB_ZERO_ZERO_TIMER_4, ATTR_INTERVAL, MEAS_TIME*1.0);

	RunUserInterface ();
	LogUpdate("Program End");
	WhileLoopFlag = 0;
	
	CmtDiscardThreadPool (poolHandle);	
	
	if(!AmpPortOpenErr)
	{
		AmpPortOpenErr = 1;
		AmpPortClose();
	}
	
	if(PlcConnectStatus)
		DisconnectFromTCPServer(hPlcComm);
	if(!PlcCommErr)
	{
		PlcCommErr = 1;
		PlcClose();
	}
	
	if(MarkConnectStatus)
	{
		MarkClose();	
	}
	
//	CmtReleaseThreadPoolFunctionID (poolHandle, ThreadFuncId);	
//	CmtReleaseThreadPoolFunctionID (poolHandle, ThreadLogId);
//	CmtReleaseThreadPoolFunctionID (poolHandle, ThreadMeasId);

	FuncDBDisconnect();
	
	DiscardPanel (mainpanel);
	DiscardPanel (modelpanel);
	DiscardPanel (resultpanel);
	DiscardPanel (setuppanel);
	DiscardPanel (portpanel);
	DiscardPanel (calpanel);
	DiscardPanel (keypad);
	DiscardPanel (pw);
	return 0;
}

int CVICALLBACK Close_MainPanel (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(ConfirmPopup("PROGRAM CLOSE", "CLOSE?"))
				QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Logo (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	return 0;
}

char	tempShift[20];
void	GetCurrShift(void)
{
	if( strncmp(CurrTime, DayStartTime, 4) >= 0 && strncmp(CurrTime, NightStartTime, 4) < 0)
			CurrShift = 0;
	else	CurrShift = 1;	
}

void 	GetDateTime(void)
{
	int hh, mm, ss;
	int YY, MM, DD;
	GetSystemDate(&MM, &DD, &YY);
	GetSystemTime(&hh, &mm, &ss);
	
	sprintf(CurrDate, "%04d-%02d-%02d", YY, MM, DD);
	sprintf(CurrTime, "%02d:%02d:%02d", hh, mm, ss);
	
	SetCtrlVal(mainpanel, MAIN_DATE, CurrDate);
	SetCtrlVal(mainpanel, MAIN_TIME, CurrTime);	

	// Check HDD & Memory
	CheckHdd();
	
	// Check Every 10 min.
	if((mm % 10 == 0) && (ss == 0))
	{
		// Check Used Days & Log Path
		if(CompareStrings (CurrTime, 0, "00:00:00", 0, 0) == 0)
		{
			InitLogPath();
			Used_Days++;
			SetRegUsedDays();
		}
		
		// Day or Night Check
		GetCurrShift();
		
		// if Changed Shift Time
		if(CurrShift != OldShift)
		{
			GetDataFileName();
			GetSaveDataNum();
			OldShift = CurrShift;
			if(CurrShift)	sprintf(tempShift, "Night Time Start");
			else			sprintf(tempShift, "Day Time Start");
			LogUpdate(tempShift);
		}
	}
}

int CVICALLBACK Cb_Timer_Time (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			GetDateTime();
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Timer_Alarm (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	int i;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			//WIN 10
			GetCtrlAttribute(mainpanel, MAIN_BT_HISTORY, ATTR_TEXT_COLOR, &i);
			if(i == 0xFF0000L)
			{
				SetCtrlAttribute(mainpanel, MAIN_BT_HISTORY, ATTR_TEXT_COLOR, VAL_BLACK);	
				SetCtrlAttribute(mainpanel, MAIN_BT_HISTORY, ATTR_TEXT_COLOR, VAL_BLACK);
			}
			else
			{
				SetCtrlAttribute(mainpanel, MAIN_BT_HISTORY, ATTR_TEXT_COLOR, VAL_RED);
				SetCtrlAttribute(mainpanel, MAIN_BT_HISTORY, ATTR_TEXT_COLOR, VAL_RED);
			}
			
			//	WIN 7
			GetCtrlAttribute(mainpanel, MAIN_ALARM, ATTR_VISIBLE, &i);
			SetCtrlAttribute(mainpanel, MAIN_ALARM, ATTR_VISIBLE, !i);
			break;
	}
	return 0;
}

