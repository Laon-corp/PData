#include <userint.h>
#include "1_Model.h"
#include "A_Global.h"

int CVICALLBACK Point_Add (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int i, j;
			char pointTemp[17][10] = {"NONE", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
			char calcTemp[5][20] = {"AVR", "MIN", "MAX", "MAX-MIN", "REFERED"};
			char useTemp[2][10] = {"Y", "N"};
			
			if(ConfirmPopup("ADD", "POINT ADD?"))
			{
				GetActiveTabPage(modelpanel, MODEL_TAB, &i);
				if(i == 0)
				{
					GetNumTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, &i);
				
					InsertTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, i+1, 1, VAL_USE_MASTER_CELL_TYPE);			
					SetTableRowAttribute(model_tab_Meas, TABPANEL_MEAS_TABLE, i+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);				
					SetTableRowAttribute(model_tab_Meas, TABPANEL_MEAS_TABLE, i+1, ATTR_ROW_HEIGHT, 35);
					
					SetTableCellRangeAttribute(model_tab_Meas, TABPANEL_MEAS_TABLE, MakeRect(i + 1, 2, 1, 7), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
					SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(1, i+1), "Added Point");	//NAME
					SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(2, i+1), 0.0);			//MASTER
					SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(3, i+1), 0.0);			//COMP
					SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(4, i+1), 100.0);			//FACTOR
					SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(5, i+1), 0.0);			//LCL
					SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(6, i+1), 0.0);			//LWL
					SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(7, i+1), 0.0);			//UWL						
					SetTableCellVal(model_tab_Meas, TABPANEL_MEAS_TABLE, MakePoint(8, i+1), 0.0);			//UCL	
					
					InsertTableRows(model_tab_Calc, TABPANEL_2_CALC_TABLE, i + 1, 1, VAL_USE_MASTER_CELL_TYPE);
					SetTableRowAttribute(model_tab_Calc, TABPANEL_2_CALC_TABLE, i + 1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);
					SetTableRowAttribute(model_tab_Calc, TABPANEL_2_CALC_TABLE, i + 1, ATTR_ROW_HEIGHT, 35);
					
					SetTableCellRangeAttribute(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakeRect(i+1, 2, 1, 6), ATTR_CELL_TYPE, VAL_CELL_RING);
					for(j = 0 ; j < 17 ; j ++)
						InsertTableCellRangeRingItem(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakeRect(i+1, 2, 1, 4), j, pointTemp[j]);
					for(j = 0 ; j < 5 ; j ++)
						InsertTableCellRangeRingItem(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakeRect(i+1, 6, 1, 1), j, calcTemp[j]);
					for(j = 0 ; j < 2 ; j ++)
						InsertTableCellRangeRingItem(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakeRect(i+1, 7, 1, 1), j, useTemp[j]);

					SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(1, i+1), "Added Point");
					SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(2, i+1), "NONE");
					SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(3, i+1), "NONE");
					SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(4, i+1), "NONE");
					SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(5, i+1), "NONE");
					SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(6, i+1), "AVR");					
					SetTableCellVal(model_tab_Calc, TABPANEL_2_CALC_TABLE, MakePoint(7, i+1), "Y");
				}
				else if(i == 1)
				{
					GetNumTableRows(model_tab_Calc, TABPANEL_2_CALC_TABLE, &i);
					
					InsertTableRows(model_tab_Calc, TABPANEL_2_CALC_TABLE, i+1, 1, VAL_USE_MASTER_CELL_TYPE);
					SetTableRowAttribute (model_tab_Calc, TABPANEL_2_CALC_TABLE, i+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);
					SetTableRowAttribute(model_tab_Calc, TABPANEL_2_CALC_TABLE, i+1, ATTR_ROW_HEIGHT, 35);
					
					InsertTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, i+1, 1, VAL_USE_MASTER_CELL_TYPE);			
					SetTableRowAttribute (model_tab_Meas, TABPANEL_MEAS_TABLE, i+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);				
					SetTableRowAttribute(model_tab_Meas, TABPANEL_MEAS_TABLE, i+1, ATTR_ROW_HEIGHT, 35);
				}
				else
					return 0;
			}
			
			break;
	}
	return 0;
}

int CVICALLBACK Point_Delete (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			Point	cell;
			int		i;
			if(ConfirmPopup("DELETE", "POINT DELETE?"))
			{
				GetActiveTabPage(modelpanel, MODEL_TAB, &i);
				if(i == 0)
				{
					GetNumTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, &i);
					if(i < 2)
						break;
					GetActiveTableCell(model_tab_Meas, TABPANEL_MEAS_TABLE, &cell);
					DeleteTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, cell.y, 1);
					DeleteTableRows(model_tab_Calc, TABPANEL_2_CALC_TABLE, cell.y, 1);
				}
				else if(i == 1)
				{
					GetNumTableRows(model_tab_Calc, TABPANEL_2_CALC_TABLE, &i);
					if(i < 2)
						break;
					GetActiveTableCell(model_tab_Calc, TABPANEL_2_CALC_TABLE, &cell);
					DeleteTableRows(model_tab_Meas, TABPANEL_MEAS_TABLE, cell.y, 1);
					DeleteTableRows(model_tab_Calc, TABPANEL_2_CALC_TABLE, cell.y, 1);
				}
				else
					return 0;
			}
			break;
	}
	return 0;
}

int CVICALLBACK Point_Save (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(ConfirmPopup("SAVE", "SAVE?"))
			{
				SaveModelData();
				LoadModelData();
			}
			break;
	}
	return 0;
}

int CVICALLBACK Point_Load (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(ConfirmPopup("ROLL-BACK", "ROLL-BACK?"))
				LoadModelData();
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Point_Table (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int		top, left, leftbtn, rightbtn, key;

	switch (event)
	{
		case EVENT_LEFT_CLICK:
			GetRelativeMouseState(panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
			GetTableCellFromPoint(panel, control, MakePoint (left, top), &PadCell);
			if(PadCell.x > 1)
			{
				SetActiveTableCell (panel, control, PadCell);
				CallKeyPadCell(panel, control);
			}
			else
			{
				PadCell.x = 0;
				PadCell.y = 0;
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_MakeMark (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			MakeMarkDataTest();
			break;
	}
	return 0;
}

int CVICALLBACK Cb_MarkCycle (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			PlcData[37] = 0;
			PlcData[56] = 1;
			break;
	}
	return 0;
}
