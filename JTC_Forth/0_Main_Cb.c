#include "3_Setup.h"
#include <userint.h>
#include "0_Main.h"
#include "A_Global.h"

int	BtCtrl[7] = {MAIN_BT_AUTO, MAIN_BT_MANUAL, MAIN_BT_ZEROSET, MAIN_BT_TABLE,
				MAIN_BT_GRAPH, MAIN_BT_HISTORY, MAIN_BT_IO};

void	MainButton(int a)
{
	int i;
	for(i = 0 ; i < 7 ; i ++)
	{
		if(i == a)
			SetCtrlVal(mainpanel, BtCtrl[i], 1);
		else
			SetCtrlVal(mainpanel, BtCtrl[i], 0);	
	}
	if(TabPage != 1)
	{	
		for(i = 0 ; i < MAX_SOL ; i ++)
		{
			PlcData[SOL_START_NO + i] = 0;
			SetCtrlVal(tab_manual, ManuSwLed[i], 0);
		}
	}
	
	if(TabPage == 1)
	{
		PlcData[1] = 0;
		PlcData[2] = 1;
		PlcData[3] = 0;
	}
	else if(TabPage == 2)
	{
		PlcData[1] = 0;
		PlcData[2] = 0;
		PlcData[3] = 1;
	}
	else
	{
		PlcData[1] = 1;
		PlcData[2] = 0;
		PlcData[3] = 0;
	}
}

int CVICALLBACK Cb_Bt_Auto (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			TabPage = 0;
			SetActiveTabPage(mainpanel, MAIN_TAB, TabPage);
			MainButton(TabPage);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Bt_Manual (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			TabPage = 1;
			SetActiveTabPage(mainpanel, MAIN_TAB, TabPage);
			MainButton(TabPage);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Bt_Zeroset (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			TabPage = 2;
			SetActiveTabPage(mainpanel, MAIN_TAB, TabPage);
			MainButton(TabPage);
			break;
	}
	return 0;
}
int CVICALLBACK Cb_Bt_Table (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			TabPage = 3;
			SetActiveTabPage(mainpanel, MAIN_TAB, TabPage);
			MainButton(TabPage);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Bt_Graph (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			TabPage = 4;
			SetActiveTabPage(mainpanel, MAIN_TAB, TabPage);
			MainButton(TabPage);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Bt_History (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			TabPage = 5;
			SetActiveTabPage(mainpanel, MAIN_TAB, TabPage);
			MainButton(TabPage);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Bt_Io (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			TabPage = 6;
			SetActiveTabPage(mainpanel, MAIN_TAB, TabPage);
			MainButton(TabPage);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Main_Model (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			break;
		case EVENT_VAL_CHANGED:
			PwMain	= 1;
			PwCali	= 0;
			PwSetup = 0;
			PwModel = 0;
			Check_Password();
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Pop_Model (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PwMain	= 0;
			PwCali	= 0;
			PwSetup = 0;
			PwModel = 1;
			Check_Password();
//			SetActivePanel(modelpanel);
//			InstallPopup(modelpanel);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Pop_Result (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetDateResult();
			SetActivePanel(resultpanel);
			InstallPopup(resultpanel);

			break;
	}
	return 0;
}

int CVICALLBACK Cb_Pop_Setup (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PwMain	= 0;
			PwCali	= 0;
			PwSetup = 1;
			PwModel = 0;
			Check_Password();
//			SetActivePanel(setuppanel);
//			InstallPopup(setuppanel);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Pop_Cali (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PwMain	= 0;
			PwCali	= 1;
			PwSetup = 0;
			PwModel = 0;
			Check_Password();
			break;
	}
	return 0;
}

int CVICALLBACK Cb_St_Auto (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:

			break;
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK Cb_St_Manual (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK Cb_St_Origin (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PlcData[7] = 1;
			break;
		case EVENT_LEFT_CLICK:
			PlcData[7] = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
//			PlcData[7] = 0;
			break;
	}
	return 0;
}

int CVICALLBACK Cb_St_Buzzer (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PlcData[8] = 1;
			break;
		case EVENT_LEFT_CLICK:
			PlcData[8] = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
//			PlcData[8] = 0;
			break;
	}
	return 0;
}

int CVICALLBACK Cb_St_Reset (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PlcData[9] = 1;
			break;
		case EVENT_LEFT_CLICK:
			PlcData[9] = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
//			PlcData[9] = 0;
			break;
	}
	return 0;
}

int CVICALLBACK Cb_St_Emergency (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PlcData[10] = 1;
			break;
		case EVENT_LEFT_CLICK:
			PlcData[10] = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
//			PlcData[10] = 0;
			break;
	}
	return 0;
}

int CVICALLBACK Cb_St_Light (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PlcData[15] = 1;
			break;
		case EVENT_LEFT_CLICK:
			PlcData[15] = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
//			PlcData[15] = 0;
			break;
	}
	return 0;
}

int CVICALLBACK Cb_St_Workout (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PlcData[11] = 1;
			break;
		case EVENT_LEFT_CLICK:
			PlcData[11] = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
//			PlcData[11] = 0;
			break;
	}
	return 0;
}

void ChangeModel(int a)
{
	ModelNo = a;
	ResetSpcData();
	LoadModelData();
	SPCDisplayPointNo = 0;
	SetCtrlIndex(tab_auto, TAB_AUTO_RING_MEASPOINT, SPCDisplayPointNo);	
	CallCtrlCallback(tab_auto, TAB_AUTO_RING_MEASPOINT, EVENT_VAL_CHANGED, 0, 0, NULL);

	SendModelBit();

	InitStData(1);

	ContinuousNgNo = 0;
	ReMeasCnt = 0;	
}
