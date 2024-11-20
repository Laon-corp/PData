#include <windows.h>
#include "A_Global.h"

int	ProgressGroup[]	= {MAIN_PROGRESSBAR1, MAIN_PROGRESSBAR2};
int	HddTitleName[] = {MAIN_HDDTITLE_1, MAIN_HDDTITLE_2}; 

void 	CheckHdd(void)
{
	long long TD_size ,DF_size,TDF_size;
	double Full, TD_temp, TDF_temp;
	
	int total, i,j=0, k=0, flag=0;
	char label[40]={0,},label2[5]={0,};
	char disk_T[10][10]={0,};
	char Temp[256] = {0,};
	unsigned long per_memory;
	unsigned int M_temp[6]={0};
	double RT_memory, RS_memory;
	
	//���� ����̺� ���� ȹ��
	total = GetLogicalDriveStrings(256, Temp);

	//����̺� Ÿ������ ���� ����̺� ����
	for(i=0; i<total/4; i++)
	{
		sprintf(label2, "%s",Temp+i*4);
		j = GetDriveType(label2);
		if (j==3)
		{
			strcpy(disk_T[k],label2);
			k++;
		}
	}
	
	//���α׷����� ���� ����
	for(i=0; i<2; i++)
	{
		if(disk_T[i]==NULL)
			break;
		GetDiskFreeSpaceEx(disk_T[i], (PULARGE_INTEGER)&DF_size, (PULARGE_INTEGER)&TD_size, (PULARGE_INTEGER)&TDF_size);
		TDF_temp = (double)TDF_size/pow(2,30);
		TD_temp = (double)TD_size/pow(2,30);

		sprintf(label,"HDD �뷮:(%s)",disk_T[i]);
		SetCtrlAttribute(mainpanel, HddTitleName[i], ATTR_CTRL_VAL,label);
		
		Full = TruncateRealNumber((((TD_temp -TDF_temp)/TD_temp)*100)+0.5); 
		
		sprintf(label,"%.1f/%.1f(GB)", TD_temp - TDF_temp,TD_temp); 
		
		SetCtrlVal(mainpanel, ProgressGroup[i], Full);
		SetCtrlAttribute(mainpanel, ProgressGroup[i], ATTR_LABEL_TEXT, label);
		
		if(Full>70)
		{
			flag=1;
		}
	}
	
	if(flag)	SetCtrlAttribute(mainpanel, MAIN_TITLE_1, ATTR_CTRL_VAL, "HDD �ʰ�!");
	else		SetCtrlAttribute(mainpanel, MAIN_TITLE_1, ATTR_CTRL_VAL, "HDD ��ȣ");
		
	// 1 = �����, 2=�� ���� �ý��� �޸�,3 = ��ü �ý��� ������ ���� �޸� ,4 = ����Ʈ ��ü ���� �ý��� �޸�
	// 5 = ��밡���� ���� �ý��� �޸�, 6 = ��� ������ ������ ���� ������, 7 = ��� ������ ���� �ý��� �޸�  (���� ����Ʈ)  
	GetMemoryInfo(&per_memory,&M_temp[0],&M_temp[1],&M_temp[2],&M_temp[3],&M_temp[4],&M_temp[5]);	
	// KB ��ȯ (�Ҽ��� ù° �ڸ� �ݿø�)
	RT_memory = (int)TruncateRealNumber((M_temp[0]/pow(2,20))+0.5);
	RS_memory = (int)TruncateRealNumber((M_temp[5]/pow(2,20))+0.5);

	sprintf(label,"%.0f/%.0f(%ld%%)", RT_memory / 100.0 * per_memory, RT_memory, per_memory);

	SetCtrlVal(mainpanel, MAIN_MAMORYBAR, (double)per_memory);
	SetCtrlAttribute(mainpanel, MAIN_MAMORYBAR, ATTR_LABEL_TEXT, label);
}