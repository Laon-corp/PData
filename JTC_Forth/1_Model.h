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

#define  MODEL                            1
#define  MODEL_CLOSE                      2       /* control type: pictButton, callback function: Cb_ModelPanel */
#define  MODEL_POINT_LOAD                 3       /* control type: command, callback function: Point_Load */
#define  MODEL_POINT_SAVE                 4       /* control type: command, callback function: Point_Save */
#define  MODEL_POINT_DELETE               5       /* control type: command, callback function: Point_Delete */
#define  MODEL_POINT_ADD                  6       /* control type: command, callback function: Point_Add */
#define  MODEL_LIST_MODEL                 7       /* control type: listBox, callback function: Cb_List_Model */
#define  MODEL_MODEL_RENAME               8       /* control type: command, callback function: Cb_Model_Rename */
#define  MODEL_MODEL_COPY                 9       /* control type: command, callback function: Cb_Model_Copy */
#define  MODEL_MODEL_ADD                  10      /* control type: command, callback function: Cb_Model_Add */
#define  MODEL_MODEL_DELETE               11      /* control type: command, callback function: Cb_Model_Delete */
#define  MODEL_MODEL_MOVEUP               12      /* control type: command, callback function: Cb_Model_MoveUp */
#define  MODEL_MODEL_MOVEDOWN             13      /* control type: command, callback function: Cb_Model_MoveDown */
#define  MODEL_TAB                        14      /* control type: tab, callback function: (none) */
#define  MODEL_DECORATION                 15      /* control type: deco, callback function: (none) */

     /* tab page panel controls */
#define  TABPANEL_MEAS_TABLE              2       /* control type: table, callback function: Cb_Point_Table */

     /* tab page panel controls */
#define  TABPANEL_2_CALC_TABLE            2       /* control type: table, callback function: (none) */

     /* tab page panel controls */
#define  TABPANEL_3_MARK_PARA_13          2       /* control type: ring, callback function: (none) */
#define  TABPANEL_3_MARK_PARA_12          3       /* control type: ring, callback function: (none) */
#define  TABPANEL_3_MARK_PARA_11          4       /* control type: ring, callback function: (none) */
#define  TABPANEL_3_MARK_PARA_3           5       /* control type: ring, callback function: (none) */
#define  TABPANEL_3_OPTIONAL_SEL_2        6       /* control type: ring, callback function: (none) */
#define  TABPANEL_3_OPTIONAL_SEL_1        7       /* control type: ring, callback function: (none) */
#define  TABPANEL_3_RULE                  8       /* control type: ring, callback function: (none) */
#define  TABPANEL_3_TEXT_1                9       /* control type: string, callback function: (none) */
#define  TABPANEL_3_MARK_PARA_5           10      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_4           11      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_15          12      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_14          13      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_2           14      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_8           15      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_7           16      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_6           17      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_9           18      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_10          19      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_PARA_1           20      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TABPANEL_3_MARK_CYCLE            21      /* control type: command, callback function: Cb_MarkCycle */
#define  TABPANEL_3_MARK_STR              22      /* control type: string, callback function: (none) */
#define  TABPANEL_3_MAKE_MARK             23      /* control type: command, callback function: Cb_MakeMark */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Cb_KeypadCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_List_Model(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_MakeMark(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_MarkCycle(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Model_Add(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Model_Copy(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Model_Delete(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Model_MoveDown(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Model_MoveUp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Model_Rename(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_ModelPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Point_Table(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Point_Add(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Point_Delete(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Point_Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Point_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif