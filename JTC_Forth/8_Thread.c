#include "windows.h"
#include "A_Global.h"

void	SleepFunc(int a)
{
	Sleep(a);	
}

void	ThreadInit(void)
{
	SetSleepPolicy(VAL_SLEEP_MORE);
	CmtNewThreadPool(5, &poolHandle);
	CmtScheduleThreadPoolFunction (poolHandle, ThreadFunc, NULL, &ThreadFuncId);
//	CmtScheduleThreadPoolFunction (poolHandle, ThreadLog, NULL, &ThreadLogId);
	CmtScheduleThreadPoolFunction (poolHandle, ThreadMeas, NULL, &ThreadMeasId);
}

int CVICALLBACK ThreadFunc (void *Data)
{
	while(WhileLoopFlag)
	{
		SleepFunc(2);
		if(TabPage == 1)
		{
			SetTableCellRangeVals(tab_manual, TAB_MANU_TABLE_CH_1, MakeRect(1, 1, 1, MAX_CH_PER_AMP), ChData_1, VAL_ROW_MAJOR);
			SetTableCellRangeVals(tab_manual, TAB_MANU_TABLE_CH_2, MakeRect(1, 1, 1, MAX_CH_PER_AMP), ChData_2, VAL_ROW_MAJOR);
		}
	}
	return 0;
}
int CVICALLBACK ThreadLog (void *Data)
{
	while(WhileLoopFlag)
	{
		SleepFunc(2);

	}
	return 0;
}
int CVICALLBACK ThreadMeas (void *Data)
{
	int j;
	while(WhileLoopFlag)
	{
		SleepFunc(2);
	
		if(ZeroMeasFlag)	//ZERO
		{
			if(MeasSig[0])	for(j = 0; j < MAX_CH; j ++)	MeasChValue[MeasChIndex[0]][j] = ChData[j];
			if(MeasSig[1])	for(j = 0; j < MAX_CH; j ++) 	MeasChValue[MeasChIndex[1]][j] = ChData[j];
			if(MeasSig[2])	for(j = 0; j < MAX_CH; j ++) 	MeasChValue[MeasChIndex[2]][j] = ChData[j];
			if(MeasSig[3])	for(j = 0; j < MAX_CH; j ++) 	MeasChValue[MeasChIndex[3]][j] = ChData[j];
			
			SetCtrlVal(tab_zeroset, TAB_ZERO_LED_ZERO_1, MeasSig[0]);
			SetCtrlVal(tab_zeroset, TAB_ZERO_LED_ZERO_2, MeasSig[1]);
			SetCtrlVal(tab_zeroset, TAB_ZERO_LED_ZERO_3, MeasSig[2]);
			SetCtrlVal(tab_zeroset, TAB_ZERO_LED_ZERO_4, MeasSig[3]);
		}
		else			//AUTO, MANUAL
		{
			if(MeasSig[0])	for(j = 0; j < MAX_CH; j ++)	MeasChValue[MeasChIndex[0]][j] = ChData[j] - ZeroValueNow[j];
			if(MeasSig[1])	for(j = 0; j < MAX_CH; j ++) 	MeasChValue[MeasChIndex[1]][j] = ChData[j] - ZeroValueNow[j];
			if(MeasSig[2])	for(j = 0; j < MAX_CH; j ++) 	MeasChValue[MeasChIndex[2]][j] = ChData[j] - ZeroValueNow[j];
			if(MeasSig[3])	for(j = 0; j < MAX_CH; j ++) 	MeasChValue[MeasChIndex[3]][j] = ChData[j] - ZeroValueNow[j];

			SetCtrlVal(tab_manual, TAB_MANU_LED_MANU_1, MeasSig[0]);
			SetCtrlVal(tab_manual, TAB_MANU_LED_MANU_2, MeasSig[1]);
			SetCtrlVal(tab_manual, TAB_MANU_LED_MANU_3, MeasSig[2]);
			SetCtrlVal(tab_manual, TAB_MANU_LED_MANU_4, MeasSig[3]);
			
			SetCtrlVal(mainpanel, MAIN_LED_MEAS, MeasSig[0] || MeasSig[1] || MeasSig[2] || MeasSig[3]);
		}
		
		if(MeasSig[0])	
		{
			MeasChIndex[0] ++;
			if( MeasChIndex[0] >= MAX_CH_CYCLE )	MeasChIndex[0] --;
		}
		if(MeasSig[1])	
		{
			MeasChIndex[1] ++;
			if( MeasChIndex[1] >= MAX_CH_CYCLE )	MeasChIndex[1] --;
		}
		if(MeasSig[2])	
		{
			MeasChIndex[2] ++;
			if( MeasChIndex[2] >= MAX_CH_CYCLE )	MeasChIndex[2] --;
		}
		if(MeasSig[3])	
		{
			MeasChIndex[3] ++;
			if( MeasChIndex[3] >= MAX_CH_CYCLE )	MeasChIndex[3] --;
		}

		SetCtrlVal(mainpanel, MAIN_LED_MEAS, MeasSig[0] || MeasSig[1] || MeasSig[2] || MeasSig[3]);
	}
	return 0;
}
