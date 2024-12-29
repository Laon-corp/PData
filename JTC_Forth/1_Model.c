#include "A_Global.h"

void SendModelBit(void)
{
	int		i, a = 0x01;
	
	for(i = 0 ; i < 8 ; i ++)						
	{
		if((ModelNo + 1) & a)
			PlcData[48 + i] = 1;
		else
			PlcData[48 + i] = 0;
		a <<= 1;
	}	
}

void LoadModel(void)
{
	int handle, i;
	char Path[1024] = {0,};
	char temp1[1024] = {0,};
	
	sprintf(Path, "%s\\ModelName.ini", Path_Model);
	
	if( SetDir(Path_Model) )	MakeDir (Path_Model);
		
	if(GetFileInfo(Path, &i) == 0)	
	{
		handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
		if(handle < 0)
			MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
		else
		{
			WriteLine(handle, "Model Count:", -1);
			WriteLine(handle, "0", -1);
			WriteLine(handle, "Model Name:", -1);
			WriteLine(handle, "Current Model No:", -1);
			CloseFile(handle);
			ModelCount = 0;		
		}
	}
	else
	{
		handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
		if(handle < 0)
			MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
		else
		{
			ReadLine(handle, temp1, -1);
			ReadLine(handle, temp1, -1);
			ModelCount = atoi(temp1);
			ReadLine(handle, temp1, -1);
			for(i = 0 ; i < ModelCount ; i ++)
			{
				ReadLine(handle, temp1, -1);
				strcpy(ModelName[i], temp1);
			}
			ReadLine(handle, temp1, -1);
			ReadLine(handle, temp1, -1);
			ModelNo = atoi(temp1) - 1;
			CloseFile(handle);
		}
	}
	
	if(ModelCount > 0)
	{
		LoadModelData();
		LoadZeroTableData();
		
		ManuItemSelected = 0;
		SetCtrlVal(tab_manual, TAB_MANU_ITEM, Model[ManuItemSelected].Name);
	}
}

void SaveModel(void)
{
	int		handle, i;
	char	Path[1024] = {0,};
	char	temp[1024] = {0,};	
	char	nameTemp[1024] = {0,};	
	
	sprintf(Path, "%s\\ModelName.ini", Path_Model);
	
	if( SetDir(Path_Model) )	MakeDir (Path_Model);
	
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if(handle < 0)
	{
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	}
	else
	{
		WriteLine(handle, "Model Count:", -1);
		GetNumListItems(modelpanel, MODEL_LIST_MODEL, &ModelCount);
		sprintf(temp, "%d", ModelCount);
		WriteLine(handle, temp, -1);
		sprintf(temp, "Model Name:");
		WriteLine(handle, temp, -1);
		for(i = 0 ; i < ModelCount ; i ++)
		{
			memset(nameTemp, 0, sizeof(nameTemp));
			GetLabelFromIndex(modelpanel, MODEL_LIST_MODEL, i, temp);
			CopyBytes(nameTemp, 0, temp, 4, strlen(temp) - 4);
			strcpy(ModelName[i], nameTemp);
			WriteLine(handle, ModelName[i], -1);
		}
		WriteLine(handle, "Current Model No:", -1);
		sprintf(temp, "%d", ModelNo + 1);
		WriteLine(handle, temp, -1);
		CloseFile(handle);
	}
}

void DeleteSaveModel(void)
{
	int		handle, i;
	char	Path[1024] = {0,};
	char	temp[1024] = {0,};	
	char	nameTemp[1024] = {0,};	
	
	sprintf(Path, "%s\\ModelName.ini", Path_Model);
	
	if( SetDir(Path_Model) )	MakeDir (Path_Model);
	
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if(handle < 0)
	{
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	}
	else
	{
		WriteLine(handle, "Model Count:", -1);
		sprintf(temp, "%d", ModelCount-1);
		WriteLine(handle, temp, -1);
		sprintf(temp, "Model Name:");
		WriteLine(handle, temp, -1);
		for(i = 0 ; i < ModelCount ; i ++)
		{
			memset(nameTemp, 0, sizeof(nameTemp));
			GetLabelFromIndex(modelpanel, MODEL_LIST_MODEL, i, temp);
			CopyBytes(nameTemp, 0, temp, 4, strlen(temp) - 4);
			strcpy(ModelName[i], nameTemp);
			if(strcmp(ModelName[i], ModelName[ModelNo]) != 0)
				WriteLine(handle, ModelName[i], -1);
		}
		WriteLine(handle, "Current Model No:", -1);
		sprintf(temp, "%d", ModelNo);
		WriteLine(handle, temp, -1);
		CloseFile(handle);
	}
}

void	SetModel_BoxPos(void)
{
	int i;
	int PLeft, PTop, PWidth, PHeight;
	char 	fmt[10] = {0,},
			temp1[64] = {0,};
	
	GetCtrlAttribute(tab_auto, TAB_AUTO_IMG, ATTR_TOP, 		&PTop);
	GetCtrlAttribute(tab_auto, TAB_AUTO_IMG, ATTR_LEFT, 	&PLeft);
	GetCtrlAttribute(tab_auto, TAB_AUTO_IMG, ATTR_HEIGHT, 	&PHeight);
	GetCtrlAttribute(tab_auto, TAB_AUTO_IMG, ATTR_WIDTH, 	&PWidth);
	
	for(i = 0 ; i < MAX_MEAS_POINTS ; i ++)
		SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_VISIBLE, 0);

	for(i = 0 ; i < MeasPoints ; i ++)
	{
		if(BoxPos[i].LabX < PLeft || BoxPos[i].LabX > (PWidth + PLeft))
			BoxPos[i].LabX = PLeft + 10;

		if(BoxPos[i].LabY < PTop || BoxPos[i].LabY > (PTop + PHeight))
			BoxPos[i].LabY = PTop + 10;

		if(BoxPos[i].BoxX < PLeft || BoxPos[i].BoxX > (PWidth + PLeft))
			BoxPos[i].BoxX = PLeft + 30;

		if(BoxPos[i].BoxY < PTop || BoxPos[i].BoxY > (PTop + PHeight))
			BoxPos[i].BoxY = PTop + 30;
		
		SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_TOP, BoxPos[i].BoxY);		
		SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_LEFT, BoxPos[i].BoxX);		
		SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_WIDTH, BoxPos[i].BoxWidth);
		SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_LABEL_TOP, BoxPos[i].LabY);		
		SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_LABEL_LEFT, BoxPos[i].LabX);		
	 
		sprintf(fmt, "%%.%df", Model[i].Unit);
		sprintf(temp1, fmt, 0.0);
		SetCtrlVal(tab_auto, PointCtrl[i], temp1);
		
		SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_LABEL_TEXT, Model[i].Name);
		
		SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_VISIBLE, 1);
	}
			
	for(i = 0 ; i < MeasPoints ; i ++)
	{
//		SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_ZPLANE_POSITION, 0);
		if(i == 0)
		{
			SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_LABEL_BGCOLOR, 0x007DC8FF);
			BeforePointCtrl = PointCtrl[i];	
		}
		else
		{
			SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_LABEL_BGCOLOR, 0x00C0C0C0);
		}
	}
}

void	SetModel_MeasPoints(void)
{
	int 	i;
	
	//model - MeasPoints
	GetNumTableRows (model_tab_Meas, TABPANEL_MEAS_TABLE, &i);
	
	if(i < MeasPoints)
	{
		SetCtrlAttribute (model_tab_Meas, TABPANEL_MEAS_TABLE, ATTR_TABLE_MODE, VAL_COLUMN);
		if(i == 0)	InsertTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, 	 1, MeasPoints, VAL_USE_MASTER_CELL_TYPE);

		else		InsertTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, 	 i, MeasPoints-i, VAL_USE_MASTER_CELL_TYPE);
	}
	else if(i > MeasPoints)
		DeleteTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, 	MeasPoints+1, i-MeasPoints);

	
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		SetTableRowAttribute(model_tab_Meas, TABPANEL_MEAS_TABLE, i+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);				
		SetTableRowAttribute(model_tab_Meas, TABPANEL_MEAS_TABLE, i+1, ATTR_ROW_HEIGHT, 35);
		SetTableCellRangeAttribute(model_tab_Meas, TABPANEL_MEAS_TABLE, MakeRect(i+1, 2, 1, 7), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
	}	
	
	//auto
	DeleteListItem(tab_auto, TAB_AUTO_RING_MEASPOINT, 0, -1);
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(1, i+1), Model[i].Name);
		SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(2, i+1), Model[i].Master);
	    SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(3, i+1), Model[i].Comp);
		SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(4, i+1), Model[i].Fact);
		SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(5, i+1), Model[i].LCL);
		SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(6, i+1), Model[i].LWL);
		SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(7, i+1), Model[i].UWL);
		SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(8, i+1), Model[i].UCL);
		
		InsertListItem(tab_auto, TAB_AUTO_RING_MEASPOINT, i, Model[i].Name, i);
	}
	
	//Graph
	DeleteListItem(tab_graph, TAB_GRAPH_RING_MEASPOINT, 0, -1);	
	InsertListItem(tab_graph, TAB_GRAPH_RING_MEASPOINT, 0, "NONE", 0);
	for(i = 0 ; i < MeasPoints ; i ++)
		InsertListItem(tab_graph, TAB_GRAPH_RING_MEASPOINT, i+1, Model[i].Name, i+1);
}

void	SetModel_Calculation(void)
{
	int 	i, j;
	char	pointTemp[17][10] = {"NONE", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
	char	calcTemp[5][20] = {"AVR", "MIN", "MAX", "MAX-MIN", "REFERED"};
	char	useTemp[2][10] = {"N", "Y"};
	
	//model - MeasPoints
	GetNumTableRows (model_tab_Calc, TABPANEL_2_CALC_TABLE, &i);
	
	if(i < MeasPoints)
	{
		SetCtrlAttribute (model_tab_Calc, TABPANEL_2_CALC_TABLE, ATTR_TABLE_MODE, VAL_COLUMN);
		if(i == 0)	InsertTableRows(model_tab_Calc, TABPANEL_2_CALC_TABLE,   1, MeasPoints, VAL_USE_MASTER_CELL_TYPE);
		else		InsertTableRows(model_tab_Calc, TABPANEL_2_CALC_TABLE,   i, MeasPoints-i, VAL_USE_MASTER_CELL_TYPE);
	}
	else if(i > MeasPoints)
		DeleteTableRows(model_tab_Calc, TABPANEL_2_CALC_TABLE, 	MeasPoints+1, i-MeasPoints);

	
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		SetTableRowAttribute(model_tab_Calc, TABPANEL_2_CALC_TABLE, i+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);
		SetTableRowAttribute(model_tab_Calc, TABPANEL_2_CALC_TABLE, i+1, ATTR_ROW_HEIGHT, 35);
		
		SetTableCellRangeAttribute(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakeRect(i+1, 2, 1, 6), ATTR_CELL_TYPE, VAL_CELL_RING);
		for(j = 0 ; j < 17 ; j ++)
			InsertTableCellRangeRingItem(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakeRect(i+1, 2, 1, 4), j, pointTemp[j]);
		for(j = 0 ; j < 5 ; j ++)
			InsertTableCellRangeRingItem(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakeRect(i+1, 6, 1, 1), j, calcTemp[j]);
		for(j = 0 ; j < 2 ; j ++)
			InsertTableCellRangeRingItem(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakeRect(i+1, 7, 1, 1), j, useTemp[j]);
	}	
	
	//model - Calculation
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(1, i+1), Model[i].Name);		
		
		if(Model[i].P1 == 999)	SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(2, i+1), "NONE");		
		else					SetTableCellValFromIndex(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(2, i+1), Model[i].P1+1);
	
		if(Model[i].P2 == 999)	SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(3, i+1), "NONE");		
		else					SetTableCellValFromIndex(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(3, i+1), Model[i].P2+1);

		if(Model[i].P3 == 999)	SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(4, i+1), "NONE");		
		else					SetTableCellValFromIndex(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(4, i+1), Model[i].P3+1);

		if(Model[i].P4 == 999)	SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(5, i+1), "NONE");		
		else					SetTableCellValFromIndex(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(5, i+1), Model[i].P4+1);
		
		SetTableCellValFromIndex(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(6, i+1), Model[i].Cal);
		SetTableCellValFromIndex(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(7, i+1), Model[i].Use);
	}
	
}

void	SetModel_Mark(void)
{
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_1, Couth.CharHeight);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_2, Couth.CharWidth);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_3, Couth.Font);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_4, Couth.Spacing);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_5, Couth.Density);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_6, Couth.Xcoo);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_7, Couth.Ycoo);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_8, Couth.Zcoo);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_9, Couth.Angle);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_10, Couth.Diameter);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_11, Couth.Con);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_12, Couth.Hmirror);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_13, Couth.Vmirror);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_14, Couth.Speed);
	SetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_15, Couth.Force);	
}

void	LoadModel_MeasPoints(void)
{
	int 	i, handle;
	char 	Path[1024] = {0,},
			temp1[1024] = {0,};
	
	//model - MeasPoints
	
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )	MakeDir(Path);
	sprintf(Path, "%s\\%s\\MeasPoints.ini", Path_Model, ModelName[ModelNo]);

	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		MeasPoints = atoi(temp1);

		for(i = 0 ; i < MeasPoints ; i ++)
		{
			ReadLine(handle, temp1, -1);	//NAME
			ReadLine(handle, Model[i].Name, -1);	
			ReadLine(handle, temp1, -1);	//COMP FACTOR LCL LWL UWL UCL UNIT
			ReadLine(handle, temp1, -1);	
			Scan(temp1, "%s>%f%f%f%f%f%f%f%i%i", 
				 &Model[i].Master, &Model[i].Comp, &Model[i].Fact, &Model[i].LCL, &Model[i].LWL, &Model[i].UWL, &Model[i].UCL, &Model[i].Unit, &Model[i].Sig);
		}
		CloseFile(handle);
	}	
	SetModel_MeasPoints();
}

void	LoadModel_Calculation(void)
{
	int 	i, j, handle;
	char 	Path[1024] = {0,},
			temp1[1024] = {0,};
	char	sign[4][4] = {0,};
	char	point[7][10] = {0,};	

	//model - Calculation
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )			MakeDir(Path);
	sprintf(Path, "%s\\%s\\Cal.ini", Path_Model, ModelName[ModelNo]);
	
	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		for(i = 0 ; i < MeasPoints ; i ++)
		{
			ReadLine(handle, temp1, -1);	//point	
			ReadLine(handle, temp1, -1);	//sign
			Scan(temp1, "%s>%s%s%s%s", sign[0], sign[1], sign[2], sign[3]);
			if(strcmp(sign[0], "+") == 0)	Model[i].sign1 = 1;
			else 							Model[i].sign1 = -1;
			if(strcmp(sign[1], "+") == 0)	Model[i].sign2 = 1;
			else 							Model[i].sign2 = -1;
			if(strcmp(sign[2], "+") == 0)	Model[i].sign3 = 1;
			else 							Model[i].sign3 = -1;
			if(strcmp(sign[3], "+") == 0)	Model[i].sign4 = 1;
			else 							Model[i].sign4 = -1;
		
			ReadLine(handle, temp1, -1);	//P1~P4 Cal Use
			Scan(temp1, "%s>%s%s%s%s%s%s%i", point[0], point[1], point[2], point[3], point[4], point[5], &j);
			if(strcmp(point[0], "NONE") == 0)	Model[i].P1 = 999;
			else								Model[i].P1 = atoi(point[0]) - 1;
			if(strcmp(point[1], "NONE") == 0)	Model[i].P2 = 999;
			else								Model[i].P2 = atoi(point[1]) - 1;
			if(strcmp(point[2], "NONE") == 0)	Model[i].P3 = 999;
			else								Model[i].P3 = atoi(point[2]) - 1;
			if(strcmp(point[3], "NONE") == 0)	Model[i].P4 = 999;
			else								Model[i].P4 = atoi(point[3]) - 1;
		
			if(strcmp(point[4], "AVR") == 0)			Model[i].Cal = 0;
			else if(strcmp(point[4], "MIN") == 0)		Model[i].Cal = 1;
			else if(strcmp(point[4], "MAX") == 0)		Model[i].Cal = 2;
			else if(strcmp(point[4], "MAX-MIN") == 0)	Model[i].Cal = 3;
			else 										Model[i].Cal = 4;
			
			if(strcmp(point[5], "Y") == 0)			Model[i].Use = 1;
			else									Model[i].Use = 0;
			
			Model[i].Offset = j;
			if(Model[i].Offset > 0)
			{
				if(Model[i].Offset == 1)
					SetCtrlVal(tab_auto, TAB_AUTO_IF_TXT_1, Model[i].Name);
				else if(Model[i].Offset == 2)
					SetCtrlVal(tab_auto, TAB_AUTO_IF_TXT_2, Model[i].Name);
				else if(Model[i].Offset == 3)
					SetCtrlVal(tab_auto, TAB_AUTO_IF_TXT_3, Model[i].Name);
				else if(Model[i].Offset == 4)
					SetCtrlVal(tab_auto, TAB_AUTO_IF_TXT_4, Model[i].Name);
				else if(Model[i].Offset == 5)
					SetCtrlVal(tab_auto, TAB_AUTO_IF_TXT_5, Model[i].Name);
				else if(Model[i].Offset == 6)
					SetCtrlVal(tab_auto, TAB_AUTO_IF_TXT_6, Model[i].Name);
				else if(Model[i].Offset == 7)
					SetCtrlVal(tab_auto, TAB_AUTO_IF_TXT_7, Model[i].Name);
				else if(Model[i].Offset == 8)
					SetCtrlVal(tab_auto, TAB_AUTO_IF_TXT_8, Model[i].Name);
				else
					;
			}
		}
		CloseFile(handle);
	}	
	SetModel_Calculation();
}

void	LoadModel_Mark(void)
{
	int 	i, handle;
	char 	Path[1024] = {0,},
			temp1[1024] = {0,};
	
	//model - MeasPoints
	
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )	MakeDir(Path);
	sprintf(Path, "%s\\%s\\Mark.ini", Path_Model, ModelName[ModelNo]);

	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		ReadLine(handle, temp1, -1);	// LINE 1
		ReadLine(handle, temp1, -1);	// PARA 1
		ReadLine(handle, temp1, -1);	
		Couth.CharHeight = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 2
		ReadLine(handle, temp1, -1);	
		Couth.CharWidth = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 3
		ReadLine(handle, temp1, -1);	
		Couth.Font = atoi(temp1);
		ReadLine(handle, temp1, -1);	// PARA 4
		ReadLine(handle, temp1, -1);	
		Couth.Spacing = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 5
		ReadLine(handle, temp1, -1);	
		Couth.Density = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 6
		ReadLine(handle, temp1, -1);	
		Couth.Xcoo = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 7
		ReadLine(handle, temp1, -1);	
		Couth.Ycoo = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 8
		ReadLine(handle, temp1, -1);	
		Couth.Zcoo = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 9
		ReadLine(handle, temp1, -1);	
		Couth.Angle = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 10
		ReadLine(handle, temp1, -1);	
		Couth.Diameter = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 11
		ReadLine(handle, temp1, -1);	
		Couth.Con = atoi(temp1);
		ReadLine(handle, temp1, -1);	// PARA 12
		ReadLine(handle, temp1, -1);	
		Couth.Hmirror = atoi(temp1);
		ReadLine(handle, temp1, -1);	// PARA 13
		ReadLine(handle, temp1, -1);	
		Couth.Vmirror = atoi(temp1);
		ReadLine(handle, temp1, -1);	// PARA 14
		ReadLine(handle, temp1, -1);	
		Couth.Speed = atof(temp1);
		ReadLine(handle, temp1, -1);	// PARA 15
		ReadLine(handle, temp1, -1);	
		Couth.Force = atof(temp1);
		
		ReadLine(handle, temp1, -1);	// format
		ReadLine(handle, temp1, -1);	
		SetCtrlVal(model_tab_Mark, TABPANEL_3_TEXT_1, temp1);
		
		ReadLine(handle, temp1, -1);	// jig sel
		ReadLine(handle, temp1, -1);
		Scan(temp1, "%s>%i", &i);
		SetCtrlVal(model_tab_Mark, TABPANEL_3_OPTIONAL_SEL_1, i);
		PlcData[160] = i;

		ReadLine(handle, temp1, -1);	// 마킹 sel
		ReadLine(handle, temp1, -1);
		Scan(temp1, "%s>%i", &i);
		SetCtrlVal(model_tab_Mark, TABPANEL_3_OPTIONAL_SEL_2, i);
		PlcData[161] = i;

		CloseFile(handle);
	}	
	SetModel_Mark();
}

void 	LoadModel_BoxPos(void)
{
	int 	i, handle;
	char 	Path[1024] = {0,},
			temp1[1024] = {0,};
	
	//model - BoxPos
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )			MakeDir(Path);
	sprintf(Path, "%s\\%s\\Pos.ini", Path_Model, ModelName[ModelNo]);
	
	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		for(i = 0 ; i < MeasPoints ; i ++)
		{
			ReadLine(handle, temp1, -1);	//point
			ReadLine(handle, temp1, -1);	// LabX, LabY, BoxX, BoxY, BoxWidth
			Scan(temp1, "%s>%i%i%i%i%i", &BoxPos[i].LabX, &BoxPos[i].LabY, &BoxPos[i].BoxX, &BoxPos[i].BoxY, &BoxPos[i].BoxWidth);
		}
		CloseFile(handle);
	}	
	SetModel_BoxPos();
}

void 	LoadModel_Img(void)
{
	int 	i;
	char 	Path[1024] = {0,};
	
	sprintf(Path, "%s\\%s\\%s.Jpg", Path_Model, ModelName[ModelNo], ModelName[ModelNo]);
	
	DeleteImage(tab_auto, TAB_AUTO_IMG);	
	if(GetFileInfo(Path, &i) == 0)	
		return;
	else
		DisplayImageFile(tab_auto, TAB_AUTO_IMG, Path);
}

void	InitTabTableData(void)
{
	int 	i;
	
	//main - Auto
	DeleteTableRows(tab_auto, TAB_AUTO_A_TABLE, 1, -1); 
	InsertTableRows(tab_auto, TAB_AUTO_A_TABLE, 1, MeasPoints, VAL_USE_MASTER_CELL_TYPE);
	for(i = 0 ; i < MeasPoints ; i ++)
	{  
		SetTableCellRangeAttribute(tab_auto, TAB_AUTO_A_TABLE, MakeRect(i+1, 2, 1, 3), ATTR_PRECISION, Model[i].Unit);
		
		SetTableCellVal(tab_auto, TAB_AUTO_A_TABLE, MakePoint(1, i+1), Model[i].Name);
		SetTableCellVal(tab_auto, TAB_AUTO_A_TABLE, MakePoint(2, i+1), Model[i].LCL);
		SetTableCellVal(tab_auto, TAB_AUTO_A_TABLE, MakePoint(4, i+1), Model[i].UCL);
	}	
	
	//main - Manual
	DeleteTableRows(tab_manual, TAB_MANU_A_TABLE, 1, -1); 
	InsertTableRows(tab_manual, TAB_MANU_A_TABLE, 1, MeasPoints, VAL_USE_MASTER_CELL_TYPE);
	for(i = 0 ; i < MeasPoints ; i ++)
	{  
		SetTableCellRangeAttribute(tab_manual, TAB_MANU_A_TABLE, MakeRect(i+1, 2, 1, 3), ATTR_PRECISION, Model[i].Unit);
		
		SetTableCellVal(tab_manual, TAB_MANU_A_TABLE, MakePoint(1, i+1), Model[i].Name);
		SetTableCellVal(tab_manual, TAB_MANU_A_TABLE, MakePoint(2, i+1), Model[i].LCL);
		SetTableCellVal(tab_manual, TAB_MANU_A_TABLE, MakePoint(4, i+1), Model[i].UCL);
		SetTableRowAttribute(tab_manual, TAB_MANU_A_TABLE, i+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);
		SetTableRowAttribute(tab_manual, TAB_MANU_A_TABLE, i+1, ATTR_ROW_HEIGHT, 35);
	}	
	

	//main - Table
	DeleteTableRows(tab_table, TAB_TABLE_TABLE, 1, -1); 
	DeleteTableColumns(tab_table, TAB_TABLE_TABLE, 1, -1);
	//마킹 추가시 확인 필요 3=>4
	InsertTableColumns(tab_table, TAB_TABLE_TABLE, 1, MeasPoints+3, VAL_USE_MASTER_CELL_TYPE); //
	
	for(i = 0 ; i < 3 ; i ++)
	{
		SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_LABEL_POINT_SIZE, 11);
		SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_LABEL_BOLD, 1);
		SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_USE_LABEL_TEXT, 1);
		
		if(i == 0)	//DATE / TIME
		{
			SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_COLUMN_WIDTH, 105);		
			SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_LABEL_TEXT, "DATE / TIME");
		}
		else if(i == 1)	// #10
		{
			SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_COLUMN_WIDTH, 26);		
			SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_LABEL_TEXT, "#10");
		}
		else if(i == 2)	//#20
		{
			SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_COLUMN_WIDTH, 26);		
			SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_LABEL_TEXT, "#20");
		}
		// 마킹기 추 가 시 주 석 해 제 3->4
		//else	//	MARK
		//{
		//	SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_COLUMN_WIDTH, 40);		
		//	SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1, ATTR_LABEL_TEXT, "MARK");
		//}
	}
	for(i = 0 ; i < MeasPoints ; i ++)
	{  
		SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1+3, ATTR_LABEL_POINT_SIZE, 11);
		SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1+3, ATTR_LABEL_BOLD, 1);
		SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1+3, ATTR_USE_LABEL_TEXT, 1);
//데이터 표 
		if(i == 0)
			SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1+3, ATTR_COLUMN_WIDTH, 60);		
		else if(i == MeasPoints - 1)
			SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1+3, ATTR_COLUMN_WIDTH, 100);		
		else
			SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1+3, ATTR_COLUMN_WIDTH, 80);				
		SetTableColumnAttribute (tab_table, TAB_TABLE_TABLE, i+1+3, ATTR_LABEL_TEXT, Model[i].Name);
	}	
}

void	LoadModelData(void)
{
	int		i;
	char	temp1[1024] = {0,};

	SetPanelAttribute(modelpanel, ATTR_DIMMED, 1);
	SetPanelAttribute(mainpanel, ATTR_DIMMED, 1);
	
	DeleteListItem(modelpanel, MODEL_LIST_MODEL, 0, -1);
	DeleteListItem(mainpanel, MAIN_MODEL_NAME, 0, -1);	
	DeleteListItem(resultpanel, RESULT_MODEL, 0, -1);	
	
	for(i = 0 ; i < ModelCount ; i ++)
	{	
		sprintf(temp1, "[%02d]%s", i+1, ModelName[i]);
		InsertListItem(modelpanel, MODEL_LIST_MODEL, i, temp1, i);
		InsertListItem(mainpanel, MAIN_MODEL_NAME, i, temp1, i);
		InsertListItem(resultpanel, RESULT_MODEL, i, temp1, i);
	}
	
	CheckListItem(modelpanel, MODEL_LIST_MODEL, ModelNo, 1);
	
	LoadModel_MeasPoints();
	LoadModel_Calculation();
	if(Mark.portNumber > 0)
		LoadModel_Mark();
	LoadModel_BoxPos();
	LoadModel_Img();

	SetCtrlAttribute(tab_auto, TAB_AUTO_POINT_1, ATTR_LABEL_BGCOLOR, 0x007DC8FF);
	BeforePointCtrl = PointCtrl[0];
	
	SetCtrlIndex(modelpanel, MODEL_LIST_MODEL, ModelNo);
	SetCtrlIndex(mainpanel, MAIN_MODEL_NAME, ModelNo);
	SetPanelAttribute(modelpanel, ATTR_DIMMED, 0);
	SetPanelAttribute(mainpanel, ATTR_DIMMED, 0);
	sprintf(temp1, "Load Model : %s", ModelName[ModelNo]);
	LogUpdate(temp1);
	
	InitTabTableData();

	//main - Zero
	LoadZeroTableData();
	GetDataFileName();
	GetSaveDataNum();
	
	SetGraphRange();
	GraphPlot();
	
	SendModelBit();
}

void 	SaveModel_MeasPoints(void)
{
	int 	i, handle;
	char 	Path[1024] = {0,};
	char 	temp1[1024] = {0,};
	
	// MeasPoints
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )			MakeDir(Path);
	sprintf(Path, "%s\\%s\\MeasPoints.ini", Path_Model, ModelName[ModelNo]);
	
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		WriteLine(handle, "Meas Points:", -1);
		GetNumTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, &MeasPoints);
		sprintf(temp1, "%d", MeasPoints);
		WriteLine(handle, temp1, -1);
		
		for(i = 0 ; i < MeasPoints ; i ++)
		{
			GetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(1, i+1), Model[i].Name);
			GetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(2, i+1), &Model[i].Master);
		    GetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(3, i+1), &Model[i].Comp);
			GetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(4, i+1), &Model[i].Fact);
			GetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(5, i+1), &Model[i].LCL);
			GetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(6, i+1), &Model[i].LWL);
			GetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(7, i+1), &Model[i].UWL);
			GetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(8, i+1), &Model[i].UCL);
			
			WriteLine(handle, "Name", -1);	//NAME
			sprintf(temp1, "%s", Model[i].Name);
			WriteLine(handle, temp1, -1);
			WriteLine(handle, "Master\tComp\tFactor\tLCL\tLWL\tUWL\tUCL\tUNIT\tSIG", -1);
			sprintf(temp1, "%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%d\t%d", 
					Model[i].Master, Model[i].Comp, Model[i].Fact, Model[i].LCL, Model[i].LWL, Model[i].UWL, Model[i].UCL, Model[i].Unit, Model[i].Sig);
			WriteLine(handle, temp1, -1);
		}
		CloseFile(handle);
	}	
}

void 	SaveModel_Calculation(void)
{
	int 	i, handle;
	char 	Path[1024] = {0,};
	char 	temp1[1024] = {0,};
	char 	point[7][10] = {0,};
		
	// Calculation
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )			MakeDir(Path);
	sprintf(Path, "%s\\%s\\Cal.ini", Path_Model, ModelName[ModelNo]);
	
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		for(i = 0 ; i < MeasPoints ; i ++)
		{
			GetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(2, i+1), point[0]);	//point1
			GetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(3, i+1), point[1]);	//point2
			GetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(4, i+1), point[2]);	//point3
			GetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(5, i+1), point[3]);	//point4
			GetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(6, i+1), point[4]);	//cal
			GetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(7, i+1), point[5]);	//use
			
			//point	
			sprintf(temp1, "point %s:", Model[i].Name);
			WriteLine(handle, temp1, -1);
			
			//sign
			if(Model[i].sign1 == 1)			sprintf(temp1, "+");
			else							sprintf(temp1, "-");
			if(Model[i].sign2 == 1)			strcat(temp1, "\t+");
			else							strcat(temp1, "\t-");
			if(Model[i].sign3 == 1)			strcat(temp1, "\t+");
			else							strcat(temp1, "\t-");
			if(Model[i].sign4 == 1)			strcat(temp1, "\t+");
			else							strcat(temp1, "\t-");
			WriteLine(handle, temp1, -1);
		
			//P1~P4 Cal Use	Offset
			sprintf(point[6], "%d", Model[i].Offset);
			
			sprintf(temp1, "%s\t%s\t%s\t%s\t%s\t%s\t%s", point[0], point[1], point[2], point[3], point[4], point[5], point[6]);
			WriteLine(handle, temp1, -1);
			
			if(strcmp(point[0], "NONE") == 0)	Model[i].P1 = 999;
			else								Model[i].P1 = atoi(point[0]) - 1;
			if(strcmp(point[1], "NONE") == 0)	Model[i].P2 = 999;
			else								Model[i].P2 = atoi(point[1]) - 1;
			if(strcmp(point[2], "NONE") == 0)	Model[i].P3 = 999;
			else								Model[i].P3 = atoi(point[2]) - 1;
			if(strcmp(point[3], "NONE") == 0)	Model[i].P4 = 999;
			else								Model[i].P4 = atoi(point[3]) - 1;
		
			if(strcmp(point[4], "AVR") == 0)			Model[i].Cal = 0;
			else if(strcmp(point[4], "MIN") == 0)		Model[i].Cal = 1;
			else if(strcmp(point[4], "MAX") == 0)		Model[i].Cal = 2;
			else if(strcmp(point[4], "MAX-MIN") == 0)	Model[i].Cal = 3;
			else 										Model[i].Cal = 4;
			
			if(strcmp(point[5], "Y") == 0)			Model[i].Use = 1;
			else									Model[i].Use = 0;
		
		}
		CloseFile(handle);
	}	
}

void 	SaveModel_Mark(void)
{
	int 	i, handle;
	char 	Path[1024] = {0,};
	char 	temp1[1024] = {0,};
	
	// MeasPoints
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )			MakeDir(Path);
	sprintf(Path, "%s\\%s\\Mark.ini", Path_Model, ModelName[ModelNo]);
	
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_1, &Couth.CharHeight);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_2, &Couth.CharWidth);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_3, &Couth.Font);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_4, &Couth.Spacing);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_5, &Couth.Density);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_6, &Couth.Xcoo);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_7, &Couth.Ycoo);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_8, &Couth.Zcoo);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_9, &Couth.Angle);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_10, &Couth.Diameter);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_11, &Couth.Con);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_12, &Couth.Hmirror);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_13, &Couth.Vmirror);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_14, &Couth.Speed);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_MARK_PARA_15, &Couth.Force);	
			
		WriteLine(handle, "LINE 1:", -1);
		WriteLine(handle, "Character Height", -1);
		sprintf(temp1, "%.1f", Couth.CharHeight);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Character Width", -1);
		sprintf(temp1, "%.1f", Couth.CharWidth);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Font", -1);
		sprintf(temp1, "%d", Couth.Font);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Spacing between characters", -1);
		sprintf(temp1, "%.1f", Couth.Spacing);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Density", -1);
		sprintf(temp1, "%.1f", Couth.Density);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "X coordinate", -1);
		sprintf(temp1, "%.1f", Couth.Xcoo);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Y coordinate", -1);
		sprintf(temp1, "%.1f", Couth.Ycoo);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Z coordinate", -1);
		sprintf(temp1, "%.1f", Couth.Zcoo);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Angle", -1);
		sprintf(temp1, "%.1f", Couth.Angle);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Diameter", -1);
		sprintf(temp1, "%.1f", Couth.Diameter);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Concave/Convex", -1);
		sprintf(temp1, "%d", Couth.Con);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Horizontal mirror", -1);
		sprintf(temp1, "%d", Couth.Hmirror);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Vertical mirror", -1);
		sprintf(temp1, "%d", Couth.Vmirror);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Speed", -1);
		sprintf(temp1, "%d", (int)Couth.Speed);
		WriteLine(handle, temp1, -1);
	
		WriteLine(handle, "Force", -1);
		sprintf(temp1, "%d", (int)Couth.Force);
		WriteLine(handle, temp1, -1);
		
		WriteLine(handle, "Format", -1);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_TEXT_1, temp1);
//		sprintf(temp1, "%s", (int)Couth.Force);
		WriteLine(handle, temp1, -1);
		
		WriteLine(handle, "상부 JIG 사용선택", -1);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_OPTIONAL_SEL_1, &i);
		sprintf(temp1, "%d", i);
		WriteLine(handle, temp1, -1);		
	
		WriteLine(handle, "마킹 사용선택", -1);
		GetCtrlVal(model_tab_Mark, TABPANEL_3_OPTIONAL_SEL_2, &i);
		sprintf(temp1, "%d", i);
		WriteLine(handle, temp1, -1);		
	
		CloseFile(handle);
	}	
}

void 	SaveModel_BoxPos(void)
{
	int 	i, handle;
	char 	Path[1024] = {0,};
	char 	temp1[1024] = {0,};
	
	//model - BoxPos
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )			MakeDir(Path);
	sprintf(Path, "%s\\%s\\Pos.ini", Path_Model, ModelName[ModelNo]);
	
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		for(i = 0 ; i < MeasPoints ; i ++)
		{
			sprintf(temp1, "point %s:", Model[i].Name);
			WriteLine(handle, temp1, -1);
			sprintf(temp1, "%d\t%d\t%d\t%d\t%d", BoxPos[i].LabX, BoxPos[i].LabY, BoxPos[i].BoxX, BoxPos[i].BoxY, BoxPos[i].BoxWidth);
			WriteLine(handle, temp1, -1);			
		}
		CloseFile(handle);
	}	
}

void	SaveModelData(void)
{
	SaveModel_MeasPoints();
	SaveModel_Calculation();
	SaveModel_Mark();
	SaveModel_BoxPos();
}

void 	FileRename(char *oldName, char *newName)	//ModelName[ModelNo], newName
{
	char 	oldPath[1024] = {0,};
	char 	newPath[1024] = {0,};
	
	// Directory
	sprintf(newPath, "%s\\%s", Path_Model, newName);
	if( SetDir(newPath) )	MakeDir(newPath);
	
	// MeasPoints
	sprintf(oldPath, "%s\\%s\\MeasPoints.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\MeasPoints.ini", Path_Model, newName);
	
	CopyFile(oldPath, newPath);
	DeleteFile(oldPath);

	// Calculation
	sprintf(oldPath, "%s\\%s\\Cal.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\Cal.ini", Path_Model, newName);
	
	CopyFile(oldPath, newPath);
	DeleteFile(oldPath);

	// BoxPos
	sprintf(oldPath, "%s\\%s\\Pos.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\Pos.ini", Path_Model, newName);
	
	CopyFile(oldPath, newPath);
	DeleteFile(oldPath);

	// Zero
	sprintf(oldPath, "%s\\%s\\Zero.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\Zero.ini", Path_Model, newName);
	
	CopyFile(oldPath, newPath);
	DeleteFile(oldPath);
	
	// IMG
	sprintf(oldPath, "%s\\%s\\%s.jpg", Path_Model, oldName, oldName);
	sprintf(newPath, "%s\\%s\\%s.jpg", Path_Model, newName, newName);

	CopyFile(oldPath, newPath);
	DeleteFile(oldPath);
	
	// Mark
	sprintf(oldPath, "%s\\%s\\Mark.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\Mark.ini", Path_Model, newName);

	CopyFile(oldPath, newPath);
	DeleteFile(oldPath);
	
	sprintf(oldPath, "%s\\%s", Path_Model, oldName);
	DeleteDir(oldPath);
}

void 	FileAdd(char *oldName, char *newName)	//ModelName[ModelNo], NewName
{
	char 	oldPath[1024] = {0,};
	char 	newPath[1024] = {0,};
	
	// Directory
	sprintf(newPath, "%s\\%s", Path_Model, newName);
	if( SetDir(newPath) )	MakeDir(newPath);
	
	// MeasPoints
	sprintf(oldPath, "%s\\%s\\MeasPoints.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\MeasPoints.ini", Path_Model, newName);
	
	CopyFile(oldPath, newPath);
//	DeleteFile(oldPath);

	// Calculation
	sprintf(oldPath, "%s\\%s\\Cal.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\Cal.ini", Path_Model, newName);
	
	CopyFile(oldPath, newPath);
//	DeleteFile(oldPath);

	// BoxPos
	sprintf(oldPath, "%s\\%s\\Pos.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\Pos.ini", Path_Model, newName);
	
	CopyFile(oldPath, newPath);
//	DeleteFile(oldPath);

	// Zero
	sprintf(oldPath, "%s\\%s\\Zero.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\Zero.ini", Path_Model, newName);
	
	CopyFile(oldPath, newPath);
//	DeleteFile(oldPath);

	// IMG
	sprintf(oldPath, "%s\\%s\\%s.jpg", Path_Model, oldName, oldName);
	sprintf(newPath, "%s\\%s\\%s.jpg", Path_Model, newName, newName);

	CopyFile(oldPath, newPath);
//	DeleteFile(oldPath);

	// Mark
	sprintf(oldPath, "%s\\%s\\Mark.ini", Path_Model, oldName);
	sprintf(newPath, "%s\\%s\\Mark.ini", Path_Model, newName);

	CopyFile(oldPath, newPath);
//	DeleteFile(oldPath);
}

void 	FileDelete(char *oldName)	//ModelName[ModelNo]
{
	char 	oldPath[1024] = {0,};
	
	// MeasPoints
	sprintf(oldPath, "%s\\%s\\MeasPoints.ini", Path_Model, oldName);
	DeleteFile(oldPath);

	// Calculation
	sprintf(oldPath, "%s\\%s\\Cal.ini", Path_Model, oldName);
	DeleteFile(oldPath);
	
	// BoxPos
	sprintf(oldPath, "%s\\%s\\Pos.ini", Path_Model, oldName);
	DeleteFile(oldPath);
	
	// Zero
	sprintf(oldPath, "%s\\%s\\Zero.ini", Path_Model, oldName);
	DeleteFile(oldPath);
	
	// IMG
	sprintf(oldPath, "%s\\%s\\%s.jpg", Path_Model, oldName, oldName);
	DeleteFile(oldPath);
	
	// Mark
	sprintf(oldPath, "%s\\%s\\Mark.ini", Path_Model, oldName);
	DeleteFile(oldPath);
	
	// Directory
	sprintf(oldPath, "%s\\%s", Path_Model, oldName);
	DeleteDir(oldPath);
}

int CVICALLBACK Cb_ModelPanel (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
//			SaveModel();
			ResetSpcData();			
			LoadModelData();

			SPCDisplayPointNo = 0;
			SetCtrlIndex(tab_auto, TAB_AUTO_RING_MEASPOINT, SPCDisplayPointNo);	
			CallCtrlCallback(tab_auto, TAB_AUTO_RING_MEASPOINT, EVENT_VAL_CHANGED, 0, 0, NULL);
			SaveModel();
			
			InitAllData();
			RemovePopup(0);
			HidePanel(panel);

			ContinuousNgNo = 0;
			ReMeasCnt = 0;	
			break;
	}
	return 0;
}
