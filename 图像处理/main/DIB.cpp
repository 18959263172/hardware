
#include"DIB.h"
#include<windows.h>
#include<stdio.h>

;
void DIB::LoadFile(const char *dibFileName)   //װ���ļ�
{
	strcpy(m_fileName,dibFileName);        

	CFile dibFile(m_fileName,CFile::modeRead);

	dibFile.Read((void *)&bitmapFileHeader,sizeof(BITMAPFILEHEADER));             

	if(bitmapFileHeader.bfType==0x4d42)      //�ж��ǲ���BMPͼƬ
	{
		DWORD fileLength=dibFile.GetLength();  //����ļ���С

		size=fileLength-sizeof(BITMAPFILEHEADER);  //���ͼƬ��С

		pDib=(BYTE *)new char[size];   //��̬�����ڴ�

		dibFile.Read((void *)pDib,(DWORD)size);   //��BMP�ļ�����,ע���ʱ��ָ���Ѿ�ָ��BITMAPFILEHEADER֮��



		dibFile.Close();   //�ر��ļ�

		m_pBitmapInfo=(BITMAPINFO*)pDib;    //��ָ��ָ��λͼ�ļ�ͷ֮��


		m_pBitmapInfoHeader=(BITMAPINFOHEADER *)pDib;  //

		m_pRGB=(RGBQUAD*)(pDib+m_pBitmapInfoHeader->biSize);

		int m_numberofColors=GetNumberOfColors();

		if(m_pBitmapInfoHeader->biClrUsed==0)

		m_pBitmapInfoHeader->biClrUsed=m_numberofColors;

		DWORD colorTableSize =m_numberofColors*sizeof(RGBQUAD);

		m_pData=pDib+m_pBitmapInfoHeader->biSize+colorTableSize;

		if(m_pRGB==(RGBQUAD*) m_pData)

			m_pRGB=NULL;

		m_pBitmapInfoHeader->biSizeImage=GetSize();
		
		m_valid=TRUE;

	}
	else
	{
		m_valid=FALSE;
		
	}
}

char* DIB::GetFileName()
{
	return m_fileName;
}
UINT DIB::GetWidth()
{
	return (UINT)m_pBitmapInfoHeader->biWidth;
}
UINT DIB::GetHeight()
{
	return (UINT)m_pBitmapInfoHeader->biHeight;
}
DWORD DIB::GetSize()
{
	if(m_pBitmapInfoHeader->biSizeImage!=0)
		return m_pBitmapInfoHeader->biSizeImage;
	else
	{
		DWORD height=(DWORD) GetHeight();
		DWORD width=(DWORD)GetWidth();
		return height*width;
	}
}
BYTE* DIB::GetData()
{
	return m_pData;
}
RGBQUAD* DIB::GetRGB()
{
	return m_pRGB;
}

WORD DIB::PaletteSize(LPBYTE lpDIB)
{
	return (DIBNumColors(lpDIB)*sizeof(RGBTRIPLE));

}
WORD DIB::DIBNumColors(LPBYTE lpDIB)
{
	WORD wBitCount;
	switch(wBitCount)
	{
	case 1:
		return 2;
	case 4:
		return 16;
	case 8:
		return 256;
	default:
		return 0;
	}
}
void DIB::saveFile(const CString filename)
{
	strcpy(m_fileName,filename);
	CFile dibFile(m_fileName,CFile::modeCreate|CFile::modeWrite);
	dibFile.Write((void *)&bitmapFileHeader,sizeof(BITMAPFILEHEADER));
	dibFile.Write((void *)pDib,size);


	dibFile.Close();
}
UINT DIB::GetNumberOfColors()
{
	int numberOfColors;
	if((m_pBitmapInfoHeader->biClrUsed==0)&&
		(m_pBitmapInfoHeader->biBitCount<9))
	{
		switch(m_pBitmapInfoHeader->biBitCount)
		{
		case 1:numberOfColors=2;break;
		case 2:numberOfColors=4;break;
		case 4:numberOfColors=16;break;
		case 8:numberOfColors=256;break;
		}
	}
	else numberOfColors=(int)m_pBitmapInfoHeader->biClrUsed;
	return numberOfColors;
	
}
BOOL DIB::saveastxt(const CString filename)
{
	unsigned char *d_p;
	unsigned char *fp;  //fpָ��BITMAPFILE HEADER��d_p����BMP�ļ�ͷת������ַ��� 
	unsigned char *lp;   //lpָ��BMPINFO_HEADER
	
	CFile dibFile(filename,CFile::modeWrite|CFile::modeCreate);

	this->saveFile(filename+".bmp");

	d_p=(unsigned char *)malloc(2*sizeof(BITMAPFILEHEADER));   //Ϊ�ļ���Ϣͷ�����ڴ�


	lp=(unsigned char *)malloc(2*(this->size));     //�����ڴ�

	fp=(unsigned char *)(&this->bitmapFileHeader);  //ָ��BITMAPFILEHEADER
	
	for(int x=0;x<sizeof(BITMAPFILEHEADER);x++)
	{
			if((int)fp[x]<0x10)    //�ж����Ĵ�С
			{
				d_p[2*x]='0';//���С�������0
				itoa((int)fp[x],(char *)d_p+2*x+1,16);      //INTת��Ϊ�ַ���
			}
			else
			{
				itoa((int)fp[x],(char *)d_p+2*x,16);    //������ֱ��ת��
			}
		
	}
	for(int x=0;x<this->size;x++)
	{
		if((int)this->pDib[x]<0x10)
		{
			lp[2*x]='0';
			itoa((int)(this->pDib[x]),(char *)lp+2*x+1,16);   
		}
		else
		{
			itoa((int)(this->pDib[x]),(char *)lp+2*x,16);   
		}
	}
	for(int x=0;x<sizeof(BITMAPFILEHEADER);x++)
	{
		dibFile.Write((void *)(d_p+x*2),2);	
		dibFile.Write((const char *)",",1);	
	}
	for(int x=0;x<(this->size);x++)
	{
		dibFile.Write((void *)(lp+x*2),2);
		dibFile.Write((char *)",",1);	
	}


	dibFile.Close();

	return TRUE;

}
void DIB::SaveAsLongBit(const CString filename)
{
	CFile file(filename,CFile::modeWrite|CFile::modeCreate);

}
