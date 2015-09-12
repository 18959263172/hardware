

#ifndef FP_FEATURE
#define FP_FEATURE
//点类型，坐标值为浮点


typedef  struct DblPoint
{
	double x;
	double y;
} DBLPOINT;


#define	MAX_SINGULARYNUM	30      
#define     MAXMINUTIANUM			60			// 最大特征点数
#define     MAXRAWMINUTIANUM        100			// 包含虚假特征点的初始特征点最大数目
#define VF_MINUTIA_END        1	// 端点
#define VF_MINUTIA_FORK       2	// 叉点
#define VF_MINUTIA_CORE		  3   //核心奇异点
#define VF_MINUTIA_DELTA	  4      //三角奇异点



#define PI					3.1415926
#define EPI					57.29578

#define SAFE_FREE(x) { if (x != NULL) free((void *)x); x = NULL; }

#define WIDTHBYTES(i)    ((i+3)/4*4)




//特征点
typedef struct tagMinutiae { 
  int    x;				// 横坐标
  int    y;				// 纵坐标
  int    Direction;		// 方向
  int	Triangle[3];	// 特征点为中心外接圆半径为定值的正三角形三个顶点的方向
  int    Type;			// 类型
} MINUTIA, *MINUTIAPTR; 

;
// 指纹特征(模板)结构
typedef struct tagFeature
{
	int		MinutiaNum;					// 特征点数
	MINUTIA		MinutiaArr[MAXMINUTIANUM]; //特征点数组
	
}FEATURE, *FEATUREPTR;


//
//匹配结果
typedef struct tagMatchResult { 
  int    Similarity;          //相似度
  int    Rotation;        //角度
  int    TransX;           //x方向偏移
  int    TransY;           //Y方向偏移
  int	MMCount;              //相似点数目
} MATCHRESULT, *PMATCHRESULT; 




typedef char  VF_FLAG;

// 精确比对模式，主要用在少量比对次数场合
#define	VF_MATCHMODE_VERIFY			1
// 快速比对模式，主要用在大量比对次数场合
#define	VF_MATCHMODE_IDENTIFY		2



int  getMinutia(char *g_lpOrgFinger, char *g_lpOrient, void * feature, int IMGW, int IMGH);

bool   IsFork(char *lpNow);
bool   IsEnd(char *lpNow);
int  GetNext(char *lpNow, char *lpLast, char **lppNext);
int  GetAngleDis(int angleBegin, int angleEnd);
int getOriChange(int angle1, int angle2, char flag);  //获得夹角

int  getMinutia( char *g_lpOrgFinger, char *g_lpOrient, void * feature, int IMGW, int IMGH);

int getSingularMinutia(unsigned char *lpOrient, int Width, int Height, char flag, void * feature); //获得奇异点


#endif