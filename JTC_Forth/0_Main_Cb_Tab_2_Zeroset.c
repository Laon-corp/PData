#include "A_Global.h"

int CVICALLBACK Cb_Zero_1 (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int 	sig = 0;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Zeroset Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_zeroset, TAB_ZERO_ZERO_TIMER_1);
			SetCtrlAttribute(tab_zeroset, TAB_ZERO_ZERO_TIMER_1, ATTR_ENABLED, 1);
			break;
			
		case EVENT_COMMIT:
			PlcData[16 + sig] = 1;
			AutoMeasFlag = 0;
			ManuMeasFlag = 0;
			ZeroMeasFlag = 1;
			break;
/*		
		case EVENT_LEFT_CLICK:
			PlcData[16 + sig] = 1;
			AutoMeasFlag = 0;
			ManuMeasFlag = 0;
			ZeroMeasFlag = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
			PlcData[16 + sig] = 0;
			break;
*/
	}
	return 0;
}

int CVICALLBACK Cb_Zero_2 (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int 	sig = 1;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Zeroset Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_zeroset, TAB_ZERO_ZERO_TIMER_2);
			SetCtrlAttribute(tab_zeroset, TAB_ZERO_ZERO_TIMER_2, ATTR_ENABLED, 1);
			break;
			
		case EVENT_COMMIT:
			PlcData[16 + sig] = 1;
			AutoMeasFlag = 0;
			ManuMeasFlag = 0;
			ZeroMeasFlag = 1;
			break;
/*		
		case EVENT_LEFT_CLICK:
			PlcData[16 + sig] = 1;
			AutoMeasFlag = 0;
			ManuMeasFlag = 0;
			ZeroMeasFlag = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
			PlcData[16 + sig] = 0;
			break;
*/
	}
	return 0;
}

int CVICALLBACK Cb_Zero_3 (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int 	sig = 2;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Zeroset Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_zeroset, TAB_ZERO_ZERO_TIMER_3);
			SetCtrlAttribute(tab_zeroset, TAB_ZERO_ZERO_TIMER_3, ATTR_ENABLED, 1);
			break;
			
		case EVENT_COMMIT:
			PlcData[16 + sig] = 1;
			AutoMeasFlag = 0;
			ManuMeasFlag = 0;
			ZeroMeasFlag = 1;
			break;
/*		
		case EVENT_LEFT_CLICK:
			PlcData[16 + sig] = 1;
			AutoMeasFlag = 0;
			ManuMeasFlag = 0;
			ZeroMeasFlag = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
			PlcData[16 + sig] = 0;
			break;
*/
	}
	return 0;
}

int CVICALLBACK Cb_Zero_4 (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int 	sig = 3;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Zeroset Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_zeroset, TAB_ZERO_ZERO_TIMER_4);
			SetCtrlAttribute(tab_zeroset, TAB_ZERO_ZERO_TIMER_4, ATTR_ENABLED, 1);
			break;
			
		case EVENT_COMMIT:
			PlcData[16 + sig] = 1;
			AutoMeasFlag = 0;
			ManuMeasFlag = 0;
			ZeroMeasFlag = 1;
			break;
/*		
		case EVENT_LEFT_CLICK:
			PlcData[16 + sig] = 1;
			AutoMeasFlag = 0;
			ManuMeasFlag = 0;
			ZeroMeasFlag = 1;
			break;
		case EVENT_LEFT_CLICK_UP:
			PlcData[16 + sig] = 0;
			break;
*/
	}
	return 0;
}

int CVICALLBACK Cb_Zero_Table (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int		top, left, leftbtn, rightbtn, key;

	switch (event)
	{
		case EVENT_LEFT_CLICK:
			GetRelativeMouseState(panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
			GetTableCellFromPoint(panel, control, MakePoint (left, top), &PadCell);
			if(PadCell.x > 3)
			{
				SetActiveTableCell (panel, control, PadCell);
				CallKeyPadCell(panel, control);
			}
			else
			{
				PadCell.x = 0;
				PadCell.y = 0;
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Zero_Save (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SaveZeroTableData();
			break;
	}
	return 0;
}

void	SaveZeroTableData(void)
{
	int		handle, i;
	char 	Path[1024] = {0,};
	char 	temp1[1024] = {0,};
	double 	dtemp[MAX_CH];
	
	GetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 1, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < MAX_CH ; i ++)
		ZeroValueBef[i] = dtemp[i];
	
	GetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 2, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < MAX_CH ; i ++)
		ZeroValueNow[i] = dtemp[i];
	
	GetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 3, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < MAX_CH ; i ++)
		ZeroValueDev[i] = dtemp[i];
	
	GetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 4, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < MAX_CH ; i ++)
		ZeroValueAlN[i] = dtemp[i];
	
	GetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 5, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < MAX_CH ; i ++)
		ZeroValueAlP[i] = dtemp[i];
	
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )			MakeDir(Path);
	sprintf(Path, "%s\\%s\\Zero.ini", Path_Model, ModelName[ModelNo]);
	
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		for(i = 0 ; i < MAX_CH ; i ++)
		{
			sprintf(temp1, "%.3f\t%.3f\t%.3f\t%.3f\t%.3f", ZeroValueBef[i], ZeroValueNow[i], ZeroValueDev[i], ZeroValueAlN[i], ZeroValueAlP[i]);
			WriteLine(handle, temp1, -1);
		}
		CloseFile(handle);
	}

}
void	LoadZeroTableData(void)
{
	int		handle, i;
	char 	Path[1024] = {0,};
	char 	temp1[1024] = {0,};
	double 	dtemp[MAX_CH];

	if( SetDir(Path_Model) )	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )			MakeDir(Path);
	sprintf(Path, "%s\\%s\\Zero.ini", Path_Model, ModelName[ModelNo]);
		
	if(GetFileInfo(Path, &i) == 0)
	{
		handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
		if(handle < 0)
			MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
		else
		{
			for(i = 0 ; i < MAX_CH ; i ++)
			{
				ZeroValueBef[i] = ZeroValueNow[i] = ZeroValueDev[i] = 0.0;
				ZeroValueAlN[i] = -5.0;	
				ZeroValueAlP[i] = +5.0;
			}
			for(i = 0 ; i < MAX_CH ; i ++)
			{
				sprintf(temp1, "%.3f\t%.3f\t%.3f\t%.3f\t%.3f", ZeroValueBef[i], ZeroValueNow[i], ZeroValueDev[i], ZeroValueAlN[i], ZeroValueAlP[i]);
				WriteLine(handle, temp1, -1);
			}
			CloseFile(handle);
		}
	}
	else
	{
		handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
		if(handle < 0)
			MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
		else
		{
			for(i = 0 ; i < MAX_CH ; i ++)
			{
				ReadLine(handle, temp1, -1);
				Scan(temp1, "%s>%f%f%f%f%f", &ZeroValueBef[i], &ZeroValueNow[i], &ZeroValueDev[i], &ZeroValueAlN[i], &ZeroValueAlP[i]);
			}
			CloseFile(handle);
		}
	}	

	for(i = 0 ; i < MAX_CH ; i ++)
		dtemp[i] = ZeroValueBef[i];		
	SetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 1, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);
	
	for(i = 0 ; i < MAX_CH ; i ++)
		dtemp[i] = ZeroValueNow[i];
	SetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 2, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);

	for(i = 0 ; i < MAX_CH ; i ++)
		dtemp[i] = ZeroValueDev[i];
	SetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 3, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);	

	for(i = 0 ; i < MAX_CH ; i ++)
		dtemp[i] = ZeroValueAlN[i];
	SetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 4, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);	

	for(i = 0 ; i < MAX_CH ; i ++)
		dtemp[i] = ZeroValueAlP[i];
	SetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 5, MAX_CH, 1), dtemp, VAL_COLUMN_MAJOR);
}


int CVICALLBACK Cb_Timer_Zero_1 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 0;
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			ZeroMeasFinish(sig);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Timer_Zero_2 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 1;
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			ZeroMeasFinish(sig);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Timer_Zero_3 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 2;
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			ZeroMeasFinish(sig);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Timer_Zero_4 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 3;
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			ZeroMeasFinish(sig);
			break;
	}
	return 0;
}