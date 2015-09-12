#include "StdAfx.h"
//////////////////////////////////////////////////////////////////////////
//此文件包含了指纹图
#ifndef FPMATH
#define  FPMATH

int  PX(char *lpPos);
int  PY(char *lpPos);
int  GetJiajiao(int angle1, int angle2);
int  GetAngle(int x0, int y0, int x1, int y1);
int  GetByDis(char *lpEnd, char **lppPos, int d);
int  AngleAbs360(int angle1, int angle2);
#endif