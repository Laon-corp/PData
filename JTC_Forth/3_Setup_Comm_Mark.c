#include <rs232.h>
#include "A_Global.h"

short CalCRC(char *data, unsigned char len)
{
	short		icrc, temp;
	unsigned	char i, j;
	
	icrc = 0x0000;
	
	for(i = 0 ; i < len ; i ++)
	{
		if(icrc == 0x00 && data[0] == 0)
		{
			icrc = 0x0000;
		}
		else
		{
			temp = ((short)data[i]) << 8;
			for(j = 0 ; j < 8 ; j ++)
			{
				if(((temp ^ icrc) & 0x8000))
				{
					icrc = ((icrc^0x0810) << 1) | 0x0001;
				}
				else
				{
					icrc <<= 1;
				}
				temp <<= 1;
			}
		}
	}
	return icrc;
}

int		SendDataMark(int type, char* data)
{
	char	temp1[128] = {0,};
	char	temp2[128] = {0,};
	char	temp3[128] = {0,};
	char 	Bytes[2];
	short 	i = 0;
	
    switch(type)
    {				  
		case 0:	//reset
			sprintf(temp1, "%c%c%c%c%c", 0x10, 0x02, 0x07, 0x00, 0x01);
			i = CalCRC(temp1, 5);
			Bytes[0] = i >> 8;		//High Byte
			Bytes[1] = i & 0x00FF;	//Low Byte
			sprintf(temp2, "%c%c", Bytes[0], Bytes[1]);
			CopyBytes(temp1, 5, temp2, 0, 2);
			ComWrt(Mark.portNumber, temp1, 7);
			break;
     
      	case 1: //Start
			sprintf(temp1, "%c%c%c%c%c", 0x10, 0x02, 0x07, 0x00, 0x31);
			i = CalCRC(temp1, 5);
			Bytes[0] = i >> 8;		//High Byte
			Bytes[1] = i & 0x00FF;	//Low Byte
			sprintf(temp2, "%c%c", Bytes[0], Bytes[1]);
			CopyBytes(temp1, 5, temp2, 0, 2);
			ComWrt(Mark.portNumber, temp1, 7);
			break;
			
		case 2: //TRANSMIT FILE
			// cmd + data + parameter
			i = 7 + strlen(data) + 52 + 2;
			sprintf(temp1, "%c%c%c%c%c", 0x10, 0x02, i, 0x00, 0x3B);

			i = (short)(Couth.CharHeight * 10.0);
			Bytes[0] = i >> 8;		//High Byte
			Bytes[1] = i & 0x00FF;	//Low Byte
			sprintf(temp2, "%c%c", Bytes[1], Bytes[0]);
			CopyBytes(temp1, 5, temp2, 0, 2);
			
			i = Couth.CharWidth;
			sprintf(temp2, "%c", i);
			CopyBytes(temp1, 7, temp2, 0, 1);
			
			GetLabelFromIndex(model_tab_Mark, TABPANEL_3_MARK_PARA_3, Couth.Font, temp2);
			StringUpperCase(temp2);
			strcat(temp2, ".FNT");
			for(i = 0 ; i < 12 ; i ++)
			{
				if(i < strlen(temp2))
					sprintf(temp3, "%c", temp2[i]);
				else
					sprintf(temp3, "%c", 0x00);
				
				CopyBytes(temp1, 8 + i, temp3, 0, 1);
			}

			i = Couth.Spacing;
			sprintf(temp2, "%c", i);
			CopyBytes(temp1, 20, temp2, 0, 1);			
			
			i = Couth.Density;
			sprintf(temp2, "%c", i);
			CopyBytes(temp1, 21, temp2, 0, 1);			
			
			i = (short)(Couth.Xcoo * 10.0);
			Bytes[0] = i >> 8;		//High Byte
			Bytes[1] = i & 0x00FF;	//Low Byte
			sprintf(temp2, "%c%c", Bytes[1], Bytes[0]);
			CopyBytes(temp1, 22, temp2, 0, 2);
			
			i = (short)(Couth.Ycoo * 10.0);
			Bytes[0] = i >> 8;		//High Byte
			Bytes[1] = i & 0x00FF;	//Low Byte
			sprintf(temp2, "%c%c", Bytes[1], Bytes[0]);
			CopyBytes(temp1, 24, temp2, 0, 2);
		
			i = (short)(Couth.Zcoo * 10.0);
//			Bytes[0] = i >> 8;		//High Byte
//			Bytes[1] = i & 0x00FF;	//Low Byte
			Bytes[0] = 0xFF;		//High Byte
			Bytes[1] = 0xFF;		//Low Byte
			sprintf(temp2, "%c%c", Bytes[1], Bytes[0]);
			CopyBytes(temp1, 26, temp2, 0, 2);	
	
			i = (short)(Couth.Angle * 10.0);	
			Bytes[0] = i >> 8;		//High Byte
			Bytes[1] = i & 0x00FF;	//Low Byte
			sprintf(temp2, "%c%c", Bytes[1], Bytes[0]);
			CopyBytes(temp1, 28, temp2, 0, 2);	
	
			i = (short)(Couth.Diameter * 10.0);	
			Bytes[0] = i >> 8;		//High Byte
			Bytes[1] = i & 0x00FF;	//Low Byte
			sprintf(temp2, "%c%c", Bytes[1], Bytes[0]);
			CopyBytes(temp1, 30, temp2, 0, 2);	

			i = Couth.Con;
			sprintf(temp2, "%c", i);
			CopyBytes(temp1, 32, temp2, 0, 1);	
			
			i = Couth.Hmirror;
			sprintf(temp2, "%c", i);
			CopyBytes(temp1, 33, temp2, 0, 1);	

			i = Couth.Vmirror;
			sprintf(temp2, "%c", i);
			CopyBytes(temp1, 34, temp2, 0, 1);	

			i = Couth.Speed;
			sprintf(temp2, "%c", i);
			CopyBytes(temp1, 35, temp2, 0, 1);	

			i = Couth.Force;
			sprintf(temp2, "%c", i);
			CopyBytes(temp1, 36, temp2, 0, 1);	
			
			for(i = 0 ; i < 20 ; i ++)
			{
				sprintf(temp2, "%c", 0xFF);
				CopyBytes(temp1, 37+i, temp2, 0, 1);			
			}

			for(i = 0 ; i < strlen(data) ; i ++)
			{
				sprintf(temp2, "%c", data[i]);
				CopyBytes(temp1, 57+i, temp2, 0, 1);			
			}
			
			Bytes[0] = 0x0B;		//High Byte
			Bytes[1] = 0x0A;		//Low Byte
			sprintf(temp2, "%c%c", Bytes[1], Bytes[0]);
			CopyBytes(temp1, 57 + strlen(data), temp2, 0, 2);	
			
			i = CalCRC(temp1, 59 + strlen(data));
			Bytes[0] = i >> 8;		//High Byte
			Bytes[1] = i & 0x00FF;	//Low Byte
			sprintf(temp2, "%c%c", Bytes[0], Bytes[1]);
			CopyBytes(temp1, 59 + strlen(data), temp2, 0, 2);
			ComWrt(Mark.portNumber, temp1, 59 + strlen(data) + 2);
			break;
	}
	return 0;
}

void 	CVICALLBACK Mark_Cb_Function (int portNo, int eventMask, void *callbackData)
{
	char	temp1[1024] = {0,};
	int 	cnt = 0;
	
	SleepFunc(50);
	
	cnt = GetInQLen(portNo);
	ComRd(portNo, temp1, cnt);
	LogUpdate(temp1);
	
	//ACK	10 00 07 00 00 81 CA	- Transmit File
	//ACK	10 00 07 00 00 81 CA	- Start COMMAND
	//		10 00 08 00 32 00 FC B0 - Marking Finish x 4
	if(strchr(temp1, 0xFF) == NULL)	//ACK
	{
		if(MarkStartFlag)
		{
			if(temp1[0] == 16 && temp1[1] == 0 && temp1[2] == 8 && temp1[3] == 0 &&
				temp1[4] == 50 && temp1[5] == 0 && temp1[6] == -4 && temp1[7] == -80)
			{
				PlcData[37] = 1;
				MarkStartFlag = 0;
				LogUpdate("Marking Finish");
			}
		}
		else
		{
			LogUpdate("Mark ack");
		}
	}
	else							//NACK
	{
		LogUpdate("Mark nack");
	}
	
	
	return;
}

void 		MarkInit(void)
{
	int ret;
	
	if(Mark.portNumber == 0)	//no select
	{
		MessagePopup ("Mark Port Error", "Mark Port Not Selected");
		MarkConnectStatus = 0;
		return; 
	}

	//  Open and Configure Com port
	ret = OpenComConfig(Mark.portNumber, "", Mark.baudRate, Mark.parity, 
						Mark.dataBits, Mark.stopBits, Mark.inputQueueSize, Mark.outputQueueSize);
	if(ret)	goto exit;
	
	//  Turn off Hardware handshaking (loopback test will not function with it on) 
	ret = SetCTSMode (Mark.portNumber, 0);
	if(ret) goto exit;
	
	ret = SetXMode(Mark.portNumber, 0);
	if(ret) goto exit;

	ret = FlushInQ(Mark.portNumber);
	if(ret) goto exit;
	
	ret = FlushOutQ(Mark.portNumber);
	
exit:
	if(ret)		//not open
	{
		MessagePopup ("Mark Port Error", "Mark Port Not Opened.");
		MarkConnectStatus = 0;
	}
	else
	{
		InstallComCallback (Mark.portNumber, LWRS_RXFLAG, 0, 0x10 , Mark_Cb_Function, NULL);		
//		InstallComCallback (Mark.portNumber, LWRS_RECEIVE, 7, 0x10 , Mark_Cb_Function, NULL);
		MarkConnectStatus = 1;
	}
	SetCtrlVal(mainpanel, MAIN_LED_MARK, MarkConnectStatus);

	return;  
}

void	MarkClose(void)
{
	CloseCom(Mark.portNumber);
}

void	MakeMarkData(void)
{
	char 	DateTemp[20] = {0,};
	char 	Y[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char	M[12] = "ABCDEFGHIJKL";
	char	D[31] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ12345";
	int 	itemp = 0;
	char 	Ytemp[10] = {0,},
			Mtemp[10] = {0,},
			Dtemp[10] = {0,};
	
	memset(MarkStr, 0, sizeof(MarkStr));
	strcpy(DateTemp, CurrDate);
	
	//format
	//J Y M D D/N
	//JSD01D
	if(CurrShift)	//Night
	{
		if(strncmp(CurrTime, DayStartTime, 4) < 0)	//Before Date 
			GetBeforeDate(DateTemp);
	}

	//Y
	CopyBytes(Ytemp, 0, DateTemp, 0, 4);
	Ytemp[4] = 0x00;
	itemp = atoi(Ytemp) - 2001;	// 2001 - A
	itemp %= 26;
	sprintf(Ytemp, "%c", Y[itemp]);
	
	//M
	CopyBytes(Mtemp, 0, DateTemp, 5, 2);
	Mtemp[2] = 0x00;
	itemp = atoi(Mtemp) - 1;		// 0/1 Base Check
	sprintf(Mtemp, "%c", M[itemp]);

	//D
	CopyBytes(Dtemp, 0, DateTemp, 8, 2);
	Dtemp[2] = 0x00;
	itemp = atoi(Dtemp);		// 0/1 Base Check
//	sprintf(Dtemp, "%c", M[itemp]);
	sprintf(Dtemp, "%02d", itemp);
	
	if(!ByPassFlag[2])	//Marking Bypass
	{
		if(CurrShift)	sprintf(MarkStr, "J%s%s%sN", Ytemp, Mtemp, Dtemp);
		else			sprintf(MarkStr, "J%s%s%sD", Ytemp, Mtemp, Dtemp);		
	}
	else
		sprintf(MarkStr, "BYPASS");
	
	SetCtrlVal(tab_auto, TAB_AUTO_MARK_DATA_1, MarkStr);

	//마킹기 추가시 주석 해제
	/*if(!ByPassFlag[2])	//Marking Bypass
		SendDataMark(2, MarkStr); */
}

void	MakeMarkDataTest(void)
{
	char 	DateTemp[20] = {0,};
	char 	Y[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char	M[12] = "ABCDEFGHIJKL";
	char	D[31] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ12345";
	int 	itemp = 0;
	char 	Ytemp[10] = {0,},
			Mtemp[10] = {0,},
			Dtemp[10] = {0,},
			ctemp[4] = {0,};
	char 	temp1[24] = {0,};
	
	memset(temp1, 0, sizeof(temp1));
	strcpy(DateTemp, CurrDate);
	
	//format
	//J Y M D D/N
	//JSD01D
	if(CurrShift)	//Night
	{
		if(strncmp(CurrTime, DayStartTime, 4) < 0)	//Before Date 
			GetBeforeDate(DateTemp);
	}

	//Y
	CopyBytes(Ytemp, 0, DateTemp, 0, 4);
	Ytemp[4] = 0x00;
	itemp = atoi(Ytemp) - 2001;	// 2001 - A
	itemp %= 26;
	sprintf(Ytemp, "%c", Y[itemp]);
	
	//M
	CopyBytes(Mtemp, 0, DateTemp, 5, 2);
	Mtemp[2] = 0x00;
	itemp = atoi(Mtemp) - 1;		// 0/1 Base Check
	sprintf(Mtemp, "%c", M[itemp]);

	//D
	CopyBytes(Dtemp, 0, DateTemp, 8, 2);
	Dtemp[2] = 0x00;
	itemp = atoi(Dtemp);		// 0/1 Base Check
//	sprintf(Dtemp, "%c", M[itemp]);
	sprintf(Dtemp, "%02d", itemp);
	
	if(!ByPassFlag[2])	//Marking Bypass
	{
		GetCtrlVal(model_tab_Mark, TABPANEL_3_TEXT_1, ctemp);
		if(CurrShift)	sprintf(temp1, "%s%s%s%sN", ctemp, Ytemp, Mtemp, Dtemp);
		else			sprintf(temp1, "%s%s%s%sD", ctemp, Ytemp, Mtemp, Dtemp);		
	}
	else
		sprintf(temp1, "BYPASS");
	
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_STR, temp1);

	if(!ByPassFlag[2])	//Marking Bypass
		SendDataMark(2, temp1);
}