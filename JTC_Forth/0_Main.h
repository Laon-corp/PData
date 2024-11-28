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

#define  MAIN                             1       /* callback function: Cb_Main */
#define  MAIN_ST_AUTO                     2       /* control type: pictRing, callback function: Cb_St_Auto */
#define  MAIN_ST_MANUAL                   3       /* control type: pictRing, callback function: Cb_St_Manual */
#define  MAIN_ST_ORIGIN                   4       /* control type: pictRing, callback function: Cb_St_Origin */
#define  MAIN_ST_BUZZER                   5       /* control type: pictRing, callback function: Cb_St_Buzzer */
#define  MAIN_ST_RESET                    6       /* control type: pictRing, callback function: Cb_St_Reset */
#define  MAIN_ST_EMERGENCY                7       /* control type: pictRing, callback function: Cb_St_Emergency */
#define  MAIN_ST_WORKOUT                  8       /* control type: pictRing, callback function: Cb_St_Workout */
#define  MAIN_ST_LIGHT                    9       /* control type: pictRing, callback function: Cb_St_Light */
#define  MAIN_LOGO                        10      /* control type: picture, callback function: Cb_Logo */
#define  MAIN_DATE                        11      /* control type: string, callback function: (none) */
#define  MAIN_TIME                        12      /* control type: string, callback function: (none) */
#define  MAIN_BT_ZEROSET                  13      /* control type: textButton, callback function: Cb_Bt_Zeroset */
#define  MAIN_BT_MANUAL                   14      /* control type: textButton, callback function: Cb_Bt_Manual */
#define  MAIN_BT_AUTO                     15      /* control type: textButton, callback function: Cb_Bt_Auto */
#define  MAIN_BT_TABLE                    16      /* control type: textButton, callback function: Cb_Bt_Table */
#define  MAIN_BT_GRAPH                    17      /* control type: textButton, callback function: Cb_Bt_Graph */
#define  MAIN_BT_HISTORY                  18      /* control type: textButton, callback function: Cb_Bt_History */
#define  MAIN_BT_IO                       19      /* control type: textButton, callback function: Cb_Bt_Io */
#define  MAIN_POP_MODEL                   20      /* control type: pictButton, callback function: Cb_Pop_Model */
#define  MAIN_POP_RESULT                  21      /* control type: pictButton, callback function: Cb_Pop_Result */
#define  MAIN_DECORATION_3                22      /* control type: deco, callback function: (none) */
#define  MAIN_POP_SETUP                   23      /* control type: pictButton, callback function: Cb_Pop_Setup */
#define  MAIN_CLOSE                       24      /* control type: pictButton, callback function: Close_MainPanel */
#define  MAIN_TAB                         25      /* control type: tab, callback function: (none) */
#define  MAIN_AMP_TIMER                   26      /* control type: timer, callback function: Cb_Timer_Amp */
#define  MAIN_PLC_TIMER                   27      /* control type: timer, callback function: Cb_Timer_Plc */
#define  MAIN_TIMER_TIME                  28      /* control type: timer, callback function: Cb_Timer_Time */
#define  MAIN_LED_MEAS                    29      /* control type: LED, callback function: (none) */
#define  MAIN_LED_MARK                    30      /* control type: LED, callback function: (none) */
#define  MAIN_LED_AMP                     31      /* control type: LED, callback function: (none) */
#define  MAIN_LED_PLC                     32      /* control type: LED, callback function: (none) */
#define  MAIN_TITLE_1                     33      /* control type: textMsg, callback function: (none) */
#define  MAIN_TEXTMSG_29                  34      /* control type: textMsg, callback function: (none) */
#define  MAIN_HDDTITLE_2                  35      /* control type: textMsg, callback function: (none) */
#define  MAIN_HDDTITLE_1                  36      /* control type: textMsg, callback function: (none) */
#define  MAIN_MAMORYBAR                   37      /* control type: scale, callback function: (none) */
#define  MAIN_PROGRESSBAR1                38      /* control type: scale, callback function: (none) */
#define  MAIN_PROGRESSBAR2                39      /* control type: scale, callback function: (none) */
#define  MAIN_TABLE_SIG                   40      /* control type: table, callback function: (none) */
#define  MAIN_MODEL_NAME                  41      /* control type: ring, callback function: Cb_Main_Model */
#define  MAIN_SPLITTER                    42      /* control type: splitter, callback function: (none) */
#define  MAIN_TEXTMSG                     43      /* control type: textMsg, callback function: (none) */
#define  MAIN_TESTNO                      44      /* control type: table, callback function: Cb_TestNo */
#define  MAIN_TIMER_ALARM                 45      /* control type: timer, callback function: Cb_Timer_Alarm */
#define  MAIN_DEC_6                       46      /* control type: deco, callback function: (none) */
#define  MAIN_DEC_5                       47      /* control type: deco, callback function: (none) */
#define  MAIN_DEC_4                       48      /* control type: deco, callback function: (none) */
#define  MAIN_DEC_3                       49      /* control type: deco, callback function: (none) */
#define  MAIN_DEC_2                       50      /* control type: deco, callback function: (none) */
#define  MAIN_DEC_1                       51      /* control type: deco, callback function: (none) */
#define  MAIN_ALARM                       52      /* control type: deco, callback function: (none) */

     /* tab page panel controls */
#define  TAB_AUTO_MEAS_1                  2       /* control type: command, callback function: Cb_Meas_1 */
#define  TAB_AUTO_MEAS_2                  3       /* control type: command, callback function: Cb_Meas_2 */
#define  TAB_AUTO_MEAS_3                  4       /* control type: command, callback function: Cb_Meas_3 */
#define  TAB_AUTO_MEAS_4                  5       /* control type: command, callback function: Cb_Meas_4 */
#define  TAB_AUTO_POINT_1                 6       /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_2                 7       /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_IMG                     8       /* control type: picture, callback function: (none) */
#define  TAB_AUTO_POINT_4                 9       /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_5                 10      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_6                 11      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_7                 12      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_8                 13      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_9                 14      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_10                15      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_11                16      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_12                17      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_13                18      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_14                19      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_15                20      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_32                21      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_31                22      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_30                23      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_29                24      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_28                25      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_27                26      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_26                27      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_25                28      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_24                29      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_23                30      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_22                31      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_21                32      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_20                33      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_19                34      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_18                35      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_17                36      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_POINT_16                37      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_TABLE_SPC               38      /* control type: table, callback function: (none) */
#define  TAB_AUTO_A_TABLE                 39      /* control type: table, callback function: (none) */
#define  TAB_AUTO_GRAPH_2                 40      /* control type: graph, callback function: (none) */
#define  TAB_AUTO_GRAPH_1                 41      /* control type: graph, callback function: (none) */
#define  TAB_AUTO_GRAPH                   42      /* control type: graph, callback function: (none) */
#define  TAB_AUTO_MARK_DATA_1             43      /* control type: string, callback function: (none) */
#define  TAB_AUTO_RING_MEASPOINT          44      /* control type: ring, callback function: Cb_Ring_MeasPoint */
#define  TAB_AUTO_MEAS_TIMER_4            45      /* control type: timer, callback function: Cb_Timer_Meas_4 */
#define  TAB_AUTO_MEAS_TIMER_3            46      /* control type: timer, callback function: Cb_Timer_Meas_3 */
#define  TAB_AUTO_MEAS_TIMER_2            47      /* control type: timer, callback function: Cb_Timer_Meas_2 */
#define  TAB_AUTO_MEAS_TIMER_1            48      /* control type: timer, callback function: Cb_Timer_Meas_1 */
#define  TAB_AUTO_POINT_3                 49      /* control type: string, callback function: Cb_Point */
#define  TAB_AUTO_CONTINUOUS_TXT          50      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_GNG                     51      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_LED_MC_6                52      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_MC_5                53      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_MC_4                54      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_MC_3                55      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_MC_2                56      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_MC_1                57      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_IF_TXT_8                58      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_IF_TXT_7                59      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_IF_TXT_6                60      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_IF_TXT_5                61      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_LED_IF_8_M              62      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_7_M              63      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_8_P              64      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_7_P              65      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_IF_TXT_4                66      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_LED_IF_6_M              67      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_6_P              68      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_5_M              69      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_5_P              70      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_IF_TXT_3                71      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_LED_IF_4_M              72      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_4_P              73      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_IF_TXT_2                74      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_LED_IF_3_M              75      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_3_P              76      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_IF_TXT_1                77      /* control type: textMsg, callback function: (none) */
#define  TAB_AUTO_LED_IF_2_M              78      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_2_P              79      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_1_M              80      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_LED_IF_1_P              81      /* control type: LED, callback function: (none) */
#define  TAB_AUTO_SPLITTER_6              82      /* control type: splitter, callback function: (none) */
#define  TAB_AUTO_SPLITTER_8              83      /* control type: splitter, callback function: (none) */
#define  TAB_AUTO_SPLITTER_7              84      /* control type: splitter, callback function: (none) */
#define  TAB_AUTO_SPLITTER_5              85      /* control type: splitter, callback function: (none) */
#define  TAB_AUTO_SPLITTER_4              86      /* control type: splitter, callback function: (none) */
#define  TAB_AUTO_SPLITTER_3              87      /* control type: splitter, callback function: (none) */
#define  TAB_AUTO_SPLITTER_2              88      /* control type: splitter, callback function: (none) */
#define  TAB_AUTO_SPLITTER                89      /* control type: splitter, callback function: (none) */
#define  TAB_AUTO_DECORATION              90      /* control type: deco, callback function: (none) */

     /* tab page panel controls */
#define  TAB_GRAPH_CH_1                   2       /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_2                   3       /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_3                   4       /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_4                   5       /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_5                   6       /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_6                   7       /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_7                   8       /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_8                   9       /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_9                   10      /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_10                  11      /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_11                  12      /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_12                  13      /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_13                  14      /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_14                  15      /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_15                  16      /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_CH_16                  17      /* control type: pictRing, callback function: Cb_GraphChButton */
#define  TAB_GRAPH_GRAPH                  18      /* control type: graph, callback function: (none) */
#define  TAB_GRAPH_RING_MEASPOINT         19      /* control type: ring, callback function: Cb_Graph_Ring_MeasPoint */
#define  TAB_GRAPH_DECORATION_4           20      /* control type: deco, callback function: (none) */
#define  TAB_GRAPH_REFRESH                21      /* control type: command, callback function: Cb_Refresh */

     /* tab page panel controls */
#define  TAB_HIS_LISTBOX                  2       /* control type: listBox, callback function: (none) */
#define  TAB_HIS_HISTORY_CLEAR            3       /* control type: command, callback function: Cb_History_Clear */

     /* tab page panel controls */
#define  TAB_IO_TABLE_OUTPUT              2       /* control type: table, callback function: (none) */
#define  TAB_IO_TABLE_INPUT               3       /* control type: table, callback function: (none) */

     /* tab page panel controls */
#define  TAB_MANU_SOL_1                   2       /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_2                   3       /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_3                   4       /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_4                   5       /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_5                   6       /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_6                   7       /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_7                   8       /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_8                   9       /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_9                   10      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_10                  11      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_11                  12      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_12                  13      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_13                  14      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_14                  15      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_15                  16      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_16                  17      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_17                  18      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_18                  19      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_19                  20      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_SOL_20                  21      /* control type: toggle, callback function: Cb_Sol */
#define  TAB_MANU_MANUAL_1                22      /* control type: command, callback function: Cb_Manual_1 */
#define  TAB_MANU_MANUAL_2                23      /* control type: command, callback function: Cb_Manual_2 */
#define  TAB_MANU_TXT_3                   24      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_TXT_4                   25      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_TXT_5                   26      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_TXT_2                   27      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_TXT_1                   28      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_DECORATION_4            29      /* control type: deco, callback function: (none) */
#define  TAB_MANU_MANUAL_3                30      /* control type: command, callback function: Cb_Manual_3 */
#define  TAB_MANU_TEXTMSG                 31      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_MANUAL_4                32      /* control type: command, callback function: Cb_Manual_4 */
#define  TAB_MANU_DECORATION_1            33      /* control type: deco, callback function: (none) */
#define  TAB_MANU_LED_MANU_4              34      /* control type: LED, callback function: (none) */
#define  TAB_MANU_TEXTMSG_2               35      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_LED_MANU_3              36      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_MANU_2              37      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_MANU_1              38      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_20                39      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_20                40      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_19                41      /* control type: LED, callback function: (none) */
#define  TAB_MANU_REPEAT                  42      /* control type: pictRing, callback function: Cb_Img_Button */
#define  TAB_MANU_DEC_6                   43      /* control type: deco, callback function: (none) */
#define  TAB_MANU_DEC_5                   44      /* control type: deco, callback function: (none) */
#define  TAB_MANU_DEC_4                   45      /* control type: deco, callback function: (none) */
#define  TAB_MANU_LED_A_19                46      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_18                47      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_18                48      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_17                49      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_17                50      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_16                51      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_16                52      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_15                53      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_SENSOR_3            54      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_SENSOR_2            55      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_SENSOR_1            56      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_15                57      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_14                58      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_14                59      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_13                60      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_13                61      /* control type: LED, callback function: (none) */
#define  TAB_MANU_A_TABLE                 62      /* control type: table, callback function: Cb_Manu_Table */
#define  TAB_MANU_LED_H_12                63      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_12                64      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_11                65      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_11                66      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_10                67      /* control type: LED, callback function: (none) */
#define  TAB_MANU_IF_TXT_5                68      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_IF_TXT_4                69      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_IF_TXT_3                70      /* control type: textMsg, callback function: (none) */
#define  TAB_MANU_LED_A_10                71      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_9                 72      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_9                 73      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_8                 74      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_8                 75      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_7                 76      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_7                 77      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_6                 78      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_6                 79      /* control type: LED, callback function: (none) */
#define  TAB_MANU_TABLE_CH_2              80      /* control type: table, callback function: (none) */
#define  TAB_MANU_TABLE_CH_1              81      /* control type: table, callback function: (none) */
#define  TAB_MANU_LED_H_5                 82      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_5                 83      /* control type: LED, callback function: (none) */
#define  TAB_MANU_MANU_TIMER_4            84      /* control type: timer, callback function: Cb_Timer_Manu_4 */
#define  TAB_MANU_MANU_TIMER_3            85      /* control type: timer, callback function: Cb_Timer_Manu_3 */
#define  TAB_MANU_MANU_TIMER_2            86      /* control type: timer, callback function: Cb_Timer_Manu_2 */
#define  TAB_MANU_MANU_TIMER_1            87      /* control type: timer, callback function: Cb_Timer_Manu_1 */
#define  TAB_MANU_LED_H_4                 88      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_4                 89      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_3                 90      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_3                 91      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_2                 92      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_2                 93      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_H_1                 94      /* control type: LED, callback function: (none) */
#define  TAB_MANU_LED_A_1                 95      /* control type: LED, callback function: (none) */
#define  TAB_MANU_ITEM                    96      /* control type: string, callback function: (none) */
#define  TAB_MANU_ITEM_VALUE              97      /* control type: listBox, callback function: (none) */
#define  TAB_MANU_DELETE                  98      /* control type: command, callback function: Cb_ManualDelete */
#define  TAB_MANU_SAVE                    99      /* control type: command, callback function: Cb_ManualSave */
#define  TAB_MANU_TESTNO                  100     /* control type: numeric, callback function: (none) */
#define  TAB_MANU_REPEATNO                101     /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TAB_MANU_REPEATNO_2              102     /* control type: numeric, callback function: Cb_KeypadCtrl */
#define  TAB_MANU_LED_40                  103     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_39                  104     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_38                  105     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_37                  106     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_36                  107     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_35                  108     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_32                  109     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_31                  110     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_30                  111     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_29                  112     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_28                  113     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_27                  114     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_26                  115     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_25                  116     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_34                  117     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_33                  118     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_24                  119     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_23                  120     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_22                  121     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_21                  122     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_20                  123     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_19                  124     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_18                  125     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_17                  126     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_16                  127     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_15                  128     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_14                  129     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_13                  130     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_12                  131     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_11                  132     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_10                  133     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_9                   134     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_8                   135     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_7                   136     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_6                   137     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_5                   138     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_4                   139     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_3                   140     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_2                   141     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_LED_1                   142     /* control type: LED, callback function: Cb_Sol_Led */
#define  TAB_MANU_PC_MEAS_CYCLE_2         143     /* control type: command, callback function: Cb_Pc_Meas_Cycle_2 */
#define  TAB_MANU_PC_MEAS_CYCLE           144     /* control type: command, callback function: Cb_Pc_Meas_Cycle */
#define  TAB_MANU_PC_MEAS_TIMER           145     /* control type: timer, callback function: Cb_Pc_Meas_Timer */

     /* tab page panel controls */
#define  TAB_TABLE_TABLE                  2       /* control type: table, callback function: (none) */

     /* tab page panel controls */
#define  TAB_ZERO_TABLE                   2       /* control type: table, callback function: Cb_Zero_Table */
#define  TAB_ZERO_CAL                     3       /* control type: command, callback function: Cb_Pop_Cali */
#define  TAB_ZERO_SAVE                    4       /* control type: command, callback function: Cb_Zero_Save */
#define  TAB_ZERO_ZERO_4                  5       /* control type: command, callback function: Cb_Zero_4 */
#define  TAB_ZERO_ZERO_3                  6       /* control type: command, callback function: Cb_Zero_3 */
#define  TAB_ZERO_ZERO_2                  7       /* control type: command, callback function: Cb_Zero_2 */
#define  TAB_ZERO_ZERO_1                  8       /* control type: command, callback function: Cb_Zero_1 */
#define  TAB_ZERO_LED_ZERO_4              9       /* control type: LED, callback function: (none) */
#define  TAB_ZERO_LED_ZERO_3              10      /* control type: LED, callback function: (none) */
#define  TAB_ZERO_LED_ZERO_2              11      /* control type: LED, callback function: (none) */
#define  TAB_ZERO_LED_ZERO_1              12      /* control type: LED, callback function: (none) */
#define  TAB_ZERO_ZERO_TIMER_4            13      /* control type: timer, callback function: Cb_Timer_Zero_4 */
#define  TAB_ZERO_ZERO_TIMER_3            14      /* control type: timer, callback function: Cb_Timer_Zero_3 */
#define  TAB_ZERO_ZERO_TIMER_2            15      /* control type: timer, callback function: Cb_Timer_Zero_2 */
#define  TAB_ZERO_ZERO_TIMER_1            16      /* control type: timer, callback function: Cb_Timer_Zero_1 */
#define  TAB_ZERO_DEC_6                   17      /* control type: deco, callback function: (none) */
#define  TAB_ZERO_PC_MEAS_CYCLE_2         18      /* control type: command, callback function: Cb_Pc_Meas_Cycle_3 */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Cb_Bt_Auto(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Bt_Graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Bt_History(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Bt_Io(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Bt_Manual(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Bt_Table(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Bt_Zeroset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Graph_Ring_MeasPoint(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_GraphChButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_History_Clear(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Img_Button(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_KeypadCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Logo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Main(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Main_Model(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Manu_Table(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Manual_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Manual_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Manual_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Manual_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_ManualDelete(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_ManualSave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Meas_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Meas_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Meas_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Meas_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Pc_Meas_Cycle(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Pc_Meas_Cycle_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Pc_Meas_Cycle_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Pc_Meas_Timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Point(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Pop_Cali(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Pop_Model(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Pop_Result(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Pop_Setup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Refresh(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Ring_MeasPoint(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Sol(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Sol_Led(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_St_Auto(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_St_Buzzer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_St_Emergency(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_St_Light(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_St_Manual(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_St_Origin(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_St_Reset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_St_Workout(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_TestNo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Alarm(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Amp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Manu_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Manu_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Manu_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Manu_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Meas_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Meas_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Meas_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Meas_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Plc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Zero_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Zero_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Zero_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Timer_Zero_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Zero_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Zero_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Zero_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Zero_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Zero_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Zero_Table(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close_MainPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif