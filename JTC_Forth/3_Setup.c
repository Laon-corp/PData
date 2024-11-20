#include <userint.h>
#include "3_Setup.h"
#include "A_Global.h"

void InitSystem(void)
{
	GetRegPath();

	if(SetDir(Path_Model) )			MakeDir (Path_Model);
	if(SetDir(Path_Result) )		MakeDir (Path_Result);			
	if(SetDir(Path_History_Reg))	MakeDir (Path_History_Reg);			
	if(SetDir(Path_Setup) )			MakeDir (Path_Setup);			
	
	SetCtrlVal(setuppanel, SETUP_PATH_MODEL, Path_Model);
	SetCtrlVal(setuppanel, SETUP_PATH_RESULT, Path_Result);
	SetCtrlVal(setuppanel, SETUP_PATH_HISTORY, Path_History_Reg);
	SetCtrlVal(setuppanel, SETUP_PATH_SETUP, Path_Setup);
	
	SetCtrlVal(setuppanel, SETUP_PATH_RULE_HISTORY, Rule_History);
	SetCtrlVal(setuppanel, SETUP_PATH_RULE_RESULT, Rule_Result);
	
	LoadSetup();
	InitLogPath();
	LoadComport();
}

void	InitManuSol(void)
{
	char 	Path[1024] = {0,};
	int		handle, i, j, len, top, height, no;
	char 	temp1[1024] = {0,};
	char 	temp2[4] = {0,};
	
	sprintf(Path, "%s\\ManualSolName.csv", Path_Setup);
	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);

	for(i = 0 ; i < MAX_SOL ; i ++)
	{
		ReadLine(handle, temp1, -1);
		len = strlen(temp1);
		no = 0;
		for(j = 0 ; j < len ; j ++)
		{
			sprintf(temp2, "%c", temp1[j]);
			if(strcmp("_", temp2) == 0)	
			{
				temp1[j] = 0x0D;
				no++;
			}
		}
	
		if(no)
		{
			GetCtrlAttribute(tab_manual, ManuSwCtrl[i], ATTR_LABEL_TOP, &top);
			SetCtrlAttribute(tab_manual, ManuSwCtrl[i], ATTR_LABEL_TOP, top-(7*no));
			GetCtrlAttribute(tab_manual, ManuSwCtrl[i], ATTR_LABEL_HEIGHT, &height);
			SetCtrlAttribute(tab_manual, ManuSwCtrl[i], ATTR_LABEL_HEIGHT, height+(16*no));
		}

		SetCtrlAttribute(tab_manual, ManuSwCtrl[i], ATTR_LABEL_TEXT, temp1);
	}
	CloseFile(handle);


	for(i = 0 ; i < MAX_SOL ; i ++)
	{
		SetCtrlAttribute(tab_manual, ManuLedHome[i], ATTR_ON_COLOR, VAL_GREEN);
		SetCtrlAttribute(tab_manual, ManuLedAct[i],  ATTR_ON_COLOR, VAL_RED);
		SetCtrlAttribute(tab_manual, ManuLedHome[i], ATTR_OFF_COLOR, VAL_BLACK);
		SetCtrlAttribute(tab_manual, ManuLedAct[i],  ATTR_OFF_COLOR, VAL_BLACK);
	}	
}

void	InitPlcErrStr(void)
{
	char 	Path[1024] = {0,};
	int		handle, i;
	
	sprintf(Path, "%s\\PlcErrMsg.csv", Path_Setup);
	
	if(GetFileInfo(Path, &i) == 0)
	{
		handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
		for(i = 0 ; i < MAX_PLC_ERR ; i ++)
		{
			sprintf(PlcErrStr[i], "Error %02d : ", i+1);
			WriteLine(handle, PlcErrStr[i], -1);
		}
		CloseFile(handle);
	}
	else
	{
		handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
		for(i = 0 ; i < MAX_PLC_ERR ; i ++)
		{
			ReadLine(handle, PlcErrStr[i], -1);
		}
		CloseFile(handle);
	}	
}

void	InitIO(void)
{
	char 	Path[1024] = {0,};
	char	temp1[1024] = {0,};
	char 	temp2[1024] = {0,};
	int		handle, i, len;
	int 	p1, p2;
	char 	*iotemp1[320];
	char 	*iotemp2[320];
	
	char	IO_PC[320][1024] = {0,};
	char	IO_PLC[320][1024] = {0,};
	
	sprintf(Path, "%s\\LAON_IO.csv", Path_Setup);
	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	

	ReadLine(handle, temp1, -1);
	ReadLine(handle, temp1, -1);	
	
	for(i = 0 ; i < 320 ; i ++)
	{
		ReadLine(handle, temp1, -1);
		len = strlen(temp1);
		p1 = FindPattern(temp1, 0, len, ",", 0, 0);
		CopyBytes(temp2, 0, temp1, p1 + 1, len - p1 + 1);

		p2 = FindPattern(temp2, 0, strlen(temp2), ",", 0, 0);
		
		CopyBytes(IO_PLC[i], 0, temp1, 0, p1);
		CopyBytes(IO_PC[i],  0, temp2, 0, p2);
		
	}
	CloseFile(handle);
	
	for(i = 0 ; i < 320 ; i ++)
	{
		iotemp1[i] = IO_PLC[i];
		iotemp2[i] = IO_PC[i];
	}
	
	DeleteTableRows(tab_io, TAB_IO_TABLE_INPUT,  1, -1);
	DeleteTableRows(tab_io, TAB_IO_TABLE_OUTPUT, 1, -1);
	InsertTableRows(tab_io, TAB_IO_TABLE_INPUT,  1, 320, VAL_USE_MASTER_CELL_TYPE);
	InsertTableRows(tab_io, TAB_IO_TABLE_OUTPUT, 1, 320, VAL_USE_MASTER_CELL_TYPE);
	SetTableCellRangeVals(tab_io, TAB_IO_TABLE_INPUT,  MakeRect(1, 1, 320, 1), iotemp1, VAL_COLUMN_MAJOR);
	SetTableCellRangeVals(tab_io, TAB_IO_TABLE_OUTPUT, MakeRect(1, 1, 320, 1), iotemp2, VAL_COLUMN_MAJOR); 
}

void 	LoadSetup(void)
{
	char 	Path[1024] = {0,};
	char	temp1[1024] = {0,};
	int		handle, i, j, a;
//	double 	t;
	
	sprintf(Path, "%s\\Setup_Bypass.ini", Path_Setup);
	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	
	if(handle < 0)
	{
		MessagePopup("NO FILE FOR BYPASS", "CHECK PROGRAM SETUP - BYPASS");
		for(i = 0 ; i < 4 ; i ++)
			ByPassFlag[i] = 0;
	}
	else
	{
		for(i = 0 ; i < 4 ; i ++)
		{
			ReadLine(handle, temp1, -1);
			ReadLine(handle, temp1, -1);
			ByPassFlag[i] = atoi(temp1);
			PlcData[40+i] = ByPassFlag[i];
		}
		CloseFile(handle);
	}
	
	sprintf(Path, "%s\\Setup_AutoMeas.ini", Path_Setup);
	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	
	if(handle < 0)
	{
		MessagePopup("NO FILE FOR AutoMeas", "CHECK PROGRAM SETUP - AutoMeas");
		ReMeasUse = 0;
		ContinuousNgAlarmUse = 0;
		ContinuousNgCount = 2;
	}
	else
	{
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		ReMeasUse = atoi(temp1);
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		ContinuousNgAlarmUse = atoi(temp1);
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		ContinuousNgCount = atoi(temp1);
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		Opt_Time_1 = atof(temp1);
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		Safety_Door = atoi(temp1);
		CloseFile(handle);
		
	}	

	sprintf(Path, "%s\\Setup_WorkTime.ini", Path_Setup);
	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	
	if(handle < 0)
	{
		MessagePopup("NO FILE FOR WorkTime", "CHECK PROGRAM SETUP - WorkTime");
		sprintf(DayStartTime, "08:00");
		sprintf(NightStartTime, "20:00");
		SeperateDayNight = 0;
	}
	else
	{
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		Scan(temp1, "%s>%s", DayStartTime);
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		Scan(temp1, "%s>%s", NightStartTime);
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		SeperateDayNight = atoi(temp1);
		CloseFile(handle);
	}
	
	SetCtrlVal(setuppanel, SETUP_BYPASS_1, ByPassFlag[0]);
	SetCtrlVal(setuppanel, SETUP_BYPASS_2, ByPassFlag[1]);
	SetCtrlVal(setuppanel, SETUP_BYPASS_3, ByPassFlag[2]);
	SetCtrlVal(setuppanel, SETUP_BYPASS_4, ByPassFlag[3]);
	
	SetCtrlVal(setuppanel, SETUP_RE_MEAS, ReMeasUse);
	SetCtrlVal(setuppanel, SETUP_CONTINUOUS_NG, ContinuousNgAlarmUse);
	SetCtrlVal(setuppanel, SETUP_CONTINUOUS_NG_CNT, ContinuousNgCount);
	SetCtrlVal(setuppanel, SETUP_OPTION_TIME_1, Opt_Time_1);
	SetCtrlVal(setuppanel, SETUP_SAFETY_DOOR, Safety_Door);
	
	PlcData[176] = Safety_Door;
	
	SetCtrlVal(setuppanel, SETUP_TIME_DAY, DayStartTime);
	SetCtrlVal(setuppanel, SETUP_TIME_NIGHT, NightStartTime);
	SetCtrlVal(setuppanel, SETUP_SEPERATE_DAY, SeperateDayNight);
}

void 	SaveSetup(void)
{
	char 	Path[1024] = {0,};
	char	temp1[1024] = {0,};
	int		handle, i, j, a;
	double 	t;
		
	GetCtrlVal(setuppanel, SETUP_BYPASS_1, &ByPassFlag[0]);
	GetCtrlVal(setuppanel, SETUP_BYPASS_2, &ByPassFlag[1]);
	GetCtrlVal(setuppanel, SETUP_BYPASS_3, &ByPassFlag[2]);
	GetCtrlVal(setuppanel, SETUP_BYPASS_4, &ByPassFlag[3]);
	
	GetCtrlVal(setuppanel, SETUP_RE_MEAS, &ReMeasUse);
	GetCtrlVal(setuppanel, SETUP_CONTINUOUS_NG, &ContinuousNgAlarmUse);
	GetCtrlVal(setuppanel, SETUP_CONTINUOUS_NG_CNT, &ContinuousNgCount);
	GetCtrlVal(setuppanel, SETUP_OPTION_TIME_1, &Opt_Time_1);
	GetCtrlVal(setuppanel, SETUP_SAFETY_DOOR, &Safety_Door);
	
	GetCtrlVal(setuppanel, SETUP_TIME_DAY, DayStartTime);
	GetCtrlVal(setuppanel, SETUP_TIME_NIGHT, NightStartTime);
	GetCtrlVal(setuppanel, SETUP_SEPERATE_DAY, &SeperateDayNight);
	
	sprintf(Path, "%s\\Setup_Bypass.ini", Path_Setup);
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR BYPASS", "CHECK PROGRAM SETUP - BYPASS");
	else
	{
		for(i = 0 ; i < 4 ; i ++)
		{
			sprintf(temp1, "BYPASS%d(0:NonUse, 1:Use)", i+1);
			WriteLine(handle, temp1, -1);
			sprintf(temp1, "%d", ByPassFlag[i]);
			WriteLine(handle, temp1, -1);
			PlcData[40+i] = ByPassFlag[i];
		}
		CloseFile(handle);
	}
	
	sprintf(Path, "%s\\Setup_AutoMeas.ini", Path_Setup);
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR AutoMeas", "CHECK PROGRAM SETUP - AutoMeas");
	else
	{
		sprintf(temp1, "NG RE-MEAS USE(0:NonUse, 1:Use)");
		WriteLine(handle, temp1, -1);
		sprintf(temp1, "%d", ReMeasUse);
		WriteLine(handle, temp1, -1);
		
		sprintf(temp1, "CONTINUOUS NG ALARM USE(0:NonUse, 1:Use)");
		WriteLine(handle, temp1, -1);
		sprintf(temp1, "%d", ContinuousNgAlarmUse);
		WriteLine(handle, temp1, -1);

		sprintf(temp1, "CONTINUOUS NG COUNT(more than 2)");
		WriteLine(handle, temp1, -1);
		sprintf(temp1, "%d", ContinuousNgCount);
		WriteLine(handle, temp1, -1);
		
		sprintf(temp1, "OPTION TIME");
		WriteLine(handle, temp1, -1);
		sprintf(temp1, "%.1f", Opt_Time_1);
		WriteLine(handle, temp1, -1);
		
		sprintf(temp1, "SAFEY DOOR(0:NonUse, 1:Use)");
		WriteLine(handle, temp1, -1);
		sprintf(temp1, "%d", Safety_Door);
		WriteLine(handle, temp1, -1);
		
		CloseFile(handle);
	}	
	
	PlcData[176] = Safety_Door;


	sprintf(Path, "%s\\Setup_WorkTime.ini", Path_Setup);
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR WorkTime", "CHECK PROGRAM SETUP - WorkTime");
	else
	{
		sprintf(temp1, "DAY START TIME :");
		WriteLine(handle, temp1, -1);
		sprintf(temp1, "%s", DayStartTime);
		WriteLine(handle, temp1, -1);
		
		sprintf(temp1, "NIGHT START TIME :");
		WriteLine(handle, temp1, -1);
		sprintf(temp1, "%s", NightStartTime);
		WriteLine(handle, temp1, -1);

		sprintf(temp1, "SEPERATE DATA FILE(0:ALL DAY, 1: DAY/NIGHT)");
		WriteLine(handle, temp1, -1);
		sprintf(temp1, "%d", SeperateDayNight);
		WriteLine(handle, temp1, -1);
		
		CloseFile(handle);
	}
}

void	InitLogPath()
{
	char	AddRule[128] = {0,};
	char 	Path[1024] = {0,};
	int 	YYYY, MM, DD;

	GetSystemDate(&MM, &DD, &YYYY);
	GetCtrlVal(setuppanel, SETUP_PATH_HISTORY, Path_History_Reg);
	
	switch (Rule_History)
	{
		case 0:	//NONE
			strcpy(Path_History, Path_History_Reg);	
			sprintf(AddRule, "\\%s.Log", CurrDate);  
			strcat(Path_History, AddRule);		
			break;
		case 1:	//YYYYMMDD
			sprintf(AddRule, "\\%04d%02d%02d", YYYY, MM, DD);
			sprintf(Path, "%s%s", Path_History_Reg, AddRule);
			if( SetDir(Path) )	MakeDir(Path);
						
			sprintf(AddRule, "\\%s.Log", CurrDate); 
			strcat(Path, AddRule);	
			strcpy(Path_History, Path);
			break;
		case 2:	//YYYY\\MMDD
			sprintf(AddRule, "\\%04d", YYYY);
			sprintf(Path, "%s%s", Path_History_Reg, AddRule);
			if( SetDir(Path) )	MakeDir(Path);	
			else
			{
				sprintf(AddRule, "\\%02d%02d", MM, DD);
				strcat(Path, AddRule);
				if( SetDir(Path) )	MakeDir(Path);
			}
						
			sprintf(AddRule, "\\%s.Log", CurrDate); 
			strcat(Path, AddRule);	
			strcpy(Path_History, Path);
			break;
		case 3:	//YYYY\\MM\\DD
			sprintf(AddRule, "\\%04d", YYYY);
			sprintf(Path, "%s%s", Path_History_Reg, AddRule);
			if( SetDir(Path) )	MakeDir(Path);
			else
			{
				sprintf(AddRule, "\\%02d", MM);
				strcat(Path, AddRule);
				if( SetDir(Path) )	MakeDir(Path);
				else
				{
					sprintf(AddRule, "\\%02d", DD);
					strcat(Path, AddRule);
					if( SetDir(Path) )	MakeDir(Path);
				}
			}
						
			sprintf(AddRule, "\\%s.Log", CurrDate); 
			strcat(Path, AddRule);	
			strcpy(Path_History, Path);
			break;
		default:
			break;
	}	
}

int 	GetRegHdd(void)
{
	int ret;
//	char HddId[512] = {"5&25d5d29f&0&000000"};	//LAON
	char HddId[512] = {"5&2f9ef5d6&0&0.0.0"};
	char GetHddId[512];	
	
	unsigned char *buffer = NULL;
	unsigned int size;	
	
	char 	Temp[1024] = {0,};
	char 	InitRoot[1024] = {0,};
	unsigned char RegTemp[1024] = {0,};
	
	sprintf(InitRoot, "SOFTWARE\\%s", INIT_ROOT);
	
	RegReadString (REGKEY_HKLM, "system\\controlSet001\\Services\\disk\\Enum", "0", NULL, 0, &size);
	buffer = (unsigned char*) malloc(size * sizeof(unsigned char));

	if (buffer != NULL)
	{
		RegReadString (REGKEY_HKLM, "system\\controlSet001\\Services\\disk\\Enum", "0", buffer, size, &size);
		sprintf(GetHddId, "%s", buffer);
		
		//Check Hdd
		memset(RegTemp, 0, sizeof(RegTemp));
		ret = RegReadString (REGKEY_HKCU, InitRoot, "Check_Hdd", RegTemp, 1024, &size);
		
		USE_HDD_CHECK = atoi(RegTemp);	
		if(USE_HDD_CHECK > 0)
		{
			memset(RegTemp, 0, sizeof(RegTemp));		
			RegReadString (REGKEY_HKCU, InitRoot, "Hdd_Id", RegTemp, 1024, &size);
			sprintf(HddId, "%s", RegTemp);
			ret = FindPattern(GetHddId, 0, strlen(GetHddId), HddId, 1, 0);
		}	
		else
			ret = 1;
		
		free (buffer);
		if(ret < 0)
			return -1;
		else
			return 1;
	}
	else
		return -1;
}

void 	GetRegPath(void)
{
	int		ret;
	char 	Temp[1024] = {0,};
	char 	InitRoot[1024] = {0,};
	unsigned int size;
	unsigned char RegTemp[1024] = {0,};
	
	sprintf(InitRoot, "SOFTWARE\\%s", INIT_ROOT);
	
	//Path_Model
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "Path_Model", RegTemp, 1024, &size);
	if (ret != 0)
	{
		GetDir(Temp);
		sprintf(Path_Model, "%s\\MODEL", Temp);
		ret = RegWriteString (REGKEY_HKCU, InitRoot, "Path_Model", Path_Model);
		if(ret != 0)
			MessagePopup ("P Registry Error", GetGeneralErrorString (ret));
	}
	else
		sprintf(Path_Model, "%s", RegTemp);
	
	//Path_Result
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "Path_Result", RegTemp, 1024, &size);
	if (ret != 0)
	{
		GetDir(Temp);
		sprintf(Path_Result, "%s\\RESULT", Temp);
		ret = RegWriteString (REGKEY_HKCU, InitRoot, "Path_Result", Path_Result);
		if(ret != 0)
			MessagePopup ("P Registry Error", GetGeneralErrorString (ret));
	}
	else
		sprintf(Path_Result, "%s", RegTemp);
	
	//Path_History
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "Path_History", RegTemp, 1024, &size);
	if (ret != 0)
	{
		GetDir(Temp);
		sprintf(Path_History_Reg, "%s\\HISTORY", Temp);
		ret = RegWriteString (REGKEY_HKCU, InitRoot, "Path_History", Path_History_Reg);
		if(ret != 0)
			MessagePopup ("P Registry Error", GetGeneralErrorString (ret));
	}
	else
		sprintf(Path_History_Reg, "%s", RegTemp);
	
	//Path_Setup
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "Path_Setup", RegTemp, 1024, &size);
	if (ret != 0)
	{
		GetDir(Temp);
		sprintf(Path_Setup, "%s\\SETUP", Temp);
		ret = RegWriteString (REGKEY_HKCU, InitRoot, "Path_Setup", Path_Setup);
		if(ret != 0)
			MessagePopup ("P Registry Error", GetGeneralErrorString (ret));
	}
	else
		sprintf(Path_Setup, "%s", RegTemp);
	
	//Rule_Result
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "Rule_Result", RegTemp, 1024, &size);
	if (ret != 0)
	{
		Rule_Result = 0;
		sprintf(RegTemp, "%d", Rule_Result);
		ret = RegWriteString (REGKEY_HKCU, InitRoot, "Rule_Result", RegTemp);
		if(ret != 0)
			MessagePopup ("UD Registry Error", GetGeneralErrorString (ret));
	}
	else
		Rule_Result = atoi(RegTemp);
	
	//Rule_History
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "Rule_History", RegTemp, 1024, &size);
	if (ret != 0)
	{
		Rule_History = 0;
		sprintf(RegTemp, "%d", Rule_History);
		ret = RegWriteString (REGKEY_HKCU, InitRoot, "Rule_History", RegTemp);
		if(ret != 0)
			MessagePopup ("UD Registry Error", GetGeneralErrorString (ret));
	}
	else
		Rule_History = atoi(RegTemp);
}

void 	SetRegPath(void)
{
	int		ret;
	char 	InitRoot[1024] = {0,};
	unsigned char RegTemp[1024] = {0,};
	
	sprintf(InitRoot, "SOFTWARE\\%s", INIT_ROOT);	
	
	//Path_Model
	memset(RegTemp, 0, sizeof(RegTemp));
	sprintf(RegTemp, "%s", Path_Model);
	ret = RegWriteString (REGKEY_HKCU, InitRoot, "Path_Model", RegTemp);
	if(ret != 0)	
		MessagePopup ("P Registry Error", GetGeneralErrorString (ret));
	
	//Path_Result
	memset(RegTemp, 0, sizeof(RegTemp));
	sprintf(RegTemp, "%s", Path_Result);
	ret = RegWriteString (REGKEY_HKCU, InitRoot, "Path_Result", RegTemp);
	if(ret != 0)	
		MessagePopup ("P Registry Error", GetGeneralErrorString (ret));

	//Path_History
	memset(RegTemp, 0, sizeof(RegTemp));
	sprintf(RegTemp, "%s", Path_History_Reg);
	ret = RegWriteString (REGKEY_HKCU, InitRoot, "Path_History", RegTemp);
	if(ret != 0)	
		MessagePopup ("P Registry Error", GetGeneralErrorString (ret));

	//Path_Setup
	memset(RegTemp, 0, sizeof(RegTemp));
	sprintf(RegTemp, "%s", Path_Setup);
	ret = RegWriteString (REGKEY_HKCU, InitRoot, "Path_Setup", RegTemp);
	if(ret != 0)	
		MessagePopup ("P Registry Error", GetGeneralErrorString (ret));
	
	//Rule_Result
	memset(RegTemp, 0, sizeof(RegTemp));
	sprintf(RegTemp, "%d", Rule_Result);
	ret = RegWriteString (REGKEY_HKCU, InitRoot, "Rule_Result", RegTemp);
	if(ret != 0)	
		MessagePopup ("P Registry Error", GetGeneralErrorString (ret));
	
	//Rule_History
	memset(RegTemp, 0, sizeof(RegTemp));
	sprintf(RegTemp, "%d", Rule_History);
	ret = RegWriteString (REGKEY_HKCU, InitRoot, "Rule_History", RegTemp);
	if(ret != 0)	
		MessagePopup ("P Registry Error", GetGeneralErrorString (ret));
}

int		GetRegUsedDays(void)
{
	int 	ret;
	char 	InitRoot[1024] = {0,};
	unsigned char RegTemp[1024] = {0,};	
	unsigned int size;
	
	sprintf(InitRoot, "SOFTWARE\\%s", INIT_ROOT);
	
	//Check Day
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "Check_Days", RegTemp, 1024, &size);
	USE_DAY_CHECK = atoi(RegTemp);	
	if(USE_DAY_CHECK < 1)
		return 1;
	
	//Used_Days
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "Used_Days", RegTemp, 1024, &size);
	if (ret != 0)
	{
		sprintf(RegTemp, "%d", Used_Days);
		ret = RegWriteString (REGKEY_HKCU, InitRoot, "Used_Days", RegTemp);
		if(ret != 0)
			MessagePopup ("UD Registry Error", GetGeneralErrorString (ret));
	}
	else
		Used_Days = atoi(RegTemp);	
		
	//Max_Days
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "Max_Days", RegTemp, 1024, &size);
	MAX_USED_DAYS = atoi(RegTemp);	
	
	if(Used_Days > MAX_USED_DAYS)
		return -1;
	else
		return 1;
}

void	SetRegUsedDays(void)
{
	int ret;
	char 	InitRoot[1024] = {0,};
	unsigned char RegTemp[1024] = {0,};
	
	sprintf(InitRoot, "SOFTWARE\\%s", INIT_ROOT);
	
	//Used_Days
	memset(RegTemp, 0, sizeof(RegTemp));
	sprintf(RegTemp, "%d", Used_Days);
	ret = RegWriteString (REGKEY_HKCU, InitRoot, "Used_Days", RegTemp);
	if(ret != 0)	
		MessagePopup ("P Registry Error", GetGeneralErrorString (ret));	
}

void	GetRegUserPw(void)
{
	int ret;
	char 	InitRoot[1024] = {0,};	
	unsigned char RegTemp[1024] = {0,};	
	unsigned int size;
	
	sprintf(InitRoot, "SOFTWARE\\%s", INIT_ROOT);
	
	//UserPassword
	memset(RegTemp, 0, sizeof(RegTemp));
	ret = RegReadString (REGKEY_HKCU, InitRoot, "UserPassword", RegTemp, 1024, &size);
	if (ret != 0)
	{
		sprintf(UserPassword, "");
		ret = RegWriteString (REGKEY_HKCU, InitRoot, "UserPassword", UserPassword);
		if(ret != 0)
			MessagePopup ("P Registry Error", GetGeneralErrorString (ret));
	}
	else
		sprintf(UserPassword, "%s", RegTemp);
}

void	SetRegUserPw(void)
{
	int ret;
	char 	InitRoot[1024] = {0,};	
	unsigned char RegTemp[1024] = {0,};
	
	sprintf(InitRoot, "SOFTWARE\\%s", INIT_ROOT);
	
	//UserPassword
	memset(RegTemp, 0, sizeof(RegTemp));
	sprintf(RegTemp, "%s", UserPassword);
	ret = RegWriteString (REGKEY_HKCU, InitRoot, "UserPassword", RegTemp);
	if(ret != 0)	
		MessagePopup ("P Registry Error", GetGeneralErrorString (ret));	
}

int CVICALLBACK Cb_SetupPanel (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			RemovePopup(0);
			HidePanel(panel);
			
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Rollback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetRegPath();
			
			SetCtrlVal(panel, SETUP_PATH_MODEL, Path_Model);
			SetCtrlVal(panel, SETUP_PATH_RESULT, Path_Result);
			SetCtrlVal(panel, SETUP_PATH_HISTORY, Path_History_Reg);
			SetCtrlVal(panel, SETUP_PATH_SETUP, Path_Setup);

			SetCtrlVal(setuppanel, SETUP_PATH_RULE_HISTORY, Rule_History);
			SetCtrlVal(setuppanel, SETUP_PATH_RULE_RESULT, Rule_Result);
			
			LoadSetup();
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Save (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(ConfirmPopup("SAVE", "SAVE?"))
			{
				GetCtrlVal(panel, SETUP_PATH_MODEL, Path_Model);
				GetCtrlVal(panel, SETUP_PATH_RESULT, Path_Result);
				GetCtrlVal(panel, SETUP_PATH_HISTORY, Path_History_Reg);
				GetCtrlVal(panel, SETUP_PATH_SETUP, Path_Setup);

				GetCtrlVal(setuppanel, SETUP_PATH_RULE_HISTORY, &Rule_History);
				GetCtrlVal(setuppanel, SETUP_PATH_RULE_RESULT, &Rule_Result);
				
				SetRegPath();
				InitLogPath();
				SaveSetup();
				GetDataFileName();
				GetSaveDataNum();
				LogUpdate("Program Setup Save");
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Path_Pop_Model (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char temp[1024] = {0,};
			if(DirSelectPopup("c:\\", "PATH : MODEL", 1, 1, temp))
			{
				SetCtrlVal(setuppanel, SETUP_PATH_MODEL, temp);
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Path_Pop_Result (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char temp[1024] = {0,};
			if(DirSelectPopup("c:\\", "PATH : RESULT", 1, 1, temp))
			{
				SetCtrlVal(setuppanel, SETUP_PATH_RESULT, temp);
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Path_Pop_History (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char temp[1024] = {0,};
			if(DirSelectPopup("c:\\", "PATH : HISTORY", 1, 1, temp))
			{
				SetCtrlVal(setuppanel, SETUP_PATH_HISTORY, temp);
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Path_Pop_Setup (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char temp[1024] = {0,};
			if(DirSelectPopup("c:\\", "PATH : SETUP", 1, 1, temp))
			{
				SetCtrlVal(setuppanel, SETUP_PATH_SETUP, temp);
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Img_Button (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			int a;
			GetCtrlVal(panel, control, &a);
			SetCtrlVal(panel, control, !a);

			break;
	}
	return 0;
}

