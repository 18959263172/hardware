

#ifndef FP_FEATURE
#define FP_FEATURE
//�����ͣ�����ֵΪ����


typedef  struct DblPoint
{
	double x;
	double y;
} DBLPOINT;


#define	MAX_SINGULARYNUM	30      
#define     MAXMINUTIANUM			60			// �����������
#define     MAXRAWMINUTIANUM        100			// �������������ĳ�ʼ�����������Ŀ
#define VF_MINUTIA_END        1	// �˵�
#define VF_MINUTIA_FORK       2	// ���
#define VF_MINUTIA_CORE		  3   //���������
#define VF_MINUTIA_DELTA	  4      //���������



#define PI					3.1415926
#define EPI					57.29578

#define SAFE_FREE(x) { if (x != NULL) free((void *)x); x = NULL; }

#define WIDTHBYTES(i)    ((i+3)/4*4)




//������
typedef struct tagMinutiae { 
  int    x;				// ������
  int    y;				// ������
  int    Direction;		// ����
  int	Triangle[3];	// ������Ϊ�������Բ�뾶Ϊ��ֵ������������������ķ���
  int    Type;			// ����
} MINUTIA, *MINUTIAPTR; 

;
// ָ������(ģ��)�ṹ
typedef struct tagFeature
{
	int		MinutiaNum;					// ��������
	MINUTIA		MinutiaArr[MAXMINUTIANUM]; //����������
	
}FEATURE, *FEATUREPTR;


//
//ƥ����
typedef struct tagMatchResult { 
  int    Similarity;          //���ƶ�
  int    Rotation;        //�Ƕ�
  int    TransX;           //x����ƫ��
  int    TransY;           //Y����ƫ��
  int	MMCount;              //���Ƶ���Ŀ
} MATCHRESULT, *PMATCHRESULT; 




typedef char  VF_FLAG;

// ��ȷ�ȶ�ģʽ����Ҫ���������ȶԴ�������
#define	VF_MATCHMODE_VERIFY			1
// ���ٱȶ�ģʽ����Ҫ���ڴ����ȶԴ�������
#define	VF_MATCHMODE_IDENTIFY		2



int  getMinutia(char *g_lpOrgFinger, char *g_lpOrient, void * feature, int IMGW, int IMGH);

bool   IsFork(char *lpNow);
bool   IsEnd(char *lpNow);
int  GetNext(char *lpNow, char *lpLast, char **lppNext);
int  GetAngleDis(int angleBegin, int angleEnd);
int getOriChange(int angle1, int angle2, char flag);  //��üн�

int  getMinutia( char *g_lpOrgFinger, char *g_lpOrient, void * feature, int IMGW, int IMGH);

int getSingularMinutia(unsigned char *lpOrient, int Width, int Height, char flag, void * feature); //��������


#endif