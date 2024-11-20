#include <userint.h>
#include "0_Main.h"
#include "A_Global.h"

int CVICALLBACK Cb_GraphChButton (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
			int a;
			GetCtrlVal(panel, control, &a);
			SetCtrlVal(panel, control, !a);

			SetCtrlIndex(panel, TAB_GRAPH_RING_MEASPOINT, 0);
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Refresh (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(MeasChIndex[0] < 1)
				return 0;
			
			int a, i, j;
			int b[MAX_CH];
			double	dtempX[MAX_CH_CYCLE] = {0.0,};
			double	dtempY[MAX_CH_CYCLE] = {0.0,};			
			double	dtempChY[MAX_CH][MAX_CH_CYCLE] = {0.0,};			
			
			DeleteGraphPlot(panel, TAB_GRAPH_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			GetCtrlIndex(panel, TAB_GRAPH_RING_MEASPOINT, &a);
			if(a < 1)
			{
				for(j = 0 ; j < MAX_CH ; j ++)
				{
					GetCtrlVal(tab_graph, TAB_GRAPH_CH_1 + j, &b[j]);
					if(b[j])
					{
						for(i = 0 ; i < MeasChIndex[0] ; i ++)
						{
							dtempX[i] = i * 1.0;
							dtempChY[j][i] = MeasChValue[i][j];
						}	

						PlotXY(panel, TAB_GRAPH_GRAPH, dtempX, dtempChY[j], MeasChIndex[0], 
							   VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_GREEN);						
					}
				}
			}
			else
			{
				GetCtrlIndex(tab_graph, TAB_GRAPH_RING_MEASPOINT, &a);
				for(i = 0 ; i < MeasChIndex[0] ; i ++)
				{
					dtempX[i] = i * 1.0;
					dtempY[i] = MeasChTemp[a-1][i];
				}
				SetAxisScalingMode (panel, TAB_GRAPH_GRAPH, VAL_XAXIS, VAL_MANUAL, 0, MeasChIndex[0]);
				SetAxisScalingMode (panel, TAB_GRAPH_GRAPH, VAL_LEFT_YAXIS, VAL_AUTOSCALE, 0, 0);

				PlotXY(panel, TAB_GRAPH_GRAPH, dtempX, dtempY, MeasChIndex[0],
					   VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_GREEN);
			}

			break;
	}
	return 0;
}

int CVICALLBACK Cb_Graph_Ring_MeasPoint (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	int		a, i;
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlIndex(panel, control, &a);
			if(a > 0)
			{
				for(i = 0 ; i < MAX_CH ; i ++)
					SetCtrlVal(tab_graph, TAB_GRAPH_CH_1 + i, 0);
			}
			break;
	}
	return 0;
}
