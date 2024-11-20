#include <userint.h>
#include "2_Result.h"
#include "A_Global.h"

int CVICALLBACK Cb_ResultPanel (int panel, int control, int event,
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

void 	SetCountDisplay(int a, int b, int c)
{
	double ratio = (c*100.0) / (a*100.0) * 100.0;
	SetTableCellVal(mainpanel, MAIN_TESTNO, MakePoint(1, 2), a);
	SetTableCellVal(mainpanel, MAIN_TESTNO, MakePoint(2, 2), b);
	SetTableCellVal(mainpanel, MAIN_TESTNO, MakePoint(3, 2), c);
	if(a > 0)
		SetTableCellVal(mainpanel, MAIN_TESTNO, MakePoint(4, 2), ratio);		
	else
		SetTableCellVal(mainpanel, MAIN_TESTNO, MakePoint(4, 2), 0.0);		
}

void	GetBeforeDate(char *date)
{
	int	MM, DD, YYYY;

	GetSystemDate(&MM, &DD, &YYYY);
	
	if( DD > 1 )
		sprintf(date, "%04d-%02d-%02d", YYYY, MM, DD - 1 );
	else
	{
		MM--;
	    switch( MM )                                      
	    {
	        case 0:
	        	YYYY--;
	        	MM = 12;
	        	DD = 31;
	        	break;
	        case 1:
	        case 3:                                             
	        case 5:                                             
	        case 7:                                             
	        case 8:                                             
	        case 10:                                            
	        case 12:
	        	DD = 31;
	        	break;
	        case 4:                                             
	        case 6:                                             
	        case 9:                                             
	        case 11: 
	        	DD = 30;
	        	break;
	        case 2:                                             
	             if( YYYY % 4 )
	             	DD = 28;
	             else
	             	DD = 29;
	    }
		sprintf(date, "%04d-%02d-%02d", YYYY, MM, DD);
	}	
}