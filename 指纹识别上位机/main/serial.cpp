

#include "afxwin.h"

#include "serial.h"

DWORD WINAPI DoRvc(PVOID pVoid);



extern unsigned char FLag;

int COMM::Serial_init(CString com)
{
	//ȫ�ֱ��������ھ��  
	m_hCom =CreateFile(com,  //COM1��  
		GENERIC_READ|GENERIC_WRITE, //�������д  
		0,  //��ռ��ʽ  
		NULL,  
		OPEN_EXISTING,  //�򿪶����Ǵ���  
		0, //ͬ����ʽ
		NULL);  
	if(m_hCom ==INVALID_HANDLE_VALUE)  
	{  
		AfxMessageBox("��COMʧ��!");  
		return FALSE;  
	}  
	SetupComm(m_hCom,3,92160); //���뻺����������������Ĵ�С����1024  

	COMMTIMEOUTS TimeOuts;  
	//�趨����ʱ  
	TimeOuts.ReadIntervalTimeout=1000;  
	TimeOuts.ReadTotalTimeoutMultiplier=0;  
	TimeOuts.ReadTotalTimeoutConstant=0;  
	//�趨д��ʱ  
	TimeOuts.WriteTotalTimeoutMultiplier=1;  
	TimeOuts.WriteTotalTimeoutConstant=1;  
	SetCommTimeouts(m_hCom,&TimeOuts); //���ó�ʱ  

	DCB dcb;  

	GetCommState(m_hCom,&dcb);  


	dcb.BaudRate=115200; //������Ϊ9600  

	dcb.ByteSize=8; //ÿ���ֽ���8λ  

	dcb.Parity=NOPARITY; //����żУ��λ  

	dcb.StopBits=ONE5STOPBITS; //һ��ֹͣλ  

	dcb.fDtrControl=DTR_CONTROL_DISABLE;

	SetCommState(m_hCom,&dcb);  

	PurgeComm(m_hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);  

	CreateThread(NULL,0,&DoRvc,this,0,0);

	return TRUE; 

}


int COMM::Serial_read()        //���ڶ�ȡ
{
	while(TRUE)
	{
		char lpInBuffer[1024]={0};  
		DWORD dwBytesRead=3;  
		DWORD wBytesRead=3;
		//ClearCommError(hCom,&dwErrorFlags,&ComStat);  
 

		if(!dwBytesRead)  
			return FALSE;  

		BOOL bReadStatus;  

		if(FLag==1)
			
		{
			bReadStatus=ReadFile(m_hCom,lpInBuffer,  
			dwBytesRead,&wBytesRead,NULL); 
			this->OnData.emit(lpInBuffer,dwBytesRead);
			PurgeComm(m_hCom, PURGE_TXABORT|  
				PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);  


		}

		if(FLag==4)
		{
			bReadStatus=ReadFile(m_hCom,lpInBuffer,  
				dwBytesRead,&wBytesRead,NULL); 
			this->OnData.emit(lpInBuffer,dwBytesRead);
			PurgeComm(m_hCom, PURGE_TXABORT|  
				PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);  

		}

	}


}
int COMM::Serial_write(char *buffer,DWORD dwBytesWritten)
{
	DWORD dwErrorFlags=0;  
	COMSTAT ComStat;  
	OVERLAPPED m_osWrite;  
	DWORD Errors;
	BOOL bWriteStat;

	bWriteStat=WriteFile(m_hCom,buffer,dwBytesWritten,  
		&dwErrorFlags,NULL); 
	PurgeComm(m_hCom, PURGE_TXABORT|  
		PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);  

	ClearCommError(m_hCom,&dwErrorFlags,&ComStat); 

	return bWriteStat;  
}

void COMM::Serialclose()
{
	if(CloseHandle(m_hCom))  ;

}

HANDLE COMM::GetHandle()
{
	return m_hCom;

}

DWORD WINAPI DoRvc(PVOID pVoid)
{
	COMM *pComm=(COMM*)pVoid;
	HANDLE hComm=pComm->GetHandle();
	pComm->Serial_read();
	return 1;
}

