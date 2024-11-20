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

#define  PORTPANEL                        1
#define  PORTPANEL_PLC_MAKER              2       /* control type: ring, callback function: (none) */
#define  PORTPANEL_PLC_PORT               3       /* control type: ring, callback function: (none) */
#define  PORTPANEL_PLC_BR                 4       /* control type: ring, callback function: (none) */
#define  PORTPANEL_PLC_DB                 5       /* control type: ring, callback function: (none) */
#define  PORTPANEL_PLC_PR                 6       /* control type: ring, callback function: (none) */
#define  PORTPANEL_PLC_SB                 7       /* control type: ring, callback function: (none) */
#define  PORTPANEL_MARK_PORT              8       /* control type: ring, callback function: (none) */
#define  PORTPANEL_MARK_BR                9       /* control type: ring, callback function: (none) */
#define  PORTPANEL_MARK_DB                10      /* control type: ring, callback function: (none) */
#define  PORTPANEL_MARK_PR                11      /* control type: ring, callback function: (none) */
#define  PORTPANEL_MARK_SB                12      /* control type: ring, callback function: (none) */
#define  PORTPANEL_AMP_PORT               13      /* control type: ring, callback function: (none) */
#define  PORTPANEL_AMP_BR                 14      /* control type: ring, callback function: (none) */
#define  PORTPANEL_AMP_DB                 15      /* control type: ring, callback function: (none) */
#define  PORTPANEL_TXT_MARK               16      /* control type: textMsg, callback function: (none) */
#define  PORTPANEL_AMP_PR                 17      /* control type: ring, callback function: (none) */
#define  PORTPANEL_AMP_SB                 18      /* control type: ring, callback function: (none) */
#define  PORTPANEL_DECORATION_4           19      /* control type: deco, callback function: (none) */
#define  PORTPANEL_ROLLBACK               20      /* control type: pictButton, callback function: Cb_Comport_Rollback */
#define  PORTPANEL_CLOSE                  21      /* control type: pictButton, callback function: Cb_ComportPanel */
#define  PORTPANEL_SAVE                   22      /* control type: pictButton, callback function: Cb_Comport_Save */
#define  PORTPANEL_TXT_AMP                23      /* control type: textMsg, callback function: (none) */
#define  PORTPANEL_TXT_1                  24      /* control type: textMsg, callback function: (none) */
#define  PORTPANEL_TXT_PLC                25      /* control type: textMsg, callback function: (none) */
#define  PORTPANEL_DECORATION_3           26      /* control type: deco, callback function: (none) */
#define  PORTPANEL_DECORATION_1           27      /* control type: deco, callback function: (none) */
#define  PORTPANEL_DECORATION_2           28      /* control type: deco, callback function: (none) */
#define  PORTPANEL_PLC_TCP_IP             29      /* control type: string, callback function: Cb_KeypadCtrl */
#define  PORTPANEL_PLC_TCP_PORT           30      /* control type: numeric, callback function: Cb_KeypadCtrl */

#define  SETUP                            2
#define  SETUP_COMPORT                    2       /* control type: pictButton, callback function: Cb_Comport */
#define  SETUP_ROLLBACK                   3       /* control type: pictButton, callback function: Cb_Rollback */
#define  SETUP_SAVE                       4       /* control type: pictButton, callback function: Cb_Save */
#define  SETUP_CLOSE                      5       /* control type: pictButton, callback function: Cb_SetupPanel */
#define  SETUP_PATH_MODEL                 6       /* control type: string, callback function: (none) */
#define  SETUP_PATH_POP_MODEL             7       /* control type: command, callback function: Cb_Path_Pop_Model */
#define  SETUP_PATH_RESULT                8       /* control type: string, callback function: (none) */
#define  SETUP_PATH_POP_RESULT            9       /* control type: command, callback function: Cb_Path_Pop_Result */
#define  SETUP_PATH_HISTORY               10      /* control type: string, callback function: (none) */
#define  SETUP_PATH_POP_HISTORY           11      /* control type: command, callback function: Cb_Path_Pop_History */
#define  SETUP_PATH_SETUP                 12      /* control type: string, callback function: (none) */
#define  SETUP_PATH_POP_SETUP             13      /* control type: command, callback function: Cb_Path_Pop_Setup */
#define  SETUP_PATH_RULE_RESULT           14      /* control type: ring, callback function: (none) */
#define  SETUP_PATH_RULE_HISTORY          15      /* control type: ring, callback function: (none) */
#define  SETUP_BYPASS_1                   16      /* control type: textButton, callback function: (none) */
#define  SETUP_BYPASS_2                   17      /* control type: textButton, callback function: (none) */
#define  SETUP_BYPASS_3                   18      /* control type: textButton, callback function: (none) */
#define  SETUP_BYPASS_4                   19      /* control type: textButton, callback function: (none) */
#define  SETUP_DECORATION_4               20      /* control type: deco, callback function: (none) */
#define  SETUP_TXT_PATH_4                 21      /* control type: textMsg, callback function: (none) */
#define  SETUP_DECORATION_3               22      /* control type: deco, callback function: (none) */
#define  SETUP_TXT_PATH_3                 23      /* control type: textMsg, callback function: (none) */
#define  SETUP_DECORATION_7               24      /* control type: deco, callback function: (none) */
#define  SETUP_DECORATION_6               25      /* control type: deco, callback function: (none) */
#define  SETUP_DECORATION_5               26      /* control type: deco, callback function: (none) */
#define  SETUP_DECORATION_2               27      /* control type: deco, callback function: (none) */
#define  SETUP_TXT_PATH_2                 28      /* control type: textMsg, callback function: (none) */
#define  SETUP_DECORATION                 29      /* control type: deco, callback function: (none) */
#define  SETUP_TXT_PATH                   30      /* control type: textMsg, callback function: (none) */
#define  SETUP_TIME_NIGHT                 31      /* control type: string, callback function: Cb_KeypadCtrl */
#define  SETUP_TIME_DAY                   32      /* control type: string, callback function: Cb_KeypadCtrl */
#define  SETUP_TEXTMSG                    33      /* control type: textMsg, callback function: (none) */
#define  SETUP_SAFETY_DOOR                34      /* control type: pictRing, callback function: Cb_Img_Button */
#define  SETUP_CONTINUOUS_NG              35      /* control type: pictRing, callback function: Cb_Img_Button */
#define  SETUP_RE_MEAS                    36      /* control type: pictRing, callback function: Cb_Img_Button */
#define  SETUP_SEPERATE_DAY               37      /* control type: pictRing, callback function: Cb_Img_Button */
#define  SETUP_OPTION_TIME_1              38      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  SETUP_CONTINUOUS_NG_CNT          39      /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  SETUP_TEXTMSG_2                  40      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Cb_Comport(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Comport_Rollback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Comport_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_ComportPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Img_Button(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_KeypadCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Path_Pop_History(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Path_Pop_Model(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Path_Pop_Result(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Path_Pop_Setup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Rollback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_SetupPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif