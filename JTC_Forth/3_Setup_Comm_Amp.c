#include <rs232.h>
#include "A_Global.h"

int ParaCtrl[8] =    {	CALPANEL_CAL_PARA_1, CALPANEL_CAL_PARA_2, CALPANEL_CAL_PARA_3, CALPANEL_CAL_PARA_4,
				    	CALPANEL_CAL_PARA_5, CALPANEL_CAL_PARA_6, CALPANEL_CAL_PARA_7, CALPANEL_CAL_PARA_8};

int Master1Ctrl[8] = {	CALPANEL_MASTER1_1, CALPANEL_MASTER1_2, CALPANEL_MASTER1_3, CALPANEL_MASTER1_4,
						CALPANEL_MASTER1_5, CALPANEL_MASTER1_6, CALPANEL_MASTER1_7, CALPANEL_MASTER1_8};

int Master2Ctrl[8] = {	CALPANEL_MASTER2_1, CALPANEL_MASTER2_2, CALPANEL_MASTER2_3, CALPANEL_MASTER2_4,
						CALPANEL_MASTER2_5, CALPANEL_MASTER2_6, CALPANEL_MASTER2_7, CALPANEL_MASTER2_8};

int OpsetCtrl[8] =   {	CALPANEL_OPSET_DATA_1, CALPANEL_OPSET_DATA_2, CALPANEL_OPSET_DATA_3, CALPANEL_OPSET_DATA_4,
						CALPANEL_OPSET_DATA_5, CALPANEL_OPSET_DATA_6, CALPANEL_OPSET_DATA_7, CALPANEL_OPSET_DATA_8};

int	LowDataCtrl[8] = {  CALPANEL_LOW_DATA_1, CALPANEL_LOW_DATA_2, CALPANEL_LOW_DATA_3, CALPANEL_LOW_DATA_4,
						CALPANEL_LOW_DATA_5, CALPANEL_LOW_DATA_6, CALPANEL_LOW_DATA_7, CALPANEL_LOW_DATA_8};

int	CalDataCtrl[8] = {  CALPANEL_CAL_DATA_1, CALPANEL_CAL_DATA_2, CALPANEL_CAL_DATA_3, CALPANEL_CAL_DATA_4,
						CALPANEL_CAL_DATA_5, CALPANEL_CAL_DATA_6, CALPANEL_CAL_DATA_7, CALPANEL_CAL_DATA_8};

int	CalCtrl1[8] = 	{  CALPANEL_CAL1_1, CALPANEL_CAL2_1, CALPANEL_CAL3_1, CALPANEL_CAL4_1,
						CALPANEL_CAL5_1, CALPANEL_CAL6_1, CALPANEL_CAL7_1, CALPANEL_CAL8_1};

int	CalCtrl2[8] = 	{  CALPANEL_CAL1_2, CALPANEL_CAL2_2, CALPANEL_CAL3_2, CALPANEL_CAL4_2,
						CALPANEL_CAL5_2, CALPANEL_CAL6_2, CALPANEL_CAL7_2, CALPANEL_CAL8_2};

char *CalBtnName1[8] = { "CAL1.1", "CAL2.1", "CAL3.1", "CAL4.1", "CAL5.1", "CAL6.1", "CAL7.1", "CAL8.1"};
char *CalBtnName2[8] = { "CAL1.2", "CAL2.2", "CAL3.2", "CAL4.2", "CAL5.2", "CAL6.2", "CAL7.2", "CAL8.2"};
	
int		CalRunFlag[8];
double	Cal_ChData[2];

int CVICALLBACK Cb_Timer_Amp (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	if( AmpCallBackIng )	
	{
	   	ResetTimer(mainpanel, MAIN_AMP_TIMER);
		return 0;
	}
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			LogUpdate("Amp Error Timer");
			AmpTimerRunFlag = 1;
			AmpCommErr = TRUE;

			SetCtrlVal(mainpanel, MAIN_LED_AMP, 0);
			
			SleepFunc(100);
			if(!AmpPortOpenErr )
				RestAmp();

		   	ResetTimer(mainpanel, MAIN_AMP_TIMER);
			AmpTimerRunFlag = 0;
			break;
	}
	return 0;
}

int RestAmp(void) 
{
	if( !WhileLoopFlag )
    	return 0;
    	
	AmpIndex = 0; // 첫번째 앰프다.
	
	FlushInQ(Amp.portNumber);
	FlushOutQ(Amp.portNumber);

//	ComWrtByte (Amp.portNumber, OneOrd);
//	ComWrtByte (Amp.portNumber, OneChar);
//	ComWrtByte (Amp.portNumber, EndAmpOrder);
	//HS
	ComWrtByte (Amp.portNumber, 0x44);	//D
	ComWrtByte (Amp.portNumber, 0x64);	//d
	ComWrtByte (Amp.portNumber, 0x30);	//0
	ComWrtByte (Amp.portNumber, EndAmpOrder);//CR
	AmpRunFlag = 1;
	return 0;
}

void CVICALLBACK 	Amp_Callback_Func (int portNo, int eventMask, void *callbackData)
{				   
	char 	buffer[34];
	int 	i, j, chno;
	unsigned char temp1, temp2;

	if( AmpParaReadIng || AmpTimerRunFlag)	
		return;  
	
	j = GetInQLen(Amp.portNumber);
	if( j < bytePerAmp )
	{
		if( j > 0 )
		{
			ComRd(Amp.portNumber, buffer, j);
			if( AmpRunFlag )
				RestAmp();
		}
		return; 
	}
	
	AmpCallBackIng = 1;
	
	ComRd(Amp.portNumber, buffer, bytePerAmp);
	
	if( !AmpRunFlag || !WhileLoopFlag )
	{
		AmpCallBackIng = 0;
		return;
	}
  
	for( j = 0; j < MAX_CH_PER_AMP; j ++ )
	{				
		temp1 = *(buffer + j * 2); 
		temp2 = *(buffer + j * 2 + 1);
		GAUGE[AmpIndex][j] = temp1 * 256 + temp2;
		if(GAUGE[AmpIndex][j] > 32767) 
			GAUGE[AmpIndex][j] -= 65536;
	}

	for(j = 0; j < MAX_CH_PER_AMP; j ++)
	{
		chno = AmpIndex * MAX_CH_PER_AMP + j;
		if(chno < MAX_CH)
		{
			ChData[chno] = (double)(GAUGE[AmpIndex][j] * CAL_PARA[AmpIndex][j] / 10.0) + Opset[AmpIndex][j];
			if(chno < MAX_CH_PER_AMP)
				ChData_1[j] = ChData[chno];
			else
				ChData_2[j] = ChData[chno];
		}
		else
			break;
	}
			
	AmpIndex ++;

	if(numAmp > 1 && AmpIndex < numAmp )
	{
		ComWrtByte(Amp.portNumber, OneOrd);
		ComWrtByte(Amp.portNumber, OneChar + AmpIndex);
		ComWrtByte(Amp.portNumber, EndAmpOrder); 
	}
	else
	{
		if( ActivePanel == calpanel ) 
		{
			GetCtrlIndex (calpanel, CALPANEL_AMP_NO, &Amp_Value);			

			for(i = 0; i < 8; i ++)
			{
				SetCtrlVal(calpanel, CalDataCtrl[i], ChData[Amp_Value * 8 + i]);
				SetCtrlVal(calpanel, LowDataCtrl[i], GAUGE[Amp_Value][i] / 10.0);
			}
		}

		AmpCommErr = FALSE;
   		RestAmp(); 
  

	}

   	ResetTimer(mainpanel, MAIN_AMP_TIMER);
	SetCtrlVal(mainpanel, MAIN_LED_AMP, 1);
	SetCtrlVal(calpanel, CALPANEL_LED_AMP, 1);
	
	AmpCallBackIng = 0;
	return; 
}

void CVICALLBACK 	Amp_Callback_Func_HS (int portNo, int eventMask, void *callbackData)
{				   
	char 	buffer[512]= {0,};
	int 	i, j;
	char	cmd[4] = {"D0"};
	char 	cdata[16][8] = {0,};
	

	if( AmpParaReadIng || AmpTimerRunFlag)	
		return;  
	
	j = GetInQLen(Amp.portNumber);
	ComRd(Amp.portNumber, buffer, j);
	i = FindPattern(buffer, 0, 2, cmd, 1, 0);
	
	if(i != 0)
	{
		if( AmpRunFlag )
			RestAmp();
		return; 
	}
	
	AmpCallBackIng = 1;
	
	if( !AmpRunFlag || !WhileLoopFlag )
	{
		AmpCallBackIng = 0;
		return;
	}
  
	for( i = 0 ; i < 16 ; i ++ )
	{				
		CopyBytes(cdata[i], 0, buffer, 2 + (i*8), 7);
		ChData[i] = atof(cdata[i]);
		if( i < 8 )
			ChData_1[i] = ChData[i];
		else
			ChData_2[i-8] = ChData[i];
	}
	
	//SetTableCellRangeVals(tab_manual, TAB_MANU_TABLE_CH_1, MakeRect(1, 1, 1, MAX_CH_PER_AMP), ChData_1, VAL_ROW_MAJOR);
	//SetTableCellRangeVals(tab_manual, TAB_MANU_TABLE_CH_2, MakeRect(1, 1, 1, MAX_CH_PER_AMP), ChData_2, VAL_ROW_MAJOR);

	AmpCommErr = FALSE;
	RestAmp(); 

   	ResetTimer(mainpanel, MAIN_AMP_TIMER);
	SetCtrlVal(mainpanel, MAIN_LED_AMP, 1);
	SetCtrlVal(calpanel, CALPANEL_LED_AMP, 1);
	
	AmpCallBackIng = 0;
	return; 
}

  
int GetAmpParameter(void)    
{
    int 	i, loopcnt, count; 
    int 	quNum;
    char 	Buffer[60] = "0";
    int 	Err = 0;
    
    FlushInQ(Amp.portNumber);
	FlushOutQ(Amp.portNumber);
 
	AmpParaReadIng = 1;
    for(i = 0 ; i < numAmp; ++i)
    {  
		ComWrtByte(Amp.portNumber, N_AmpParOrder);		   
		ComWrtByte(Amp.portNumber, OneChar + i);		
		ComWrtByte(Amp.portNumber, EndAmpOrder); 
		
		count = 0;
		loopcnt = 0; 
		do
		{
			if( !WhileLoopFlag )
				return 0;
			
			quNum = GetInQLen(Amp.portNumber);
			
			if( quNum < 0 )
				goto ErrPos;
			
			if(quNum > 0)
			{  
				if((count + quNum) > N_BytePerPar)
					goto ErrPos;
				
				ComRd( Amp.portNumber, (Buffer+count), quNum );
				count += quNum;
			}
			
			loopcnt++;
			
			SleepFunc(30); 
			if(loopcnt > MAXLOOP) 
				
				goto ErrPos;
			
		}	while( quNum || (count != N_BytePerPar) ); 
		
	}
	
	goto	OkPos;
	
ErrPos:
	loopcnt =0;
	Err = 1;
	AmpParaReadFlag = 0;
	AmpParaReadIng = 0;
	return	Err;
	
OkPos:
	AmpParaReadFlag = 1;
	AmpParaReadIng = 0;
	SetCtrlVal(mainpanel, MAIN_LED_AMP,1);
	return Err; 
}  

int CVICALLBACK ThreadAmp(void *functionData)
{
	#define EventChar	 13             // CR 문자
	#define Eventchar2   10				// LF
	
    SetSleepPolicy(VAL_SLEEP_SOME);

	//InstallComCallback(Amp.portNumber,  LWRS_RECEIVE, bytePerAmp, EventChar, Amp_Callback_Func, NULL); 	
	//InstallComCallback(Amp.portNumber,  LWRS_RXFLAG, bytePerAmp, 0x0A, Amp_Callback_Func_HS, NULL); 
	InstallComCallback(Amp.portNumber,  LWRS_RXFLAG, 132, 0x0A, Amp_Callback_Func_HS, NULL); 

	
	return 0;
}

int	AmpPortOpen(void)  
{
	int	ret;
	
	SetCtrlAttribute (mainpanel, MAIN_AMP_TIMER, ATTR_ENABLED, FALSE);
	
	if(Amp.portNumber == 0 )
	{
		MessagePopup ("Amp Port Not Selected", "Amp Port Not Selected.");
		AmpPortOpenErr = 1;

		return -1; 
	}
	
	ret = OpenComConfig(Amp.portNumber, Amp.deviceName, Amp.baudRate, Amp.parity,
						Amp.dataBits, Amp.stopBits, Amp.inputQueueSize, Amp.outputQueueSize);
							
    if(ret) goto exit;
    
	ret = FlushInQ(Amp.portNumber);
	if(ret) goto exit;
	
	ret = FlushOutQ(Amp.portNumber);
	
exit:
	if(ret)
	{
		MessagePopup ("Amp. Port Error", "Amp. Port Not Opened.");
		AmpPortOpenErr = 1;
		AmpCommErr = 1;
	}
	else	
	{
		CmtScheduleThreadPoolFunction(poolHandle, ThreadAmp, (void *)0, &ThreadAmpId);
		AmpPortOpenErr = 0;
		AmpCommErr = 0;
		RestAmp();
	}
	
	return ret;  
}
			

void AmpPortClose(void)
{ 
//	CmtReleaseThreadPoolFunctionID (poolHandle, ThreadAmpId);
	CloseCom(Amp.portNumber); 
}

void	AmpStart(char flag)
{
	if( flag ) 
	{
		if( !AmpPortOpenErr && !AmpRunFlag )
		{
			AmpRunFlag = 1;
			if( !AmpParaReadFlag )
			{
				GetAmpParameter(); 
			}			
					
			RestAmp();
			
	   		ResetTimer(mainpanel, MAIN_AMP_TIMER);
			SetCtrlAttribute (mainpanel, MAIN_AMP_TIMER, ATTR_ENABLED, TRUE);
   		}
	}
	else 	
	{
		if( MeasSig[0] )
		{
			AmpRunFlag = 0;
			SetCtrlAttribute (mainpanel, MAIN_AMP_TIMER, ATTR_ENABLED, FALSE);
		}
	}
}

