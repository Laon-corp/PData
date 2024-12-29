#include "A_Global.h"

int CVICALLBACK Cb_Main (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	int 	a, i;
	char 	temp1[1024] = {0,};
	char 	fmt[10] = {0,};
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;

		case EVENT_KEYPRESS:

			// ALT + A ~ Z 			: 131169 ~ 131194
			// CTL + A ~ Z 			: 262209 ~ 262234
			// ALT + SHIFT + A ~ Z	: 196673 ~ 196698
			// CTL + SHIFT + A ~ Z	: 327745 ~ 327770
			// CTL + SHIFT + 1		: 327713
			// CTL + SHIFT + 2		: 327744
			// CTL + SHIFT + 3		: 327715
			// CTL + SHIFT + 4		: 327716
			// CTL + SHIFT + 5		: 327717
			// CTL + SHIFT + 6		: 327774
			// CTL + SHIFT + 7		: 327718
			// CTL + SHIFT + 8		: 327722
			// CTL + SHIFT + 9		: 327720
			
			// CTL + ALT : NO WORKS			
			switch(eventData1)	
			{
				case 262209:	// CTRL + A
					//SendDataMark(0, "test");
					SendDataMark(0, "LAON.LLP0");
					break;
				case 262210:	// CTRL + B
					//SendDataMark(0, "test");
					SendDataMark(2, "LAON.LLP2");
					break;
				case 262211:	// CTRL + C
					SendDataMark(1, "LAON.LLP1");
					MarkStartFlag = 1;
					break;
				case 334336:	// CTL + SHIFT + F12
					if(TabPage != 0 && !d_in[6] && !PointCtrlMove)
						return 0;
					
					PointCtrlMove = !PointCtrlMove;
					if(!PointCtrlMove)
					{
						for(i = 0 ; i < MeasPoints ; i ++)
						{
							GetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_TOP, &BoxPos[i].BoxY);		
							GetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_LEFT, &BoxPos[i].BoxX);		
							GetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_LABEL_TOP, &BoxPos[i].LabY);		
							GetCtrlAttribute(tab_auto, PointCtrl[i], ATTR_LABEL_LEFT, &BoxPos[i].LabX);	
						}
						
						SaveModel_BoxPos();
						MessagePopup("Point Move Finished", "Saved Box Pos Data");
					}
					else
					{
						MessagePopup("Point Move Started", "Click Point, Use Keyboard");					
					}
					
					break;

				case 0x0600:	// UP
					if(PointCtrlMove)
					{
						GetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_TOP, &a);
						SetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_TOP, --a);
					}
					break;
				case 0x0700:	// DOWN
					if(PointCtrlMove)
					{
						GetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_TOP, &a);
						SetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_TOP, ++a);
					}
					break;
				case 0x00000800:	// LEFT
					if(PointCtrlMove)
					{
						GetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LEFT, &a);
						SetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LEFT, --a);
					}
					break;
				case 0x00000900:	// RIGHT
					if(PointCtrlMove)
					{
						GetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LEFT, &a);
						SetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LEFT, ++a);
					}
					break;
					
				case 0x00010600:	// SHIFT + UP
					if(PointCtrlMove)
					{
						GetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LABEL_TOP, &a);
						SetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LABEL_TOP, --a);
					}
					break;
				case 0x00010700:	// SHIFT + DOWN
					if(PointCtrlMove)
					{
						GetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LABEL_TOP, &a);
						SetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LABEL_TOP, ++a);
					}
					break;
				case 0x00010800:	// SHIFT + LEFT
					if(PointCtrlMove)
					{
						GetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LABEL_LEFT, &a);
						SetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LABEL_LEFT, --a);
					}
					break;
				case 0x00010900:	// SHIFT + RIGHT
					if(PointCtrlMove)
					{
						GetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LABEL_LEFT, &a);
						SetCtrlAttribute(tab_auto, PointCtrl[SPCDisplayPointNo], ATTR_LABEL_LEFT, ++a);
					}
					break;
					
				case 327762:	// CTL + SHIFT + R
					ReadSensorValueFile();

					break;
				case 327713:	// CTL + SHIFT + 1
					a = 0;
					goto MEAS;
				case 327744:
					a = 1;
					goto MEAS;
				case 327715:
					a = 2;
					goto MEAS;
				case 327716:
					a = 3;
					goto MEAS;
			}
			break;
	}
	return 0;
	
MEAS:

	for(MeasChIndex[a] = 0; MeasChIndex[a] < 10; MeasChIndex[a] ++)
		for(i = 0; i < MAX_CH; i++)
			MeasChValue[MeasChIndex[a]][i] = (double)(rand() / 10000);
	
	//for(i = 0 ; i <= MeasPoints ; i ++)
	//{
	//	sprintf(fmt, "%%.%df", Model[i].Unit);
	//	sprintf(temp1, fmt, Mc[0].Mode[0].ResultValue[i][Mc[0].Mode[0].EndDataNo - 1]);
	//	SetCtrlVal(tab_auto, PointCtrl[i], temp1);
	//}
	
	liveFlag = 1;
	
	if(TabPage == 1)
		ManuMeasFinish(a);
	else if(TabPage == 2)
		ZeroMeasFinish(a);
	else
		AutoMeasFinish(a);
	return 0;
}