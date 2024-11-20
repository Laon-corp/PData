#include "A_Global.h"


int		CalRunFlag[8];
double	Cal_ChData[2];

int CVICALLBACK Cb_CalPanel (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int i = 0;
			
			for(i = 0 ; i < MAX_CH_PER_AMP ; i ++)
			{
				GetCtrlVal(calpanel, CALPANEL_MASTER1_1 + i,	&CAL_MASTER1[Amp_Value][i]);
				GetCtrlVal(calpanel, CALPANEL_MASTER2_1 + i,	&CAL_MASTER2[Amp_Value][i]);
				GetCtrlVal(calpanel, CALPANEL_CAL_PARA_1 + i,	&CAL_PARA[Amp_Value][i]);
				GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_1 + i,	&Opset[Amp_Value][i]);				
			}
			
			SaveCali();
			
			RemovePopup(0);
			HidePanel(panel);
			break;
	}
	return 0;
}

int CVICALLBACK Amp_No (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			
			for(i = 0; i < 8 ; i ++)
			{
				GetCtrlVal(calpanel, CALPANEL_MASTER1_1	+ i,	&CAL_MASTER1[Amp_Value][i]);
				GetCtrlVal(calpanel, CALPANEL_MASTER2_1 + i,	&CAL_MASTER2[Amp_Value][i]);
				GetCtrlVal(calpanel, CALPANEL_CAL_PARA_1 + i,	&CAL_PARA[Amp_Value][i]);
				GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_1 + i,	&Opset[Amp_Value][i]);
			}
			
			GetCtrlIndex (calpanel, CALPANEL_AMP_NO, &Amp_Value);			
			if(Amp_Value >= numAmp)
				Amp_Value = 0;
			
			SetCtrlIndex (calpanel, CALPANEL_AMP_NO, Amp_Value);			
			
			for(i = 0; i < 8 ; i ++)
			{
				SetCtrlVal(calpanel, CALPANEL_MASTER1_1	+ i,	CAL_MASTER1[Amp_Value][i]);
				SetCtrlVal(calpanel, CALPANEL_MASTER2_1 + i,	CAL_MASTER2[Amp_Value][i]);
				SetCtrlVal(calpanel, CALPANEL_CAL_PARA_1 + i,	CAL_PARA[Amp_Value][i]);
				SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_1 + i, Opset[Amp_Value][i]);
			}
			
			break;
	}
	return 0;
}

int CVICALLBACK Calibration_Master1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		i;
	char 	CalBtnName1[8][8] = { "1.1", "2.1", "3.1", "4.1", "5.1", "6.1", "7.1", "8.1"}; 
	
	switch (event)
	{
		case EVENT_COMMIT:
			for(i = 0; i < 8; i ++)
			{
				CalRunFlag[i] = FALSE;
				SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1 + i, ATTR_LABEL_TEXT, CalBtnName1[i]);
			}
			GetCtrlIndex ( calpanel, CALPANEL_AMP_NO, &Amp_Value);			
			
  			switch(control)
			{
				case CALPANEL_CAL1_1 :	
					if(!CalRunFlag[0])
					{
						GetCtrlVal(calpanel, CALPANEL_MASTER1_1, &CAL_MASTER1[Amp_Value][0]);
						GetCtrlVal(calpanel, CALPANEL_MASTER2_1, &CAL_MASTER2[Amp_Value][0]);

						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT, "Proceeding");
						CalRunFlag[0] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_1, &Cal_ChData[0]);
					}
					break;

				case CALPANEL_CAL2_1 :	
					if(!CalRunFlag[1])
					{
						GetCtrlVal(calpanel, CALPANEL_MASTER1_2, &CAL_MASTER1[Amp_Value][1]);
						GetCtrlVal(calpanel, CALPANEL_MASTER2_2, &CAL_MASTER2[Amp_Value][1]);
						
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT, "Proceeding");
						CalRunFlag[1] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_2, &Cal_ChData[0]);
					}
					break;

				case CALPANEL_CAL3_1 :	
					if(!CalRunFlag[2])
					{
						GetCtrlVal(calpanel, CALPANEL_MASTER1_3, &CAL_MASTER1[Amp_Value][2]);
						GetCtrlVal(calpanel, CALPANEL_MASTER2_3,& CAL_MASTER2[Amp_Value][2]);

						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT, "Proceeding");
						CalRunFlag[2] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_3, &Cal_ChData[0]);
					}
					break;

				case CALPANEL_CAL4_1 :	
					if(!CalRunFlag[3])
					{
						GetCtrlVal(calpanel, CALPANEL_MASTER1_4, &CAL_MASTER1[Amp_Value][3]);
						GetCtrlVal(calpanel, CALPANEL_MASTER2_4, &CAL_MASTER2[Amp_Value][3]);

						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT, "Proceeding");
						CalRunFlag[3] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_4, &Cal_ChData[0]);
					}
			 		break;

				case CALPANEL_CAL5_1 :	
					if(!CalRunFlag[4])
					{
						GetCtrlVal(calpanel, CALPANEL_MASTER1_5,&CAL_MASTER1[Amp_Value][4]);
						GetCtrlVal(calpanel, CALPANEL_MASTER2_5,&CAL_MASTER2[Amp_Value][4]);
					
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"Proceeding");
						CalRunFlag[4] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_5, &Cal_ChData[0]);
					}
					break;

				case CALPANEL_CAL6_1 :	
					if(!CalRunFlag[5])
					{
						GetCtrlVal(calpanel, CALPANEL_MASTER1_6, &CAL_MASTER1[Amp_Value][5]);
						GetCtrlVal(calpanel, CALPANEL_MASTER2_6, &CAL_MASTER2[Amp_Value][5]);
						
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT, "Proceeding");
						CalRunFlag[5] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_6, &Cal_ChData[0]);
					}
					break;

				case CALPANEL_CAL7_1 :	
					if(!CalRunFlag[6])
					{
						GetCtrlVal(calpanel, CALPANEL_MASTER1_7, &CAL_MASTER1[Amp_Value][6]);
						GetCtrlVal(calpanel, CALPANEL_MASTER2_7, &CAL_MASTER2[Amp_Value][6]);
						
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT, "Proceeding");
						CalRunFlag[6] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_7, &Cal_ChData[0]);
					}
					break;

				case CALPANEL_CAL8_1 :	
					if(!CalRunFlag[7])
					{
						GetCtrlVal(calpanel, CALPANEL_MASTER1_8, &CAL_MASTER1[Amp_Value][7]);
						GetCtrlVal(calpanel, CALPANEL_MASTER2_8, &CAL_MASTER2[Amp_Value][7]);
						
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT, "Proceeding");
						CalRunFlag[7] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_8, &Cal_ChData[0]);
					}
					break;
			}
			break;


	}
	return 0;

}


int CVICALLBACK Calibration_Master2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	char 	CalBtnName1[8][8] = { "1.1", "2.1", "3.1", "4.1", "5.1", "6.1", "7.1", "8.1"}; 
	
	switch (event)
	{
		case EVENT_COMMIT:
			for(i = 0; i < 8; i ++)
			{
			//	CalRunFlag[i] = FALSE;
				SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1 + i, ATTR_LABEL_TEXT, CalBtnName1[i]);
			}
			GetCtrlIndex ( calpanel, CALPANEL_AMP_NO, &Amp_Value);			
	
			switch(control)
			{
				case CALPANEL_CAL1_2 :	
					if(CalRunFlag[0])
					{
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_1, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][0] = (CAL_MASTER1[Amp_Value][0] - CAL_MASTER2[Amp_Value][0])
													/ (Cal_ChData[0] - Cal_ChData[1]) * 1000.0;
						SetCtrlVal(calpanel, CALPANEL_CAL_PARA_1, CAL_PARA[Amp_Value][0]);

						Opset[Amp_Value][0] = CAL_MASTER2[Amp_Value][0] * 1000.0 - (Cal_ChData[1] * CAL_PARA[Amp_Value][0]);
						SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_1, Opset[Amp_Value][0]);
					}
					break;

				case CALPANEL_CAL2_2 :	
					if(CalRunFlag[1])
					{
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_2, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][1] = (CAL_MASTER1[Amp_Value][1] - CAL_MASTER2[Amp_Value][1])
													/ (Cal_ChData[0] - Cal_ChData[1]) * 1000.0;
						SetCtrlVal(calpanel, CALPANEL_CAL_PARA_2, CAL_PARA[Amp_Value][1]);
						Opset[Amp_Value][1] = CAL_MASTER2[Amp_Value][1] * 1000.0 - (Cal_ChData[1] * CAL_PARA[Amp_Value][1]);
						SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_2, Opset[Amp_Value][1]);
					}
					break;

				case CALPANEL_CAL3_2 :	
					if(CalRunFlag[2])
					{
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_3, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][2] = (CAL_MASTER1[Amp_Value][2] - CAL_MASTER2[Amp_Value][2])
													/ (Cal_ChData[0] - Cal_ChData[1]) * 1000;
						SetCtrlVal(calpanel, CALPANEL_CAL_PARA_3, CAL_PARA[Amp_Value][2]);
						Opset[Amp_Value][2] = CAL_MASTER2[Amp_Value][2] * 1000.0 - (Cal_ChData[1] * CAL_PARA[Amp_Value][2]);
						SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_3, Opset[Amp_Value][2]);
					}
					break;

				case CALPANEL_CAL4_2 :	
					if(CalRunFlag[3])
					{
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_4, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][3] = (CAL_MASTER1[Amp_Value][3] - CAL_MASTER2[Amp_Value][3])
													/ (Cal_ChData[0] - Cal_ChData[1]) * 1000.0;
						SetCtrlVal(calpanel, CALPANEL_CAL_PARA_4, CAL_PARA[Amp_Value][3]);
						Opset[Amp_Value][3] = CAL_MASTER2[Amp_Value][3] * 1000.0 - (Cal_ChData[1] * CAL_PARA[Amp_Value][3]);
						SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_4, Opset[Amp_Value][3]);
					}
					break;

				case CALPANEL_CAL5_2 :	
					if(CalRunFlag[4])
					{
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_5, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][4] = (CAL_MASTER1[Amp_Value][4] - CAL_MASTER2[Amp_Value][4])
													/ (Cal_ChData[0] - Cal_ChData[1]) * 1000.0;
						SetCtrlVal(calpanel, CALPANEL_CAL_PARA_5,CAL_PARA[Amp_Value][4]);
						Opset[Amp_Value][4] = CAL_MASTER2[Amp_Value][4] * 1000.0 - (Cal_ChData[1] * CAL_PARA[Amp_Value][4]);
						SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_5, Opset[Amp_Value][4]);
					}
					break;

				case CALPANEL_CAL6_2 :	
					if(CalRunFlag[5])
					{
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_6, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][5] = (CAL_MASTER1[Amp_Value][5] - CAL_MASTER2[Amp_Value][5])
													/ (Cal_ChData[0] - Cal_ChData[1]) * 1000.0;
						SetCtrlVal(calpanel, CALPANEL_CAL_PARA_6, CAL_PARA[Amp_Value][5]);
						Opset[Amp_Value][5] = CAL_MASTER2[Amp_Value][5] * 1000.0 - (Cal_ChData[1] * CAL_PARA[Amp_Value][5]);
						SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_6, Opset[Amp_Value][5]);
					}
					break;

				case CALPANEL_CAL7_2 :	
					if(CalRunFlag[6])
					{
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_7, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][6] = (CAL_MASTER1[Amp_Value][6] - CAL_MASTER2[Amp_Value][6])
													/ (Cal_ChData[0] - Cal_ChData[1]) * 1000.0;
						SetCtrlVal(calpanel, CALPANEL_CAL_PARA_7, CAL_PARA[Amp_Value][6]);
						Opset[Amp_Value][6] = CAL_MASTER2[Amp_Value][6] * 1000.0 - (Cal_ChData[1] * CAL_PARA[Amp_Value][6]);
						SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_7, Opset[Amp_Value][6]);
					}
					break;

				case CALPANEL_CAL8_2 :	
					if(CalRunFlag[7])
					{
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_8, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][7] = (CAL_MASTER1[Amp_Value][7] - CAL_MASTER2[Amp_Value][7])
													/ (Cal_ChData[0] - Cal_ChData[1]) * 1000.0;
						SetCtrlVal(calpanel, CALPANEL_CAL_PARA_8, CAL_PARA[Amp_Value][7]);
						Opset[Amp_Value][7] = CAL_MASTER2[Amp_Value][7] * 1000.0 - (Cal_ChData[1] * CAL_PARA[Amp_Value][7]);
						SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_8, Opset[Amp_Value][7]);
					}
					break;
			}
		break;
	}
	return 0;
}


int CVICALLBACK Update1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			switch(control)
			{
				case CALPANEL_UPDATE_1 :	
					GetCtrlVal(calpanel, CALPANEL_CAL_PARA_1,&CAL_PARA[Amp_Value][0]);
					GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_1,&Opset[Amp_Value][0]);
				break;
				case CALPANEL_UPDATE_2 :	
					GetCtrlVal(calpanel, CALPANEL_CAL_PARA_2,&CAL_PARA[Amp_Value][1]);
					GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_2,&Opset[Amp_Value][1]);
				break;
				case CALPANEL_UPDATE_3 :	
					GetCtrlVal(calpanel, CALPANEL_CAL_PARA_3,&CAL_PARA[Amp_Value][2]);
					GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_3,&Opset[Amp_Value][2]);
				break;
				case CALPANEL_UPDATE_4 :	
					GetCtrlVal(calpanel, CALPANEL_CAL_PARA_4,&CAL_PARA[Amp_Value][3]);
					GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_4,&Opset[Amp_Value][3]);
				break;
				case CALPANEL_UPDATE_5 :	
					GetCtrlVal(calpanel, CALPANEL_CAL_PARA_5,&CAL_PARA[Amp_Value][4]);
					GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_5,&Opset[Amp_Value][4]);
				break;
				case CALPANEL_UPDATE_6 :	
					GetCtrlVal(calpanel, CALPANEL_CAL_PARA_6,&CAL_PARA[Amp_Value][5]);
					GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_6,&Opset[Amp_Value][5]);
				break;
				case CALPANEL_UPDATE_7 :	
					GetCtrlVal(calpanel, CALPANEL_CAL_PARA_7,&CAL_PARA[Amp_Value][6]);
					GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_7,&Opset[Amp_Value][6]);
				break;
				case CALPANEL_UPDATE_8 :	
					GetCtrlVal(calpanel, CALPANEL_CAL_PARA_8,&CAL_PARA[Amp_Value][7]);
					GetCtrlVal(calpanel, CALPANEL_OPSET_DATA_8,&Opset[Amp_Value][7]);
					break;
			}
		break;
	}
	return 0;
}


int CVICALLBACK Cb_Panel_Cali (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	int i;
	
	switch (event)
	{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;

 			AmpStart(1);
			SetCtrlIndex ( calpanel, CALPANEL_AMP_NO, 0);
			
			GetCtrlIndex ( calpanel, CALPANEL_AMP_NO, &Amp_Value);
			for(i = 0 ; i < MAX_CH_PER_AMP ; i ++)
			{
				SetCtrlVal(calpanel, CALPANEL_MASTER1_1 + i, CAL_MASTER1[Amp_Value][i]);
				SetCtrlVal(calpanel, CALPANEL_MASTER2_1 + i, CAL_MASTER2[Amp_Value][i]);
				SetCtrlVal(calpanel, CALPANEL_CAL_PARA_1 + i, CAL_PARA[Amp_Value][i]);
				SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_1 + i, Opset[Amp_Value][i]);
			}
			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
	}
	return 0;
}

void	SaveCali(void)
{
	char 	Path[1024] = {0,};
	char	temp1[1024] = {0,};
	int		handle, i, j;
	
	sprintf(Path, "%s\\Setup_Calibration.ini", Path_Setup);
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR CALIBRATION", "CHECK PROGRAM SETUP");
	else
	{
		for(i = 0 ; i < MAX_AMP ; i ++)
		{
			for(j = 0 ; j < MAX_CH_PER_AMP ; j ++)
			{
				sprintf(temp1, "%d\t%f\t%f\t%f\t%f",
						i * MAX_CH_PER_AMP + j + 1, CAL_PARA[i][j], CAL_MASTER1[i][j], CAL_MASTER2[i][j], Opset[i][j]);
				WriteLine (handle, temp1, -1);
			}
		}	
		CloseFile(handle);
	}	
}

void	LoadCali(void)
{
	char 	Path[1024] = {0,};
	char	temp1[1024] = {0,};
	int		handle, i, j, no;
	
	sprintf(Path, "%s\\Setup_Calibration.ini", Path_Setup);

	if(GetFileInfo(Path, &i) == 0)
	{
		for( i = 0; i < MAX_AMP; i++ )
		{
			for(j = 0; j < MAX_CH_PER_AMP; j ++)
			{
				CAL_PARA[i][j] = 1.0;
				CAL_MASTER1[i][j]= 0.5;
				CAL_MASTER2[i][j]= -0.5;
				Opset[i][j]= 0.0;
			}
		}
		SaveCali();	
	}
	else
	{
	    handle = OpenFile (Path, VAL_READ_ONLY, VAL_TRUNCATE, VAL_ASCII);
		
		for( i = 0 ; i < MAX_AMP ; i ++ )
		{
			for(j = 0 ; j < MAX_CH_PER_AMP ; j ++)
			{
				ReadLine (handle, temp1, -1);
				Scan(temp1,"%s>%i%f%f%f%f", &no, &CAL_PARA[i][j], &CAL_MASTER1[i][j], &CAL_MASTER2[i][j], &Opset[i][j]);
			}
		}
		CloseFile(handle);
	}
	
	SetCtrlIndex ( calpanel, CALPANEL_AMP_NO, 0);
	
	GetCtrlIndex ( calpanel, CALPANEL_AMP_NO, &Amp_Value);
	for(i = 0 ; i < MAX_CH_PER_AMP ; i ++)
	{
		SetCtrlVal(calpanel, CALPANEL_MASTER1_1 + i, CAL_MASTER1[Amp_Value][i]);
		SetCtrlVal(calpanel, CALPANEL_MASTER2_1 + i, CAL_MASTER2[Amp_Value][i]);
		SetCtrlVal(calpanel, CALPANEL_CAL_PARA_1 + i, CAL_PARA[Amp_Value][i]);
		SetCtrlVal(calpanel, CALPANEL_OPSET_DATA_1 + i, Opset[Amp_Value][i]);
	}	
}

