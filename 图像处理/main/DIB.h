#pragma once
#include"stdAfx.h"
class DIB :public CObject
{
public:
	RGBQUAD *m_pRGB;  //位图数据
	BYTE* m_pData;   //
	UINT m_numberofColors;  //数据位深
	BOOL m_valid;   //
	BITMAPFILEHEADER bitmapFileHeader;   //BMP文件头
	BITMAPINFOHEADER* m_pBitmapInfoHeader;  //BMP信息头
	BITMAPINFO* m_pBitmapInfo;   
	BYTE* pDib;
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
}

