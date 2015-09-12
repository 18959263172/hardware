#pragma once
#include"stdAfx.h"

class DIB :public CObject
{
public:
	RGBQUAD *m_pRGB;  //λͼ����
	BYTE* m_pData;   //
	UINT m_numberofColors;  //����λ��
	BOOL m_valid;   //
	BITMAPFILEHEADER bitmapFileHeader;   //BMP�ļ�ͷ
	BITMAPINFOHEADER* m_pBitmapInfoHeader;  //BMP��Ϣͷ
	BITMAPINFO* m_pBitmapInfo;   //λͼ��Ϣ
	BYTE* pDib;   //�ļ�����

	DWORD size; 

public:
	char m_fileName[256];
	char *GetFileName();
	BOOL IsValid();
	DWORD GetSize();
	UINT GetWidth();
	UINT GetHeight();
	UINT GetNumberOfColors();   
	RGBQUAD *GetRGB();
	BYTE* GetData();
	BITMAPINFO *GetInfo();
	WORD PaletteSize(LPBYTE lpDIB);
	WORD DIBNumColors(LPBYTE lpDIB);
	BOOL saveastxt(const CString filename);
	void saveFile(const CString filename);
	void LoadFile(const char *dibFileName);              
	void SaveAsLongBit(const CString filename);
	void TxttoBmp(unsigned char *bmp);
	void resize(float ps);

}

