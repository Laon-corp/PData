#include "toolbox.h"
#include <cvirte.h>		
#include <userint.h>
#include "0_Main.h"
#include "1_Model.h"
#include "2_Result.h"
#include "3_Setup.h"
#include "4_Calibration.h"
#include "5_Keypad.h"
#include "6_Password.h"
#include <time.h>
#include <utility.h>
#include <stdlib.h>
#include <ansi_c.h>
#include <formatio.h>
#include <tcpsupp.h>

// LAON.LLP SETTING PART
int USE_HDD_CHECK;
int USE_DAY_CHECK;
int	MAX_USED_DAYS;
#define MAX_PW_CHARS	10
#define	MASTER_PW		"LAON.LLP"
#define INIT_ROOT		"LAON"

#define	MEAS_TIME 		1
#define LAST_SIG		0

#define	MAX_SOL			40
#define SOL_START_NO	64

// Amp
#define MAX_AMP			2
#define MAX_CH_PER_AMP	8
#define	MAX_CH 			(MAX_AMP*MAX_CH_PER_AMP)

#define MAX_MODEL_NO	128
#define MAX_MEAS_POINTS	32
#define MAX_MEAS_CYCLE	6000
#define	MAX_MODE		2		// AUTO : 0 , MANUAL : 1
#define MAX_MACHINE		5

#define AmpParOrder		0xA8  
#define	OneOrd			0xA5			// 1개 Amp, 또는 다수 앰프 래치없이 사용시 명령어
#define	AllOrd			0xA7			// 2개 이상 AMP 사용 명령어 
#define	LatOrd			0xA6			// Latch 명령어 
#define	EndAmpOrder		0x0d			//CR
#define	BytePerPar		59				// 1개 Amp당 파라메타 응답 바이트 수 
#define	bytePerAmp		16				// 1개 AMP당 측정 응답 바이트 수( AmpPro수 * 2바이트) 
#define	OneChar  		'1'
#define N_AmpParOrder	0xA5   			// The S 
#define	N_BytePerPar	16				// The S amp parameter bype no

#define	bytePerEnc		20				// 1개 Enc bd당 측정 응답 바이트 수
#define MAXLOOP  		10

#define	MAX_MEAS_SIG	4
#define	MAX_CH_CYCLE 	5000

// PLC
// MELSEC Q
// DATA CODE - ASCII
// ENABLE ONLINE CHANGE
// TCP, MC PROTOCOL, PORT NO 4000
#define	StationNo				"00"		// (2)국 번호
#define	PlcNo					"FF"		// (2)PLC 번호
#define	FrameIdentifier			"F9"		// (2)프레임 선언
#define	NetworkNo				"00"		// (2)네트워크 번호
#define	SelfStation				"00"		// (2)자국 번호
#define	ReadCommand				"0401"		// (4)읽기 워드 일괄
#define	ReadSubCommand			"0000"		// (4)읽기 Sub Command(4)
#define	ReadDeviceName			"M*"		// (2)디바이스 이름
#define	WriteCommand			"1401"		// (4)쓰기 워드 일괄
#define	WriteSubCommand			"0000"		// (4)쓰기 Sub Command(4)
#define	WriteDeviceName			"M*"		// (2)사용 디바이스명

#define	SubHeader				"5000"		// (4)서브 헤더
#define	ModuleNo				"03FF"		// (4)모듈 번호
#define	CpuTimer				0x02		// (4)CPU 감시 타이머 (*250ms = 0.4s)

//MELSEC
#define	PlcAddressRead			"000000"    	// 16 배수 사용
#define	PlcAddressWrite			"000320"    
//LS
#define	LsPlcAddressRead			"%MW000"    	// 16 배수 사용
#define	LsPlcAddressWrite			"%MW020"    

#define	PlcReadWordNo			40 		   								
#define	PlcWriteWordStNo		20									   	
#define	PlcWriteWordNo			(PlcReadWordNo - PlcWriteWordStNo)  	
#define	PlcInOutByteMax			(PlcReadWordNo * 16)				

#define	PlcDataInNo				(PlcReadWordNo * 16)
#define	PlcDataOutNo			(PlcWriteWordNo * 16)

#define	PlcHeaderLength			18						// 종료코드를 제외한 헤더 길이
#define	PlcEndCodeLength		4						// 종료코드 길이
#define	PlcReadDataLength		PlcReadWordNo * 4		// 읽기시 실제 데이터 길이

#define MAX_PLC_ERR			80
#define	MAX_PLOT_NO			51
#define	MAX_KEYPAD_CHARS	20

//main
int mainpanel;
int modelpanel;
int resultpanel;
int setuppanel;
int portpanel;
int calpanel;
int keypad;
int pw;

int tab_auto,
	tab_manual,
 	tab_zeroset,
 	tab_table,
 	tab_graph,
 	tab_history,
 	tab_io;

char 	CurrDate[12];
char 	CurrTime[10];

int 	CurrShift, OldShift;
void	GetCurrShift(void);

int 	ActivePanel;
int 	TabPage;
void	MainButton(int);
int		BtCtrl[7];
int 	PointCtrl[MAX_MEAS_POINTS];
void 	LoadModel_BoxPos(void);
void 	SaveModel_BoxPos(void);
void	SetModel_BoxPos(void);
void 	LoadModel_Img(void);
int 	BeforePointCtrl;
int 	PointCtrlMove;

//DB
int		DBhandle, DBret, DBStmt;
void	FuncDBConnect(void);
void 	FuncDBDisconnect(void);

//windows
void 	GetDateTime(void);
void 	CheckHdd(void);

//main_Cb_Zeroset
void	SaveZeroTableData(void);
void	LoadZeroTableData(void);
double 	ZeroValueBef[MAX_CH];
double 	ZeroValueNow[MAX_CH];
double 	ZeroValueDev[MAX_CH];
double 	ZeroValueAlN[MAX_CH];
double 	ZeroValueAlP[MAX_CH];

//model
int	 	model_tab_Meas,
		model_tab_Calc,
 		model_tab_Mark;

void	LoadModel(void);
void 	SaveModel(void);
void 	DeleteSaveModel(void);
void 	LoadModelData(void);
void 	SaveModelData(void);
void 	FileRename(char *, char *);
void 	FileAdd(char *, char *);
void 	FileDelete(char *);
int 	ModelNo, ModelCount;
int 	MeasPoints;
void 	LoadModel_MeasPoints(void);
void	LoadModel_Calculation(void);
void 	LoadModel_Mark(void);

//Measure
int 	AutoMode;
int 	LastSig;
int		TotalGFlag;
int 	GFlag[MAX_MEAS_POINTS];
int 	McID, ModeID;
int 	McNo1, McNo2;
char 	MeasTime[10], MeasDate[12];
int		TotalNo, OkNo, NgNo;

struct	Result
{
	double	ResultValue[MAX_MEAS_POINTS][MAX_MEAS_CYCLE];
	int CycleIndex,
		StartDataNo,
		EndDataNo;
};

struct	Mode
{
	struct	Result	Mode[MAX_MODE];
};
struct	Mode	Mc[MAX_MACHINE];

struct	Spc
{
	double	Cp,		//공정능력
			Cpk,	//공정능력 지수 
			Avg,	//평균 Average
			Dev,	//편차 Max - Min
			Sdev,	//표준편차	sigma
			V,		//분산
			Min,
			Max;
};
struct Points
{
	struct 	Spc	Points[MAX_MEAS_POINTS];	
	int 	G;
	int 	NG;
};
struct	Points 	McSpc[MAX_MACHINE];

struct	GRAPHDATA
{
	int	DataNum,
		HandleData,
		HandleLCL,
		HandleLWL,
		HandleUWL,
		HandleUCL;
	double 	Data[MAX_MEAS_POINTS][MAX_PLOT_NO],
			LCL[MAX_PLOT_NO],
			LWL[MAX_PLOT_NO],
			UWL[MAX_PLOT_NO],
			UCL[MAX_PLOT_NO];	
};
struct	GRAPHDATA	GraphData, GraphData1, GraphData2;

char 	ModelName[MAX_MODEL_NO][64];

struct	MODELSET
{
	char Name[64];
	double Master,
			Comp,
			Fact,
			LCL,
			LWL,
			UWL,
			UCL;
	
	int P1,
		P2,
		P3,
		P4;
	
	int Use,
		Cal,
		Unit,
		Sig,
		Offset;
	
	int sign1,
		sign2,
		sign3,
		sign4;
};
struct	MODELSET Model[MAX_MEAS_POINTS];

struct	BOXPOS
{
	int	LabX,
		LabY,
		BoxX,
		BoxY,
		BoxWidth;
};
struct	BOXPOS BoxPos[MAX_MEAS_POINTS];

struct 	COUTH
{
	double	CharHeight,	//PARA 1
		 	CharWidth,	//PARA 2
		 	Spacing,	//PARA 4
		 	Density,	//PARA 5
		 	Xcoo,		//PARA 6
		 	Ycoo,		//PARA 7
		 	Zcoo,		//PARA 8
		 	Angle,		//PARA 9
		 	Diameter,	//PARA 10
		 	Speed,		//PARA 14
		 	Force;		//PARA 15
	
	int 	Font,		//PARA 3
			Con,		//PARA 11
			Hmirror,	//PARA 12
			Vmirror;	//PARA 13
};
struct 	COUTH	Couth;

void	SetSpcPrecision(void);
void 	SetSpcData(int);
void 	ResetSpcData(void);

void	InitStData(int);
void	InitAllData(void);

void 	ReadSensorValueFile();

//result.c
void 	SetDateResult(void);
void	SaveDataBase(void);
void	SaveDataFile(void);
void	GetSaveDataNum(void);
void	GetDataFileName(void);
char	DataFileNameAll[1024],
		DataFileNameNg[1024],
		DataFileNameOk[1024];
void 	SetCountDisplay(int, int, int);
void	GetBeforeDate(char *);
void	LoadDataFromFile(int a);
void 	CreateDataFile(void);
//Setup.c
void 	InitSystem(void);
void 	InitLogPath(void);
char	Path_Model[1024],
		Path_Result[1024],
		Path_History[1024],
		Path_History_Reg[1024],
		Path_Setup[1024];
int  	Rule_History,
	 	Rule_Result;
char 	UserPassword[11];

int		GetRegHdd(void);
void 	GetRegPath(void);
void	SetRegPath(void);
int 	GetRegUsedDays(void);
void 	SetRegUsedDays(void);
void 	GetRegUserPw(void);
void 	SetRegUserPw(void);

void	SaveSetup(void);
void	LoadSetup(void);
int 	ByPassFlag[4];

int		ReMeasNo, ReMeasUse, ReMeasCnt;
int 	ContinuousNgAlarmUse,
		ContinuousNgCount,
		ContinuousNgNo;
char 	DayStartTime[6],
		NightStartTime[6];
int 	SeperateDayNight;

unsigned int 	Used_Days;

void 	InitPlcErrStr(void);
void	InitManuSol(void);
void	InitIO(void);

//thread.c
int 	poolHandle,
		ThreadFuncId,
		ThreadLogId,
		ThreadMeasId;
		ThreadAmpId;
int 	WhileLoopFlag;
void 	ThreadInit(void);
int 	CVICALLBACK ThreadFunc(void *Data);
int 	CVICALLBACK ThreadLog(void *Data);
int 	CVICALLBACK ThreadMeas(void *Data);
void 	SleepFunc(int);

//keypad.c
unsigned int	locate;
char			InputString[MAX_KEYPAD_CHARS+1];
int				PadPanel, PadControl, PadAtr;
Point			PadCell;
void 			CallKeyPadCell(int, int);



//password.c
int		Password_Control_Handle;
void 	Check_Password(void);
int 	PwMain,
		PwCali,
		PwSetup,
		PwModel;

//Comport
struct	COMPORT
{
	int 	portNumber;
	char 	deviceName[64];
	long	baudRate;
	int		parity;
	int		dataBits;
	int		stopBits;
	int 	inputQueueSize;
	int 	outputQueueSize;
	int 	maker;
};
struct	COMPORT Amp, Plc, Mark;

//Amp
int 	GAUGE[MAX_AMP][MAX_CH_PER_AMP];
double 	CAL_PARA[MAX_AMP][MAX_CH_PER_AMP];
double 	CAL_MASTER1[MAX_AMP][MAX_CH_PER_AMP];
double 	CAL_MASTER2[MAX_AMP][MAX_CH_PER_AMP];
char	AmpTimerRunFlag;
double 	Opset[MAX_AMP][MAX_CH_PER_AMP];

double	ChVal[MAX_CH];

int 	Amp_Value;
			
int 	AmpIndex;
int 	numAmp;			
int		AmpRunFlag;
int 	AmpCommErr;
int		AmpParaReadFlag;
int		AmpCallBackIng;
char	AmpParaReadIng;

double 	CAL_PARA[MAX_AMP][MAX_CH_PER_AMP];
double 	CAL_MASTER1[MAX_AMP][MAX_CH_PER_AMP];
double 	CAL_MASTER2[MAX_AMP][MAX_CH_PER_AMP];
double 	Opset[MAX_AMP][MAX_CH_PER_AMP];
double	ChVal[MAX_CH];

void 	AmpStart(char);
void 	SaveCali(void);
void 	LoadCali(void);
int 	GetAmpParameter(void);
int		AmpPortOpen(void);
int		AmpPortOpenErr;
void 	AmpPortClose(void);
int 	RestAmp(void);

double 	ChData[MAX_CH];
double	ChData_1[MAX_CH_PER_AMP];
double	ChData_2[MAX_CH_PER_AMP];

//commPlc.c
int 	PlcErr[MAX_PLC_ERR];
char 	PlcErrStr[MAX_PLC_ERR][512];

unsigned	int 	hPlcComm;
void	PlcInit(void);
void 	PlcConnect(void);
int		PlcConnectStatus;

char	PlcCmdHeader[64], 
		PlcCmdRead[128], 
		PlcCmdWrite[512],
		PlcCmdReadReq[PlcInOutByteMax],
		PlcCmdWriteReq[PlcInOutByteMax],
   		PlcCmdWriteReqHeader[PlcInOutByteMax];

char	PLCPortInBuff[800], PLCPortOutBuff[800];
int   	PlcReadFlag;
void	PlcOpen(void);
void 	PlcClose(void);
int  	PlcCommErr;
int 	PLCReadCMDReturnDataPosition;


unsigned 	short	PlcWordOut[PlcWriteWordNo], OldPlcWordOut[PlcWriteWordNo];
unsigned	short	PlcWordIn[PlcReadWordNo];

void 	PlcBuff(char *);
void	calc_out_data(int, int);
void 	check_iomon(void);
char	d_in[PlcDataInNo],
		d_out[PlcDataOutNo],
		def_in[PlcDataInNo],
		def_out[PlcDataOutNo];

int		PlcWriteFlag;
int 	PlcData[PlcDataOutNo];
int 	PlcDataT[PlcDataOutNo];

char	Plc_TcpIp[20];
int 	Plc_TcpPort;
void 	SaveComport(void);
void 	LoadComport(void);
void 	SendModelBit();

//Mark
void 	MarkInit(void);
int 	MarkConnectStatus;
char 	MarkStr[48];
void 	MakeMarkData(void);
void 	MakeMarkDataTest(void);
int		SendDataMark(int, char*);
void	MarkClose(void);
int		MarkStartFlag;

//Measure
int		MeasSig[MAX_MEAS_SIG];
int		MeasChIndex[MAX_MEAS_SIG];
double	MeasChValue[MAX_CH_CYCLE][MAX_CH];
double	MeasChTemp[MAX_MEAS_POINTS][MAX_CH_CYCLE];
void 	SaveSensorValue(int);

void	AutoMeasFinish(int);
void	ManuMeasFinish(int);
void	ZeroMeasFinish(int);

int 	AutoMeasFlag,
		ManuMeasFlag,
		ZeroMeasFlag;

void 	CalcSpcData(int);
void	MakeGraphData(void);
void	GraphPlot(void);
void 	SetGraphRange(void);

//main_Cb_Auto
int		SPCDisplayPointNo;
void 	ChangeModel(int);

//main_Cb_History
void 	LogUpdate(char *);
void 	SaveLog(void);

//main_Cb_Manual
int		ManuSwCtrl[MAX_SOL];
char	ManuSwLedCtrl[MAX_SOL][32];
int 	ManuSwLed[MAX_SOL];
int		ManuLedHome[MAX_SOL];
int		ManuLedAct[MAX_SOL];
int 	ManuItemSelected;
int		MeasCycleNo;

int 	Pc_Cycle;
double 	Opt_Time_1;
int 	Safety_Door;