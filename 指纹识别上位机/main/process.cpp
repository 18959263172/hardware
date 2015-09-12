
#include "process.h"
#include "math.h"

#define  MAXIMGSIZE  256*360

sint32  	IMGW = 256;		// 当前处理图像的宽度
sint32      IMGH = 360;		// 当前处理图像的高度
sint32      IMGSIZE = (IMGW*IMGH);	// 当前处理图像的大小


unsigned char *data;

#define  PI          3.141593
#define  EPI         57.29578


uint8		g_OrgFinger[MAXIMGSIZE];	// 处理图像数据缓冲区
uint8		g_Orient[MAXIMGSIZE];		// 方向场数据缓冲区
uint8		g_Divide[MAXIMGSIZE];		// 分割图数据缓冲区
uint8		g_Temp[MAXIMGSIZE];			// 临时数据缓冲区

//uint8		*g_lpOrgFinger = &g_OrgFinger[0];	// 处理图像数据缓冲区首地址
//uint8		*g_lpOrient = &g_Orient[0];			// 方向场数据缓冲区首地址
uint8		*g_gray = &g_Divide[0];			// 分割图数据缓冲区首地址
//uint8		*g_lpTemp = &g_Temp[0];				// 临时数据缓冲区首地址

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
/* function:装载图片
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
/* function:图片二值化
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
/* function:模糊    
authorer:ZCY
*/ 
/************************************************************************/

void smooth(BYTE *lpInBuffer, BYTE *lpOutBuffer, int IMGW, int IMGH, int r, int d)
{
	////////////////////////////////////////////////////////////////////////
	//	lpInBuffer: [in] 要平滑的图像数据缓冲区
	//	lpOutBuffer: [out] 平滑后的图像数据缓冲区
	//	r: [in] 平滑滤波器半径
	//	d: [in] 平滑滤波器步长
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
function:获得方向场

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
			for(i = -r; i <= r; i++)	// 为提高速度，步长为
			{
				if(y+i<1 || y+i>=IMGH/2-1) continue;
				for(j = -r; j <= r; j++)	// 为提高速度，步长为
				{
					if(x+j<1 || x+j>=IMGW/2-1) continue;
					lpSrc = g_lpTemp + (y+i)*(IMGW/2) + x+j;
					//求x方向偏导
					vx = *(lpSrc + IMGW/2 + 1) - *(lpSrc + IMGW/2 - 1) +
						*(lpSrc + 1)*2 - *(lpSrc - 1)*2 +
						*(lpSrc - IMGW/2 + 1) - *(lpSrc - IMGW/2 - 1);
					//求y方向偏导
					vy = *(lpSrc + IMGW/2 - 1) - *(lpSrc - IMGW/2 - 1) +
						*(lpSrc + IMGW/2)*2 - *(lpSrc - IMGW/2)*2 +
						*(lpSrc + IMGW/2 + 1) - *(lpSrc - IMGW/2 + 1);

					gradSum += (abs(vx)+abs(vy));		
					num++; 
				}
			}

			if(num == 0)
				num = 1;
			// 求幅值，保存到g_gray中，用于分割前景背景
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

	// 边缘部分
	for(y = 0; y < IMGH; y+=2) //图片压缩,将IMAGH处索引的灰度搬移到IMGH/2处
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

	// 非边缘部分用高斯模板提取低频信息
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
			for(i = -r; i <= r; i++)	// 为提高速度，步长为
			{
				if(y+i<1 || y+i>=IMGH/2-1) continue;
				for(j = -r; j <= r; j++)	// 为提高速度，步长为
				{
					if(x+j<1 || x+j>=IMGW/2-1) continue;
					lpSrc = g_lpTemp + (y+i)*(IMGW/2) + x+j;
					//求x方向偏导
					vx = *(lpSrc + IMGW/2 + 1) - *(lpSrc + IMGW/2 - 1) +
						*(lpSrc + 1)*2 - *(lpSrc - 1)*2 +
						*(lpSrc - IMGW/2 + 1) - *(lpSrc - IMGW/2 - 1);
					//求y方向偏导
					vy = *(lpSrc + IMGW/2 - 1) - *(lpSrc - IMGW/2 - 1) +
						*(lpSrc + IMGW/2)*2 - *(lpSrc - IMGW/2)*2 +
						*(lpSrc + IMGW/2 + 1) - *(lpSrc - IMGW/2 + 1);

					lvx += vx * vy * 2;//sin(2sita)
					lvy += vx*vx - vy*vy;//cos(2sita)
					num++;
				}
			}

			if(num == 0) num = 1;

			// 求弧度
			fAngle = atan2((long double)lvy, (long double)lvx);
			// 变换到(0 - 2*pi)
			if(fAngle < 0)	fAngle += 2*PI;

			// 求纹线角度
			fAngle = (fAngle*EPI*0.5 + 0.5);
			angle = (long)fAngle;

			// 因为采用sobel算子，所以角度偏转了度，所以要旋转求得的角度
			angle -= 135;
			// 角度变换到（-180）
			if(angle <= 0)	angle += 180;

			angle = 180-angle;
			// 最终纹线角度
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

	// 对方向场幅值图像进行高度平滑滤波
	smooth(g_gray, fpout, WIDTH, HEIGHT,6, 2);

	// 图像边缘均设置为背景
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
			// 根据幅值与阈值大小判断是否为背景区域
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

	// 如果前景区域面积小于总面积的十分之一，则表示前景区域太小，返回错误
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
			// 如果是背景区域，则置该点为白点
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

	// 指向源图像的指针
	BYTE*	lpSrc;
	BYTE*	lpRst;

	// 临时变量
	int	lTemp;
	// 循环变量
	int	i;
	int	j;

	// 灰度映射表
	BYTE	bMap[256];

	// 灰度映射表
	int	lCount[256];

	// 图像每行的字节数
	int	lLineBytes;

	// 计算图像每行的字节数
	//lLineBytes = WIDTHBYTES(lWidth * 8);
	lLineBytes = lWidth;

	// 重置计数为0
	for (i = 0; i < 256; i ++)
	{
		// 清零
		lCount[i] = 0;
	}

	// 计算各个灰度值的计数
	for (i = 0; i < lHeight; i ++)
	{
		for (j = 0; j < lWidth; j ++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;

			// 计数加1
			lCount[*(lpSrc)]++;
		}
	}

	// 计算灰度映射表
	for (i = 0; i < 256; i++)
	{
		// 初始为0
		lTemp = 0;

		for (j = 0; j <= i ; j++)
		{
			lTemp += lCount[j];
		}

		// 计算对应的新灰度值
		bMap[i] = (BYTE) (lTemp * 255 / lHeight / lWidth);
	}
	// 每行
	for(i = 0; i < lHeight; i++)
	{		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			lpRst = (unsigned char*)lpDataOut + lLineBytes * (lHeight - 1 - i) + j;
			// 计算新的灰度值
			*lpRst = bMap[*lpSrc];
		}
	}
	// 返回


}

//////////////////////////////////////////////////////////////////////////
/*
*/
//////////////////////////////////////////////////////////////////////////
/*************************************************************************
 *
 * \函数名称：
 *   MakeGauss()
 *
 * \输入参数:
 *   double sigma									        - 高斯函数的标准差
 *   double **pdKernel										- 指向高斯数据数组的指针
 *   int *pnWindowSize										- 数据的长度
 *
 * \返回值:
 *   无
 *
 * \说明:
 *   这个函数可以生成一个一维的高斯函数的数字数据，理论上高斯数据的长度应
 *   该是无限长的，但是为了计算的简单和速度，实际的高斯数据只能是有限长的
 *   pnWindowSize就是数据长度
 *   
 *************************************************************************
 */
void MakeGauss(double sigma, double **pdKernel, int *pnWindowSize)
{
	// 循环控制变量
	int i   ;
	
	// 数组的中心点
	int nCenter;

	// 数组的某一点到中心点的距离
	double  dDis  ; 

	
	// 中间变量
	double  dValue; 
	double  dSum  ;
	dSum = 0 ; 
	
	// 数组长度，根据概率论的知识，选取[-3*sigma, 3*sigma]以内的数据。
	// 这些数据会覆盖绝大部分的滤波系数
	*pnWindowSize = (int)(1 + 2 * ceil(3 * sigma));
	
	// 中心
	nCenter = (*pnWindowSize) / 2;
	
	// 分配内存
	*pdKernel = new double[*pnWindowSize] ;
	
	for(i=0; i< (*pnWindowSize); i++)
	{
		dDis = (double)(i - nCenter);
		dValue = exp(-(1/2)*dDis*dDis/(sigma*sigma)) / (sqrt(2 * PI) * sigma );
		(*pdKernel)[i] = dValue ;
		dSum += dValue;
	}
	
	// 归一化
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

	// 高斯滤波器的数组长度
	int nWindowSize;

	//  窗口长度的1/2
	int	nHalfLen;   

	// 一维高斯数据滤波器
	double *pdKernel ;

	// 高斯系数与图像数据的点乘
	double  dDotMul     ;

	// 高斯滤波系数的总和
	double  dWeightSum     ;          

	// 中间变量
	double * pdTmp ;

	// 分配内存
	pdTmp = new double[nWidth*nHeight];

	// 产生一维高斯数据滤波器
	MakeGauss(sigma, &pdKernel, &nWindowSize) ;

	// MakeGauss返回窗口的长度，利用此变量计算窗口的半长
	nHalfLen = nWindowSize / 2;

	// x方向进行滤波
	for(y=0; y<nHeight; y++)
	{
		for(x=0; x<nWidth; x++)
		{
			dDotMul		= 0;
			dWeightSum = 0;
			for(i=(-nHalfLen); i<=nHalfLen; i++)
			{
				// 判断是否在图像内部
				if( (i+x) >= 0  && (i+x) < nWidth )
				{
					dDotMul += (double)pUnchImg[y*nWidth + (i+x)] * pdKernel[nHalfLen+i];
					dWeightSum += pdKernel[nHalfLen+i];
				}
			}
			pdTmp[y*nWidth + x] = dDotMul/dWeightSum ;
		}
	}

	// y方向进行滤波
	for(x=0; x<nWidth; x++)
	{
		for(y=0; y<nHeight; y++)
		{
			dDotMul		= 0;
			dWeightSum = 0;
			for(i=(-nHalfLen); i<=nHalfLen; i++)
			{
				// 判断是否在图像内部
				if( (i+y) >= 0  && (i+y) < nHeight )
				{
					dDotMul += (double)pdTmp[(y+i)*nWidth + x] * pdKernel[nHalfLen+i];
					dWeightSum += pdKernel[nHalfLen+i];
				}
			}
			pUnchSmthdImg[y*nWidth + x] = (BYTE)(int)(dDotMul / dWeightSum);
		}
	}

	// 释放内存
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
	// 纹线方向上进行平滑滤波的平滑滤波器
	int Hw[7] = {1, 1, 1, 1, 1, 1, 1};
	// 纹线方向的垂直方向上进行锐化滤波的锐化滤波器
	int Vw[7] = {-3, -1, 3, 9, 3, -1, -3};
	int hsum = 0;
	int vsum = 0;
	int temp = 0;
	BYTE  *lpSrc = NULL;
	BYTE  *lpDir = NULL;

	BYTE *g_lpTemp = new BYTE[IMGW * IMGH];

	// 纹线方向上进行平滑滤波
	temp = 0;
	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{
			lpDir = g_lpOrient + temp + x;
			lpSrc = g_lpOrgFinger + temp + x;
			// 纹线方向的索引
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

	// 纹线方向的垂直方向上进行锐化滤波
	temp = 0;
	for(y = 0; y < IMGH; y++)
	{
		for(x = 0; x < IMGW; x++)
		{
			lpDir = g_lpOrient + temp + x;
			lpSrc = g_lpTemp + temp + x;

			// 纹线方向的垂直方向的索引
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
	//	angle: [in] 角度 （0 - 180）
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
//	lpBits: [in, out] 要细化的图像数据缓冲区 
//	Width: [in] 要细化的图像宽度
//	Height: [in] 要细化的图像高度
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
	
	//结束标志置成假
	Finished=FALSE;
	while(!Finished){ //还没有结束
              //结束标志置成假
            Finished=TRUE;
       //先进行水平方向的细化
              for (y=1;y<Height-1;y++)
			  { //注意为防止越界，y的范围从1到高度-2
                     //lpPtr指向原图数据，lpTempPtr指向新图数据

                     lpPtr=(BYTE *)lpBits+y*Width;
                     lpTempPtr=(BYTE *)g_lpTemp+y*Width;

                     x=1; //注意为防止越界，x的范围从1到宽度-2

                     while(x<Width-1)
					 {
                            if(*(lpPtr+x)==0)
							{ //是黑点才做处理
                                   w = *(lpPtr+x-1);  //左邻点
                                   e = *(lpPtr+x+1);  //右邻点

                                   if( (w==255)|| (e==255)){ 

									//如果左右两个邻居中至少有一个是白点才处理

                                          nw=*(lpPtr+x+Width-1); //左上邻点

                                          n=*(lpPtr+x+Width); //上邻点

                                          ne=*(lpPtr+x+Width+1); //右上邻点

                                          sw=*(lpPtr+x-Width-1); //左下邻点

                                          s=*(lpPtr+x-Width); //下邻点

                                          se=*(lpPtr+x-Width+1); //右下邻点

                                          //计算索引

                            num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+
								sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //经查表，可以删除

												//在原图缓冲区中将该黑点删除

                                                 *(lpPtr+x)=255; 

													//结果图中该黑点也删除

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=FALSE; //有改动，结束标志置成假

                                                 x++; //水平方向跳过一个象素

                                          }

                                   }

                            }

                            x++; //扫描下一个象素

                     }

              }

       //再进行垂直方向的细化

              for (x=1;x<Width-1;x++){ //注意为防止越界，x的范围从1到宽度-2

                     y=1; //注意为防止越界，y的范围从1到高度-2

                     while(y<Height-1){

                            lpPtr=lpBits+y*Width;

                            lpTempPtr=g_lpTemp+y*Width;

                            if(*(lpPtr+x)==0){ //是黑点才做处理

                                   n=*(lpPtr+x+Width);

                                   s=*(lpPtr+x-Width);

                                   if( (n==255)|| (s==255)){

//如果上下两个邻居中至少有一个是白点才处理

                                          nw=*(lpPtr+x+Width-1);

                                          ne=*(lpPtr+x+Width+1);

                                          w=*(lpPtr+x-1);

                                          e=*(lpPtr+x+1);

                                          sw=*(lpPtr+x-Width-1);

                                          se=*(lpPtr+x-Width+1);

                                          //计算索引

										num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+

											sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //经查表，可以删除

//在原图缓冲区中将该黑点删除

                                                 *(lpPtr+x)=255; 

//结果图中该黑点也删除

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=FALSE; //有改动，结束标志置成假

                                                 y++;//垂直方向跳过一个象素

                                          }

                                   }

                            }

                            y++; //扫描下一个象素

                     }

              } 

	}
	
	//memcpy((void *)lpBits, (void *)g_lpTemp, Width*Height);

	return 0;
}


int imageThinembed(BYTE *lpBits, BYTE *g_lpTemp, int Width, int Height)
{
/////////////////////////////////////////////////////////////////
//	lpBits: [in, out] 要细化的图像数据缓冲区 
//	Width: [in] 要细化的图像宽度
//	Height: [in] 要细化的图像高度
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
	
	//结束标志置成假
	Finished=0;
	while(!Finished){ //还没有结束
              //结束标志置成假
            Finished=1;
       //先进行水平方向的细化
              for (y=1;y<Height-1;y++)
			  { //注意为防止越界，y的范围从1到高度-2
                     //lpPtr指向原图数据，lpTempPtr指向新图数据

                     lpPtr=(BYTE *)lpBits+y*Width;
                     lpTempPtr=(BYTE *)g_lpTemp+y*Width;

                     x=1; //注意为防止越界，x的范围从1到宽度-2

                     while(x<Width-1)
					 {
                            if(*(lpPtr+x)==0)
							{ //是黑点才做处理
                                   w = *(lpPtr+x-1);  //左邻点
                                   e = *(lpPtr+x+1);  //右邻点

                                   if( (w==255)|| (e==255))
                                   { 

									//如果左右两个邻居中至少有一个是白点才处理

                                          nw=*(lpPtr+x+Width-1); //左上邻点

                                          n=*(lpPtr+x+Width); //上邻点

                                          ne=*(lpPtr+x+Width+1); //右上邻点

                                          sw=*(lpPtr+x-Width-1); //左下邻点

                                          s=*(lpPtr+x-Width); //下邻点

                                          se=*(lpPtr+x-Width+1); //右下邻点

                                          //计算索引

                            num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+
								sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //经查表，可以删除

												//在原图缓冲区中将该黑点删除

                                                 *(lpPtr+x)=255; 

													//结果图中该黑点也删除

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=0; //有改动，结束标志置成假

                                                 x++; //水平方向跳过一个象素

                                      }

                                   }

                            }

                            x++; //扫描下一个象素

                     }

              }

       //再进行垂直方向的细化

              for (x=1;x<Width-1;x++){ //注意为防止越界，x的范围从1到宽度-2

                     y=1; //注意为防止越界，y的范围从1到高度-2

                     while(y<Height-1){

                            lpPtr=lpBits+y*Width;

                            lpTempPtr=g_lpTemp+y*Width;

                            if(*(lpPtr+x)==0){ //是黑点才做处理

                                   n=*(lpPtr+x+Width);

                                   s=*(lpPtr+x-Width);

                                   if( (n==255)|| (s==255)){

//如果上下两个邻居中至少有一个是白点才处理

                                          nw=*(lpPtr+x+Width-1);

                                          ne=*(lpPtr+x+Width+1);

                                          w=*(lpPtr+x-1);

                                          e=*(lpPtr+x+1);

                                          sw=*(lpPtr+x-Width-1);

                                          se=*(lpPtr+x-Width+1);

                                          //计算索引

										num=nw/255+n/255*2+ne/255*4+w/255*8+e/255*16+

											sw/255*32+s/255*64+se/255*128;

                                          if(erasetable[num]==1){ //经查表，可以删除

//在原图缓冲区中将该黑点删除

                                                 *(lpPtr+x)=255; 

//结果图中该黑点也删除

                                                 *(lpTempPtr+x)=255; 

                                                 Finished=0; //有改动，结束标志置成假

                                                 y++;//垂直方向跳过一个象素

                                          }

                                   }

                            }

                            y++; //扫描下一个象素

                     }

              } 

	}
	
	//memcpy((void *)lpBits, (void *)g_lpTemp, Width*Height);

	return 0;
}
