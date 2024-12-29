#include <userint.h>
#include "0_Main.h"
#include <rs232.h>
#include "A_Global.h"

int		PlcCallBackIng;
int		PlcCommRetryNum; // plc error check
char 	OutRes;

void 	CalcBcc(char *buff, char *sbcc)
{
	char	temp[8];
	int		i, bcc = 0;
	int		len = strlen(buff);
	
	if(Plc.maker == 0 && Plc.portNumber != 10)
	{
		for(i = 1; i < len; i ++)
			bcc += (int)buff[i];
	}
	else
	{
		for(i = 0; i < len; i ++)
			bcc += (int)buff[i];
	}
		
	sprintf(temp, "%04X", bcc);
	for(i = 0; i < 2; i ++)
		temp[i] = temp[i + 2];
	temp[2] = 0x00;
	
	strcat(buff, temp);
	strcpy(sbcc, temp);
}

void	PlcInCommSend(void)
{
	PlcReadFlag = 1;
	strcpy(PLCPortOutBuff, PlcCmdReadReq);
	ComWrt(Plc.portNumber, PLCPortOutBuff, strlen(PLCPortOutBuff));
}

void	PlcOutCommSend(void)
{
	int		i;
	char	temp[30];
	
	PlcReadFlag = 0;

	strcpy(PLCPortOutBuff, PlcCmdWriteReqHeader);
	for( i = 0; i < PlcWriteWordNo; i ++ )
	{
		sprintf(temp, "%04X", PlcWordOut[i]);
		strcat(PLCPortOutBuff, temp);
	}
	sprintf(temp, "%c", 0x04);
	strcat(PLCPortOutBuff, temp);
	ComWrt(Plc.portNumber, PLCPortOutBuff, strlen(PLCPortOutBuff));
}

void CVICALLBACK PLC_IO_Function (int portNo, int eventMask, void *callbackData)
{
	int		i, j;
	
	if(!WhileLoopFlag)
		return;
	
	PlcCallBackIng = 1;
	SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 0);
	
	j = GetInQLen(Plc.portNumber);
	if( j < 1 )
		return;
	
	ComRd(Plc.portNumber, PLCPortInBuff, j);
	
	if(PlcReadFlag)
	{
		if((PLCPortInBuff[0] == 0x06) && ( j >= PLCReadCMDReturnDataPosition + 4 * PlcReadWordNo))
		{
//			memcpy(temp, &PLCPortInBuff[PLCReadCMDReturnDataPosition], PlcReadWordNo * 4);
			PlcBuff(PLCPortInBuff);
			for( i = 0; i < PlcWriteWordNo; i++ )
			{
				if( PlcWordOut[i] != OldPlcWordOut[i] )
				{
					OutRes = 1;
					break;
				}
			}
		
   			if(OutRes)						   
   			{
   				OutRes = 0;
   				PlcOutCommSend();
   			}
   			else
			{
				PlcInCommSend();
			}
		
			PlcCommRetryNum = 0;
			PlcCommErr = 0;
		}
		else
		{
       		SleepFunc(100); 
			PlcInCommSend();
   			
   			PlcCommRetryNum++;
   			if(PlcCommRetryNum > 6)
   			{
				PlcCommErr = 1;
   			}
   		}
   	}
   	else
   	{
		if(PLCPortInBuff[0] != 0x06)
		{
       		SleepFunc(100);
   			PlcOutCommSend();
   			
   			PlcCommRetryNum++;
   			if(PlcCommRetryNum > 6)
   			{
				PlcCommErr = 1;
   			}
   		}
   		else
   		{
			PlcInCommSend();
 			
   			PlcCommRetryNum = 0;
			PlcCommErr = 0;
   		}
   	}
   	ResetTimer(mainpanel, MAIN_PLC_TIMER);
	SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 1);
	PlcCallBackIng = 0;
	return;
}

void	PlcOpen(void)
{
	int		ret;

	if(Plc.portNumber == 0)
	{
		MessagePopup ("Plc Port Error", "Plc Port Not Selected");
		PlcCommErr = 1;
		SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 0);
		return; 
	}
	
    /*  Open and Configure Com port */
    ret = 	OpenComConfig (Plc.portNumber, Plc.deviceName, Plc.baudRate, Plc.parity,
							Plc.dataBits, Plc.stopBits, Plc.inputQueueSize, Plc.outputQueueSize);
    if(ret) goto exit;
    
	ret = FlushInQ(Plc.portNumber);
	if(ret) goto exit;
	
	ret = FlushOutQ(Plc.portNumber);
	
exit:
	if(ret)
	{
		MessagePopup ("Plc. Port Error", "PLC Port Not Opened.");
		SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 0);
		PlcCommErr = 1;
	}
	else
	{
		InstallComCallback (Plc.portNumber, LWRS_RXFLAG, 0, 0x03, PLC_IO_Function, NULL); 
		PlcInCommSend();
		ResetTimer(mainpanel, MAIN_PLC_TIMER);
		SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 1);
		PlcCommErr = 0;
	}
	return;  						   	
}

void	PlcClose(void)
{
	CloseCom(Plc.portNumber);
}

void PlcInit(void)
{		
	char	temp[8] = {0,};

	//MELSEC
	if(Plc.maker == 0)	
	{
		//TCP-IP
		if(Plc.portNumber == 10)
		{
			sprintf(PlcCmdHeader, "%s%s%s%s%s", SubHeader, NetworkNo, PlcNo, ModuleNo, StationNo);		
			sprintf(PlcCmdRead, "%04X%s%s%s%s%04X", CpuTimer, ReadCommand, ReadSubCommand, ReadDeviceName, PlcAddressRead, PlcReadWordNo);		  
			sprintf(PlcCmdReadReq, "%s%04X%s", 	PlcCmdHeader, strlen(PlcCmdRead), PlcCmdRead); 			
		}
		//RS-232
		else
		{
			sprintf(PlcCmdReadReq, "%c%s%s%s%s%s%s%s%s%s%04X", 0x05, FrameIdentifier, StationNo, NetworkNo,
					PlcNo, SelfStation, ReadCommand, ReadSubCommand, ReadDeviceName, PlcAddressRead, PlcReadWordNo); 
			CalcBcc(PlcCmdReadReq,temp);
			sprintf(temp, "%c%c", 0x0D, 0x0A); 
			strcat(PlcCmdReadReq, temp);
	
			sprintf(PlcCmdWriteReqHeader, "%c%s%s%s%s%s%s%s%s%s%04X", 0x05, FrameIdentifier, StationNo, NetworkNo,
					PlcNo, SelfStation, WriteCommand, WriteSubCommand, WriteDeviceName, PlcAddressWrite, PlcWriteWordNo);
			PLCReadCMDReturnDataPosition = 11;
		}		
	}
	//LS
	else if(Plc.maker == 1)
	{
		sprintf(PlcCmdReadReq, "%c00RSB06%s%02X%c", 0x05, LsPlcAddressRead, PlcReadWordNo, 0x04); 
		sprintf(PlcCmdWriteReqHeader, "%c00WSB06%s%02X", 0x05, LsPlcAddressWrite, PlcWriteWordNo); 
		PLCReadCMDReturnDataPosition = 10;
	}
	
	if(Plc.portNumber == 10)
		PlcConnect();	
	else
		PlcOpen();
}

int CVICALLBACK Cb_Timer_Plc (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			if(Plc.portNumber == 10)
				PlcConnect();
			else
			{
				if( PlcCommErr )
				{
					SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 0);
					return 0;
				}

				int ret;
				if( PlcCallBackIng ) 	
				{
					ResetTimer (panel, control);
					return 0;
				}		
				ret = 	FlushInQ (Plc.portNumber);  
				if( ret == -2 || ret == -3 )
				{
					SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 0);
					return 0;
				}
				
				FlushOutQ (Plc.portNumber);
				
				SleepFunc(100); // 0.1초 지연
				PlcInCommSend();
				ResetTimer (panel, control);
			}
			break;
	}
	return 0;
}

void PlcBuff(char *buff)
{
	int	i, j, st = PlcWriteWordStNo * 16,
			  ed = PlcReadWordNo * 16;
	unsigned short 	ChkWord;
	char	temp[30];

	for(i = 0; i < PlcReadWordNo; i++)
	{
		strncpy(temp, &buff[i * 4 + PLCReadCMDReturnDataPosition], 4);
		temp[4] = 0x00;
		sscanf(temp, "%x", (int *)&PlcWordIn[i]);
		
		ChkWord = 1;
		for(j = 0; j < 16; j++)
		{
			if( PlcWordIn[i] & ChkWord )
				d_in[i * 16 + j] = 1;
			else
				d_in[i * 16 + j] = 0;
			ChkWord <<= 1;
		}
	}
	
	for(i = 0; i < PlcWriteWordNo; i++)
		OldPlcWordOut[i] = PlcWordIn[i + PlcWriteWordStNo];
	
	for( i = st; i < ed; i++ ) 
		d_out[i - st] = d_in[i];

	check_iomon();
}

void PlcEthernetTransmit(void)
{			
	int		i;
	char	temp[24];
	
	if(PlcWriteFlag)
	{
		sprintf(PlcCmdWrite, "%04X%s%s%s%s%04X",	CpuTimer,
													WriteCommand,
													WriteSubCommand,
													WriteDeviceName,
													PlcAddressWrite,
													PlcWriteWordNo);
		for(i = 0; i < PlcWriteWordNo; i ++)
		{
			sprintf(temp, "%04X", PlcWordOut[i]);
			strcat(PlcCmdWrite, temp);
		}
		sprintf(PlcCmdWriteReq, "%s%04X%s", PlcCmdHeader,
											strlen(PlcCmdWrite), 
											PlcCmdWrite);
		
		if (ClientTCPWrite(hPlcComm, PlcCmdWriteReq, strlen(PlcCmdWriteReq), 200) < 0)
		{
		    if (PlcConnectStatus)
		        DisconnectFromTCPServer(hPlcComm);
			PlcConnectStatus = 0;
		}
	}
	else	
	{
		if (ClientTCPWrite (hPlcComm, PlcCmdReadReq, strlen(PlcCmdReadReq), 200) < 0)
		{
		    if (PlcConnectStatus)
		        DisconnectFromTCPServer(hPlcComm);
			PlcConnectStatus = 0;
		}
	}
	
	ResetTimer (mainpanel, MAIN_PLC_TIMER);
	SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 1);
}

int CVICALLBACK PlcClient(unsigned handle, int event, int error, void *callbackData)
{
	char	temp[512], **endPoint = 0;
	int		endCode, dataLen, bytesToRead;
    char 	receiveBuf[512] = {0};
    ssize_t dataSize = sizeof(receiveBuf) - 1;

	switch (event)
	{
		case TCP_DATAREADY:
			if ((dataSize = ClientTCPRead(hPlcComm, receiveBuf, dataSize, 1000)) < 0)
			{
			    if (PlcConnectStatus)
			        DisconnectFromTCPServer(hPlcComm);
				PlcConnectStatus = 0;
				ResetTimer (mainpanel, MAIN_PLC_TIMER);
				SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 1);
			}
			else
			{			  
				// Data 4 Hex Bytes Of Buf[14] ~ Buf[17]
				CopyBytes(temp, 0, receiveBuf, 14, 4);
				temp[4] = '\0';
				dataLen = (int)strtol(temp, endPoint, 16);
				
				if(PlcWriteFlag)
					bytesToRead = PlcEndCodeLength;
				else
					bytesToRead = PlcEndCodeLength + PlcReadDataLength;
				
				if(dataLen == bytesToRead)
				{
					CopyBytes(temp, 0, receiveBuf, 18, PlcEndCodeLength);
					temp[4] = '\0';
					endPoint = 0;
					endCode = (int)strtol(temp, endPoint, 16);
					if(!endCode)	
					{
						memcpy(temp, &receiveBuf[PlcHeaderLength + PlcEndCodeLength], PlcReadDataLength);
						PlcBuff(temp);
 						PlcWriteFlag = !PlcWriteFlag;
					}
				}
				else
					PlcWriteFlag = 0;
				
				if(PlcConnectStatus)
					PlcEthernetTransmit();
			}
			break;
		case TCP_DISCONNECT:
		    if (PlcConnectStatus)
		        DisconnectFromTCPServer(hPlcComm);
			PlcConnectStatus = 0;

			ResetTimer (mainpanel, MAIN_PLC_TIMER);
			SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 1);
			break;
	}
	return 0;
}

void PlcConnect(void)
{
    SetWaitCursor (1);
    if (ConnectToTCPServer(&hPlcComm, Plc_TcpPort, Plc_TcpIp, PlcClient, NULL, 2000) < 0)
	{
		PlcConnectStatus = 0;
		LogUpdate("Plc Connect Fail");
		ResetTimer(mainpanel, MAIN_PLC_TIMER);
		SetCtrlAttribute (mainpanel, MAIN_PLC_TIMER, ATTR_ENABLED, 1);
	}
	else
    {
	    SetWaitCursor (0);
	    PlcConnectStatus = 1;
		LogUpdate("Plc Connect Success");
		PlcEthernetTransmit();
    }
}

void  calc_out_data(int bit, int set)
{
	div_t 	x;
	unsigned short 	mask_bit;
	int 	port_no, bit_no;

	x = div(bit, 16);
	port_no = x.quot;
	bit_no = x.rem;

	mask_bit = 0x01;
	mask_bit <<= bit_no;

	if(set)	PlcWordOut[port_no] |= mask_bit;
	else   	PlcWordOut[port_no] &= (~mask_bit);
}

int		PlcIoMap1[PlcDataInNo/2];
int		PlcIoMap2[PlcDataOutNo];

void  	check_iomon(void)
{
	int		i, j, a;
	double	CycleTime;
	char 	temp1[1024] = {0,};
	
	//Comm Status
	SetCtrlVal(mainpanel, MAIN_LED_PLC, d_in[0]);	
	PlcData[0] = d_in[0];
	
	//Meas Signal Reset
	for(i = 0 ; i < MAX_MEAS_SIG ; i ++)
	{
		if(d_out[16 + i])
			PlcData[16 + i] = 0;
	}
	
	//OP Signal Reset
	for(i = 7 ; i < 12 ; i ++)
	{
		if(d_out[i])
			PlcData[i] = 0;
	}
	
	//Light
	if(d_out[15])
		PlcData[15] = 0;
	
	//Mark Cycle Reset
	if(d_out[56])			
		PlcData[56] = 0;
	
	//OP Selected In
	for(i = 0 ; i < 7 ; i ++)
	{
		SetCtrlIndex(mainpanel, MAIN_ST_AUTO + i, d_in[5+i]);
		if(d_in[9])	// RESET
		{
			PlcData[38] = 0;	// Auto Mastering
			PlcData[39] = 0;	// Continuous Ng Alarm
			SetCtrlAttribute(tab_auto, TAB_AUTO_CONTINUOUS_TXT, ATTR_VISIBLE, 0);
		}
		if(d_in[10]) // EMERGENCY
		{	
			SetCtrlAttribute(tab_manual, TAB_MANU_PC_MEAS_TIMER, ATTR_ENABLED, 0);
			SetCtrlAttribute(tab_manual, TAB_MANU_PC_MEAS_CYCLE, ATTR_DIMMED, 0);
			Pc_Cycle = 0;
			PlcData[144] = 0;
			PlcData[145] = 0;
			PlcData[146] = 0;
			PlcData[147] = 0;
			PlcData[148] = 0;
			PlcData[149] = 0;
			PlcData[150] = 0;
			PlcData[151] = 0;
			PlcData[152] = 0;
			PlcData[153] = 0;
		}
	}
//	if(d_in[15] != def_in[15])
		SetCtrlIndex(mainpanel, MAIN_ST_LIGHT, d_in[15]);
	
	//Screen Change Signal
	if(d_in[1] != def_in[1] && d_in[1])	CallCtrlCallback(mainpanel, MAIN_BT_AUTO, 		EVENT_COMMIT, 0, 0, NULL);
	if(d_in[2] != def_in[2] && d_in[2])	CallCtrlCallback(mainpanel, MAIN_BT_MANUAL, 	EVENT_COMMIT, 0, 0, NULL);
	if(d_in[3] != def_in[3] && d_in[3])	CallCtrlCallback(mainpanel, MAIN_BT_ZEROSET,	EVENT_COMMIT, 0, 0, NULL);
	
	if(d_in[5] != def_in[5])
	{
		SetCtrlAttribute(mainpanel, MAIN_POP_MODEL, ATTR_DIMMED, d_in[5]);
		SetCtrlAttribute(mainpanel, MAIN_POP_SETUP, ATTR_DIMMED, d_in[5]);
		SetCtrlAttribute(mainpanel, MAIN_POP_RESULT, ATTR_DIMMED, d_in[5]);		
		SetTabPageAttribute(mainpanel, MAIN_TAB, 1, ATTR_DIMMED, d_in[5]);	//MANUAL
		SetTabPageAttribute(mainpanel, MAIN_TAB, 2, ATTR_DIMMED, d_in[5]);	//ZEROSET
	}
		
	//Auto Meas Flag
	if(d_in[5] != def_in[5] && d_in[5])
	{
		AutoMeasFlag = 1;
		ManuMeasFlag = 0;
		ZeroMeasFlag = 0;
	}	
		
	PlcData[12] = AmpCommErr;
	PlcData[13] = !MarkConnectStatus;
	
	//Manual Sol
	for(i = 0 ; i < MAX_SOL ; i ++)
	{
		if(d_out[SOL_START_NO + i])
			PlcData[SOL_START_NO + i] = 0;
	}
	
	//Pc Data Out To PLC
	for(i = 0 ; i < PlcDataOutNo ; i ++)
		PlcDataT[i] = PlcData[i];
	
	for(i = 0 ; i < PlcDataOutNo ; i ++)
		calc_out_data(i, PlcDataT[i]);
	
	//Manual
//	if(TabPage == 1)
	{
		for(i = 0 ; i < MAX_SOL ; i ++)
		{
		//	SetCtrlVal(tab_manual, ManuLedHome[i], d_in[64+0+(i*2)]);
		//	SetCtrlVal(tab_manual, ManuLedAct[i],  d_in[64+1+(i*2)]);
			SetCtrlVal(tab_manual, ManuSwLed[i],  d_in[SOL_START_NO+i]);
			if(d_in[SOL_START_NO+i])
			{
				SetCtrlAttribute(tab_manual, ManuSwLed[i], ATTR_LABEL_COLOR, VAL_BLACK);
				SetCtrlAttribute(tab_manual, ManuSwLed[i], ATTR_ON_COLOR, 0x0000FFFF);
			}
			else
			{
				SetCtrlAttribute(tab_manual, ManuSwLed[i], ATTR_LABEL_COLOR, VAL_WHITE);
			}
		}
	}
	
	//Meas Request Sig
	for(i = 0 ; i < MAX_MEAS_SIG ; i ++)
	{
		if(d_in[16 + i] != def_in[16 + i])
		{
			if(d_in[16 + i])
			{
				//Manual
				if(ManuMeasFlag)
				{
					sprintf(temp1, "Manual Measuring Request Sig %d ON", i+1);
					LogUpdate(temp1);
					CallCtrlCallback(tab_manual, TAB_MANU_MANUAL_1 + i, EVENT_RIGHT_DOUBLE_CLICK, 0, 0, NULL);
				}
				//AUTO
				else
				{
					sprintf(temp1, "Auto Measuring Request Sig %d ON", i+1);
					LogUpdate(temp1);
					CallCtrlCallback(tab_auto, TAB_AUTO_MEAS_1 + i, EVENT_RIGHT_DOUBLE_CLICK, 0, 0, NULL);
				}
			}
		}
	}	

	//Meas Request Sig
	for(i = 0 ; i < MAX_MEAS_SIG ; i ++)
	{
		if(d_in[20 + i] != def_in[20 + i])
		{
			if(d_in[20 + i])
			{
				if(ZeroMeasFlag)
				{
					sprintf(temp1, "Zeroset Measuring Request Sig %d ON", i+1);
					LogUpdate(temp1);
					CallCtrlCallback(tab_zeroset, TAB_ZERO_ZERO_1 + i, EVENT_RIGHT_DOUBLE_CLICK, 0, 0, NULL);
				}
			}
		}
	}
	
	//Initialization Station Data
	for(i = 0 ; i < MAX_MEAS_SIG ; i ++)
	{
		if(d_in[24 + i] != def_in[24 + i])
		{
			InitStData(i);
		}
	}
	
	//Data Shift
	if(d_in[36] != def_in[36])
	{
		if(d_in[36])
			;
	}
		
	//Marking Start
	if(d_in[37] != def_in[37])
	{
		if(d_in[37])
		{
			LogUpdate("Marking Start");
			SendDataMark(1, "");
			MarkStartFlag = 1;
		}
	}
	
	if(d_in[40])
		McNo2 = 0;
	else if(d_in[41])
		McNo2 = 1;
	else if(d_in[42])
		McNo2 = 2;
	else if(d_in[43])
		McNo2 = 3;
	else
		McNo2 = 0;
	
	if(d_in[44])
		McNo1 = 0;
	else if(d_in[45])
		McNo1 = 1;
	else if(d_in[34])
		McNo1 = 2;
	else if(d_in[35])
		McNo1 = 3;
	else
		McNo1 = 0;
	
	if(d_in[40] != def_in[40])		SetCtrlVal(tab_auto, TAB_AUTO_LED_MC_1, d_in[40]); //201
	if(d_in[41] != def_in[41])		SetCtrlVal(tab_auto, TAB_AUTO_LED_MC_2, d_in[41]); //202
	if(d_in[42] != def_in[42])		SetCtrlVal(tab_auto, TAB_AUTO_LED_MC_3, d_in[42]); //203
	if(d_in[43] != def_in[43])		SetCtrlVal(tab_auto, TAB_AUTO_LED_MC_4, d_in[43]); //204
	if(d_in[44] != def_in[44])		SetCtrlVal(tab_auto, TAB_AUTO_LED_MC_5, d_in[44]); //101
	if(d_in[45] != def_in[45])		SetCtrlVal(tab_auto, TAB_AUTO_LED_MC_6, d_in[45]); //102
	if(d_in[34] != def_in[34])		SetCtrlVal(tab_auto, TAB_AUTO_LED_MC_7, d_in[34]); //103
	if(d_in[35] != def_in[35])		SetCtrlVal(tab_auto, TAB_AUTO_LED_MC_8, d_in[35]); //104
	
	if(d_out[241] != def_out[241])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_1_M, d_out[241]);
	if(d_out[243] != def_out[243])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_1_P, d_out[243]);
	if(d_out[246] != def_out[246])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_2_M, d_out[246]);
	if(d_out[248] != def_out[248])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_2_P, d_out[248]);
	if(d_out[251] != def_out[251])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_3_M, d_out[251]);
	if(d_out[253] != def_out[253])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_3_P, d_out[253]);
	if(d_out[256] != def_out[256])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_4_P, d_out[256]);
	if(d_out[258] != def_out[258])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_4_M, d_out[258]);
	if(d_out[261] != def_out[261])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_5_M, d_out[261]);
	if(d_out[263] != def_out[263])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_5_P, d_out[263]);
	if(d_out[266] != def_out[266])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_6_M, d_out[266]);
	if(d_out[268] != def_out[268])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_6_P, d_out[268]);
	if(d_out[271] != def_out[271])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_7_M, d_out[271]);
	if(d_out[273] != def_out[273])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_7_P, d_out[273]);
	if(d_out[276] != def_out[276])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_8_M, d_out[276]);
	if(d_out[278] != def_out[278])	SetCtrlVal(tab_auto, TAB_AUTO_LED_IF_8_P, d_out[278]);
	
	//MANUAL 제품감지 센서 LAMP
	if(d_in[216] != def_in[216])		SetCtrlVal(tab_manual, TAB_MANU_LED_SENSOR_1, d_in[216]); 
	if(d_in[217] != def_in[217])		SetCtrlVal(tab_manual, TAB_MANU_LED_SENSOR_2, d_in[217]);
	if(d_in[218] != def_in[218])		SetCtrlVal(tab_manual, TAB_MANU_LED_SENSOR_3, d_in[218]);
	
	//IO
	if(TabPage == 6)
	{
		for(i = 0 ; i < PlcDataInNo ; i ++)
		{
			if(i < PlcDataInNo/2)
				PlcIoMap1[i] = d_in[i];
			else
				PlcIoMap2[i - PlcDataInNo/2] = d_in[i];
		}
	
		SetTableCellRangeVals(tab_io, TAB_IO_TABLE_INPUT,  MakeRect(1, 2, 320, 1), PlcIoMap1, VAL_COLUMN_MAJOR);
		SetTableCellRangeVals(tab_io, TAB_IO_TABLE_OUTPUT, MakeRect(1, 2, 320, 1), PlcIoMap2, VAL_COLUMN_MAJOR);
	}
	
	// Cycle Time Display
	a = 0x01;
	for(i = 0, CycleTime = 0; i < 16; i ++)
	{
		if(d_in[224 + i])	
			CycleTime += a;
		a <<= 1;
	}
	SetTableCellVal(mainpanel, MAIN_TESTNO, MakePoint(5, 2), (CycleTime*0.1));
	
	j = (int)(Opt_Time_1 * 10.0);
	a = 0x01;
	for(i = 0 ; i < 16 ; i ++)
	{
		if(j & a)	PlcData[112+i] = 1;
		else 		PlcData[112+i] = 0;
		a <<= 1;
	}
	
	a = 0;
	for(i = 0 ; i < MAX_PLC_ERR ; i ++) 
	{
		if(d_in[240 + i] ) 
		{
			PlcErr[i] = 1;
			if(!def_in[240 + i])
			{
				sprintf(temp1, "%s ON", PlcErrStr[i]);
				LogUpdate(temp1);
			}
			a++;
		}
		else
		{
			PlcErr[i] = 0;
			if(def_in[240 + i])
			{
				sprintf(temp1, "%s OFF", PlcErrStr[i]);
				LogUpdate(temp1);
			}
		}
	}
	
	if(a > 0)
	{
		GetCtrlAttribute(mainpanel, MAIN_TIMER_ALARM, ATTR_ENABLED, &i);
		if(i == 0)	//ENABLE - FALSE
		{
			SetCtrlAttribute(mainpanel, MAIN_TIMER_ALARM, ATTR_ENABLED, 1);
		}
	}
	else
	{
		SetCtrlAttribute(mainpanel, MAIN_ALARM, ATTR_VISIBLE, 0);
		SetCtrlAttribute(mainpanel, MAIN_BT_HISTORY, ATTR_TEXT_COLOR, VAL_BLACK);	
		SetCtrlAttribute(mainpanel, MAIN_TIMER_ALARM, ATTR_ENABLED, 0);
		ResetTimer(mainpanel, MAIN_TIMER_ALARM);
	}
	
	for( i = 0; i < PlcDataInNo; i++ )
	{
		if( d_in[i] != def_in[i] )
			def_in[i] = d_in[i];
		
		if( i < PlcDataOutNo )
		{
			if( d_out[i] != def_out[i])
				def_out[i] = d_out[i];
		}
	}	
}
