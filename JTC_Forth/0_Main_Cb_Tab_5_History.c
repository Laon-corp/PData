#include "A_Global.h"

int CVICALLBACK Cb_History_Clear (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ClearListCtrl(tab_history, TAB_HIS_LISTBOX);
			break;
	}
	return 0;
}

void	LogUpdate(char *data)
{
	char 	temp[1024] = {0,};
	int 	lineNo = 0;
	int 	handle;

	if(strlen(Path_History) < 1)
		InitLogPath();
	
	sprintf(temp, "[%s] [%s] : %s", CurrDate, CurrTime, data);
	InsertListItem(tab_history, TAB_HIS_LISTBOX, -1, temp, 0);
	
	GetNumListItems(tab_history, TAB_HIS_LISTBOX, &lineNo);
	SetCtrlIndex(tab_history, TAB_HIS_LISTBOX, lineNo - 1);
	
	if(lineNo > 1000)
		DeleteListItem(tab_history, TAB_HIS_LISTBOX, 0, 1);

	if(GetFileInfo (Path_History, &lineNo) == 0) 
			handle = OpenFile (Path_History, VAL_WRITE_ONLY, VAL_TRUNCATE, 	VAL_ASCII);
	else	handle = OpenFile (Path_History, VAL_WRITE_ONLY, VAL_APPEND, 	VAL_ASCII);
	
	WriteLine(handle, temp, -1);
	CloseFile(handle);
}