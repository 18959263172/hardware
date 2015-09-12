#ifndef  serial
#define  serial
#include "sigslot.h"

using namespace sigslot;


class COMM
{
private:
	HANDLE m_hCom;
public:
	int Serial_init(CString com);
	int Serial_read();
	void Serialclose();
	int Serial_write(char *buffer,DWORD dwBytesWritten);
	HANDLE GetHandle();
	sigslot::signal2<char*,int> OnData;

};

#endif
