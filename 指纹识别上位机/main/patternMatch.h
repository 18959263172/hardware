#ifndef M_PATTEN
#define M_PATTEN
#include <vector>
using namespace std;
//������� 
void align(FEATUREPTR lpFeature, FEATUREPTR lpAlignedFeature, MINUTIAPTR lpFeatureCore,int rotation, int transx, 
	int transy);
//�Ѷ��������ƥ��
void alignMatch(FEATUREPTR lpAlignFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult, VF_FLAG matchMode);

//���ĵ�ƥ��

void coreMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, 
				  PMATCHRESULT lpMatchResult, VF_FLAG matchMode, int n, int m);
//���ǵ�ƥ��
void deltaMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, 
				  PMATCHRESULT lpMatchResult, VF_FLAG matchMode, vector<int>& n_delta, vector<int>& m_delta);
//��ȡ�����ľ���
int dist(int x0, int y0, int x1, int y1);
//�����������ƥ��
void centralMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult, VF_FLAG matchMode);

//ȫ��ƥ��
void  globalMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, 
				  PMATCHRESULT lpMatchResult, VF_FLAG matchMode);


//����ƥ��Ĵ󼯺ϣ�ƥ����ѡȡ��õ�
void  patternMatch(FEATUREPTR lpFeature, FEATUREPTR lpTemplate, PMATCHRESULT lpMatchResult, VF_FLAG matchMode);

#endif