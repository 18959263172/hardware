
#ifndef PROCESS
#define  PROCESS
#include "DIB.h"
#define sint32 signed int
#define uint8 unsigned char
#define uchar unsigned char
/************************************************************************/
/*        autor:zcy                                                              */
/************************************************************************/

;
int Binary(DIB *Dib1);
void smooth(BYTE *lpInBuffer, BYTE *lpOutBuffer, int IMGW, int IMGH, int r, int d);  //图像平滑
void getGrads(unsigned char* g_lpTemp, unsigned char* g_lpDivide, int IMGW, int IMGH, long r);//计算梯度场
void zoomout(BYTE *g_lpOrgFinger, BYTE *g_lpTemp, int IMGW, int IMGH);
void getOrientMap(unsigned char* g_lpTemp, unsigned char* g_lpOrient, int IMGW, int IMGH, long  r);
int segment(uchar *g_gray,uchar *fpout,uchar threshold,int WIDTH,int HEIGHT);
void segment_clearEdge(BYTE *g_lpOrgFinger, BYTE *g_lpOrient, BYTE* g_lpDivide, int IMGW, int IMGH);
void equalize(BYTE *lpDIBBits, BYTE *lpDataOut, int lWidth, int lHeight);
void GaussSmooth(BYTE *pUnchImg, BYTE *pUnchSmthdImg, int nWidth, int nHeight, double sigma);
void MakeGauss(double sigma, double **pdKernel, int *pnWindowSize);
void orientEnhance(BYTE *g_lpOrient, BYTE *g_lpOrgFinger, int IMGW, int IMGH);
int DDIndex(int angle);


#endif  