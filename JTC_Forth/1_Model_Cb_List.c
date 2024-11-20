#include "A_Global.h"

int CVICALLBACK Cb_List_Model (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{									//eventData1 - MARK STATE
		case EVENT_MARK_STATE_CHANGE:	//eventData2 - List Index(Zero Based)
			int i;
			char temp[256] = {0,};
		
			if(eventData2 < 0)
				eventData2 = 0;
			
			if(eventData1)
			{	
				GetNumListItems(modelpanel, MODEL_LIST_MODEL, &ModelCount);
				for(i = 0 ; i < ModelCount ; i ++)
				{
					if(eventData2 != i)
						CheckListItem(panel, MODEL_LIST_MODEL, i, 0);
					else
						CheckListItem(panel, MODEL_LIST_MODEL, i, 1);
				}
				// Display Selected Model's Data Using eventData2;
				sprintf(temp, "Model Selected:%s", ModelName[eventData2]);
				LogUpdate(temp);
				ModelNo = eventData2;
				LoadModel_MeasPoints();
				LoadModel_Calculation();
				if(Mark.portNumber > 0)
					LoadModel_Mark();
				LoadModel_BoxPos();
				LoadModel_Img();
				ContinuousNgNo = 0;
				ReMeasCnt = 0;
			}
			break;
		
		case EVENT_COMMIT:				//eventData1 - List Index(Zero Based)
			int j;
			GetNumCheckedItems(panel, MODEL_LIST_MODEL, &j);
			if(j < 1)	//None Checked Item
			{
				CheckListItem(panel, MODEL_LIST_MODEL, eventData1, 1);
				ModelNo = eventData1;
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Model_Add (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char temp[256] = {0,};
			char temp2[256] = {0,};
			if(VAL_GENERIC_POPUP_BTN1 == 
					GenericMessagePopup("Add Model", "Input Model Name", "Add", "Cancel", "", temp, 63, 1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN2))
			{
				sprintf(temp2, "[%02d]%s", ModelCount+1, temp);
				InsertListItem(modelpanel, MODEL_LIST_MODEL, -1, temp2, -1);
				FileAdd(ModelName[ModelNo], temp);
				SaveModel();
				sprintf(temp, "Add Model : %s", temp);
				LogUpdate(temp);
			}

			break;
	}
	return 0;
}

int CVICALLBACK Cb_Model_Delete (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int j;
			char temp[256] = {0,};
			GetNumCheckedItems(panel, MODEL_LIST_MODEL, &j);
			if(j < 1)
			{
				MessagePopup("SELECT MODEL", "NONE SELETED MODEL");
				return 0;
			}
			else
			{
				if(ModelCount == 1)
					break;
				DeleteSaveModel();
				
				DeleteListItem(modelpanel, MODEL_LIST_MODEL, ModelNo, 1);
				FileDelete(ModelName[ModelNo]);
				sprintf(temp, "Delete Model : %s", ModelName[ModelNo]);
				LogUpdate(temp);
				CallCtrlCallback(modelpanel, MODEL_LIST_MODEL, EVENT_MARK_STATE_CHANGE, 1, ModelNo - 1, 0);
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Model_Rename (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int j;
			char temp[256] = {0,};
			char temp2[256] = {0,};
			GetNumCheckedItems(panel, MODEL_LIST_MODEL, &j);
			if(j < 1)
			{
				MessagePopup("SELECT MODEL", "NONE SELETED MODEL");
				return 0;
			}
			else
			{
				if(VAL_GENERIC_POPUP_BTN1 == 
					GenericMessagePopup("Rename Model", "Input Model Name", "Rename", "Cancel", "", temp, 63, 1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN1, VAL_GENERIC_POPUP_BTN2))
				{
					sprintf(temp2, "[%02d]%s", ModelNo+1, temp);
					ReplaceListItem(modelpanel, MODEL_LIST_MODEL, ModelNo, temp2, ModelNo);
					FileRename(ModelName[ModelNo], temp);
					strcpy(ModelName[ModelNo], temp);
					sprintf(temp, "Model Rename : %s -> %s", ModelName[ModelNo], temp);
					SaveModel();
				}			
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Model_Copy (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK Cb_Model_MoveUp (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int j;
			char temp[64] = {0,};
			GetNumCheckedItems(panel, MODEL_LIST_MODEL, &j);
			if(j < 1)
			{
				MessagePopup("SELECT MODEL", "NONE SELETED MODEL");
				return 0;
			}
			else
			{
				if(ModelNo < 1)
					break;
				sprintf(temp, "[%02d]%s", ModelNo, ModelName[ModelNo]);
				ReplaceListItem(modelpanel, MODEL_LIST_MODEL, ModelNo-1, temp, ModelNo-1);
				sprintf(temp, "[%02d]%s", ModelNo+1, ModelName[ModelNo-1]);
				ReplaceListItem(modelpanel, MODEL_LIST_MODEL, ModelNo, temp, ModelNo);
				CheckListItem(modelpanel, MODEL_LIST_MODEL, ModelNo-1, 1);
				CheckListItem(modelpanel, MODEL_LIST_MODEL, ModelNo, 0);
				ModelNo = ModelNo - 1;
				SaveModel();
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Model_MoveDown (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int j;
			char temp[64] = {0,};
			GetNumCheckedItems(panel, MODEL_LIST_MODEL, &j);
			if(j < 1)
			{
				MessagePopup("SELECT MODEL", "NONE SELETED MODEL");
				return 0;
			}
			else
			{
				if(ModelNo >= ModelCount - 1)
					break;
				sprintf(temp, "[%02d]%s", ModelNo+2, ModelName[ModelNo]);
				ReplaceListItem(modelpanel, MODEL_LIST_MODEL, ModelNo+1, temp, ModelNo+1);
				sprintf(temp, "[%02d]%s", ModelNo+1, ModelName[ModelNo+1]);
				ReplaceListItem(modelpanel, MODEL_LIST_MODEL, ModelNo, temp, ModelNo);
				CheckListItem(modelpanel, MODEL_LIST_MODEL, ModelNo+1, 1);
				CheckListItem(modelpanel, MODEL_LIST_MODEL, ModelNo, 0);
				ModelNo = ModelNo + 1;
				SaveModel();
			}
			break;
	}
	return 0;
}