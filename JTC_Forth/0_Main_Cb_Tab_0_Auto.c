#include "A_Global.h"


int PointCtrl[MAX_MEAS_POINTS] = {TAB_AUTO_POINT_1, TAB_AUTO_POINT_2, TAB_AUTO_POINT_3, TAB_AUTO_POINT_4, TAB_AUTO_POINT_5,
								 TAB_AUTO_POINT_6, TAB_AUTO_POINT_7, TAB_AUTO_POINT_8, TAB_AUTO_POINT_9, TAB_AUTO_POINT_10,
								 TAB_AUTO_POINT_11, TAB_AUTO_POINT_12, TAB_AUTO_POINT_13, TAB_AUTO_POINT_14, TAB_AUTO_POINT_15,
								 TAB_AUTO_POINT_16, TAB_AUTO_POINT_17, TAB_AUTO_POINT_18, TAB_AUTO_POINT_19, TAB_AUTO_POINT_20,
								 TAB_AUTO_POINT_21, TAB_AUTO_POINT_22, TAB_AUTO_POINT_23, TAB_AUTO_POINT_24, TAB_AUTO_POINT_25,
								 TAB_AUTO_POINT_26, TAB_AUTO_POINT_27, TAB_AUTO_POINT_28, TAB_AUTO_POINT_29, TAB_AUTO_POINT_30,
								 TAB_AUTO_POINT_31, TAB_AUTO_POINT_32};

int CVICALLBACK Cb_Point (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	int 	i;
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			SetCtrlAttribute(panel, BeforePointCtrl, ATTR_LABEL_BGCOLOR, 0x00C0C0C0);
			for(i = 0 ; i < MeasPoints ; i ++)
			{
				if(control == PointCtrl[i])
				{
					BeforePointCtrl = PointCtrl[i];
					SetCtrlAttribute(panel, control, ATTR_LABEL_BGCOLOR, 0x007DC8FF);
					SetCtrlVal(panel, TAB_AUTO_RING_MEASPOINT, i);
					CallCtrlCallback(panel, TAB_AUTO_RING_MEASPOINT, EVENT_VAL_CHANGED, 0, 0, NULL);
				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Ring_MeasPoint (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlIndex(tab_auto, TAB_AUTO_RING_MEASPOINT, &SPCDisplayPointNo);	
			SetSpcPrecision();
			SetGraphRange();
			GraphPlot();
					
			SetSpcData(0);
			break;
	}
	return 0;
}


int CVICALLBACK Cb_Meas_1 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 0;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Manual Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_auto, TAB_AUTO_MEAS_TIMER_1);
			SetCtrlAttribute(tab_auto, TAB_AUTO_MEAS_TIMER_1, ATTR_ENABLED, 1);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Meas_2 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 1;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Manual Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_auto, TAB_AUTO_MEAS_TIMER_2);
			SetCtrlAttribute(tab_auto, TAB_AUTO_MEAS_TIMER_2, ATTR_ENABLED, 1);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Meas_3 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 2;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Manual Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_auto, TAB_AUTO_MEAS_TIMER_3);
			SetCtrlAttribute(tab_auto, TAB_AUTO_MEAS_TIMER_3, ATTR_ENABLED, 1);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Meas_4 (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 3;
//	char 	temp1[64] = {0,};
	switch (event)
	{
		case EVENT_RIGHT_DOUBLE_CLICK:
//			sprintf(temp1, "Manual Request Sig : %d", sig+1);
//			LogUpdate(temp1);
			MeasChIndex[sig] = 0;
			MeasSig[sig] = 1;
			ResetTimer(tab_auto, TAB_AUTO_MEAS_TIMER_4);
			SetCtrlAttribute(tab_auto, TAB_AUTO_MEAS_TIMER_4, ATTR_ENABLED, 1);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Timer_Meas_1 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 0;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			AutoMeasFinish(sig);
			break;
	}
	return 0;
}
int CVICALLBACK Cb_Timer_Meas_2 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 1;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			AutoMeasFinish(sig);
			break;
	}
	return 0;
}
int CVICALLBACK Cb_Timer_Meas_3 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 2;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			AutoMeasFinish(sig);
			break;
	}
	return 0;
}
int CVICALLBACK Cb_Timer_Meas_4 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int		sig = 3;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(panel, control, ATTR_ENABLED, 0);
			MeasSig[sig] = 0;
			MeasChIndex[sig] --;
			AutoMeasFinish(sig);
			break;
	}
	return 0;
}
