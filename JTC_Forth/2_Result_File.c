#include "0_Main.h"
#include <userint.h>
#include "A_Global.h"

char 	DataBuff[13][MAX_MEAS_CYCLE][50];

void 	GetSaveDataNum(void)
{
	int		i, handle;
	int 	fileSize, len, currFilePtr;
	char 	temp[1024] = {0,};
	
	if(GetFileInfo(DataFileNameAll, &fileSize) == 0)
	{
		TotalNo = NgNo = OkNo = 0;		
	}
	else
	{
		handle = OpenFile(DataFileNameAll, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
		for(i = 0 ; i < 6 ; i ++)
			ReadLine(handle, temp, -1);
		
		//Data Start
		ReadLine(handle, temp, -1);
		len = strlen(temp);
		if(len > 10)
		{
			currFilePtr = SetFilePtr(handle, 0, 1);
			currFilePtr = currFilePtr - (len + 2);
			
			Mc[0].Mode[0].CycleIndex = (fileSize - currFilePtr) / (len + 2);
			
			if(GetFileInfo (DataFileNameNg, &fileSize))
			{
				if(fileSize > currFilePtr)
				{
					McSpc[0].NG = (fileSize - currFilePtr) / (len + 2);
					NgNo = McSpc[0].NG; 
				}
			}

			if(GetFileInfo (DataFileNameOk, &fileSize))
			{
				if(fileSize > currFilePtr)
				{
					McSpc[0].G = (fileSize - currFilePtr) / (len + 2);
					OkNo = McSpc[0].G; 
				}
			}
			TotalNo = OkNo + NgNo;
		}
		else
		{
			Mc[0].Mode[0].CycleIndex = 0;
			McSpc[0].NG = McSpc[0].G = 0;
			TotalNo = NgNo = OkNo = 0;
		}
		CloseFile(handle);
	}
	
	SetCountDisplay(TotalNo, OkNo, NgNo);	

	if(TotalNo > 0)
		LoadDataFromFile(TotalNo);
}

void 	LoadDataFromFile(int no)
{
	int		i, j, handle;
	char 	temp[1024] = {0,};
	int 	comma[13] = {0,};
	char 	ctemp[13][24] = {0,};
	double 	dtemp[MAX_MEAS_POINTS] = {0.0,};
	int		gflag[MAX_MEAS_POINTS] = {0,};
	int		totalflag = 1;
	char 	*ttemp[1000];

	handle = OpenFile(DataFileNameAll, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	for(i = 0 ; i < 6 ; i ++)
		ReadLine(handle, temp, -1);

	if(no > 1000)
	{
		for(i = 0 ; i < no - 1000 ; i ++)
			ReadLine(handle, temp, -1);	
		
		no = 1000;
	}
	
	for(i = 0 ; i < no ; i ++)
	{
		ReadLine(handle, temp, -1);	
		if(strlen(temp) < 10)
			break;
		for(j = 0 ; j < 13 ; j ++)
		{
			if(j == 0)
				comma[j] = FindPattern(temp, 0, strlen(temp), ",", 0, 0);
			else
				comma[j] = FindPattern(temp, comma[j-1]+1, strlen(temp), ",", 0, 0);
		}
		
		CopyBytes(ctemp[0], 0, temp, 0, comma[0]);
		for(j = 1 ; j < 13 ; j ++)
		{
			CopyBytes(ctemp[j], 0, temp, comma[j-1] + 1, comma[j] - comma[j-1] - 1);
		}

		for(j = 0 ; j < 13 ; j ++)
			strcpy(DataBuff[j][i], ctemp[j]);
	}
	
	DeleteTableRows (tab_table, TAB_TABLE_TABLE, 1, -1);
	InsertTableRows (tab_table, TAB_TABLE_TABLE, 1, no, VAL_CELL_STRING);
	
	for(i = 0 ; i < no ; i ++)
	{
		sprintf(temp, "%d", atoi(DataBuff[0][i]));
		SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, i+1, ATTR_USE_LABEL_TEXT, 1);
		SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, i+1, ATTR_LABEL_POINT_SIZE, 11);
		SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, i+1, ATTR_LABEL_BOLD , 0);
		SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, i+1, ATTR_LABEL_TEXT, temp);
		SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, i+1, ATTR_ROW_HEIGHT, 15);
	   
		//마킹기 추 가 시 3 -> 4
		SetTableCellRangeAttribute(tab_table, TAB_TABLE_TABLE, MakeRect(i+1, 1, 1, MeasPoints+3), ATTR_TEXT_POINT_SIZE, 11);
		SetTableCellRangeAttribute(tab_table, TAB_TABLE_TABLE, MakeRect(i+1, 1, 1, MeasPoints+3), ATTR_CELL_JUSTIFY, VAL_CENTER_RIGHT_JUSTIFIED);
		SetTableCellRangeAttribute(tab_table, TAB_TABLE_TABLE, MakeRect(i+1, 1, 1, MeasPoints+3), ATTR_TEXT_BOLD, 0);
	 	SetTableCellRangeAttribute(tab_table, TAB_TABLE_TABLE, MakeRect(i+1, 1, 1, MeasPoints+3), ATTR_CELL_TYPE, VAL_CELL_STRING);
	}
	//DataBuff[8][i]; <=마킹, 마킹기 추가시 같이 삽입
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[9][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 1, no, 1), ttemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[11][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 2, no, 1), ttemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[12][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 3, no, 1), ttemp, VAL_COLUMN_MAJOR);
	//for(i = 0 ; i < no ; i ++)
	//	ttemp[i] = DataBuff[12][i];
	//SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 4, no, 1), ttemp, VAL_COLUMN_MAJOR);

	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[1][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 4, no, 1), ttemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[2][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 5, no, 1), ttemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[3][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 6, no, 1), ttemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[4][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 7, no, 1), ttemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[5][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 8, no, 1), ttemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[6][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 9, no, 1), ttemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[7][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 10, no, 1), ttemp, VAL_COLUMN_MAJOR);
	for(i = 0 ; i < no ; i ++)
		ttemp[i] = DataBuff[8][i];
	SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 11, no, 1), ttemp, VAL_COLUMN_MAJOR);
	//for(i = 0 ; i < no ; i ++)
	//	ttemp[i] = DataBuff[9][i];
	//SetTableCellRangeVals(tab_table, TAB_TABLE_TABLE, MakeRect(1, 11, no, 1), ttemp, VAL_COLUMN_MAJOR);
	
	for(j = 0 ; j < no ; j ++)
	{
		totalflag = 1;
		for(i = 0 ; i < MeasPoints ; i ++)
		{
			dtemp[i] = atof(DataBuff[i+1][j]);
			
			gflag[i] = 1;
			if(dtemp[i] < Model[i].LCL || dtemp[i] > Model[i].UCL)
			{
				gflag[i] = 0;
				totalflag = 0;
			}
			else if((dtemp[i] >= Model[i].LCL && dtemp[i] <= Model[i].LWL) || (dtemp[i] <= Model[i].UCL && dtemp[i] >= Model[i].UWL))
			{
				if(Model[i].Offset)
					gflag[i] = 2;
			}
		}
		//마킹기 추 가 시 3-> 4, 4-> 5 //보정 신호 관련  
		if(!totalflag)
		{
			SetTableCellRangeAttribute (tab_table, TAB_TABLE_TABLE, MakeRect(j+1, 1, 1, MeasPoints+3), ATTR_TEXT_BGCOLOR, 0xFFDDDD);
			for( i = 0; i < MeasPoints; i++ )
			{
				if(gflag[i] == 0)
				{
					SetTableCellAttribute (tab_table, TAB_TABLE_TABLE, MakePoint(i+4, j+1), ATTR_TEXT_BGCOLOR, VAL_RED);
					SetTableCellAttribute (tab_table, TAB_TABLE_TABLE, MakePoint(i+4, j+1), ATTR_TEXT_COLOR, VAL_BLACK);
				}
			}
		}
		else
		{
			for( i = 0; i < MeasPoints; i++ )
			{
				if(gflag[i] == 2)
				{
					SetTableCellAttribute (tab_table, TAB_TABLE_TABLE, MakePoint(i+4, j+1), ATTR_TEXT_BGCOLOR, VAL_GREEN);
				}
			}
		}
		//마킹기 추 가 시 3-> 4
		SetTableSelection(tab_table, TAB_TABLE_TABLE, MakeRect(j+1, 1, 1, MeasPoints+3));		
			
	}

	CloseFile(handle);
	
	for(i = 0 ; i < MAX_MEAS_CYCLE ; i ++)
		memset(ttemp, 0, sizeof(ttemp));
	
	if(no > 1000)
	{
		DeleteTableRows(tab_table, TAB_TABLE_TABLE, 1001, no - 1000);
	}
}

void	GetDataFileName(void)
{
	char	Date[30];
	int 	MM, DD, YYYY;
	char	AddRule[128] = {0,};
	char 	Path[1024] = {0,};
	
	GetSystemDate(&MM, &DD, &YYYY);
	sprintf(Date, "%04d-%02d-%02d", YYYY, MM, DD);
	
	if( CurrShift == 0 ) // 주간
	{
		if( SeperateDayNight )  // 주야간 파일 분리
			strcat(Date, "_DAY");
	}
	else
	{
		if( strncmp(CurrTime, DayStartTime, 4) < 0 ) // 전날 야간
			GetBeforeDate( Date );
			
		if( SeperateDayNight )
			strcat(Date, "_NIGHT");
	}
	
	strcpy(Path, Path_Result);
	switch (Rule_Result)
	{
		case 0:	//ModelName\
			
			sprintf(AddRule, "\\%s", ModelName[ModelNo]);  
			strcat(Path, AddRule);		
			if( SetDir(Path) )	MakeDir(Path);
			
			break;
		case 1:	//ModelName\YYYYMMDD\
			
			sprintf(AddRule, "\\%s", ModelName[ModelNo]);  
			strcat(Path, AddRule);		
			if( SetDir(Path) )	MakeDir(Path);
			
			sprintf(AddRule, "\\%04d%02d%02d", YYYY, MM, DD);
			strcat(Path, AddRule);		
			if( SetDir(Path) )	MakeDir(Path);
						
			break;
		case 2:	//ModelName\\YYYY\MMDD\
			
			sprintf(AddRule, "\\%s", ModelName[ModelNo]);  
			strcat(Path, AddRule);		
			if( SetDir(Path) )	MakeDir(Path);
						
			sprintf(AddRule, "\\%04d", YYYY);
			strcat(Path, AddRule);
			if( SetDir(Path) )	MakeDir(Path);	
			
			sprintf(AddRule, "\\%02d%02d", MM, DD);
			strcat(Path, AddRule);
			if( SetDir(Path) )	MakeDir(Path);	
			
			break;
		case 3:	//ModelName\\YYYY\MM\DD\
			
			sprintf(AddRule, "\\%s", ModelName[ModelNo]);  
			strcat(Path, AddRule);		
			if( SetDir(Path) )	MakeDir(Path);
						
			sprintf(AddRule, "\\%04d", YYYY);
			strcat(Path, AddRule);
			if( SetDir(Path) )	MakeDir(Path);	
			
			sprintf(AddRule, "\\%02d", MM);
			strcat(Path, AddRule);
			if( SetDir(Path) )	MakeDir(Path);	
			
			sprintf(AddRule, "\\%02d", DD);
			strcat(Path, AddRule);
			if( SetDir(Path) )	MakeDir(Path);	
			
			break;
		default:
			break;
	}	
	strcat(Path, "\\");
	strcpy(DataFileNameAll, Path);
	strcat(DataFileNameAll, Date);

	strcpy(DataFileNameNg, DataFileNameAll);
	strcpy(DataFileNameOk, DataFileNameAll);
	
	strcat(DataFileNameAll, "_ALL.csv");
	strcat(DataFileNameNg,  "_NG.csv");
	strcat(DataFileNameOk,  "_OK.csv");
}
void 	CreateDataFile()
{
	char	fmt[10];
	int		handleAll, handleOk, handleNg, i;
	char	temp[1024], temp1[128];
	
	handleAll = OpenFile(DataFileNameAll, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	handleOk = OpenFile(DataFileNameOk, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	handleNg = OpenFile(DataFileNameNg, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);

	// Model Name
	sprintf(temp, "Model,%s,", ModelName[ModelNo]);
	WriteLine(handleAll, temp, -1);
	WriteLine(handleOk, temp, -1);
	WriteLine(handleNg, temp, -1);
	
	// MeasPoints Num
	sprintf(temp, "Point_Num,%i,", MeasPoints);   
	WriteLine(handleAll, temp, -1);
	WriteLine(handleOk, temp, -1);
	WriteLine(handleNg, temp, -1);

    // Meas Item Names
	sprintf(temp, "%s,", "NAME");
	for(i = 0 ; i < MeasPoints ; i ++)								
	{
		sprintf(temp1, "%s,", Model[i].Name);
		strcat(temp, temp1);
	}

	// Time
	sprintf(temp1, "%s,", "Time");
	strcat(temp, temp1); 
	
	// Marking Data 마킹기 추 가 시 석 헤 제
	//sprintf(temp1, "%s,", "MARKING");
    //strcat(temp, temp1);

	// #10
	sprintf(temp1, "%s,", "#10");
    strcat(temp, temp1);

	// #20
	sprintf(temp1, "%s,", "#20");
    strcat(temp, temp1);

	WriteLine(handleAll, temp, -1);
	WriteLine(handleOk, temp, -1);
	WriteLine(handleNg, temp, -1);
	
	// Unit
    sprintf(temp, "%s,", "UNIT");
	for(i = 0 ; i < MeasPoints ; i ++)								
	{
		sprintf(temp1, "%d,", Model[i].Unit);
 		strcat(temp, temp1);	 
	}
	WriteLine(handleAll, temp, -1);
	WriteLine(handleOk, temp, -1);
	WriteLine(handleNg, temp, -1);

	// UCL
	sprintf(temp, "%s,", "UCL");
	for(i = 0 ; i < MeasPoints ; i ++)								
	{
		sprintf(fmt, "%%.%df,", Model[i].Unit);
		sprintf(temp1, fmt, Model[i].UCL);
		strcat(temp, temp1);
	}
	WriteLine(handleAll, temp, -1);
	WriteLine(handleOk, temp, -1);
	WriteLine(handleNg, temp, -1);

	//LCL
    sprintf(temp, "%s,", "LCL");
	for(i = 0 ; i < MeasPoints ; i ++)								
	{
		sprintf(fmt, "%%.%df,", Model[i].Unit);
		sprintf(temp1, fmt, Model[i].LCL);
		strcat(temp, temp1);
	}
	WriteLine(handleAll, temp, -1);
	WriteLine(handleOk, temp, -1);
	WriteLine(handleNg, temp, -1);

	CloseFile(handleAll);
	CloseFile(handleOk);
	CloseFile(handleNg);	
}
void 	CreateDataNgFile()
{
	char	fmt[10];
	int		handleNg, i;
	char	temp[1024], temp1[128];
	
	handleNg = OpenFile(DataFileNameNg, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);

	// Model Name
	sprintf(temp, "Model,%s,", ModelName[ModelNo]);
	WriteLine(handleNg, temp, -1);
	
	// MeasPoints Num
	sprintf(temp, "Point_Num,%i,", MeasPoints);   
	WriteLine(handleNg, temp, -1);

    // Meas Item Names
	sprintf(temp, "%s,", "NAME");
	for(i = 0 ; i < MeasPoints ; i ++)								
	{
		sprintf(temp1, "%s,", Model[i].Name);
		strcat(temp, temp1);
	}

	// Time
	sprintf(temp1, "%s,", "Time");
	strcat(temp, temp1); 
	
	// Marking Data 마킹기 추 가 시 주 석 해 제
	//sprintf(temp1, "%s,", "MARKING");
    //strcat(temp, temp1);

	// #10
	sprintf(temp1, "%s,", "#10");
    strcat(temp, temp1);

	// #20
	sprintf(temp1, "%s,", "#20");
    strcat(temp, temp1);

	WriteLine(handleNg, temp, -1);
	
	// Unit
    sprintf(temp, "%s,", "UNIT");
	for(i = 0 ; i < MeasPoints ; i ++)								
	{
		sprintf(temp1, "%d,", Model[i].Unit);
 		strcat(temp, temp1);	 
	}
	WriteLine(handleNg, temp, -1);

	// UCL
	sprintf(temp, "%s,", "UCL");
	for(i = 0 ; i < MeasPoints ; i ++)								
	{
		sprintf(fmt, "%%.%df,", Model[i].Unit);
		sprintf(temp1, fmt, Model[i].UCL);
		strcat(temp, temp1);
	}
	WriteLine(handleNg, temp, -1);

	//LCL
    sprintf(temp, "%s,", "LCL");
	for(i = 0 ; i < MeasPoints ; i ++)								
	{
		sprintf(fmt, "%%.%df,", Model[i].Unit);
		sprintf(temp1, fmt, Model[i].LCL);
		strcat(temp, temp1);
	}
	WriteLine(handleNg, temp, -1);

	CloseFile(handleNg);	
}

void	SaveDataFile(void)
{
	int 	handleAll, handleOkNg, i;
	char	temp[1024], temp1[128];
	char	fmt[10], ctemp[48] = {0,}, *str;
	
	handleAll = OpenFile(DataFileNameAll, VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);
	if(TotalGFlag) 
			handleOkNg = OpenFile(DataFileNameOk, VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);
	else	handleOkNg = OpenFile(DataFileNameNg, VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);

//	sprintf(temp, "%04d,", Mc[0].Mode[0].CycleIndex);
	sprintf(temp, "%04d,", TotalNo);
	
    for(i = 0 ; i < MeasPoints ; i ++)							
	{
		sprintf(fmt, "%%.%df,", Model[i].Unit);					   
		sprintf(temp1, fmt, Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1]);
		strcat(temp, temp1);
	}
	sprintf(temp1, "%s/%s,", MeasDate, MeasTime);					
	strcat(temp, temp1);
	
//	if(TotalGFlag)
		//마킹기 추 가 시 주 석 해 제 
		//strcpy(ctemp, MarkStr);
//	else
//		strcpy(ctemp, "NG");
	
	sprintf(temp1, "%s,", ctemp);
	strcat(temp, temp1);
  	
	sprintf(ctemp, "%d", 101 + McNo1);
	sprintf(temp1, "%s,", ctemp);
	strcat(temp, temp1);
	
	sprintf(ctemp, "%d", 201 + McNo2);
	sprintf(temp1, "%s,", ctemp);
	strcat(temp, temp1);
  		
	WriteLine(handleAll, temp, -1);
	CloseFile(handleAll);
	
	if( TotalGFlag ) // 합격이면
			sprintf(temp1, "%04d", OkNo);
	else	sprintf(temp1, "%04d", NgNo);
	
	str = strstr(temp, ",");
	strcat(temp1, str);
	WriteLine(handleOkNg, temp1, -1);   
	CloseFile(handleOkNg);	
}

int CVICALLBACK Cb_TestNo (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int		top, left, leftbtn, rightbtn, key;

	switch (event)
	{
		case EVENT_LEFT_CLICK:
			GetRelativeMouseState(panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
			GetTableCellFromPoint(panel, control, MakePoint (left, top), &PadCell);
			if(!d_in[5])
			{
				if(PadCell.x == 3 && PadCell.y == 1)
				{
					if(ConfirmPopup("DELETE NG FILE", "ARE YOU SURE?"))	
					{
						DeleteFile(DataFileNameAll);
						DeleteFile(DataFileNameNg);
						CopyFile(DataFileNameOk, DataFileNameAll);
						CreateDataNgFile();
						LogUpdate("Ng Data File Delete");
						TotalNo = OkNo;
						NgNo = 0;
						LoadDataFromFile(TotalNo);

						SetCountDisplay(TotalNo, OkNo, NgNo);	
						ResetSpcData();			
						GraphPlot();
					}
				}
			}

			break;
	}
	return 0;
}
