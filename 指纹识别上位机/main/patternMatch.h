#ifndef M_PATTEN
#define M_PATTEN
#include <vector>
using namespace std;
//坐标对齐 
void align(FEATUREPTR lpFeature, FEATUREPTR lpAlignedFeature, MINUTIAPTR lpFeatureCore,int rotation, int transx, 
	int transy);
//已对齐坐标的匹配
void alignMatch(FEATUREPTR lpAlignFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult, VF_FLAG matchMode);

//中心点匹配

void coreMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, 
				  PMATCHRESULT lpMatchResult, VF_FLAG matchMode, int n, int m);
//三角点匹配
void deltaMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, 
				  PMATCHRESULT lpMatchResult, VF_FLAG matchMode, vector<int>& n_delta, vector<int>& m_delta);
//获取两点间的距离
int dist(int x0, int y0, int x1, int y1);
//基于特征点的匹配
void centralMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult, VF_FLAG matchMode);

//全局匹配
void  globalMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, 
				  PMATCHRESULT lpMatchResult, VF_FLAG matchMode);


//所有匹配的大集合，匹配结果选取最好的
void  patternMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult, VF_FLAG matchMode);

#endif