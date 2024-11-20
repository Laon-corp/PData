/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PW                               1       /* callback function: Cb_PwPanel */
#define  PW_PASSWORD                      2       /* control type: string, callback function: Cb_KeypadCtrl */
#define  PW_CANCEL                        3       /* control type: command, callback function: Cb_Cancel */
#define  PW_OK                            4       /* control type: command, callback function: Cb_Ok */
#define  PW_DECORATION                    5       /* control type: deco, callback function: (none) */
#define  PW_TIMER_PW                      6       /* control type: timer, callback function: Cb_Timer_Pw */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Cb_Cancel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_KeypadCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Ok(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_PwPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Pw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif