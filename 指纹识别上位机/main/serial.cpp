

#include "afxwin.h"

#include "serial.h"

DWORD WINAPI DoRvc(PVOID pVoid);



extern unsigned char FLag;

int COMM::Serial_init(CString com)
{
	//全局变量，串口句柄  
	m_hCom =CreateFile(com,  //COM1口  
		GENERIC_READ|GENERIC_WRITE, //允许读和写  
		0,  //独占方式  
		NULL,  
		OPEN_EXISTING,  //打开而不是创建  
		0, //同步方式
		NULL);  
	if(m_hCom ==INVALID_HANDLE_VALUE)  
	{  
		AfxMessageBox("打开COM失败!");  
		return FALSE;  
	}  
	SetupComm(m_hCom,3,92160); //输入缓冲区和输出缓冲区的大小都是1024  

	COMMTIMEOUTS TimeOuts;  
	//设定读超时  
	TimeOuts.ReadIntervalTimeout=1000;  
	TimeOuts.ReadTotalTimeoutMultiplier=0;  
	TimeOuts.ReadTotalTimeoutConstant=0;  
	//设定写超时  
	TimeOuts.WriteTotalTimeoutMultiplier=1;  
	TimeOuts.WriteTotalTimeoutConstant=1;  
	SetCommTimeouts(m_hCom,&TimeOuts); //设置超时  

	DCB dcb;  

	GetCommState(m_hCom,&dcb);  


	dcb.BaudRate=115200; //波特率为9600  

	dcb.ByteSize=8; //每个字节有8位  

	dcb.Parity=NOPARITY; //无奇偶校验位  

	dcb.StopBits=ONE5STOPBITS; //一个停止位  

	dcb.fDtrControl=DTR_CONTROL_DISABLE;

	SetCommState(m_hCom,&dcb);  

	PurgeComm(m_hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);  

	CreateThread(NULL,0,&DoRvc,this,0,0);

	return TRUE; 

}


int COMM::Serial_read()        //串口读取
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

