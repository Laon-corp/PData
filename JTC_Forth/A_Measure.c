#include <advanlys.h>
#include "A_Global.h"

double	ResultValue[MAX_MEAS_POINTS] = {0.0,};

void	ReadSensorValueFile(void)
{
	int handle, i, j;
	char Path[1024] = {0,};
	char temp1[1024] = {0,};
	char temp2[1024] = {0,};
	double	dtemp[MAX_CH] = {0.0,};
	int 	DotPosition[17] = {9, 19, 29, 39, 49,
							   59, 69, 79, 89, 99,
							   109, 119, 129, 139, 149, 
							   159, 169};
	
	sprintf(Path, "%s\\%s\\SensorValue_00.csv", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path_Model) )	MakeDir (Path_Model);
		
	if(GetFileInfo(Path, &i) != 0)	
	{
		handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);

		ReadLine(handle, temp1, -1);	//Sig
		ReadLine(handle, temp1, -1);	//MeasSigIndex
		MeasChIndex[0] = atoi(temp1);
		ReadLine(handle, temp1, -1);	//Ch Name


		for(j = 0 ; j < MeasChIndex[0] ; j ++)
		{
			ReadLine(handle, temp1, -1);	//Value
			for(i = 0 ; i < MAX_CH ; i ++)
			{
				CopyBytes(temp2, 0, temp1, DotPosition[i]+1, 9);
				dtemp[i] = atof(temp2);
			}
			for(i = 0 ; i < MAX_CH ; i ++)
				MeasChValue[j][i] = dtemp[i];
		}
		CloseFile(handle);
	}
	ManuMeasFinish(0);
}

void	InitAllData(void)
{
	int i;
	
	for(i = 0 ; i < MAX_MEAS_SIG ; i ++)
		InitStData(i);
}

void	InitStData(int sig)
{
	int 	i;
	char 	fmt[24] = {0,},
			temp1[24] = {0,};
	
	sig += 1;
	
	memset(MarkStr, 0, sizeof(MarkStr));
	
	//Point Ctrl
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		if(Model[i].Sig == sig)
		{
			SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_TEXT_BGCOLOR, VAL_WHITE);
			SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
			sprintf(fmt, "%%.%df", Model[i].Unit);
			sprintf(temp1, fmt, 0.0);
			SetCtrlVal(tab_auto, PointCtrl[i], temp1);
		}
	}
	//A_TABLE	- main
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		if(Model[i].Sig == sig)
		{
			SetTableCellAttribute(tab_auto, TAB_AUTO_A_TABLE, MakePoint(3, i+1), ATTR_TEXT_BGCOLOR, VAL_WHITE);
//			sprintf(fmt, "%%.%df", Model[i].Unit);
//			sprintf(temp1, fmt, 0.0);
			SetTableCellVal(tab_auto, TAB_AUTO_A_TABLE, MakePoint(3, i+1), 0.0);
		}
	}	
	//A_TABLE	- manual
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		if(Model[i].Sig == sig)
		{
			SetTableCellAttribute(tab_manual, TAB_MANU_A_TABLE, MakePoint(3, i+1), ATTR_TEXT_COLOR, VAL_BLACK);
//			sprintf(fmt, "%%.%df", Model[i].Unit);
//			sprintf(temp1, fmt, 0.0);
			SetTableCellVal(tab_manual, TAB_MANU_A_TABLE, MakePoint(3, i+1), 0.0);
		}
	}
	
	//Reset Signal
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		if(Model[i].Sig == sig)
		{
			PlcData[20 + sig - 1] = 0;			//Re-meas
			PlcData[24 + ((sig - 1)*2)] = 0;	//Judgment for each sig
			PlcData[25 + ((sig - 1)*2)] = 0;	//Judgment for each sig
			PlcData[32 + sig - 1] = 0;			//Measuring Finish Signal
		}
	}
	//Interface sig
	for(i = 240 ; i < 320 ; i ++)
		PlcData[i] = 0;
	
	PlcData[32 + sig - 1] = 0;
	PlcData[37] = 0;			//Marking End Signal
}

void	SetSpcPrecision(void)
{
	if(SPCDisplayPointNo < 0)
		SPCDisplayPointNo = 0;
	
	SetTableCellRangeAttribute(tab_auto, TAB_AUTO_TABLE_SPC, MakeRect(1, 1, 1, 4), ATTR_PRECISION, Model[SPCDisplayPointNo].Unit);	
}

void	ResetSpcData(void)
{
	int i, j;
	for(i = 0; i  <MAX_MACHINE; i ++)
	{
		for(j = 0; j < MAX_MODE; j ++)
		{
			Mc[i].Mode[j].CycleIndex  = 0;
			Mc[i].Mode[j].StartDataNo = 1;
			Mc[i].Mode[j].EndDataNo   = 1;
		}
		McSpc[i].NG = McSpc[i].G = 0; // 합격, 불량 수량
	}	
	GraphData.DataNum  = 0;
	GraphData1.DataNum = 0;
	GraphData2.DataNum = 0;	
}

void	MakeGraphData(void)
{
	int	i;

	// MAIN
	if(GraphData.DataNum >= MAX_PLOT_NO)
	{
		GraphData.DataNum = MAX_PLOT_NO;
		for(i = 0; i < MeasPoints; i++ )
		{
			memmove(&GraphData.Data[i][0], &GraphData.Data[i][1], (GraphData.DataNum - 1) * sizeof(double) );
			GraphData.Data[i][MAX_PLOT_NO - 1] = Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1];
		}
	}
	else											
	{
		for(i = 0; i < MeasPoints; i++ )
			GraphData.Data[i][GraphData.DataNum] = Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1];

		GraphData.DataNum ++;
	}
/* // 가공기 확인? 
	// MC 1
	if(McID == 0)
	{
		if( GraphData1.DataNum >= MAX_PLOT_NO ) // Data full
		{
			GraphData1.DataNum = MAX_PLOT_NO;
			for(i = 0; i < MeasPoints; i++ )
			{
				memmove(&GraphData1.Data[i][0], &GraphData1.Data[i][1], (GraphData1.DataNum - 1) * sizeof(double) );
				GraphData1.Data[i][MAX_PLOT_NO - 1] = Mc[1].Mode[0].ResultValue[i][Mc[1].Mode[0].EndDataNo - 1];
			}
		}
		else											
		{
			for(i = 0; i < MeasPoints; i++ )
				GraphData1.Data[i][GraphData1.DataNum] = Mc[1].Mode[0].ResultValue[i][Mc[1].Mode[0].EndDataNo - 1];

			GraphData1.DataNum ++;
		}
		CalcSpcData(1); 
	}
	// MC 2
	else if(McID == 1)
	{
		if( GraphData2.DataNum >= MAX_PLOT_NO ) // Data full
		{
			GraphData2.DataNum = MAX_PLOT_NO;
			for(i = 0; i < MeasPoints; i++ )
			{
				memmove(&GraphData2.Data[i][0], &GraphData2.Data[i][1], (GraphData2.DataNum - 1) * sizeof(double) );
				GraphData2.Data[i][MAX_PLOT_NO - 1] = 	Mc[2].Mode[0].ResultValue[i][Mc[2].Mode[0].EndDataNo - 1];
			}
		}
		else											
		{
			for(i = 0; i < MeasPoints; i++ )
				GraphData2.Data[i][GraphData2.DataNum] = Mc[2].Mode[0].ResultValue[i][Mc[2].Mode[0].EndDataNo - 1];

			GraphData2.DataNum ++;
		}
		CalcSpcData(2); 
	}
*/
}
void	GraphPlot(void)
{
	int		OldHandleData = 0;
	int		OldHandleData1 = 0;
	int		OldHandleData2 = 0;
	
	int		i, j;
	double	Cen, Upper, Lower;
	double 	Center_Point[MAX_PLOT_NO];
	
	Cen = (*GraphData.UCL - *GraphData.LCL) * 50. / 100.;
	Upper = *GraphData.UCL + (*GraphData.UCL - *GraphData.LCL) * 20. / 100.;
	Lower = *GraphData.LCL - (*GraphData.UCL - *GraphData.LCL) * 20. / 100.;

	for(j = 0; j < MAX_PLOT_NO ; j ++)
		Center_Point[j] = *GraphData.LCL + Cen;
	
	//main
	if( GraphData.HandleData != 0 )
		OldHandleData = GraphData.HandleData;
	else
	{
		DeleteGraphPlot(tab_auto, TAB_AUTO_GRAPH, -1, VAL_IMMEDIATE_DRAW);
		DeleteGraphPlot(tab_auto, TAB_AUTO_GRAPH_1, -1, VAL_IMMEDIATE_DRAW);
		DeleteGraphPlot(tab_auto, TAB_AUTO_GRAPH_2, -1, VAL_IMMEDIATE_DRAW);
		
		GraphData.HandleLCL = PlotY(tab_auto, TAB_AUTO_GRAPH, GraphData.LCL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DOT, 1, 0xFF4000);
		GraphData.HandleUCL = PlotY(tab_auto, TAB_AUTO_GRAPH, GraphData.UCL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DOT, 1, 0xFF4000);
		GraphData.HandleUWL = PlotY(tab_auto, TAB_AUTO_GRAPH, GraphData.UWL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DOT, 1, 0xFFC000);		
		GraphData.HandleLWL = PlotY(tab_auto, TAB_AUTO_GRAPH, GraphData.LWL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DOT, 1, 0xFFC000);

		PlotY(tab_auto, TAB_AUTO_GRAPH, Center_Point, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, 0x80FF00);
	}

	// MC 1
	if( GraphData1.HandleData != 0)
		OldHandleData1 = GraphData1.HandleData;
	else
	{
		GraphData1.HandleLCL = PlotY(tab_auto, TAB_AUTO_GRAPH_1, GraphData1.LCL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DOT, 1, 0xFF4000);
		GraphData1.HandleUCL = PlotY(tab_auto, TAB_AUTO_GRAPH_1, GraphData1.UCL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DOT, 1, 0xFF4000);
		GraphData1.HandleUWL = PlotY(tab_auto, TAB_AUTO_GRAPH_1, GraphData1.UWL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DOT, 1, 0xFFC000);		
		GraphData1.HandleLWL = PlotY(tab_auto, TAB_AUTO_GRAPH_1, GraphData1.LWL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DOT, 1, 0xFFC000);

		PlotY(tab_auto, TAB_AUTO_GRAPH_1, Center_Point, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, 0x80FF00);
	}
	
	// MC 2
	if( GraphData2.HandleData != 0)
		OldHandleData2 = GraphData2.HandleData;
	else
	{
		GraphData2.HandleLCL = PlotY(tab_auto, TAB_AUTO_GRAPH_2, GraphData2.LCL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DASH, 1, 0xFF4000);
		GraphData2.HandleUCL = PlotY(tab_auto, TAB_AUTO_GRAPH_2, GraphData2.UCL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DASH, 1, 0xFF4000);
		GraphData2.HandleUWL = PlotY(tab_auto, TAB_AUTO_GRAPH_2, GraphData2.UWL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DASH, 1, 0xFFC000);		
		GraphData2.HandleLWL = PlotY(tab_auto, TAB_AUTO_GRAPH_2, GraphData2.LWL, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_DASH, 1, 0xFFC000);

		PlotY(tab_auto, TAB_AUTO_GRAPH_2, Center_Point, MAX_PLOT_NO, VAL_DOUBLE, VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, 0x80FF00);
	}
		
	for(i = 0; i < MeasPoints; i++ )
	{
		GraphData.Data[i][0] = Center_Point[i];
		GraphData1.Data[i][0] = Center_Point[i];
		GraphData2.Data[i][0] = Center_Point[i];
	}

	if( GraphData.DataNum < 1 )		GraphData.DataNum = 1;
	if( GraphData1.DataNum < 1 )	GraphData1.DataNum = 1;
	if( GraphData2.DataNum < 1 )	GraphData2.DataNum = 1;
	
	//Data Graph
	GraphData.HandleData = PlotY(tab_auto, TAB_AUTO_GRAPH, &GraphData.Data[SPCDisplayPointNo], GraphData.DataNum, VAL_DOUBLE,
							VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_CIRCLE, VAL_SOLID, 1, VAL_BLUE);
	//1) Graph2
	GraphData1.HandleData = PlotY(tab_auto, TAB_AUTO_GRAPH_1, &GraphData1.Data[SPCDisplayPointNo], GraphData1.DataNum, VAL_DOUBLE,
							VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_CIRCLE, VAL_SOLID, 1, VAL_BLUE);
	//2) Graph3
	GraphData2.HandleData = PlotY(tab_auto, TAB_AUTO_GRAPH_2, &GraphData2.Data[SPCDisplayPointNo], GraphData2.DataNum, VAL_DOUBLE,
							VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_CIRCLE, VAL_SOLID, 1, VAL_BLUE);
	
	if( OldHandleData != 0 ) 
		DeleteGraphPlot(tab_auto, TAB_AUTO_GRAPH, OldHandleData, VAL_IMMEDIATE_DRAW);
	if( OldHandleData1 != 0 )
		DeleteGraphPlot(tab_auto, TAB_AUTO_GRAPH_1, OldHandleData1, VAL_IMMEDIATE_DRAW);
	if( OldHandleData2 != 0 )
		DeleteGraphPlot(tab_auto, TAB_AUTO_GRAPH_2, OldHandleData2, VAL_IMMEDIATE_DRAW);
	
	SetAxisScalingMode(tab_auto, TAB_AUTO_GRAPH, VAL_LEFT_YAXIS, VAL_MANUAL, Lower, Upper);
	SetAxisScalingMode(tab_auto, TAB_AUTO_GRAPH_1, VAL_LEFT_YAXIS, VAL_MANUAL, Lower, Upper);
	SetAxisScalingMode(tab_auto, TAB_AUTO_GRAPH_2, VAL_LEFT_YAXIS, VAL_MANUAL, Lower, Upper);
}

void 	SetGraphRange(void)
{
	int		i;
	
	GraphData.HandleData = 0;
	GraphData.HandleLCL = 0;
	GraphData.HandleLWL = 0;
	GraphData.HandleUWL = 0;
	GraphData.HandleUCL = 0;
	
	GraphData1.HandleData = 0;
	GraphData1.HandleLCL = 0;
	GraphData1.HandleLWL = 0;
	GraphData1.HandleUWL = 0;
	GraphData1.HandleUCL = 0;
	
	GraphData2.HandleData = 0;
	GraphData2.HandleLCL = 0;
	GraphData2.HandleLWL = 0;
	GraphData2.HandleUWL = 0;
	GraphData2.HandleUCL = 0;
	
	for(i = 0; i < MAX_PLOT_NO; i++ )
	{
		GraphData.LCL[i] = Model[SPCDisplayPointNo].LCL;
		GraphData.LWL[i] = Model[SPCDisplayPointNo].LWL;
		GraphData.UWL[i] = Model[SPCDisplayPointNo].UWL;
		GraphData.UCL[i] = Model[SPCDisplayPointNo].UCL;
		
		GraphData1.LCL[i] = Model[SPCDisplayPointNo].LCL;
		GraphData1.LWL[i] = Model[SPCDisplayPointNo].LWL;
		GraphData1.UWL[i] = Model[SPCDisplayPointNo].UWL;
		GraphData1.UCL[i] = Model[SPCDisplayPointNo].UCL;
		
		GraphData2.LCL[i] = Model[SPCDisplayPointNo].LCL;
		GraphData2.LWL[i] = Model[SPCDisplayPointNo].LWL;
		GraphData2.UWL[i] = Model[SPCDisplayPointNo].UWL;
		GraphData2.UCL[i] = Model[SPCDisplayPointNo].UCL;
	}
}

void 	SetSpcData(int mc)
{
	int		mcid = McID;
	
	SetTableCellVal(tab_auto, TAB_AUTO_TABLE_SPC, MakePoint(1, 2), McSpc[mcid].Points[SPCDisplayPointNo].Max);
	SetTableCellVal(tab_auto, TAB_AUTO_TABLE_SPC, MakePoint(2, 2), McSpc[mcid].Points[SPCDisplayPointNo].Min);
	SetTableCellVal(tab_auto, TAB_AUTO_TABLE_SPC, MakePoint(3, 2), McSpc[mcid].Points[SPCDisplayPointNo].Avg);
	SetTableCellVal(tab_auto, TAB_AUTO_TABLE_SPC, MakePoint(4, 2), McSpc[mcid].Points[SPCDisplayPointNo].Dev);
	SetTableCellVal(tab_auto, TAB_AUTO_TABLE_SPC, MakePoint(5, 2), McSpc[mcid].Points[SPCDisplayPointNo].Cp);
	SetTableCellVal(tab_auto, TAB_AUTO_TABLE_SPC, MakePoint(6, 2), McSpc[mcid].Points[SPCDisplayPointNo].Cpk);
}

void	CalcSpcData(int mc)
{
	int			i, j, StartIndex, aDataNo, MaxIndex, MinIndex, NumIdx;
	double		TempData[MAX_MEAS_CYCLE] = {0,};
	double		TempData2[MAX_MEAS_CYCLE] = {0,};
	double		TempData3 = 0.0, Cpl, Cpu;
	int 		SpcDataNo = 50,
				SpcSigma = 6;
	
	int			mcid = McID, modeid =  ModeID;
	
	StartIndex = Mc[mcid].Mode[modeid].EndDataNo - SpcDataNo;
	if( StartIndex < 0 )
	{
		if( Mc[mcid].Mode[modeid].EndDataNo < Mc[mcid].Mode[modeid].StartDataNo )
		{
			StartIndex = Mc[mcid].Mode[modeid].StartDataNo;
			aDataNo = ( MAX_MEAS_CYCLE > SpcDataNo ) ? SpcDataNo : MAX_MEAS_CYCLE;
		}
		else
		{
			StartIndex = Mc[mcid].Mode[modeid].StartDataNo;
			aDataNo = Mc[mcid].Mode[modeid].EndDataNo - Mc[mcid].Mode[modeid].StartDataNo;
		}
	}
	else aDataNo = SpcDataNo;

	for(i = 0; i < MeasPoints; i++)
	{
		NumIdx = StartIndex;
		for(j = StartIndex; j < StartIndex + aDataNo; j++)
		{
			if( j >= MAX_MEAS_CYCLE )
				NumIdx = 1;
			TempData[j-StartIndex] = Mc[mcid].Mode[modeid].ResultValue[i][NumIdx++];
		}
		
		// Average
		TempData3 = 0.0;
		for(j = 0 ; j < aDataNo ; j ++)
			TempData3 += TempData[j];
		McSpc[mcid].Points[i].Avg = (TempData3/aDataNo);
		
		// Deviation
		for(j = 0 ; j < aDataNo ; j ++)
			TempData2[j] = TempData[j] - McSpc[mcid].Points[i].Avg;
		
		// Deviation^2
		for(j = 0 ; j < aDataNo ; j ++)	
			TempData2[j] = TempData2[j] * TempData2[j];	
		
		// Variance
		TempData3 = 0.0;
		for(j = 0 ; j < aDataNo ; j ++)	
			TempData3 += TempData2[j];
		McSpc[mcid].Points[i].V = (TempData3/aDataNo);
	
		// Standard Deviation
		McSpc[mcid].Points[i].Sdev = sqrt(McSpc[mcid].Points[i].V);

		// Cp
		McSpc[mcid].Points[i].Cp = (Model[i].UCL - Model[i].LCL)/(SpcSigma * McSpc[mcid].Points[i].Sdev);
		
		// Cpk = Min(Cpl, Cpu)
		Cpu = (Model[i].UCL - McSpc[mcid].Points[i].Avg)/(3.0 * McSpc[mcid].Points[i].Sdev);
		Cpl = (McSpc[mcid].Points[i].Avg - Model[i].LCL)/(3.0 * McSpc[mcid].Points[i].Sdev);
		McSpc[mcid].Points[i].Cpk = Min(Cpu, Cpl);
		/*
		// Near Upper
		if(McSpc[mcid].Points[i].Avg > (Model[i].UCL + Model[i].LCL)/2)
			McSpc[mcid].Points[i].Cpk = (Model[i].UCL - McSpc[mcid].Points[i].Avg)/(3.0 * McSpc[mcid].Points[i].Sdev);	
		// Near Lower
		else
			McSpc[mcid].Points[i].Cpk = (McSpc[mcid].Points[i].Avg - Model[i].LCL)/(3.0 * McSpc[mcid].Points[i].Sdev);	
		*/	

		if(McSpc[mcid].Points[i].Cp > 100.0)		McSpc[mcid].Points[i].Cp = 99.999;
		else if(McSpc[mcid].Points[i].Cp < 0.0)		McSpc[mcid].Points[i].Cp = 0.0;
			
		if(McSpc[mcid].Points[i].Cpk > 100.0)		McSpc[mcid].Points[i].Cpk = 99.999;
		else if(McSpc[mcid].Points[i].Cpk < 0.0)	McSpc[mcid].Points[i].Cpk = 0.0;
		
		//	Max. Min. Range계산
		if( aDataNo != 0)
			MaxMin1D (TempData, aDataNo, &McSpc[mcid].Points[i].Max, &MaxIndex, &McSpc[mcid].Points[i].Min, &MinIndex);
		McSpc[mcid].Points[i].Dev = McSpc[mcid].Points[i].Max - McSpc[mcid].Points[i].Min;
	}
}

void	SendResultToPlc(void)
{
	int i, no;
	
	GetNumTableRows (tab_table, TAB_TABLE_TABLE, &no);
	
	for(i = 0; i < MeasPoints ; i ++)
	{
		if(Model[i].Offset)
		{
			// -NG
			if(Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] < Model[i].LCL)
			{
				PlcData[240 + ((Model[i].Offset-1)*5)] = 1;
			}
			// -OK
			else if(Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] >=  Model[i].LCL &&
					Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] <= Model[i].LWL)
			{
				PlcData[241 + ((Model[i].Offset-1)*5)] = 1;
				SetTableCellAttribute (tab_table, TAB_TABLE_TABLE, MakePoint(i + 5, no), ATTR_TEXT_BGCOLOR, VAL_GREEN);
			}
			// OK
			else if(Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] > Model[i].LWL &&
					Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] < Model[i].UWL)
			{
				PlcData[242 + ((Model[i].Offset-1)*5)] = 1;
			}
			// +OK
			else if(Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] >= Model[i].UWL &&
					Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] <=  Model[i].UCL)
			{
				PlcData[243 + ((Model[i].Offset-1)*5)] = 1;
				SetTableCellAttribute (tab_table, TAB_TABLE_TABLE, MakePoint(i + 5, no), ATTR_TEXT_BGCOLOR, VAL_GREEN);
			}
			// +NG
			else if(Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] >  Model[i].UCL)
			{
				PlcData[244 + ((Model[i].Offset-1)*5)] = 1;
			}
		}
	}
}

void 	SetDataValue(void)
{
	int		i = 0, no;
	char    temp[24],fmt[12];
	double	dtemp[MAX_MEAS_POINTS] = {0.0,};
	
	//TAB_TABLE_TABLE
	InsertTableRows (tab_table, TAB_TABLE_TABLE, -1, 1, VAL_CELL_STRING);
	GetNumTableRows (tab_table, TAB_TABLE_TABLE, &no);

//	if(!(no % 2))
//		SetTableCellRangeAttribute (tab_table, TAB_TABLE_TABLE, MakeRect(no, 1, 1, MeasPoints+2), ATTR_TEXT_BGCOLOR, 0x99CCFFL);

	if(no > 1000)
	{
		DeleteTableRows(tab_table, TAB_TABLE_TABLE, 1, 1);
		no--;
	}

	GetTableCellVal(mainpanel, MAIN_TESTNO, MakePoint(1, 2), &i);

	sprintf(temp, "%d", i);
	SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, no, ATTR_USE_LABEL_TEXT, 1);
	SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, no, ATTR_LABEL_POINT_SIZE, 11);
	SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, no, ATTR_LABEL_BOLD , 0);
	SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, no, ATTR_LABEL_TEXT, temp);
	SetTableRowAttribute(tab_table, TAB_TABLE_TABLE, no, ATTR_ROW_HEIGHT, 15);
    // 마킹기 추 가 시 3 -> 4
	SetTableCellRangeAttribute(tab_table, TAB_TABLE_TABLE, MakeRect(no, 1, 1, MeasPoints+3), ATTR_TEXT_POINT_SIZE, 11);
	SetTableCellRangeAttribute(tab_table, TAB_TABLE_TABLE, MakeRect(no, 1, 1, MeasPoints+3), ATTR_CELL_JUSTIFY, VAL_CENTER_RIGHT_JUSTIFIED);
	SetTableCellRangeAttribute(tab_table, TAB_TABLE_TABLE, MakeRect(no, 1, 1, MeasPoints+3), ATTR_TEXT_BOLD, 0);
 	SetTableCellRangeAttribute(tab_table, TAB_TABLE_TABLE, MakeRect(no, 1, 1, MeasPoints+3), ATTR_CELL_TYPE, VAL_CELL_STRING);
	
	for(i = 0 ; i < 4; i ++)
	{
		if(i == 0)	//DATE / TIME
		{
			sprintf(temp, "%s/%s", MeasDate, MeasTime);
			SetTableCellVal(tab_table, TAB_TABLE_TABLE, MakePoint(i+1, no), temp);
		}
		else if(i == 1)	// #10
		{
			sprintf(temp, "%d", McNo1 + 101);
			SetTableCellVal(tab_table, TAB_TABLE_TABLE, MakePoint(i+1, no), temp);
		}
		else if(i == 2)	// #20
		{
			sprintf(temp, "%d", McNo2 + 201);
			SetTableCellVal(tab_table, TAB_TABLE_TABLE, MakePoint(i+1, no), temp);
		}
		// 마킹기 추 가 시 주 석 해 제
		//else	//	MARK
		//{
		//	sprintf(temp, "%s", MarkStr);
		//	SetTableCellVal(tab_table, TAB_TABLE_TABLE, MakePoint(i+1, no), temp);
		//}
	}
	
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		dtemp[i] = Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1];

		sprintf(fmt, "%%.%df", Model[i].Unit);
		sprintf(temp, fmt, dtemp[i]);
		SetTableCellVal(tab_table, TAB_TABLE_TABLE, MakePoint(i+1+3, no), temp); 				// 마킹기 추 가 시 3-> 4
	}

	if(!TotalGFlag)
	{
		// 마킹기 추 가 시 3-> 4
		SetTableCellRangeAttribute (tab_table, TAB_TABLE_TABLE, MakeRect(no, 1, 1, MeasPoints+3), ATTR_TEXT_BGCOLOR, 0xFFDDDD);
		for( i = 0; i < MeasPoints; i++ )
		{
			if(GFlag[i] == FALSE)
			{
				// 마킹기 추 가 시 4-> 5
				SetTableCellAttribute (tab_table, TAB_TABLE_TABLE, MakePoint(i+4, no), ATTR_TEXT_BGCOLOR, VAL_RED);
				SetTableCellAttribute (tab_table, TAB_TABLE_TABLE, MakePoint(i+4, no), ATTR_TEXT_COLOR, VAL_BLACK);
			}
		}
	}
	else
		SendResultToPlc();
	// 마킹기 추 가 시 3-> 4
	SetTableSelection(tab_table, TAB_TABLE_TABLE, MakeRect(no, 1, 1, MeasPoints+3));	
}

void	CalculateResultValue(int sig)
{
	int		i, j, p;
	int 	MaxIndex, MinIndex;
	double  MaxValue1 = 0.0, MinValue1 = 0.0, AvgValue = 0.0;
	double  MaxValue2 = 0.0, MinValue2 = 0.0;//, AvgValue = 0.0;
	double 	DataPerChValue[MAX_CH][3] = {0.0};	// 0: AVG, 1:Min, 2:Max
	double 	MinTemp[MAX_CH] = {0.0,};
	double 	MaxTemp[MAX_CH] = {0.0,};
	
	for(i = 0 ; i < MAX_CH ; i ++)
	{
		for(j = 0 ; j < MeasChIndex[sig] ; j ++)
		{
			MeasChTemp[i][j] = MeasChValue[j][i];
		}
		MaxMin1D(MeasChTemp[i], MeasChIndex[sig], &DataPerChValue[i][2], &MaxIndex, &DataPerChValue[i][1], &MinIndex);
		Mean(MeasChTemp[i], MeasChIndex[sig], &DataPerChValue[i][0]);	
	}
		
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		//AVG
		p = 0;
		AvgValue = 0.0;
		if(Model[i].P1 != 999)
		{
			AvgValue += (DataPerChValue[Model[i].P1][0]*Model[i].sign1);
			p++;
		}
		if(Model[i].P2 != 999)
		{
			AvgValue += (DataPerChValue[Model[i].P2][0]*Model[i].sign2);
			p++;
		}
		if(Model[i].P3 != 999)
		{
			AvgValue += (DataPerChValue[Model[i].P3][0]*Model[i].sign3);
			p++;
		}
		if(Model[i].P4 != 999)
		{
			AvgValue += (DataPerChValue[Model[i].P4][0]*Model[i].sign4);
			p++;
		}
		if(p < 4)
		{
			if(p == 2)
				AvgValue = AvgValue / (1.0);		
			else
				AvgValue = AvgValue / (p*1.0);		
		}
		else
			AvgValue = AvgValue / (p*1.0) / 2.0;

		//MIN
		p = 0;
		MinValue1 = 0.0;
		if(Model[i].P1 != 999)	MinTemp[p++] = (DataPerChValue[Model[i].P1][1]*Model[i].sign1);
		if(Model[i].P2 != 999)	MinTemp[p++] = (DataPerChValue[Model[i].P2][1]*Model[i].sign2);
		if(Model[i].P3 != 999)	MinTemp[p++] = (DataPerChValue[Model[i].P3][1]*Model[i].sign3);
		if(Model[i].P4 != 999)	MinTemp[p++] = (DataPerChValue[Model[i].P4][1]*Model[i].sign4);
		
		if(p > 0)
		{
			MaxMin1D(MinTemp, p, &MaxValue1, &MaxIndex, &MinValue1, &MinIndex);
/*
			for(j = 0 ; j < p-1 ; j ++)
			{
				if(MinTemp[j] < MinTemp[j+1])
					MinValue = MinTemp[j];
				else
					MinValue = MinTemp[j];
			}
*/
		}
		
		//MAX
		p = 0;
		MaxValue2 = 0.0;
		if(Model[i].P1 != 999)	MaxTemp[p++] = (DataPerChValue[Model[i].P1][2]*Model[i].sign1);
		if(Model[i].P2 != 999)	MaxTemp[p++] = (DataPerChValue[Model[i].P2][2]*Model[i].sign2);
		if(Model[i].P3 != 999)	MaxTemp[p++] = (DataPerChValue[Model[i].P3][2]*Model[i].sign3);
		if(Model[i].P4 != 999)	MaxTemp[p++] = (DataPerChValue[Model[i].P4][2]*Model[i].sign4);
	
		if(p > 0)
		{
			MaxMin1D(MaxTemp, p, &MaxValue2, &MaxIndex, &MinValue2, &MinIndex);
/*			
			for(j = 0 ; j < p-1 ; j ++)
			{
				if(MaxTemp[j] > MaxTemp[j+1])
					MaxValue = MaxTemp[j];
				else
					MaxValue = MaxTemp[j+1];					
			}
*/
		}
		
		switch(Model[i].Cal)
		{
			case 0:	//AVG
				ResultValue[i] = AvgValue;
//				ResultValue[i] /= 1000.0;
				break;
			case 1:	//MIN
				ResultValue[i] = MinValue1;
//				ResultValue[i] /= 1000.0;
				break;
			case 2:	//MAX	
				ResultValue[i] = MaxValue2;
//				ResultValue[i] /= 1000.0;
				break;
			case 3:	//MAX-MIN
				if(MaxValue2 > 0.0 && MinValue1 > 0.0)
					ResultValue[i] = MaxValue2 - MinValue1;
				else if(MaxValue2 > 0.0 && MinValue1 < 0.0)
					ResultValue[i] = MaxValue2 - MinValue1;
				else if(MaxValue2 < 0.0 && MinValue1 < 0.0)
					ResultValue[i] = MaxValue2 - MinValue1;
				else
					ResultValue[i] = MaxValue2 + MinValue1;
					
				if(ResultValue[i] < 0)
					ResultValue[i] *= -1.0;
//				ResultValue[i] /= 1000.0;
				break;
			case 4: //REFERED VALUES
				ResultValue[i] = 0.0;
				if(Model[i].P1 != 999)	ResultValue[i] += ResultValue[Model[i].P1]*Model[i].sign1;
				if(Model[i].P2 != 999)	ResultValue[i] += ResultValue[Model[i].P2]*Model[i].sign2;
				if(Model[i].P3 != 999)	ResultValue[i] += ResultValue[Model[i].P3]*Model[i].sign3;
				if(Model[i].P4 != 999)	ResultValue[i] += ResultValue[Model[i].P4]*Model[i].sign4;

//				ResultValue[i] = ResultValue[i-1] + ResultValue[i-3];
				break;
		}
		ResultValue[i] = ResultValue[i] + Model[i].Comp + Model[i].Master;
		ResultValue[i] = ResultValue[i] * Model[i].Fact / 100.0;
		ResultValue[i] = TruncateRealNumber(ResultValue[i] * pow(10., Model[i].Unit)) / pow(10., Model[i].Unit);
	}
	
	Mc[0].Mode[ModeID].CycleIndex ++;
	Mc[0].Mode[ModeID].EndDataNo ++;
	
	// McID :0 = 선반1, 선반2 데이터  모두
	// McID :1 = 선반1 데이터만
	// McID :2 = 선반2 데이터만
	if( Mc[0].Mode[ModeID].EndDataNo >= MAX_MEAS_CYCLE )
		Mc[0].Mode[ModeID].EndDataNo = 1;
	if( Mc[0].Mode[ModeID].EndDataNo == Mc[0].Mode[ModeID].StartDataNo )
		Mc[0].Mode[ModeID].StartDataNo = Mc[0].Mode[ModeID].EndDataNo + 1;
	if( Mc[0].Mode[ModeID].StartDataNo >= MAX_MEAS_CYCLE )
			Mc[0].Mode[ModeID].StartDataNo = 1;	
	
	if(AutoMode)
	{
		Mc[McID + 1].Mode[ModeID].CycleIndex ++;
		Mc[McID + 1].Mode[ModeID].EndDataNo ++;

		// 선반별로 데이터 저장
		if( Mc[McID + 1].Mode[ModeID].EndDataNo >= MAX_MEAS_CYCLE )
			Mc[McID + 1].Mode[ModeID].EndDataNo = 1;
		if( Mc[McID + 1].Mode[ModeID].EndDataNo == Mc[McID + 1].Mode[ModeID].StartDataNo )
			Mc[McID + 1].Mode[ModeID].StartDataNo = Mc[McID + 1].Mode[ModeID].EndDataNo + 1;
		if( Mc[McID + 1].Mode[ModeID].StartDataNo >= MAX_MEAS_CYCLE )
				Mc[McID + 1].Mode[ModeID].StartDataNo = 1;	
	}
}

void ShiftSensorValueFile(int a)
{
	int		i;
	char 	Path1[1024] = {0,};
	char 	Path2[1024] = {0,};
	
	sprintf(Path1, "%s\\%s\\SensorValue_%02d.csv", Path_Model, ModelName[ModelNo], a);	
	sprintf(Path2, "%s\\%s\\SensorValue_%02d.csv", Path_Model, ModelName[ModelNo], a+1);	
	
	if(GetFileInfo(Path2, &i) > 0)
		DeleteFile(Path2);
	
	rename(Path1, Path2);

}

void SaveSensorValue(int sig)
{
	int 	i, j, handle;
	char 	Path[1024] = {0,};
	char 	temp1[1024] = {0,};
	char 	temp2[1024] = {0,};
	char 	fmt[64] = {0,};
	
	if( SetDir(Path_Model) ) 	MakeDir(Path_Model);
	sprintf(Path, "%s\\%s", Path_Model, ModelName[ModelNo]);
	
	if( SetDir(Path) )			MakeDir(Path);
	sprintf(Path, "%s\\%s\\SensorValue_%02d.csv", Path_Model, ModelName[ModelNo], 0);
	
	for(i = 9 ; i >= 0 ; i --)
		ShiftSensorValueFile(i);
	
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR MODEL", "CHECK PROGRAM SETUP - PATH : MODEL");
	else
	{
		// Sig No
		sprintf(temp2, "%d", sig + 1);
		WriteLine(handle, temp2, -1);
			
		// Ch Index
		sprintf(temp2, "%d", MeasChIndex[sig]-1);
		WriteLine(handle, temp2, -1);
		
		// Ch Name
		sprintf(temp1, ",");
		sprintf(temp2, "%10s", temp1);
		
		for(j = 0 ; j < MAX_CH ; j ++)
		{
			sprintf(temp1, "CH%02d,", j + 1);
			sprintf(fmt, "%10s", temp1);
			strcat(temp2, fmt);
		}
		WriteLine(handle, temp2, -1);
		
		// Ch Value
		for(j = 1 ; j <  MeasChIndex[sig] ; j ++)
		{
			sprintf(temp1, "%d,", j + 1);
			sprintf(temp2, "%10s", temp1);
			for(i = 0 ; i < MAX_CH ; i ++)
			{
				sprintf(temp1, "%.3f,", MeasChValue[j][i]);
				sprintf(fmt, "%10s", temp1);
				strcat(temp2, fmt);
			}
			WriteLine(handle, temp2, -1);			
		}
		CloseFile(handle);
	}	
}

void AutoMeasFinish(int sig)
{
	int		i;
	char 	temp1[1024] = {0,};
	char 	fmt[10] = {0,};
	long	fileSize;	
	
	GetDataFileName();
	if(GetFileInfo (DataFileNameAll, &fileSize) == 0) 
	{
		CreateDataFile();
		TotalNo = OkNo = NgNo = 0;
	}
	
	LastSig = 0;
	
	strcpy(MeasTime, CurrTime);
	strcpy(MeasDate, CurrDate);
	
	ModeID = 0;
	TotalGFlag = 1;
	
	SaveSensorValue(sig);
	CalculateResultValue(sig);
	//가공기 관련 확인 사항
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		Mc[0].Mode[ModeID].ResultValue[i][Mc[0].Mode[ModeID].EndDataNo - 1] = ResultValue[i];
//		Mc[McID + 1].Mode[ModeID].ResultValue[i][Mc[McID + 1].Mode[ModeID].EndDataNo - 1] = ResultValue[i];
	}
	
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		// NEED : Sperate Model Sig - Measuring Sig each for MeasPoints
		GFlag[i] = 1;
		
		if(Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] < Model[i].LCL ||
		   Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1] > Model[i].UCL )
			GFlag[i] = 0;
		
		if(Model[i].Use != 1)
			GFlag[i] = 1;
		
		if(GFlag[i] == 0)
			TotalGFlag = 0;
	}
	
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		if(GFlag[i])
		{
			SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_TEXT_BGCOLOR, 0x80ff00);
			SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
		}
		else
		{
			SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_TEXT_BGCOLOR, 0xFF0000);
			SetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
		}
		sprintf(fmt, "%%.%df", Model[i].Unit);
		sprintf(temp1, fmt, Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1]);
		SetCtrlVal(tab_auto, PointCtrl[i], temp1);
	}
	
	if(!TotalGFlag && ReMeasUse && (2 > ++ReMeasCnt))
	{
		Mc[0].Mode[ModeID].CycleIndex --;
		Mc[0].Mode[ModeID].EndDataNo --;
		
		Mc[McID + 1].Mode[ModeID].CycleIndex --;
		Mc[McID + 1].Mode[ModeID].EndDataNo --;

		SetCtrlVal(tab_auto, TAB_AUTO_GNG, "\nRe-Meas\n");
		SetCtrlAttribute(tab_auto, TAB_AUTO_GNG, ATTR_TEXT_BGCOLOR, VAL_RED);
		SetCtrlAttribute(tab_auto, TAB_AUTO_GNG, ATTR_TEXT_COLOR, VAL_WHITE);
		PlcData[20+sig] = 1;
		
		// Judgment for Each Measuring Signal
		PlcData[24+(sig*2)] = TotalGFlag;	
		PlcData[25+(sig*2)] = !TotalGFlag;		
		
		// Measuring Finish Signal		
		PlcData[32+sig] = 1;
		return;
	}	
	PlcData[20+sig] = 0;
	ReMeasCnt = 0;
	
	// Judgment for Each Measuring Signal
	PlcData[24+(sig*2)] = TotalGFlag;	
	PlcData[25+(sig*2)] = !TotalGFlag;	

	// Measuring Finish Signal		
	PlcData[32+sig] = 1;
	
	// LastSig 설정부분
	if(sig < LastSig)	
	{
		Mc[0].Mode[ModeID].CycleIndex --;
		Mc[0].Mode[ModeID].EndDataNo --;
		
		Mc[McID + 1].Mode[ModeID].CycleIndex --;
		Mc[McID + 1].Mode[ModeID].EndDataNo --;		
		return;
	}
	
	if(TotalGFlag)
	{
		TotalNo++;
		OkNo++;
		ContinuousNgNo = 0;
		SetCtrlVal(tab_auto, TAB_AUTO_GNG, "\nOK\n");
		SetCtrlAttribute(tab_auto, TAB_AUTO_GNG, ATTR_TEXT_BGCOLOR, VAL_BLUE);
		SetCtrlAttribute(tab_auto, TAB_AUTO_GNG, ATTR_TEXT_COLOR, VAL_WHITE);
	}
	else
	{
		TotalNo++;
		NgNo++;
		ContinuousNgNo++;
		SetCtrlVal(tab_auto, TAB_AUTO_GNG, "\nNG\n");
		SetCtrlAttribute(tab_auto, TAB_AUTO_GNG, ATTR_TEXT_BGCOLOR, VAL_RED);
		SetCtrlAttribute(tab_auto, TAB_AUTO_GNG, ATTR_TEXT_COLOR, VAL_WHITE);
	}
	
	if(ContinuousNgNo >= ContinuousNgCount && ContinuousNgAlarmUse)
	{
		PlcData[39] = 1;
		LogUpdate("Continuous NG Alarm");
		SetCtrlAttribute(tab_auto, TAB_AUTO_CONTINUOUS_TXT, ATTR_VISIBLE, 1);
		ContinuousNgNo = 0;
	}
	
	//Counter Display
	SetCountDisplay(TotalNo, OkNo, NgNo);	
	CalcSpcData(0);
	CalcSpcData(McID+1);
	SetSpcData(0);


	MakeGraphData();
	GraphPlot();
	
//	if(TotalGFlag)	
	//마킹 추가 시 주석 해제
	//if(Mark.portNumber > 0 && PlcData[161])
		//MakeMarkData();
	
	SetDataValue();

	SaveDataBase();
	SaveDataFile();
	
	sprintf(temp1, "Auto Sig:%d, Sensing Count:%d", sig+1, MeasChIndex[sig]);
	LogUpdate(temp1);
//	PlcData[32+sig] = 1;
}

void ManuMeasFinish(int sig)
{
	int		i;
	char 	temp1[1024] = {0,},
			fmt[10] = {0,};	
	int 	RepeatNo, Repeat;
	
	ModeID = 1;
	
	SaveSensorValue(sig);
	CalculateResultValue(sig);

	for(i = 0 ; i < MeasPoints ; i ++)
	{
		Mc[McID].Mode[ModeID].ResultValue[i][Mc[McID].Mode[ModeID].EndDataNo - 1] = ResultValue[i];
//		Mc[McID + 1].Mode[ModeID].ResultValue[i][Mc[McID + 1].Mode[ModeID].EndDataNo - 1] = ResultValue[i];
	}
	
	for(i = 0 ; i < MeasPoints ; i ++)
	{
		SetTableCellVal(tab_manual, TAB_MANU_A_TABLE, MakePoint(3, i+1), Mc[McID].Mode[ModeID].ResultValue[i][Mc[McID].Mode[ModeID].EndDataNo - 1]); 
		if((Model[i].LCL > Mc[McID].Mode[ModeID].ResultValue[i][Mc[McID].Mode[ModeID].EndDataNo - 1])
		|| Model[i].UCL < Mc[McID].Mode[ModeID].ResultValue[i][Mc[McID].Mode[ModeID].EndDataNo - 1])
			SetTableCellAttribute(tab_manual, TAB_MANU_A_TABLE, MakePoint(3, i+1), ATTR_TEXT_COLOR, VAL_RED);
		else 
			SetTableCellAttribute(tab_manual, TAB_MANU_A_TABLE, MakePoint(3, i+1), ATTR_TEXT_COLOR, VAL_BLUE);
	}
	sprintf(temp1, "Manual Sig:%d, Sensing Count:%d", sig+1, MeasChIndex[sig]);
	LogUpdate(temp1);
	
	//Meas Data Update
	sprintf(fmt, "%%.%df", Model[ManuItemSelected].Unit);
	sprintf(temp1, fmt, Mc[McID].Mode[ModeID].ResultValue[ManuItemSelected][Mc[McID].Mode[ModeID].EndDataNo - 1]);

	InsertListItem(tab_manual, TAB_MANU_ITEM_VALUE, -1, temp1, 0);	
	GetNumListItems(tab_manual, TAB_MANU_ITEM_VALUE, &i);
	SetCtrlIndex(tab_manual, TAB_MANU_ITEM_VALUE, i-1);
	
	SetCtrlVal(tab_manual, TAB_MANU_TESTNO, Mc[McID].Mode[ModeID].CycleIndex);
	
	//Repeat
	GetCtrlIndex(tab_manual, TAB_MANU_REPEAT, &Repeat);
	if(Repeat)
	{
		GetCtrlVal(tab_manual, TAB_MANU_REPEATNO, &RepeatNo);
		if(++MeasCycleNo < RepeatNo)
		{
			PlcData[20+sig] = 1;
		}
		else
		{
			PlcData[20+sig] = 0;
			MeasCycleNo = 0;
		}
	}
	else
	{
		PlcData[20+sig] = 0;
		MeasCycleNo = 0;		
	}
	SetCtrlVal(tab_manual, TAB_MANU_REPEATNO_2, MeasCycleNo);
	PlcData[32+sig] = 1;
}

void ZeroMeasFinish(int sig)
{
	int		i, j;
	double	Data[MAX_CH] = {0.0,};
	char 	temp1[1024] = {0,};
	
	if(MeasChIndex[sig] != 0)
	{
		for(i = 0 ; i < MAX_CH ; i ++)
		{
			for(j = 0 ; j < MeasChIndex[sig] ; j ++)
				Data[i] += MeasChValue[j][i];
			
			Data[i] /= MeasChIndex[sig];
		}
	}
	
	for(i = 0 ; i < MAX_CH ; i ++)
	{
		ZeroValueBef[i] = ZeroValueNow[i];
		ZeroValueNow[i] = Data[i];
		ZeroValueDev[i] = ZeroValueBef[i] - ZeroValueNow[i];
	}
	
	SetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 1, MAX_CH, 1), ZeroValueBef, VAL_COLUMN_MAJOR);
	SetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 2, MAX_CH, 1), ZeroValueNow, VAL_COLUMN_MAJOR);
	SetTableCellRangeVals(tab_zeroset, TAB_ZERO_TABLE, MakeRect(1, 3, MAX_CH, 1), ZeroValueDev, VAL_COLUMN_MAJOR);
	
	for(i = 0 ; i < MAX_CH ; i ++)
	{
		if((ZeroValueDev[i] < ZeroValueAlN[i]) || (ZeroValueDev[i] > ZeroValueAlP[i]))
			SetTableCellAttribute(tab_zeroset, TAB_ZERO_TABLE, MakePoint(3, i+1), ATTR_TEXT_COLOR, VAL_RED);
		else 
			SetTableCellAttribute(tab_zeroset, TAB_ZERO_TABLE, MakePoint(3, i+1), ATTR_TEXT_COLOR, VAL_BLUE);
	}
	sprintf(temp1, "Zeroset Sig:%d, Sensing Count:%d", sig+1, MeasChIndex[sig]);
	LogUpdate(temp1);
	SaveZeroTableData();
	
	PlcData[32+sig] = 1;
}