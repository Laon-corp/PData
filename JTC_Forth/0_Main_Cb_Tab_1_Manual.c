#include <userint.h>
#include "0_Main.h"
#include "A_Global.h"

int	ManuSwCtrl[MAX_SOL] = {TAB_MANU_SOL_1, TAB_MANU_SOL_2, TAB_MANU_SOL_3, TAB_MANU_SOL_4, TAB_MANU_SOL_5,
						  TAB_MANU_SOL_6, TAB_MANU_SOL_7, TAB_MANU_SOL_8, TAB_MANU_SOL_9, TAB_MANU_SOL_10,
						  TAB_MANU_SOL_11, TAB_MANU_SOL_12, TAB_MANU_SOL_13, TAB_MANU_SOL_14, TAB_MANU_SOL_15,
						  TAB_MANU_SOL_16, TAB_MANU_SOL_17, TAB_MANU_SOL_18, TAB_MANU_SOL_19, TAB_MANU_SOL_20};
int	ManuLedHome[MAX_SOL] = {TAB_MANU_LED_H_1, TAB_MANU_LED_H_2, TAB_MANU_LED_H_3, TAB_MANU_LED_H_4, TAB_MANU_LED_H_5,
						  TAB_MANU_LED_H_6, TAB_MANU_LED_H_7, TAB_MANU_LED_H_8, TAB_MANU_LED_H_9, TAB_MANU_LED_H_10,
						  TAB_MANU_LED_H_11, TAB_MANU_LED_H_12, TAB_MANU_LED_H_13, TAB_MANU_LED_H_14, TAB_MANU_LED_H_15,
						  TAB_MANU_LED_H_16, TAB_MANU_LED_H_17, TAB_MANU_LED_H_18, TAB_MANU_LED_H_19, TAB_MANU_LED_H_20};
int	ManuLedAct[MAX_SOL] = {TAB_MANU_LED_A_1, TAB_MANU_LED_A_2, TAB_MANU_LED_A_3, TAB_MANU_LED_A_4, TAB_MANU_LED_A_5,
						  TAB_MANU_LED_A_6, TAB_MANU_LED_A_7, TAB_MANU_LED_A_8, TAB_MANU_LED_A_9, TAB_MANU_LED_A_10,
						  TAB_MANU_LED_A_11, TAB_MANU_LED_A_12, TAB_MANU_LED_A_13, TAB_MANU_LED_A_14, TAB_MANU_LED_A_15,
						  TAB_MANU_LED_A_16, TAB_MANU_LED_A_17, TAB_MANU_LED_A_18, TAB_MANU_LED_A_19, TAB_MANU_LED_A_20};
char	ManuSwLedCtrl[MAX_SOL][32] = 
	{"LED_1",   "LED_2",   "LED_3",   "LED_4",   "LED_5",   "LED_6",   "LED_7",   "LED_8",   "LED_9",   "LED_10",
 	 "LED_11",  "LED_12",  "LED_13",  "LED_14",  "LED_15",  "LED_16",  "LED_17",  "LED_18",  "LED_19",  "LED_20",
	 "LED_21",  "LED_22",  "LED_23",  "LED_24",  "LED_25",  "LED_26",  "LED_27",  "LED_28",  "LED_29",  "LED_30",
	 "LED_31",  "LED_32",  "LED_33",  "LED_34",  "LED_35",  "LED_36",  "LED_37",  "LED_38",  "LED_39",  "LED_40"};
int ManuSwLed[MAX_SOL] = {TAB_MANU_LED_1, TAB_MANU_LED_2, TAB_MANU_LED_3, TAB_MANU_LED_4, TAB_MANU_LED_5,
						 TAB_MANU_LED_6, TAB_MANU_LED_7, TAB_MANU_LED_8, TAB_MANU_LED_9, TAB_MANU_LED_10,
						 TAB_MANU_LED_11,TAB_MANU_LED_12,TAB_MANU_LED_13,TAB_MANU_LED_14,TAB_MANU_LED_15,
						 TAB_MANU_LED_16,TAB_MANU_LED_17,TAB_MANU_LED_18,TAB_MANU_LED_19,TAB_MANU_LED_20,
						 TAB_MANU_LED_21,TAB_MANU_LED_22,TAB_MANU_LED_23,TAB_MANU_LED_24,TAB_MANU_LED_25,
						 TAB_MANU_LED_26,TAB_MANU_LED_27,TAB_MANU_LED_28,TAB_MANU_LED_29,TAB_MANU_LED_30,
						 TAB_MANU_LED_31,TAB_MANU_LED_32,TAB_MANU_LED_33,TAB_MANU_LED_34,TAB_MANU_LED_35,
						 TAB_MANU_LED_36,TAB_MANU_LED_37,TAB_MANU_LED_38,TAB_MANU_LED_39,TAB_MANU_LED_40};
int CVICALLBACK Cb_Sol (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	int 	i, a;
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			GetCtrlVal(panel, control, &a);
			a = !a;
			for( i = 0; i < MAX_SOL; i ++ )
			{
				if( ManuSwCtrl[i] == control )
					PlcData[SOL_START_NO + i] = a;
				else
					PlcData[SOL_START_NO + i] = 0;
				SetCtrlVal(panel, ManuSwCtrl[i], PlcData[SOL_START_NO + i]);						  					 
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Manual_1 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 0;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Manual Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_manual, TAB_MANU_MANU_TIMER_1);
			SetCtrlAttribute(tab_manual, TAB_MANU_MANU_TIMER_1, ATTR_ENABLED, 1);
			break;

		case EVENT_COMMIT:
			PlcData[16 + sig] = 1;
			MeasCycleNo = 0;
			AutoMeasFlag = 0;
			ManuMeasFlag = 1;
			ZeroMeasFlag = 0;
			break;	
/*		case EVENT_LEFT_CLICK:
			PlcData[16 + sig] = 1;
			MeasCycleNo = 0;
			AutoMeasFlag = 0;
			ManuMeasFlag = 1;
			ZeroMeasFlag = 0;
			break;
		case EVENT_LEFT_CLICK_UP:
			PlcData[16 + sig] = 0;
			break;
*/
	}
	return 0;
}

int CVICALLBACK Cb_Manual_2 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 1;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Manual Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_manual, TAB_MANU_MANU_TIMER_2);
			SetCtrlAttribute(tab_manual, TAB_MANU_MANU_TIMER_2, ATTR_ENABLED, 1);
			break;
		case EVENT_COMMIT:
			PlcData[16 + sig] = 1;
			MeasCycleNo = 0;
			AutoMeasFlag = 0;
			ManuMeasFlag = 1;
			ZeroMeasFlag = 0;
			break;	
/*		case EVENT_LEFT_CLICK:
			PlcData[16 + sig] = 1;
			MeasCycleNo = 0;
			AutoMeasFlag = 0;
			ManuMeasFlag = 1;
			ZeroMeasFlag = 0;
			break;
		case EVENT_LEFT_CLICK_UP:
			PlcData[16 + sig] = 0;
			break;
*/
	}
	return 0;
}

int CVICALLBACK Cb_Manual_3 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 2;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Manual Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_manual, TAB_MANU_MANU_TIMER_3);
			SetCtrlAttribute(tab_manual, TAB_MANU_MANU_TIMER_3, ATTR_ENABLED, 1);
			break;
		case EVENT_COMMIT:
			PlcData[16 + sig] = 1;
			MeasCycleNo = 0;
			AutoMeasFlag = 0;
			ManuMeasFlag = 1;
			ZeroMeasFlag = 0;
			break;	
/*		case EVENT_LEFT_CLICK:
			PlcData[16 + sig] = 1;
			MeasCycleNo = 0;
			AutoMeasFlag = 0;
			ManuMeasFlag = 1;
			ZeroMeasFlag = 0;
			break;
		case EVENT_LEFT_CLICK_UP:
			PlcData[16 + sig] = 0;
			break;
*/
	}
	return 0;
}

int CVICALLBACK Cb_Manual_4 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 3;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Manual Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_manual, TAB_MANU_MANU_TIMER_4);
			SetCtrlAttribute(tab_manual, TAB_MANU_MANU_TIMER_4, ATTR_ENABLED, 1);
			break;
			
		case EVENT_COMMIT:
			PlcData[16 + sig] = 1;
			MeasCycleNo = 0;
			AutoMeasFlag = 0;
			ManuMeasFlag = 1;
			ZeroMeasFlag = 0;
			break;	
/*		case EVENT_LEFT_CLICK:
			PlcData[16 + sig] = 1;
			MeasCycleNo = 0;
			AutoMeasFlag = 0;
			ManuMeasFlag = 1;
			ZeroMeasFlag = 0;
			break;
		case EVENT_LEFT_CLICK_UP:
			PlcData[16 + sig] = 0;
			break;
*/
	}
	return 0;
}

int CVICALLBACK Cb_Timer_Manu_1 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 0;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			ManuMeasFinish(sig);
			break;
	}
	return 0;
}
int CVICALLBACK Cb_Timer_Manu_2 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 1;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			ManuMeasFinish(sig);
			break;
	}
	return 0;
}
int CVICALLBACK Cb_Timer_Manu_3 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 2;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			ManuMeasFinish(sig);
			break;
	}
	return 0;
}
int CVICALLBACK Cb_Timer_Manu_4 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 3;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			ManuMeasFinish(sig);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Manu_Table (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	Point	point;
	Rect	rect;
	int 	i;
	char 	fmt[10] = {0,},
			temp1[32] = {0,};
	
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			ModeID = 1;
			
			GetRelativeMouseState(panel, 0, &rect.left, &rect.top, 0, 0, 0);
			GetTableCellFromPoint(panel, control, MakePoint (rect.left, rect.top), &point);
			
			if(point.y - 1 < 0)
				return 0;
		
			ManuItemSelected = point.y - 1;
			ClearListCtrl(tab_manual, TAB_MANU_ITEM_VALUE);
			SetCtrlVal(tab_manual, TAB_MANU_ITEM, Model[ManuItemSelected].Name);
			
			if(Mc[McID].Mode[ModeID].CycleIndex <= 0)
				return 0;
			
			for(i = Mc[McID].Mode[ModeID].StartDataNo ; i <= Mc[McID].Mode[ModeID].CycleIndex ; i++)
			{
				if(i == Mc[McID].Mode[ModeID].EndDataNo)	break;
				if(i >= MAX_MEAS_CYCLE)
					i = 1;

				sprintf(fmt, "%%.%df", Model[ManuItemSelected].Unit);
				sprintf(temp1, fmt , Mc[McID].Mode[ModeID].ResultValue[ManuItemSelected][i]);

				InsertListItem (tab_manual, TAB_MANU_ITEM_VALUE, -1, temp1, 0); 
			} 

			GetNumListItems (tab_manual, TAB_MANU_ITEM_VALUE, &i);
			if(i > 0)
				SetCtrlIndex (tab_manual, TAB_MANU_ITEM_VALUE, i-1);			

			break;
	}
	return 0;
}

int CVICALLBACK Cb_ManualSave (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	char 	name[1024] 	= {0,},
			temp[1024] 	= {0,},
			temp1[128] 	= {0,},
			Path[1024] 	= {0,},
			fmt[10]		= {0,};
	int 	handle, i, j;	
	
	switch (event)
	{
		case EVENT_COMMIT:

			sprintf(name, "%s_%s_save.csv", ModelName[ModelNo], CurrDate);
	
			sprintf(Path, "%s", Path_Result);

			i = FileSelectPopup (Path, name, "*.csv",
									  "Save Manual Test Data",
									  VAL_SAVE_BUTTON, 0, 1, -1, 1,
									  temp);

			//	1  VAL_EXISTING_FILE_SELECTED
			//	2  VAL_NEW_FILE_SELECTED
       		if( i == 1 || i == 2 ) // file selected
       		{
				handle = OpenFile (temp, VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII);

				// Model Name
				sprintf(temp, "Model,%s,", ModelName[ModelNo]);
				WriteLine (handle, temp, -1);
	
				// MeasPoints Num
		        sprintf(temp, "Point_Num,%i,", MeasPoints);   
				WriteLine (handle, temp, -1);

    			// Meas Item Names
			    sprintf(temp, "%s,", "NAME");
		        for( i = 0; i < MeasPoints; i++)
		        {
					sprintf(temp1, "%s,", Model[i].Name);
					strcat(temp, temp1);
		        }
 
				// Time
				sprintf(temp1, "%s,", "Time");
				strcat(temp, temp1); 
				
				// Marking Data
				sprintf(temp1, "%s,", "MARKING");
			    strcat(temp, temp1);
				
				WriteLine (handle, temp, -1);

				// Unit
			    sprintf(temp, "%s,", "UNIT");
				for(i = 0 ; i < MeasPoints ; i ++)								
				{
					sprintf(temp1, "%d,", Model[i].Unit);
			 		strcat(temp, temp1);	 
				}
				WriteLine (handle, temp, -1);
				
				// UCL
				sprintf(temp, "%s,", "UCL");
				for(i = 0 ; i < MeasPoints ; i ++)								
				{
					sprintf(fmt, "%%.%df,", Model[i].Unit);
					sprintf(temp1, fmt, Model[i].UCL);
					strcat(temp, temp1);
				}
				WriteLine (handle, temp, -1);
				
				//LCL
			    sprintf(temp, "%s,", "LCL");
				for(i = 0 ; i < MeasPoints ; i ++)								
				{
					sprintf(fmt, "%%.%df,", Model[i].Unit);
					sprintf(temp1, fmt, Model[i].LCL);
					strcat(temp, temp1);
				}
				WriteLine (handle, temp, -1);
				
				for(j = Mc[McID].Mode[ModeID].StartDataNo; j <= Mc[McID].Mode[ModeID].CycleIndex; j ++) 
				{
					if(j == Mc[McID].Mode[ModeID].EndDataNo)
						break;
					if(j >= MAX_MEAS_CYCLE)
						j = 1;

				    sprintf(temp, "%d,", j);
			        for(i = 0; i < MeasPoints ; i ++)
					{
						sprintf(fmt, "%%.%df", Model[i].Unit);
					    sprintf(temp1, fmt, Mc[McID].Mode[ModeID].ResultValue[i][j]);
						strcat(temp1, ",");
						strcat(temp, temp1);
					}
					
				    sprintf(temp1, "%s,", CurrTime);
					strcat(temp, temp1);
					
				  	WriteLine (handle, temp,-1);
				}
				
				CloseFile(handle);
			}
		break;
	}

	return 0;
}

int CVICALLBACK Cb_ManualDelete (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			Mc[0].Mode[1].CycleIndex = 0;
			Mc[0].Mode[1].StartDataNo = 1;
			Mc[0].Mode[1].EndDataNo = 1;
			
			ClearListCtrl(tab_manual, TAB_MANU_ITEM_VALUE);
			SetCtrlVal(tab_manual, TAB_MANU_TESTNO, 0);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Sol_Led (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	int 	i;
	char	temp[32] = {0,};
	switch (event)
	{
		case EVENT_LEFT_CLICK:
		case EVENT_COMMIT:
			GetCtrlAttribute(panel, control, ATTR_CONSTANT_NAME, temp);
			LogUpdate(temp);
			for(i = 0 ; i < MAX_SOL ; i ++)
			{
				if(strcmp(ManuSwLedCtrl[i], temp) == 0)
				{
					PlcData[SOL_START_NO + i] = 1;
				}
//				else
//				{
//					PlcData[SOL_START_NO + i] = 0;
//				}
			}
			break;
		case EVENT_LEFT_CLICK_UP:
//			for(i = 0 ; i < MAX_SOL ; i ++)
//				PlcData[SOL_START_NO + i] = 0;
			break;
	}
	return 0;
}



int CVICALLBACK Cb_Pc_Meas_Cycle (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ResetTimer(tab_manual, TAB_MANU_PC_MEAS_TIMER);
			SetCtrlAttribute(tab_manual, TAB_MANU_PC_MEAS_TIMER, ATTR_ENABLED, 1);
			SetCtrlAttribute(tab_manual, TAB_MANU_PC_MEAS_CYCLE, ATTR_DIMMED, 1);
			Pc_Cycle = 1;
			if(panel == tab_manual)
			{
				ManuMeasFlag = 1;
				ZeroMeasFlag = 0;
			}

			break;
	}
	return 0;
}

int CVICALLBACK Cb_Pc_Meas_Timer (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			if(Pc_Cycle == 1)
			{
				if(d_in[78] 			//측정 셔틀 후진 상태
						&& d_in[80] 	//측정 셔틀 상승 상태
						&& d_in[82] 	//측정 검사 리프트 상승 상태
						&& d_in[84] 	//프로브 복귀 상태
						&& d_in[86])	
				{
					PlcData[144] = 1;
					Pc_Cycle++;
				}
			}
			else if(Pc_Cycle == 2)
			{
				if(d_in[79] 			//측정 셔틀 전진 상태
						&& d_in[80] 	//측정 셔틀 상승 상태
						&& d_in[82] 	//측정 검사 리프트 상승 상태
						&& d_in[84] 	//프로브 복귀 상태
						&& d_in[86])	
				{
					PlcData[144] = 0;
					PlcData[145] = 1;
					Pc_Cycle++;
				}				
			}
			else if(Pc_Cycle == 3)
			{
				if(d_in[79] 			//측정 셔틀 전진 상태
						&& d_in[81] 	//측정 셔틀 하강 상태
						&& d_in[82] 	//측정 검사 리프트 상승 상태
						&& d_in[84] 	//프로브 복귀 상태
						&& d_in[86])	
				{
					PlcData[145] = 0;
					PlcData[146] = 1;
					Pc_Cycle++;
				}				
			}
			else if(Pc_Cycle == 4)
			{
				if(d_in[79] 			//측정 셔틀 전진 상태
						&& d_in[81] 	//측정 셔틀 하강 상태
						&& d_in[83] 	//측정 검사 리프트 하강 상태
						&& d_in[84] 	//프로브 복귀 상태
						&& d_in[86])	
				{
					PlcData[146] = 0;
					PlcData[147] = 1;
					PlcData[148] = 1;
					Pc_Cycle++;
				}				
			}
			else if(Pc_Cycle == 5)	//측정 타이밍
			{
				if(d_in[79] 			//측정 셔틀 전진 상태
						&& d_in[81] 	//측정 셔틀 하강 상태
						&& d_in[83] 	//측정 검사 리프트 하강 상태
						&& d_in[85] 	//프로브 동작 상태
						&& d_in[87])	
				{
					if(ManuMeasFlag)
						CallCtrlCallback(tab_manual, TAB_MANU_MANUAL_1, EVENT_RIGHT_DOUBLE_CLICK, 0, 0, NULL);
					else if(ZeroMeasFlag)
						CallCtrlCallback(tab_zeroset, TAB_ZERO_ZERO_1, EVENT_RIGHT_DOUBLE_CLICK, 0, 0, NULL);
					PlcData[146] = 0;
					PlcData[147] = 1;
					PlcData[148] = 1;
					Pc_Cycle++;
				}				
			}
			else if(Pc_Cycle == 6)	
			{
				if(d_in[79] 			//측정 셔틀 전진 상태
						&& d_in[81] 	//측정 셔틀 하강 상태
						&& d_in[83] 	//측정 검사 리프트 하강 상태
						&& d_in[85] 	//프로브 동작 상태
						&& d_in[87])	
				{
					PlcData[147] = 0;
					PlcData[148] = 0;
					PlcData[149] = 1;
					PlcData[150] = 1;
					Pc_Cycle++;
				}				
			}

			else if(Pc_Cycle == 7)	
			{
				if(d_in[79] 			//측정 셔틀 전진 상태
						&& d_in[81] 	//측정 셔틀 하강 상태
						&& d_in[83] 	//측정 검사 리프트 하강 상태
						&& d_in[84] 	//프로브 복귀 상태
						&& d_in[86])	
				{
					PlcData[149] = 0;
					PlcData[150] = 0;
					PlcData[151] = 1;
					Pc_Cycle++;
				}				
			}
			else if(Pc_Cycle == 8)	
			{
				if(d_in[79] 			//측정 셔틀 전진 상태
						&& d_in[81] 	//측정 셔틀 하강 상태
						&& d_in[82] 	//측정 검사 리프트 상승 상태
						&& d_in[84] 	//프로브 복귀 상태
						&& d_in[86])	
				{
					PlcData[151] = 0;
					PlcData[152] = 1;
					Pc_Cycle++;
				}				
			}
			else if(Pc_Cycle == 9)	
			{
				if(d_in[79] 			//측정 셔틀 전진 상태
						&& d_in[80] 	//측정 셔틀 상승 상태
						&& d_in[82] 	//측정 검사 리프트 상승 상태
						&& d_in[84] 	//프로브 복귀 상태
						&& d_in[86])	
				{
					PlcData[152] = 0;
					PlcData[153] = 1;
					Pc_Cycle++;
				}				
			}

			else if(Pc_Cycle == 10)	
			{
				if(d_in[78] 			//측정 셔틀 후진 상태
						&& d_in[80] 	//측정 셔틀 상승 상태
						&& d_in[82] 	//측정 검사 리프트 상승 상태
						&& d_in[84] 	//프로브 복귀 상태
						&& d_in[86])	
				{
					PlcData[153] = 0;
					Pc_Cycle = 0;
					SetCtrlAttribute(tab_manual, TAB_MANU_PC_MEAS_CYCLE, ATTR_DIMMED, 0);
					SetCtrlAttribute(tab_manual, TAB_MANU_PC_MEAS_TIMER, ATTR_ENABLED, 0);		
					if(PlcData[20])	//Repeat
					{
						CallCtrlCallback(tab_manual, TAB_MANU_PC_MEAS_CYCLE, EVENT_COMMIT, 0, 0, 0);
					}
				}				
			}

			break;
	}
	return 0;
}

int CVICALLBACK Cb_Pc_Meas_Cycle_2 (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			AutoMeasFlag = 0;
			ManuMeasFlag = 1;
			ZeroMeasFlag = 0;
			MeasChIndex[0] = 0 ;
			MeasSig[0] = 1;
			
			break;
		case EVENT_LEFT_CLICK_UP:
			MeasSig[0] = 0;
			
			ManuMeasFinish(0);
			
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Pc_Meas_Cycle_3 (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			AutoMeasFlag = 0;
			ManuMeasFlag = 0;
			ZeroMeasFlag = 1;
			MeasChIndex[0] = 0;
			MeasSig[0] = 1;
			
			break;
		case EVENT_LEFT_CLICK_UP:
			MeasSig[0] = 0;
			
			ZeroMeasFinish(0);

			break;
	}
	return 0;
}
