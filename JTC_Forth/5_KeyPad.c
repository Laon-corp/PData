#include "0_Main.h"
#include <userint.h>
#include "5_Keypad.h"
#include "A_Global.h"

void	CallKeyPadCell(int panel, int control)
{
	PadPanel = panel;
	PadControl = control;
	GetTableCellAttribute(PadPanel, TABPANEL_MEAS_TABLE, MakePoint(PadCell.x, PadCell.y), ATTR_DATA_TYPE, &PadAtr);
	CallCtrlCallback(keypad, KEYPAD_CLEAR, EVENT_COMMIT, 0, 0, NULL);
	DisplayPanel(keypad);
	InstallPopup(keypad);
	return;
}

int CVICALLBACK Cb_KeypadCtrl (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			PadPanel = panel;
			PadControl = control;
			PadCell.x = 0;
			PadCell.y = 0;
			GetCtrlAttribute(panel, control, ATTR_DATA_TYPE, &PadAtr);
			
			CallCtrlCallback(keypad, KEYPAD_CLEAR, EVENT_COMMIT, 0, 0, NULL);
			DisplayPanel(keypad);
			InstallPopup(keypad);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_KeypadPanel (int panel, int control, int event,
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


int CVICALLBACK Cb_0 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '0';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_1 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '1';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_2 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '2';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_3 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '3';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_4 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '4';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_5 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '5';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_6 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '6';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_7 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '7';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_8 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '8';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_9 (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '9';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Dot (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '.';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_A (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'A';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_B (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'B';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_C (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'C';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_D (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'D';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_E (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'E';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_F (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'F';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_G (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'G';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_H (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'H';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_I (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'I';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_J (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'J';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_K (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'K';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_L (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'L';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_M (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'M';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_N (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'N';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_O (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'O';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_P (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'P';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Q (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'Q';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_R (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'R';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_S (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'S';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_T (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'T';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_U (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'U';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_V (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'V';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_W (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'W';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_X (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'X';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Y (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'Y';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Z (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = 'Z';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Space (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = ' ';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Plus (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '+';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Minus (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = '-';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Colon (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(locate < MAX_KEYPAD_CHARS)
			{
				 InputString[locate++] = ':';
				 InputString[locate] = 0;
			}
			SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Bs (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		    if(locate > 0)
			{
				locate--;
				InputString[locate] = 0; 
			}
		    SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Clear (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		    locate = 0;
		    InputString[locate] = 0; 
		    SetCtrlVal (keypad, KEYPAD_STRING, InputString);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Enter (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//Table Cell
			if(PadCell.x > 0)
			{
				if(PadAtr == VAL_STRING)
					SetTableCellVal(PadPanel, PadControl, MakePoint(PadCell.x, PadCell.y), InputString);
				else if(PadAtr == VAL_INTEGER)
					SetTableCellVal(PadPanel, PadControl, MakePoint(PadCell.x, PadCell.y), atoi(InputString));
				else if(PadAtr == VAL_DOUBLE)
					SetTableCellVal(PadPanel, PadControl, MakePoint(PadCell.x, PadCell.y), atof(InputString));
			}
			//Ctrl
			else
			{
				if(PadAtr == VAL_STRING)
					SetCtrlVal(PadPanel, PadControl, InputString);
				else if(PadAtr == VAL_INTEGER)
				{	
					SetCtrlVal(PadPanel, PadControl, atoi(InputString));
				}
				else if(PadAtr == VAL_DOUBLE)
					SetCtrlVal(PadPanel, PadControl, atof(InputString));
			}
			
			RemovePopup(0);
			HidePanel(panel);

			break;
	}
	return 0;
}

