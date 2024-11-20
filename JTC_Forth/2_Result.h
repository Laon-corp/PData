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

#define  RESULT                           1
#define  RESULT_GFLAG                     2       /* control type: ring, callback function: (none) */
#define  RESULT_MODEL                     3       /* control type: ring, callback function: (none) */
#define  RESULT_CLOSE                     4       /* control type: pictButton, callback function: Cb_ResultPanel */
#define  RESULT_SEARCH                    5       /* control type: command, callback function: Cb_Db_Search */
#define  RESULT_CSVSAVE                   6       /* control type: pictButton, callback function: Cb_CsvSave */
#define  RESULT_DTPICKER_2                7       /* control type: activeX, callback function: (none) */
#define  RESULT_DTPICKER                  8       /* control type: activeX, callback function: (none) */
#define  RESULT_TABLE                     9       /* control type: table, callback function: (none) */
#define  RESULT_MSG_WAIT                  10      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Cb_CsvSave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Db_Search(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_ResultPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif