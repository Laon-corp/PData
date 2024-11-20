#include "cvi_db.h"
#include <cviauto.h>
#include "MSCOMCT2.h"
#include <userint.h>
#include "A_Global.h"

char	DB_Data_Model[30000][100];
char	DB_Data_DateTime[30000][100];
char	DB_Data_Gflag[30000][100];
char	DB_Data_Mc1[30000][100];
char	DB_Data_Mc2[30000][100];
char	DB_Data_Mark[30000][100];
char	DB_Data_Buff1[30000][100];
char	DB_Data_Buff2[30000][100];
char	DB_Data_Buff3[30000][100];
char	DB_Data_Buff4[30000][100];
char	DB_Data_Buff5[30000][100];
char	DB_Data_Buff6[30000][100];
char	DB_Data_Buff7[30000][100];
char	DB_Data_Buff8[30000][100];

// SQL Error Message Display
void ShowError()
{
    MessagePopup("Database Error", DBErrorMessage());
}

void FuncDBConnect(void)
{
	// SQL DataBase Connect
	DBhandle = DBConnect ("DSN=LAON1;UID=admin;PWD=1234");
	if (DBhandle == -10 || DBhandle == -11)
	{
		MessagePopup ("Could not connect to data source", "The SQL Toolkit could not connect");
		LogUpdate("DB Connect Fail");
		return;
	}
}

void FuncDBDisconnect(void)
{
	// DisConnect SQL Server
    DBret = DBDisconnect (DBhandle);
    if (DBret != DB_SUCCESS)
	{
		ShowError();
		LogUpdate("DB Disconnect Fail");
		return;
	}
	LogUpdate("DB Disconnect Success");
}


int CVICALLBACK Cb_Db_Search (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	CAObjHandle objectHandle;
	CAObjHandle objectHandle2;
	VARIANT 	pvdateValue;
	DATE		Date = 0.0;
	char		DateStamp[30] = {0,};	
	char		DateStamp2[30] = {0,};
	int			no, i = 0;
	char		ctemp[1024] = {0,};
	char		ctemp2[128] = {0,};
	char		*data[17];
	char		*temp[3000];
	
	switch (event)
	{
		case EVENT_COMMIT:
 			GetObjHandleFromActiveXCtrl(resultpanel, RESULT_DTPICKER, &objectHandle);
 			GetObjHandleFromActiveXCtrl(resultpanel, RESULT_DTPICKER_2, &objectHandle2);
			
			// Start Day
			MSComCtl2_IDTPickerGet_Value (objectHandle, NULL, &pvdateValue);
			if( CA_VariantHasDate (&pvdateValue) == 1 ) // Date Information Detect
				CA_VariantGetDate (&pvdateValue, &Date);
			FormatDateTimeString ((Date-2)*24*60*60, "%Y-%m-%d", DateStamp, 30);

			// End Day
			MSComCtl2_IDTPickerGet_Value (objectHandle2, NULL, &pvdateValue);
			if( CA_VariantHasDate (&pvdateValue) == 1 ) // Date Information Detect
				CA_VariantGetDate (&pvdateValue, &Date);
			FormatDateTimeString ((Date-2)*24*60*60, "%Y-%m-%d", DateStamp2, 30);

			// SQL
			// select * from datatable where date(datetime) between '2020-12-10' AND '2020-12-20'; 
			sprintf(ctemp, "select MODEL, DATETIME, GFLAG, MC1, MC2, MARK, DATA1, DATA2, DATA3, DATA4, DATA5, DATA6, DATA7 from LAON.dataTABLE where date(datetime) between '%s' AND '%s' ", DateStamp, DateStamp2);
			// ALL, MODEL, ...
			GetCtrlIndex(resultpanel, RESULT_MODEL, &no);
//			GetLabelFromIndex(resultpanel, RESULT_MODEL, no, ModelNameTemp);
//			if(no > 0)
			{
//				sprintf(ctemp2, "AND MODEL = '%s' ", ModelNameTemp);
				sprintf(ctemp2, "AND MODEL = '%s' ", ModelName[no]);
				strcat(ctemp, ctemp2);
			}
			
			// ALL, OK, NG
			GetCtrlIndex(resultpanel, RESULT_GFLAG, &no);
			if(no > 0)
			{
				if(no == 1)	sprintf(ctemp2, "AND GFLAG = 'OK' ");
				else		sprintf(ctemp2, "AND GFLAG = 'NG' ");
				strcat(ctemp, ctemp2);
			}

			DBStmt = DBActivateSQL(DBhandle, ctemp);
			if (DBStmt <= 0)
			{
				ShowError();
				LogUpdate("DB Data Search Fail");
				LogUpdate(ctemp);
				return 0;
			}
			
			SetCtrlAttribute(resultpanel, RESULT_MSG_WAIT, ATTR_VISIBLE, 1);
			
			no = DBNumberOfRecords(DBStmt);
			if(no < 1)
			{
				DeleteTableRows(resultpanel, RESULT_TABLE, 1, -1);
				MessagePopup ("No Data", "Check Again");
				DBret = DBDeactivateSQL(DBStmt);
				return 0;
			}
			i = 0;
			while ((DBret = DBFetchNext (DBStmt)) == DB_SUCCESS)
			{
				DBret = DBGetColChar(DBStmt, 1, &data[0], "");		//MODEL
				DBret = DBGetColChar(DBStmt, 2, &data[1], "");		//DATETIME
				DBret = DBGetColChar(DBStmt, 3, &data[2], "");		//GFLAG
				DBret = DBGetColChar(DBStmt, 4, &data[3], "");		//MC1
				DBret = DBGetColChar(DBStmt, 5, &data[4], "");		//MC2
				DBret = DBGetColChar(DBStmt, 6, &data[5], "");   	//MARK
				
				DBret = DBGetColChar(DBStmt, 7, &data[6], "");		//DATA1
				DBret = DBGetColChar(DBStmt, 8, &data[7], ""); 		//DATA2
				DBret = DBGetColChar(DBStmt, 9, &data[8], "");		//DATA3
				DBret = DBGetColChar(DBStmt, 10, &data[9], "");		//DATA4
				DBret = DBGetColChar(DBStmt, 11, &data[10], "");		//DATA5
				DBret = DBGetColChar(DBStmt, 12, &data[11], "");	//DATA6
				DBret = DBGetColChar(DBStmt, 13, &data[12], "");	//DATA7	
				//DBret = DBGetColChar(DBStmt, 14, &data[13], "");	//DATA8
				
				if(data[0] != NULL)	strcpy(DB_Data_Model[i], data[0]);
				else				strcpy(DB_Data_Model[i],  " ");
				
				if(data[1] != NULL)	strcpy(DB_Data_DateTime[i], data[1]);
				else				strcpy(DB_Data_DateTime[i],  " ");
				
				if(data[2] != NULL)	strcpy(DB_Data_Gflag[i], data[2]);
				else				strcpy(DB_Data_Gflag[i],  " ");
			
				if(data[3] != NULL)	strcpy(DB_Data_Mc1[i], data[3]);
				else				strcpy(DB_Data_Mc1[i],  " ");
				
				if(data[4] != NULL)	strcpy(DB_Data_Mc2[i], data[4]);
				else				strcpy(DB_Data_Mc2[i],  " ");
				
				if(data[5] != NULL)	strcpy(DB_Data_Mark[i], data[5]);
				else				strcpy(DB_Data_Mark[i],  " ");
				
				if(data[6] != NULL)	strcpy(DB_Data_Buff1[i], data[6]);
				else				strcpy(DB_Data_Buff1[i],  " ");
				
				if(data[7] != NULL)	strcpy(DB_Data_Buff2[i], data[7]);
				else				strcpy(DB_Data_Buff2[i],  " ");
				
				if(data[8] != NULL)	strcpy(DB_Data_Buff3[i], data[8]);
				else				strcpy(DB_Data_Buff3[i],  " ");
			
				if(data[9] != NULL)	strcpy(DB_Data_Buff4[i], data[9]);
				else				strcpy(DB_Data_Buff4[i],  " ");
			
				if(data[10] != NULL)	strcpy(DB_Data_Buff5[i], data[10]);
				else					strcpy(DB_Data_Buff5[i],  " ");

				if(data[11] != NULL)	strcpy(DB_Data_Buff6[i], data[11]);
				else					strcpy(DB_Data_Buff6[i],  " ");

				if(data[12] != NULL)	strcpy(DB_Data_Buff7[i], data[12]);
				else					strcpy(DB_Data_Buff7[i],  " ");

				//if(data[13] != NULL)	strcpy(DB_Data_Buff8[i], data[13]);
				//else					strcpy(DB_Data_Buff8[i],  " ");


				DBFree(data[0]);
				DBFree(data[1]);
				DBFree(data[2]);
				DBFree(data[3]);
				DBFree(data[4]);
				DBFree(data[5]);
				DBFree(data[6]);
				DBFree(data[7]);
				DBFree(data[8]);
				DBFree(data[9]);
				DBFree(data[10]);
				DBFree(data[11]);
				DBFree(data[12]);
				//DBFree(data[13]);
				
				i++;
				if(i >= 30000)
				{
				    MessagePopup("DATA OVER", "LOAD DATA LESS THAN 30000");
					break;
				}
			}
			
			DBret = DBDeactivateSQL(DBStmt);
			

			DeleteTableRows(resultpanel, RESULT_TABLE, 1, -1);
			InsertTableRows(resultpanel, RESULT_TABLE, 1, i, VAL_CELL_STRING);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Model[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 1, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_DateTime[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 2, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Gflag[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 3, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Mc1[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 4, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Mc2[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 5, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Mark[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 6, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Buff1[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 7, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Buff2[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 8, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Buff3[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 9, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Buff4[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 10, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Buff5[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 11, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Buff6[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 12, i, 1), temp, VAL_COLUMN_MAJOR);
			for( no = 0 ; no < i ; no ++ )
				temp[no] = DB_Data_Buff7[no];	
			SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 13, i, 1), temp, VAL_COLUMN_MAJOR);
			//for( no = 0 ; no < i ; no ++ )
			//	temp[no] = DB_Data_Buff8[no];	
			//SetTableCellRangeVals(resultpanel, RESULT_TABLE, MakeRect(1, 14, i, 1), temp, VAL_COLUMN_MAJOR);
			
			SetCtrlAttribute(resultpanel, RESULT_MSG_WAIT, ATTR_VISIBLE, 0);
			
			break;
	}
	return 0;
}

void	SetDateResult(void)
{
	CAObjHandle objectHandle;
	CAObjHandle objectHandle2;
	VARIANT 	pvdateValue;
	DATE		Date = 0.0;
	double 		d;
	int			diffday, i;
	
	GetObjHandleFromActiveXCtrl(resultpanel, RESULT_DTPICKER, &objectHandle);
	GetObjHandleFromActiveXCtrl(resultpanel, RESULT_DTPICKER_2, &objectHandle2);
	
	MSComCtl2_IDTPickerGet_Value (objectHandle, NULL, &pvdateValue);
	if( CA_VariantHasDate (&pvdateValue) == 1 ) // Date Information Detect
		CA_VariantGetDate (&pvdateValue, &Date);

	GetCurrentDateTime(&d);
	d = d / 60 / 60 / 24 ;
	diffday = (int)(d + 2.0);
	
	diffday = diffday - Date;
	Date = Date + diffday;
	
	CA_VariantSetDate (&pvdateValue, Date);
	MSComCtl2_IDTPickerSet_Value (objectHandle, NULL, pvdateValue);
	MSComCtl2_IDTPickerSet_Value (objectHandle2, NULL, pvdateValue);
	
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 1, ATTR_COLUMN_WIDTH, 70);	//MODEL
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 2, ATTR_COLUMN_WIDTH, 115);	//DATE/TIME
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 3, ATTR_COLUMN_WIDTH, 50);	//OK/NG
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 4, ATTR_COLUMN_WIDTH, 30);	//#10
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 5, ATTR_COLUMN_WIDTH, 30);	//#20
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 6, ATTR_COLUMN_WIDTH, 50);	//MARK
	
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 1, ATTR_LABEL_TEXT, "MODEL");
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 2, ATTR_LABEL_TEXT, "DATE/TIME");
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 3, ATTR_LABEL_TEXT, "OK/NG");
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 4, ATTR_LABEL_TEXT, "#10");
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 5, ATTR_LABEL_TEXT, "#20");
	SetTableColumnAttribute(resultpanel, RESULT_TABLE, 6, ATTR_LABEL_TEXT, "MARK");
	
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		SetTableColumnAttribute(resultpanel, RESULT_TABLE, 7+i, ATTR_LABEL_TEXT, Model[i].Name);
		SetTableColumnAttribute(resultpanel, RESULT_TABLE, 7+i, ATTR_COLUMN_WIDTH, 90);
	}
}

void	SaveDataBase(void)
{
	char		ctemp[1024] = {0,};
	char		ctemp2[128] = {0,};
	char		Gflag[10] = {0,};
	char		Mc1[10] = {0,};
	char		Mc2[10] = {0,};
	char		dtemp[14][20] = {0,};
	char		DateTime[48] = {0,};
	char		DataTemp[48] = {0,};
	int			i;
	char		fmt[10];
	
	sprintf(DateTime, "%s %s", 	MeasDate, MeasTime);

	// SQL command
	if(TotalGFlag)
		sprintf(Gflag, "OK");
	else
		sprintf(Gflag, "NG");
	
	if(McNo1 == 0)
		sprintf(Mc1, "101");
	else if(McNo1 == 1)
		sprintf(Mc1, "102");
	else if(McNo1 == 2)
		sprintf(Mc1, "103");
	
	if(McNo2 == 0)
		sprintf(Mc2, "201");
	else if(McNo2 == 1)
		sprintf(Mc2, "202");
	else if(McNo2 == 2)
		sprintf(Mc2, "203");

	for(i = 0; i < MeasPoints ; i++)							
	{
		sprintf(fmt, "%%.%df", Model[i].Unit);
		sprintf(DataTemp, fmt, Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1]);
		strcpy(dtemp[i], DataTemp);
	}

	sprintf(ctemp, "INSERT INTO laon.datatable (MODEL, DATETIME, GFLAG, MC1, MC2, MARK, ");
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		sprintf(ctemp2, "DATA%d", i+1);	
		if(i < MeasPoints - 1)
			strcat(ctemp2, ", ");
		else
			strcat(ctemp2, ") VALUES ( ");
		strcat(ctemp, ctemp2);
	}

	sprintf(ctemp2, "'%s', '%s', '%s', '%s', '%s', '%s', ", ModelName[ModelNo], DateTime, Gflag, Mc1, Mc2, MarkStr);
	
	strcat(ctemp, ctemp2);
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		sprintf(ctemp2, "'%s'", dtemp[i]);
		if(i < MeasPoints - 1)
			strcat(ctemp2, ", ");
		else
			strcat(ctemp2, ") ");
		strcat(ctemp, ctemp2);
	}	
		
	DBStmt = DBActivateSQL(DBhandle, ctemp);
	if (DBStmt <= 0)
	{
		ShowError(); 
		LogUpdate("DB Data Save Fail");
		LogUpdate(ctemp);
		return;
	}																			   
	DBret = DBDeactivateSQL(DBStmt);
}

int CVICALLBACK Cb_CsvSave (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	int	 	i, no;
    char 	FileName[512] = {0,};
	char 	ctemp[1024] = {0,};
    int  	handle;
   
	CAObjHandle objectHandle;
	CAObjHandle objectHandle2;
	VARIANT 	pvdateValue;
	DATE		Date = 0.0;
	char		DateStamp[30] = {0,};
	char		DateStamp2[30] = {0,};
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetNumTableRows(resultpanel, RESULT_TABLE, &no);
			if(no < 1)
			{
				MessagePopup("No Data", "No Data");
				return 0;
			}
			
 			GetObjHandleFromActiveXCtrl(resultpanel, RESULT_DTPICKER, &objectHandle);
 			GetObjHandleFromActiveXCtrl(resultpanel, RESULT_DTPICKER_2, &objectHandle2);
			
			// Start Day
			MSComCtl2_IDTPickerGet_Value (objectHandle, NULL, &pvdateValue);
			if( CA_VariantHasDate (&pvdateValue) == 1 ) // Date Information Detect
				CA_VariantGetDate (&pvdateValue, &Date);
			FormatDateTimeString ((Date-2)*24*60*60, "%Y-%m-%d", DateStamp, 30);

			// End Day
			MSComCtl2_IDTPickerGet_Value (objectHandle2, NULL, &pvdateValue);
			if( CA_VariantHasDate (&pvdateValue) == 1 ) // Date Information Detect
				CA_VariantGetDate (&pvdateValue, &Date);
			FormatDateTimeString ((Date-2)*24*60*60, "%Y-%m-%d", DateStamp2, 30);			
			
			GetCtrlIndex(resultpanel, RESULT_MODEL, &i);
			sprintf(ctemp, "%s\\%s", Path_Result, ModelName[i]);
			
			if( SetDir(ctemp) )	MakeDir (ctemp);
			
			strcat(ctemp, "\\data");
			
			if( SetDir(ctemp) )	MakeDir (ctemp);

			sprintf(FileName, "%s-%s.csv", DateStamp, DateStamp2);

			handle = FileSelectPopup(ctemp, FileName, "*.*", "DATA SAVE", VAL_SAVE_BUTTON, 0, 1, -1, 1, FileName);
    	   	if(handle <= 0)
    	   	{   
				MessagePopup ("FILE CHOICE ERROR", "No file is choosen");
				return 0;
    	   	}
			handle = OpenFile (FileName, VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII);
			sprintf(ctemp, "%s - %s", DateStamp, DateStamp2);
			WriteLine(handle, ctemp, -1);
			
			for(i = 0 ; i < no ; i ++)
			{
				sprintf(ctemp, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,", 
					i+1,	DB_Data_Model[i], DB_Data_DateTime[i], DB_Data_Gflag[i], 
							DB_Data_Mc1[i],   DB_Data_Mc2[i],      //DB_Data_Mark[i],
							DB_Data_Buff1[i], DB_Data_Buff2[i], DB_Data_Buff3[i], DB_Data_Buff4[i], DB_Data_Buff5[i],
							DB_Data_Buff6[i], DB_Data_Buff7[i]);
				WriteLine(handle, ctemp, -1);
			}
			CloseFile(handle);
			break;
	}
	return 0;
}
