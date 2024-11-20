#include <userint.h>
#include "3_Setup.h"
#include "A_Global.h"

void 	LoadComport(void)
{
	char 	Path[1024] = {0,};
	char	temp1[1024] = {0,};
	int		handle;
	
	sprintf(Path, "%s\\Setup_Comm.ini", Path_Setup);
	handle = OpenFile(Path, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	
	if(handle < 0)
		MessagePopup("NO FILE FOR COMPORT", "CHECK PROGRAM SETUP - COMPORT");
	else
	{
	
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		Scan(temp1, "%s>%i%i%i%i%i%i", &Plc.maker, &Plc.portNumber, &Plc.baudRate, &Plc.parity, &Plc.dataBits, &Plc.stopBits);
		ReadLine(handle, temp1, -1);
		Scan(temp1, "%s>%s%i", Plc_TcpIp, &Plc_TcpPort);

		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		Scan(temp1, "%s>%i%i%i%i%i", &Amp.portNumber, &Amp.baudRate, &Amp.parity, &Amp.dataBits, &Amp.stopBits);
		
		ReadLine(handle, temp1, -1);
		ReadLine(handle, temp1, -1);
		Scan(temp1, "%s>%i%i%i%i%i", &Mark.portNumber, &Mark.baudRate, &Mark.parity, &Mark.dataBits, &Mark.stopBits);
			
		CloseFile(handle);
	}
	
		
	//PLC
	SetCtrlVal(portpanel, PORTPANEL_PLC_MAKER, Plc.maker);					//Maker
	SetCtrlVal(portpanel, PORTPANEL_PLC_PORT, Plc.portNumber);				//PortNumber
	SetCtrlIndex(portpanel, PORTPANEL_PLC_PORT, Plc.portNumber);
	GetLabelFromIndex(portpanel, PORTPANEL_PLC_PORT, Plc.portNumber, Plc.deviceName);	//DeviceName
	SetCtrlVal(portpanel, PORTPANEL_PLC_BR, Plc.baudRate);					//BaudRate
	SetCtrlVal(portpanel, PORTPANEL_PLC_PR, Plc.parity);					//Parity
	SetCtrlVal(portpanel, PORTPANEL_PLC_DB, Plc.dataBits);					//DataBits
	SetCtrlVal(portpanel, PORTPANEL_PLC_SB, Plc.stopBits);					//StopBits
	
	Plc.inputQueueSize = 1024;
	Plc.outputQueueSize = 1024;
	
	SetCtrlVal(portpanel, PORTPANEL_PLC_TCP_IP, Plc_TcpIp);
	SetCtrlVal(portpanel, PORTPANEL_PLC_TCP_PORT, Plc_TcpPort);
	
	//AMP
	SetCtrlVal(portpanel, PORTPANEL_AMP_PORT, Amp.portNumber);				//PortNumber
	SetCtrlIndex(portpanel, PORTPANEL_AMP_PORT, Amp.portNumber);
	GetLabelFromIndex(portpanel, PORTPANEL_AMP_PORT, Amp.portNumber, Amp.deviceName);	//DeviceName
	SetCtrlVal(portpanel, PORTPANEL_AMP_BR, Amp.baudRate);					//BaudRate
	SetCtrlVal(portpanel, PORTPANEL_AMP_PR, Amp.parity);					//Parity
	SetCtrlVal(portpanel, PORTPANEL_AMP_DB, Amp.dataBits);					//DataBits
	SetCtrlVal(portpanel, PORTPANEL_AMP_SB, Amp.stopBits);					//StopBits
	
	Amp.inputQueueSize = 1024;
	Amp.outputQueueSize = 1024;
	
	//MARKING
	SetCtrlVal(portpanel, PORTPANEL_MARK_PORT, Mark.portNumber);				//PortNumber
	SetCtrlIndex(portpanel, PORTPANEL_MARK_PORT, Mark.portNumber);
	GetLabelFromIndex(portpanel, PORTPANEL_MARK_PORT, Mark.portNumber, Mark.deviceName);		//DeviceName
	SetCtrlVal(portpanel, PORTPANEL_MARK_BR, Mark.baudRate);					//BaudRate
	SetCtrlVal(portpanel, PORTPANEL_MARK_PR, Mark.parity);						//Parity
	SetCtrlVal(portpanel, PORTPANEL_MARK_DB, Mark.dataBits);					//DataBits
	SetCtrlVal(portpanel, PORTPANEL_MARK_SB, Mark.stopBits);					//StopBits

	Mark.inputQueueSize = 1024;
	Mark.outputQueueSize = 1024;
	
	
	
	LogUpdate("Comport Setup Load");	
}

void 	SaveComport(void)
{
	char 	Path[1024] = {0,};
	char	temp1[1024] = {0,};
	int		handle, i;
	
	//PLC
	GetCtrlVal(portpanel, PORTPANEL_PLC_MAKER, &Plc.maker);					//maker
	GetCtrlVal(portpanel, PORTPANEL_PLC_PORT, &Plc.portNumber);				//PortNumber
	GetCtrlIndex(portpanel, PORTPANEL_PLC_PORT, &i);
	GetLabelFromIndex(portpanel, PORTPANEL_PLC_PORT, i, Plc.deviceName);	//DeviceName
	GetCtrlVal(portpanel, PORTPANEL_PLC_BR, &Plc.baudRate);					//BaudRate
	GetCtrlVal(portpanel, PORTPANEL_PLC_PR, &Plc.parity);					//Parity
	GetCtrlVal(portpanel, PORTPANEL_PLC_DB, &Plc.dataBits);					//DataBits
	GetCtrlVal(portpanel, PORTPANEL_PLC_SB, &Plc.stopBits);					//StopBits
	
	Plc.inputQueueSize = 1024;
	Plc.outputQueueSize = 1024;
	
	GetCtrlVal(portpanel, PORTPANEL_PLC_TCP_IP, Plc_TcpIp);
	GetCtrlVal(portpanel, PORTPANEL_PLC_TCP_PORT, &Plc_TcpPort);
	
	//AMP
	GetCtrlVal(portpanel, PORTPANEL_AMP_PORT, &Amp.portNumber);				//PortNumber
	GetCtrlIndex(portpanel, PORTPANEL_AMP_PORT, &i);
	GetLabelFromIndex(portpanel, PORTPANEL_AMP_PORT, i, Amp.deviceName);	//DeviceName
	GetCtrlVal(portpanel, PORTPANEL_AMP_BR, &Amp.baudRate);					//BaudRate
	GetCtrlVal(portpanel, PORTPANEL_AMP_PR, &Amp.parity);					//Parity
	GetCtrlVal(portpanel, PORTPANEL_AMP_DB, &Amp.dataBits);					//DataBits
	GetCtrlVal(portpanel, PORTPANEL_AMP_SB, &Amp.stopBits);					//StopBits
	
	Amp.inputQueueSize = 1024;
	Amp.outputQueueSize = 1024;
	
	//MARKING
	GetCtrlVal(portpanel, PORTPANEL_MARK_PORT, &Mark.portNumber);				//PortNumber
	GetCtrlIndex(portpanel, PORTPANEL_MARK_PORT, &i);
	GetLabelFromIndex(portpanel, PORTPANEL_MARK_PORT, i, Mark.deviceName);		//DeviceName
	GetCtrlVal(portpanel, PORTPANEL_MARK_BR, &Mark.baudRate);					//BaudRate
	GetCtrlVal(portpanel, PORTPANEL_MARK_PR, &Mark.parity);						//Parity
	GetCtrlVal(portpanel, PORTPANEL_MARK_DB, &Mark.dataBits);					//DataBits
	GetCtrlVal(portpanel, PORTPANEL_MARK_SB, &Mark.stopBits);					//StopBits
	
	Mark.inputQueueSize = 1024;
	Mark.outputQueueSize = 1024;			
	
	
	sprintf(Path, "%s\\Setup_Comm.ini", Path_Setup);
	handle = OpenFile(Path, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	
	if(handle < 0)
		MessagePopup("NO DIRECTORY FOR COMPORT", "CHECK PROGRAM SETUP - COMPORT");
	else
	{
		WriteLine(handle, "COMPORT:PLC", -1);
		sprintf(temp1, "%d\t%d\t%d\t%d\t%d\t%d", Plc.maker, Plc.portNumber, Plc.baudRate, Plc.parity, Plc.dataBits, Plc.stopBits);
		WriteLine(handle, temp1, -1);
		sprintf(temp1, "%s\t%d", Plc_TcpIp, Plc_TcpPort);
		WriteLine(handle, temp1, -1);
		
		WriteLine(handle, "COMPORT:AMP", -1);
		sprintf(temp1, "%d\t%d\t%d\t%d\t%d", Amp.portNumber, Amp.baudRate, Amp.parity, Amp.dataBits, Amp.stopBits);
		WriteLine(handle, temp1, -1);
		
		WriteLine(handle, "COMPORT:MARKING", -1);
		sprintf(temp1, "%d\t%d\t%d\t%d\t%d", Mark.portNumber, Mark.baudRate, Mark.parity, Mark.dataBits, Mark.stopBits);
		WriteLine(handle, temp1, -1);
		
		CloseFile(handle);
	}
	
	LogUpdate("Comport Setup Save");
}

int CVICALLBACK Cb_ComportPanel (int panel, int control, int event,
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

int CVICALLBACK Cb_Comport_Rollback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			LoadComport();

			break;
	}
	return 0;
}

int CVICALLBACK Cb_Comport_Save (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(ConfirmPopup("SAVE", "SAVE?"))
			{
				int a, b, c;
				
				GetCtrlVal(panel, PORTPANEL_PLC_PORT, &a);
				GetCtrlVal(panel, PORTPANEL_AMP_PORT, &b);
				GetCtrlVal(panel, PORTPANEL_MARK_PORT, &c);
				
				if(a != 0 && (a == b || a == c))
				{
					MessagePopup("Port No Error", "Duplicate Port No Selected");
					return 0;
				}
			
				if(b != 0 && b == c)
				{
					MessagePopup("Port No Error", "Duplicate Port No Selected");
					return 0;
				}
				SaveComport();
			}
			break;
	}
	return 0;
}

int CVICALLBACK Cb_Comport (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DisplayPanel(portpanel);
			InstallPopup(portpanel);
			break;
	}
	return 0;
}
