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

#define  KEYPAD                           1
#define  KEYPAD_CLOSE                     2       /* control type: pictButton, callback function: Cb_KeypadPanel */
#define  KEYPAD_STRING                    3       /* control type: string, callback function: (none) */
#define  KEYPAD_DOT                       4       /* control type: command, callback function: Cb_Dot */
#define  KEYPAD_9                         5       /* control type: command, callback function: Cb_9 */
#define  KEYPAD_8                         6       /* control type: command, callback function: Cb_8 */
#define  KEYPAD_7                         7       /* control type: command, callback function: Cb_7 */
#define  KEYPAD_6                         8       /* control type: command, callback function: Cb_6 */
#define  KEYPAD_5                         9       /* control type: command, callback function: Cb_5 */
#define  KEYPAD_4                         10      /* control type: command, callback function: Cb_4 */
#define  KEYPAD_3                         11      /* control type: command, callback function: Cb_3 */
#define  KEYPAD_2                         12      /* control type: command, callback function: Cb_2 */
#define  KEYPAD_1                         13      /* control type: command, callback function: Cb_1 */
#define  KEYPAD_0                         14      /* control type: command, callback function: Cb_0 */
#define  KEYPAD_ENTER                     15      /* control type: command, callback function: Cb_Enter */
#define  KEYPAD_SPACE                     16      /* control type: command, callback function: Cb_Space */
#define  KEYPAD_M                         17      /* control type: command, callback function: Cb_M */
#define  KEYPAD_N                         18      /* control type: command, callback function: Cb_N */
#define  KEYPAD_B                         19      /* control type: command, callback function: Cb_B */
#define  KEYPAD_V                         20      /* control type: command, callback function: Cb_V */
#define  KEYPAD_C                         21      /* control type: command, callback function: Cb_C */
#define  KEYPAD_X                         22      /* control type: command, callback function: Cb_X */
#define  KEYPAD_Z                         23      /* control type: command, callback function: Cb_Z */
#define  KEYPAD_L                         24      /* control type: command, callback function: Cb_L */
#define  KEYPAD_K                         25      /* control type: command, callback function: Cb_K */
#define  KEYPAD_J                         26      /* control type: command, callback function: Cb_J */
#define  KEYPAD_H                         27      /* control type: command, callback function: Cb_H */
#define  KEYPAD_G                         28      /* control type: command, callback function: Cb_G */
#define  KEYPAD_F                         29      /* control type: command, callback function: Cb_F */
#define  KEYPAD_D                         30      /* control type: command, callback function: Cb_D */
#define  KEYPAD_S                         31      /* control type: command, callback function: Cb_S */
#define  KEYPAD_A                         32      /* control type: command, callback function: Cb_A */
#define  KEYPAD_P                         33      /* control type: command, callback function: Cb_P */
#define  KEYPAD_O                         34      /* control type: command, callback function: Cb_O */
#define  KEYPAD_I                         35      /* control type: command, callback function: Cb_I */
#define  KEYPAD_U                         36      /* control type: command, callback function: Cb_U */
#define  KEYPAD_Y                         37      /* control type: command, callback function: Cb_Y */
#define  KEYPAD_T                         38      /* control type: command, callback function: Cb_T */
#define  KEYPAD_R                         39      /* control type: command, callback function: Cb_R */
#define  KEYPAD_E                         40      /* control type: command, callback function: Cb_E */
#define  KEYPAD_W                         41      /* control type: command, callback function: Cb_W */
#define  KEYPAD_Q                         42      /* control type: command, callback function: Cb_Q */
#define  KEYPAD_COLON                     43      /* control type: command, callback function: Cb_Colon */
#define  KEYPAD_MINUS                     44      /* control type: command, callback function: Cb_Minus */
#define  KEYPAD_PLUS                      45      /* control type: command, callback function: Cb_Plus */
#define  KEYPAD_CLEAR                     46      /* control type: command, callback function: Cb_Clear */
#define  KEYPAD_ESC                       47      /* control type: command, callback function: Cb_KeypadPanel */
#define  KEYPAD_BS                        48      /* control type: command, callback function: Cb_Bs */
#define  KEYPAD_DECORATION                49      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Cb_0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_A(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_B(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Bs(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_C(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Clear(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Colon(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_D(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Dot(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_E(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Enter(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_F(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_G(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_H(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_I(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_J(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_K(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_KeypadPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_L(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_M(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Minus(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_N(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_O(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_P(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Plus(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Q(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_R(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_S(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Space(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_T(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_U(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_V(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_W(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_X(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Y(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Cb_Z(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif