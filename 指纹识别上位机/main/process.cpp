
#include "process.h"
#include "math.h"

#define  MAXIMGSIZE  256*360

sint32  	IMGW = 256;		// ��ǰ����ͼ��Ŀ��
sint32      IMGH = 360;		// ��ǰ����ͼ��ĸ߶�
sint32      IMGSIZE = (IMGW*IMGH);	// ��ǰ����ͼ��Ĵ�С


unsigned char *data;

#define  PI          3.141593
#define  EPI         57.29578


uint8		g_OrgFinger[MAXIMGSIZE];	// ����ͼ�����ݻ�����
uint8		g_Orient[MAXIMGSIZE];		// �������ݻ�����
uint8		g_Divide[MAXIMGSIZE];		// �ָ�ͼ���ݻ�����
uint8		g_Temp[MAXIMGSIZE];			// ��ʱ���ݻ�����

//uint8		*g_lpOrgFinger = &g_OrgFinger[0];	// ����ͼ�����ݻ������׵�ַ
//uint8		*g_lpOrient = &g_Orient[0];			// �������ݻ������׵�ַ
uint8		*g_gray = &g_Divide[0];			// �ָ�ͼ���ݻ������׵�ַ
//uint8		*g_lpTemp = &g_Temp[0];				// ��ʱ���ݻ������׵�ַ

int  g_DDSite[12][7][2] = {
	-3, 0,  -2, 0,  -1, 0,   0, 0,   1, 0,   2, 0,   3, 0,
	-3,-1,  -2,-1,  -1, 0,   0, 0,   1, 0,   2, 1,   3, 1,
	-3,-2,  -2,-1,  -1,-1,   0, 0,   1, 1,   2, 1,   3, 2,
	-3,-3,  -2,-2,  -1,-1,   0, 0,   1, 1,   2, 2,   3, 3,
	-2,-3,  -1,-2,  -1,-1,   0, 0,   1, 1,   1, 2,   2, 3,
	-1,-3,  -1,-2,   0,-1,   0, 0,   0, 1,   1, 2,   1, 3,
	0,-3,   0,-2,   0,-1,   0, 0,   0, 1,   0, 2,   0, 3,
	-1, 3,  -1, 2,   0, 1,   0, 0,   0,-1,   1,-2,   1,-3,
	-2, 3,  -1, 2,  -1, 1,   0, 0,   1,-1,   1,-2,   2,-3,
	-3, 3,  -2, 2,  -1, 1,   0, 0,   1,-1,   2,-2,   3,-3,
	-3, 2,  -2, 1,  -1, 1,   0, 0,   1,-1,   2,-1,   3,-2,
	-3, 1,  -2, 1,  -1, 0,   0, 0,   1, 0,   2,-1,   3,-1
};


/************************************************************************/
/* function:װ��ͼƬ
 author:ZCY
*/
/************************************************************************/
void load_FP(DIB *Dib1)
{
	extern unsigned char *data;

	IMGW=Dib1->GetWidth();
	IMGH=Dib1->GetHeight();
	data=Dib1->GetData();
	
}


/************************************************************************/
/* function:ͼƬ��ֵ��
 author:ZCY
*/
/************************************************************************/
int Binary(DIB *Dib1)
{
	int width,height;

	width=Dib1->GetWidth();

	height=Dib1->GetHeight();

	data=(unsigned char *)malloc(width*height);

	data=Dib1->GetData();

	if (Dib1->m_pBitmapInfoHeader->biBitCount>8)
	{
		MessageBox(NULL,TEXT("NO 8-bit"),0,MB_OK);
		return 0;
	}
	else
	{
		for (int x=0;x<width*height;x++)
		{
			if (data[x]<200)
			{
				data[x]=0;
			}
			else
				data[x]=255;
		}
	}


}
/************************************************************************/
/* function:ģ��    
authorer:ZCY
*/ 
/************************************************************************/

void smooth(BYTE *lpInBuffer, BYTE *lpOutBuffer, int IMGW, int IMGH, int r, int d)
{
	////////////////////////////////////////////////////////////////////////
	//	lpInBuffer: [in] Ҫƽ����ͼ�����ݻ�����
	//	lpOutBuffer: [out] ƽ�����ͼ�����ݻ�����
	//	r: [in] ƽ���˲����뾶
	//	d: [in] ƽ���˲�������
	////////////////////////////////////////////////////////////////////////
	int	x, y, i, j;
	BYTE	*lpSrc;
	BYTE	*lpRst;
	int	sum, num;


	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{
			lpSrc = lpInBuffer + y*IMGW + x;
			lpRst = lpOutBuffer + y*IMGW + x;
			sum = 0; 
			num = 0;
			for(i = -r; i <= r; i+=d)
			{
				if(i+y<0 || i+y>=IMGH)
					continue;
				for(j = -r; j <= r; j+=d)
				{
					if(j+x<0 || j+x>=IMGW)
						continue;
					sum += *(lpSrc + i*IMGW + j);
					num++;
				}
			}
			*lpRst = (BYTE)(sum/num);
		}
	}


}


;
/************************************************************************/
/*
function:��÷���

*/
/************************************************************************/
void getGrads(unsigned char* g_lpTemp, unsigned char* g_gray, int IMGW, int IMGH, long r)
{
	long  x, y, i, j;
	long  vx, vy, lvx, lvy;
	unsigned char   *lpSrc = NULL;
	unsigned char   *lpDiv = NULL;
	long	num;
	int gradSum;
	int grad;


	for(y = 0; y < IMGH/2; y++)
	{
		for(x = 0; x < IMGW/2; x++)
		{			
			lpDiv = g_gray + 2*y*IMGW + 2*x;
			lvx = 0;
			lvy = 0;
			num = 0;
			gradSum = 0;
			for(i = -r; i <= r; i++)	// Ϊ����ٶȣ�����Ϊ
			{
				if(y+i<1 || y+i>=IMGH/2-1) continue;
				for(j = -r; j <= r; j++)	// Ϊ����ٶȣ�����Ϊ
				{
					if(x+j<1 || x+j>=IMGW/2-1) continue;
					lpSrc = g_lpTemp + (y+i)*(IMGW/2) + x+j;
					//��x����ƫ��
					vx = *(lpSrc + IMGW/2 + 1) - *(lpSrc + IMGW/2 - 1) +
						*(lpSrc + 1)*2 - *(lpSrc - 1)*2 +
						*(lpSrc - IMGW/2 + 1) - *(lpSrc - IMGW/2 - 1);
					//��y����ƫ��
					vy = *(lpSrc + IMGW/2 - 1) - *(lpSrc - IMGW/2 - 1) +
						*(lpSrc + IMGW/2)*2 - *(lpSrc - IMGW/2)*2 +
						*(lpSrc + IMGW/2 + 1) - *(lpSrc - IMGW/2 + 1);

					gradSum += (abs(vx)+abs(vy));		
					num++; 
				}
			}

			if(num == 0)
				num = 1;
			// ���ֵ�����浽g_gray�У����ڷָ�ǰ������
			grad = gradSum/num;

			if(grad > 255)
				grad = 255;
			*lpDiv = (BYTE)grad;
			*(lpDiv + 1) = (BYTE)grad;
			*(lpDiv + IMGW) = (BYTE)grad;
			*(lpDiv + IMGW + 1) = (BYTE)grad;
		}
	}	

}	
//////////////////////////////////////////////////////////////////////////
/*
	

*/
//////////////////////////////////////////////////////////////////////////
void zoomout(BYTE *g_lpOrgFinger, BYTE *g_lpTemp, int IMGW, int IMGH)
{
	int	x, y;
	BYTE	*lpSrc;
	BYTE	*lpRst;
	int	sum;
	int	SiteD8[8] = {IMGW-1, IMGW, IMGW+1, 1, -IMGW+1, -IMGW, -IMGW-1, -1};

	// ��Ե����
	for(y = 0; y < IMGH; y+=2) //ͼƬѹ��,��IMAGH�������ĻҶȰ��Ƶ�IMGH/2��
	{
		lpSrc = g_lpOrgFinger + y*IMGW;
		lpRst = g_lpTemp + (y/2)*(IMGW/2);
		*lpRst = *lpSrc;
		lpSrc = g_lpOrgFinger + y*IMGW + IMGW - 1;
		lpRst = g_lpTemp + (y/2)*(IMGW/2) + (IMGW/2 - 1);
		*lpRst = *lpSrc;
	}
	for(x = 0; x < IMGW; x+=2)
	{
		lpSrc = g_lpOrgFinger + x;
		lpRst = g_lpTemp + x/2;
		*lpRst = *lpSrc;
		lpSrc = g_lpOrgFinger + (IMGH-1)*IMGW + x;
		lpRst = g_lpTemp + (IMGH/2-1)*(IMGW/2) + x/2;
		*lpRst = *lpSrc;
	}

	// �Ǳ�Ե�����ø�˹ģ����ȡ��Ƶ��Ϣ
	for(y = 2; y < IMGH-2; y+=2)
	{
		for(x = 2; x < IMGW-2; x+=2)
		{
			lpSrc = g_lpOrgFinger + y*IMGW + x;
			lpRst = g_lpTemp + (y/2)*(IMGW/2) + x/2;
			sum = *lpSrc*4 + *(lpSrc + SiteD8[0]) +
				*(lpSrc + SiteD8[1])*2 + *(lpSrc + SiteD8[2]) +
				*(lpSrc + SiteD8[3])*2 + *(lpSrc + SiteD8[4]) +
				*(lpSrc + SiteD8[5])*2 + *(lpSrc + SiteD8[6]) +
				*(lpSrc + SiteD8[7])*2;
			sum = sum>>4;
			*lpRst = (BYTE)sum;
		}
	}


}

//////////////////////////////////////////////////////////////////////////
/*


*/
//////////////////////////////////////////////////////////////////////////
void getOrientMap(unsigned char* g_lpTemp, unsigned char* g_lpOrient, int IMGW, int IMGH, long  r)
{
	long  x, y, i, j;
	long  vx, vy, lvx, lvy;
	unsigned char   *lpSrc = NULL;
	unsigned char   *lpOri = NULL;
	long	angle, num;
	double  fAngle;

	for(y = 0; y < IMGH/2; y++)
	{
		for(x = 0; x < IMGW/2; x++)
		{
			lpOri = g_lpOrient + 2 * y * IMGW + 2 * x;
			lvx = 0;
			lvy = 0;
			num = 0;
			for(i = -r; i <= r; i++)	// Ϊ����ٶȣ�����Ϊ
			{
				if(y+i<1 || y+i>=IMGH/2-1) continue;
				for(j = -r; j <= r; j++)	// Ϊ����ٶȣ�����Ϊ
				{
					if(x+j<1 || x+j>=IMGW/2-1) continue;
					lpSrc = g_lpTemp + (y+i)*(IMGW/2) + x+j;
					//��x����ƫ��
					vx = *(lpSrc + IMGW/2 + 1) - *(lpSrc + IMGW/2 - 1) +
						*(lpSrc + 1)*2 - *(lpSrc - 1)*2 +
						*(lpSrc - IMGW/2 + 1) - *(lpSrc - IMGW/2 - 1);
					//��y����ƫ��
					vy = *(lpSrc + IMGW/2 - 1) - *(lpSrc - IMGW/2 - 1) +
						*(lpSrc + IMGW/2)*2 - *(lpSrc - IMGW/2)*2 +
						*(lpSrc + IMGW/2 + 1) - *(lpSrc - IMGW/2 + 1);

					lvx += vx * vy * 2;//sin(2sita)
					lvy += vx*vx - vy*vy;//cos(2sita)
					num++;
				}
			}

			if(num == 0) num = 1;

			// �󻡶�
			fAngle = atan2((long double)lvy, (long double)lvx);
			// �任��(0 - 2*pi)
			if(fAngle < 0)	fAngle += 2*PI;

			// �����߽Ƕ�
			fAngle = (fAngle*EPI*0.5 + 0.5);
			angle = (long)fAngle;

			// ��Ϊ����sobel���ӣ����ԽǶ�ƫת�˶ȣ�����Ҫ��ת��õĽǶ�
			angle -= 135;
			// �Ƕȱ任����-180��
			if(angle <= 0)	angle += 180;

			angle = 180-angle;
			// �������߽Ƕ�
			*lpOri = (unsigned char)angle;
			*(lpOri + 1) = (unsigned char)angle;
			*(lpOri + IMGW) = (unsigned char)angle;
			*(lpOri + IMGW + 1) = (unsigned char)angle;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
/*

*/


void getHistor(uchar *datain,uchar *dataout,int width,int height)
{
	










}
//////////////////////////////////////////////////////////////////////////
/*




*/
//////////////////////////////////////////////////////////////////////////
int segment(uchar *g_gray,uchar *fpout,uchar threshold,int WIDTH,int HEIGHT)
{
	int	x, y;
	int  num = 0;

	// �Է��򳡷�ֵͼ����и߶�ƽ���˲�
	smooth(g_gray, fpout, WIDTH, HEIGHT,6, 2);

	// ͼ���Ե������Ϊ����
	for(y = 0; y < IMGH; y++)
	{
		*(g_gray + y*IMGW) = 255;
		*(g_gray + y*IMGW + IMGW - 1) = 255;
	}
	for(x = 0; x < IMGW; x++)
	{
		*(g_gray + x) = 255;
		*(g_gray + (IMGH-1)*IMGW + x) = 255;
	}

	for(y = 1; y < IMGH-1; y++)
	{
		for(x = 1; x < IMGW-1; x++)
		{
			// ���ݷ�ֵ����ֵ��С�ж��Ƿ�Ϊ��������
			if(*(g_gray + y*IMGW + x) < threshold)
			{
				*(g_gray + y*IMGW + x) = 0;
			}
			else
			{
				*(g_gray + y*IMGW + x) = 255;
				num++;
			}
		}
	}

	// ���ǰ���������С���������ʮ��֮һ�����ʾǰ������̫С�����ش���
	if(num < IMGH * IMGW/10)
		return 1;
	else
		return 0;

}

//////////////////////////////////////////////////////////////////////////
/*

*/
//////////////////////////////////////////////////////////////////////////
void segment_clearEdge(BYTE *g_lpOrgFinger, BYTE *g_lpOrient, BYTE* g_lpDivide, int IMGW, int IMGH)
{
	int	x, y;
	int  temp;
	temp = 0;

	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{	
			// ����Ǳ����������øõ�Ϊ�׵�
			if(*(g_lpDivide + temp + x) == 0)
			{
				*(g_lpOrgFinger + temp + x) = 255;
				*(g_lpOrient + temp + x) = 255;
			}
		}
		temp += IMGW;
	}
}
//////////////////////////////////////////////////////////////////////////
/*


*/
//////////////////////////////////////////////////////////////////////////

void equalize(BYTE *lpDIBBits, BYTE *lpDataOut, int lWidth, int lHeight)
{

	// ָ��Դͼ���ָ��
	BYTE*	lpSrc;
	BYTE*	lpRst;

	// ��ʱ����
	int	lTemp;
	// ѭ������
	int	i;
	int	j;

	// �Ҷ�ӳ���
	BYTE	bMap[256];

	// �Ҷ�ӳ���
	int	lCount[256];

	// ͼ��ÿ�е��ֽ���
	int	lLineBytes;

	// ����ͼ��ÿ�е��ֽ���
	//lLineBytes = WIDTHBYTES(lWidth * 8);
	lLineBytes = lWidth;

	// ���ü���Ϊ0
	for (i = 0; i < 256; i ++)
	{
		// ����
		lCount[i] = 0;
	}

	// ��������Ҷ�ֵ�ļ���
	for (i = 0; i < lHeight; i ++)
	{
		for (j = 0; j < lWidth; j ++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;

			// ������1
			lCount[*(lpSrc)]++;
		}
	}

	// ����Ҷ�ӳ���
	for (i = 0; i < 256; i++)
	{
		// ��ʼΪ0
		lTemp = 0;

		for (j = 0; j <= i ; j++)
		{
			lTemp += lCount[j];
		}

		// �����Ӧ���»Ҷ�ֵ
		bMap[i] = (BYTE) (lTemp * 255 / lHeight / lWidth);
	}
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			lpRst = (unsigned char*)lpDataOut + lLineBytes * (lHeight - 1 - i) + j;
			// �����µĻҶ�ֵ
			*lpRst = bMap[*lpSrc];
		}
	}
	// ����


}

//////////////////////////////////////////////////////////////////////////
/*
*/
//////////////////////////////////////////////////////////////////////////
/*************************************************************************
 *
 * \�������ƣ�
 *   MakeGauss()
 *
 * \�������:
 *   double sigma									        - ��˹�����ı�׼��
 *   double **pdKernel										- ָ���˹���������ָ��
 *   int *pnWindowSize										- ���ݵĳ���
 *
 * \����ֵ:
 *   ��
 *
 * \˵��:
 *   ���������������һ��һά�ĸ�˹�������������ݣ������ϸ�˹���ݵĳ���Ӧ
 *   �������޳��ģ�����Ϊ�˼���ļ򵥺��ٶȣ�ʵ�ʵĸ�˹����ֻ�������޳���
 *   pnWindowSize�������ݳ���
 *   
 *************************************************************************
 */
void MakeGauss(double sigma, double **pdKernel, int *pnWindowSize)
{
	// ѭ�����Ʊ���
	int i   ;
	
	// ��������ĵ�
	int nCenter;

	// �����ĳһ�㵽���ĵ�ľ���
	double  dDis  ; 

	
	// �м����
	double  dValue; 
	double  dSum  ;
	dSum = 0 ; 
	
	// ���鳤�ȣ����ݸ����۵�֪ʶ��ѡȡ[-3*sigma, 3*sigma]���ڵ����ݡ�
	// ��Щ���ݻḲ�Ǿ��󲿷ֵ��˲�ϵ��
	*pnWindowSize = (int)(1 + 2 * ceil(3 * sigma));
	
	// ����
	nCenter = (*pnWindowSize) / 2;
	
	// �����ڴ�
	*pdKernel = new double[*pnWindowSize] ;
	
	for(i=0; i< (*pnWindowSize); i++)
	{
		dDis = (double)(i - nCenter);
		dValue = exp(-(1/2)*dDis*dDis/(sigma*sigma)) / (sqrt(2 * PI) * sigma );
		(*pdKernel)[i] = dValue ;
		dSum += dValue;
	}
	
	// ��һ��
	for(i=0; i<(*pnWindowSize) ; i++)
	{
		(*pdKernel)[i] /= dSum;
	}
}



//////////////////////////////////////////////////////////////////////////
/*


*/

//////////////////////////////////////////////////////////////////////////
void GaussSmooth(BYTE *pUnchImg, BYTE *pUnchSmthdImg, int nWidth, int nHeight, double sigma)
{
	int y;
	int x;
	int i;

	// ��˹�˲��������鳤��
	int nWindowSize;

	//  ���ڳ��ȵ�1/2
	int	nHalfLen;   

	// һά��˹�����˲���
	double *pdKernel ;

	// ��˹ϵ����ͼ�����ݵĵ��
	double  dDotMul     ;

	// ��˹�˲�ϵ�����ܺ�
	double  dWeightSum     ;          

	// �м����
	double * pdTmp ;

	// �����ڴ�
	pdTmp = new double[nWidth*nHeight];

	// ����һά��˹�����˲���
	MakeGauss(sigma, &pdKernel, &nWindowSize) ;

	// MakeGauss���ش��ڵĳ��ȣ����ô˱������㴰�ڵİ볤
	nHalfLen = nWindowSize / 2;

	// x��������˲�
	for(y=0; y<nHeight; y++)
	{
		for(x=0; x<nWidth; x++)
		{
			dDotMul		= 0;
			dWeightSum = 0;
			for(i=(-nHalfLen); i<=nHalfLen; i++)
			{
				// �ж��Ƿ���ͼ���ڲ�
				if( (i+x) >= 0  && (i+x) < nWidth )
				{
					dDotMul += (double)pUnchImg[y*nWidth + (i+x)] * pdKernel[nHalfLen+i];
					dWeightSum += pdKernel[nHalfLen+i];
				}
			}
			pdTmp[y*nWidth + x] = dDotMul/dWeightSum ;
		}
	}

	// y��������˲�
	for(x=0; x<nWidth; x++)
	{
		for(y=0; y<nHeight; y++)
		{
			dDotMul		= 0;
			dWeightSum = 0;
			for(i=(-nHalfLen); i<=nHalfLen; i++)
			{
				// �ж��Ƿ���ͼ���ڲ�
				if( (i+y) >= 0  && (i+y) < nHeight )
				{
					dDotMul += (double)pdTmp[(y+i)*nWidth + x] * pdKernel[nHalfLen+i];
					dWeightSum += pdKernel[nHalfLen+i];
				}
			}
			pUnchSmthdImg[y*nWidth + x] = (BYTE)(int)(dDotMul / dWeightSum);
		}
	}

	// �ͷ��ڴ�
	delete []pdKernel;
	pdKernel = NULL ;

	delete []pdTmp;
	pdTmp = NULL;
}
//////////////////////////////////////////////////////////////////////////
/*




*/
//////////////////////////////////////////////////////////////////////////
void orientEnhance(BYTE *g_lpOrient, BYTE *g_lpOrgFinger, int IMGW, int IMGH)
{
	int x, y;
	int i;
	int d = 0;
	int sum = 0;
	// ���߷����Ͻ���ƽ���˲���ƽ���˲���
	int Hw[7] = {1, 1, 1, 1, 1, 1, 1};
	// ���߷���Ĵ�ֱ�����Ͻ������˲������˲���
	int Vw[7] = {-3, -1, 3, 9, 3, -1, -3};
	int hsum = 0;
	int vsum = 0;
	int temp = 0;
	BYTE  *lpSrc = NULL;
	BYTE  *lpDir = NULL;

	BYTE *g_lpTemp = new BYTE[IMGW * IMGH];

	// ���߷����Ͻ���ƽ���˲�
	temp = 0;
	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{
			lpDir = g_lpOrient + temp + x;
			lpSrc = g_lpOrgFinger + temp + x;
			// ���߷��������
			d = DDIndex(*lpDir);
			sum = 0;
			hsum = 0;
			for(i = 0; i < 7; i++)
			{
				if(y+g_DDSite[d][i][1] < 0 || y+g_DDSite[d][i][1] >= IMGH ||
					x+g_DDSite[d][i][0] < 0 || x+g_DDSite[d][i][0] >= IMGW)
				{
					continue;
				}
				sum += Hw[i]*(*(lpSrc + g_DDSite[d][i][1]*IMGW + g_DDSite[d][i][0]));
				hsum += Hw[i];
			}
			if(hsum != 0)
			{
				*(g_lpTemp + temp + x) = (BYTE)(sum/hsum);
			}
			else
			{
				*(g_lpTemp + temp + x) = 255;
			}
		}
		temp += IMGW;	
	}

	// ���߷���Ĵ�ֱ�����Ͻ������˲�
	temp = 0;
	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{
			lpDir = g_lpOrient + temp + x;
			lpSrc = g_lpTemp + temp + x;

			// ���߷���Ĵ�ֱ���������
			d = (DDIndex(*lpDir)+6) % 12;

			sum = 0;
			vsum = 0;
			for(i = 0; i < 7; i++)
			{
				if(y+g_DDSite[d][i][1] < 0 || y+g_DDSite[d][i][1] >= IMGH ||
					x+g_DDSite[d][i][0] < 0 || x+g_DDSite[d][i][0] >= IMGW)
				{
					continue;
				}
				sum += Vw[i]*(*(lpSrc + g_DDSite[d][i][1]*IMGW + g_DDSite[d][i][0]));
				vsum += Vw[i];
			}
			if(vsum > 0)
			{
				sum /= vsum;
				if(sum > 255)
				{
					*(g_lpOrgFinger + temp + x) = 255;
				}
				else if(sum < 0)
				{
					*(g_lpOrgFinger + temp + x) = 0;
				}
				else
				{
					*(g_lpOrgFinger + temp + x) = (BYTE)sum;
				}
			}
			else
			{
				*(g_lpOrgFinger + temp + x) = 255;
			}
		}
		temp += IMGW;
	}

}
//////////////////////////////////////////////////////////////////////////
/*

*/
//////////////////////////////////////////////////////////////////////////

int DDIndex(int angle)
{
	/////////////////////////////////////////////////////////////////////////
	//	angle: [in] �Ƕ� ��0 - 180��
	/////////////////////////////////////////////////////////////////////////
	if(angle >= 173 || angle < 8)
	{
		return 0;
	}
	else
	{
		return ((angle-8)/15 + 1);
	}
}


/////////////////////////////////////////////////////////////////
/*



*/
/////////////////////////////////////////////////////////////////
int imageThin(BYTE *lpBits, BYTE *g_lpTemp, int Width, int Height)
{
/////////////////////////////////////////////////////////////////
//	lpBits: [in, out] Ҫϸ����ͼ�����ݻ����� 
//	Width: [in] Ҫϸ����ͼ����
//	Height: [in] Ҫϸ����ͼ��߶�
/////////////////////////////////////////////////////////////////
	BYTE  erasetable[256]={
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
			1,1,0,0,1,1,0,0,             0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,             1,1,0,1,1,1,0,1,
			0,0,0,0,0,0,0,0,             0,0,0,0,0,0,0,0,
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,             1,1,0,1,1,1,0,0,
			1,1,0,0,1,1,1,0,             1,1,0,0,1,0,0,0
	};
	int		x,y;
	int      num;
	BOOL        Finished;
	BYTE       nw,n,ne,w,e,sw,s,se;
	BYTE       *lpPtr = NULL;
	BYTE       *lpTempPtr = NULL;	

	memcpy((void *)g_lpTemp, (void *)lpBits, Width*Height);
	
	//������־�óɼ�
	Finished=FALSE;
	while(!Finished){ //��û�н���
              //������־�óɼ�
            Finished=TRUE;
       //�Ƚ���ˮƽ�����ϸ��
              for (y=1;y<Height-1;y++)
			  { //ע��Ϊ��ֹԽ�磬y�ķ�Χ��1���߶�-2
                     //lpPtrָ��ԭͼ���ݣ�lpTempPtrָ����ͼ����

                     lpPtr=(BYTE *)lpBits+y*Width;
                     lpTempPtr=(BYTE *)g_lpTemp+y*Width;

                     x=1; //ע��Ϊ��ֹԽ�磬x�ķ�Χ��1�����-2

                     while(x<Width-1)
					 {
                            if(*(lpPtr+x)==0)
							{ //�Ǻڵ��������
                                   w = *(lpPtr+x-1);  //���ڵ�
                                   e = *(lpPtr+x+1);  //���ڵ�

                                   if( (w==255)|| (e==255)){ 

									//������������ھ���������һ���ǰ׵�Ŵ���

                                          nw=*(lpPtr+x+Width-1); //�����ڵ�

                                          n=*(lpPtr+x+Width); //���ڵ�

                                          ne=*(lpPtr+x+Width+1); //�����ڵ�

                                          sw=*(lpPtr+x-Width-1); //�����ڵ�

                                          s=*(lpPtr+x-Width); //���ڵ�

                                          se=*(lpPtr+x-Width+1); //�����ڵ�

                                          //��������

                            num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+
								sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //���������ɾ��

												//��ԭͼ�������н��úڵ�ɾ��

                                                 *(lpPtr+x)=255; 

													//���ͼ�иúڵ�Ҳɾ��

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=FALSE; //�иĶ���������־�óɼ�

                                                 x++; //ˮƽ��������һ������

                                          }

                                   }

                            }

                            x++; //ɨ����һ������

                     }

              }

       //�ٽ��д�ֱ�����ϸ��

              for (x=1;x<Width-1;x++){ //ע��Ϊ��ֹԽ�磬x�ķ�Χ��1�����-2

                     y=1; //ע��Ϊ��ֹԽ�磬y�ķ�Χ��1���߶�-2

                     while(y<Height-1){

                            lpPtr=lpBits+y*Width;

                            lpTempPtr=g_lpTemp+y*Width;

                            if(*(lpPtr+x)==0){ //�Ǻڵ��������

                                   n=*(lpPtr+x+Width);

                                   s=*(lpPtr+x-Width);

                                   if( (n==255)|| (s==255)){

//������������ھ���������һ���ǰ׵�Ŵ���

                                          nw=*(lpPtr+x+Width-1);

                                          ne=*(lpPtr+x+Width+1);

                                          w=*(lpPtr+x-1);

                                          e=*(lpPtr+x+1);

                                          sw=*(lpPtr+x-Width-1);

                                          se=*(lpPtr+x-Width+1);

                                          //��������

										num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+

											sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //���������ɾ��

//��ԭͼ�������н��úڵ�ɾ��

                                                 *(lpPtr+x)=255; 

//���ͼ�иúڵ�Ҳɾ��

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=FALSE; //�иĶ���������־�óɼ�

                                                 y++;//��ֱ��������һ������

                                          }

                                   }

                            }

                            y++; //ɨ����һ������

                     }

              } 

	}
	
	//memcpy((void *)lpBits, (void *)g_lpTemp, Width*Height);

	return 0;
}


int imageThinembed(BYTE *lpBits, BYTE *g_lpTemp, int Width, int Height)
{
/////////////////////////////////////////////////////////////////
//	lpBits: [in, out] Ҫϸ����ͼ�����ݻ����� 
//	Width: [in] Ҫϸ����ͼ����
//	Height: [in] Ҫϸ����ͼ��߶�
/////////////////////////////////////////////////////////////////
	BYTE  erasetable[256]={
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
			1,1,0,0,1,1,0,0,             0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,             1,1,0,1,1,1,0,1,
			0,0,0,0,0,0,0,0,             0,0,0,0,0,0,0,0,
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,1,
			0,0,1,1,0,0,1,1,             1,1,0,1,1,1,0,1,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,1,1,             0,0,0,0,0,0,0,0,
			1,1,0,0,1,1,0,0,             1,1,0,1,1,1,0,0,
			1,1,0,0,1,1,1,0,             1,1,0,0,1,0,0,0
	};
	int		x,y;
	int      num;
	char        Finished;
	BYTE       nw,n,ne,w,e,sw,s,se;
	BYTE       *lpPtr ;
	BYTE       *lpTempPtr ;	

	//memcpy((void *)g_lpTemp, (void *)lpBits, Width*Height);
	
	//������־�óɼ�
	Finished=0;
	while(!Finished){ //��û�н���
              //������־�óɼ�
            Finished=1;
       //�Ƚ���ˮƽ�����ϸ��
              for (y=1;y<Height-1;y++)
			  { //ע��Ϊ��ֹԽ�磬y�ķ�Χ��1���߶�-2
                     //lpPtrָ��ԭͼ���ݣ�lpTempPtrָ����ͼ����

                     lpPtr=(BYTE *)lpBits+y*Width;
                     lpTempPtr=(BYTE *)g_lpTemp+y*Width;

                     x=1; //ע��Ϊ��ֹԽ�磬x�ķ�Χ��1�����-2

                     while(x<Width-1)
					 {
                            if(*(lpPtr+x)==0)
							{ //�Ǻڵ��������
                                   w = *(lpPtr+x-1);  //���ڵ�
                                   e = *(lpPtr+x+1);  //���ڵ�

                                   if( (w==255)|| (e==255))
                                   { 

									//������������ھ���������һ���ǰ׵�Ŵ���

                                          nw=*(lpPtr+x+Width-1); //�����ڵ�

                                          n=*(lpPtr+x+Width); //���ڵ�

                                          ne=*(lpPtr+x+Width+1); //�����ڵ�

                                          sw=*(lpPtr+x-Width-1); //�����ڵ�

                                          s=*(lpPtr+x-Width); //���ڵ�

                                          se=*(lpPtr+x-Width+1); //�����ڵ�

                                          //��������

                            num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+
								sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //���������ɾ��

												//��ԭͼ�������н��úڵ�ɾ��

                                                 *(lpPtr+x)=255; 

													//���ͼ�иúڵ�Ҳɾ��

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=0; //�иĶ���������־�óɼ�

                                                 x++; //ˮƽ��������һ������

                                      }

                                   }

                            }

                            x++; //ɨ����һ������

                     }

              }

       //�ٽ��д�ֱ�����ϸ��

              for (x=1;x<Width-1;x++){ //ע��Ϊ��ֹԽ�磬x�ķ�Χ��1�����-2

                     y=1; //ע��Ϊ��ֹԽ�磬y�ķ�Χ��1���߶�-2

                     while(y<Height-1){

                            lpPtr=lpBits+y*Width;

                            lpTempPtr=g_lpTemp+y*Width;

                            if(*(lpPtr+x)==0){ //�Ǻڵ��������

                                   n=*(lpPtr+x+Width);

                                   s=*(lpPtr+x-Width);

                                   if( (n==255)|| (s==255)){

//������������ھ���������һ���ǰ׵�Ŵ���

                                          nw=*(lpPtr+x+Width-1);

                                          ne=*(lpPtr+x+Width+1);

                                          w=*(lpPtr+x-1);

                                          e=*(lpPtr+x+1);

                                          sw=*(lpPtr+x-Width-1);

                                          se=*(lpPtr+x-Width+1);

                                          //��������

										num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+

											sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //���������ɾ��

//��ԭͼ�������н��úڵ�ɾ��

                                                 *(lpPtr+x)=255; 

//���ͼ�иúڵ�Ҳɾ��

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=0; //�иĶ���������־�óɼ�

                                                 y++;//��ֱ��������һ������

                                          }

                                   }

                            }

                            y++; //ɨ����һ������

                     }

              } 

	}
	
	//memcpy((void *)lpBits, (void *)g_lpTemp, Width*Height);

	return 0;
}
