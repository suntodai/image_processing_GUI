//#define MAX 65536//������Ҫ�޸ķ����ջ��ԭʼ��1MB���������Բ��ö�̬����
#define  MAX 262144
//����PSNR����
double psnr(unsigned char* imgP,unsigned char* imgComp,int imgWidth,int imgHeight,int n);
//��������ͼ���֮���MADֵ
double costFuncMAD(unsigned char** currentBlk,unsigned char** refBlk,int mbSize);
//���㿪��������С�ĺ��
void minCost(double costs[3][3], double pVector[]);
//TSS�˶������㷨
void motionEstTSS(unsigned char *imgP, unsigned char* imgI, int imgWidth, int imgHeight, int motionVect[2][MAX], double* TSScomputations);
//TSS�˶�����
void motionComp(unsigned char* imgI,int mbSize,int imgWidth,int imgHeight,int motionVect[2][MAX],unsigned char* imgComp);
//��һά�������Сֵ�����±�
void minSearch(double* matrix,int N,double* minNum,int* index);
//DS�˶�����
void motionEstDS(unsigned char *imgP, unsigned char* imgI, int imgWidth, int imgHeight, int motionVect[2][MAX], double* DScomputations);