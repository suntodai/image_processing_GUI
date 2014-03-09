//#define MAX 65536//导致需要修改分配的栈，原始的1MB不够，可以采用动态分配
#define  MAX 262144
//计算PSNR函数
double psnr(unsigned char* imgP,unsigned char* imgComp,int imgWidth,int imgHeight,int n);
//计算两个图像块之间的MAD值
double costFuncMAD(unsigned char** currentBlk,unsigned char** refBlk,int mbSize);
//计算开销函数最小的宏块
void minCost(double costs[3][3], double pVector[]);
//TSS运动估计算法
void motionEstTSS(unsigned char *imgP, unsigned char* imgI, int imgWidth, int imgHeight, int motionVect[2][MAX], double* TSScomputations);
//TSS运动补偿
void motionComp(unsigned char* imgI,int mbSize,int imgWidth,int imgHeight,int motionVect[2][MAX],unsigned char* imgComp);
//求一维矩阵的最小值及其下标
void minSearch(double* matrix,int N,double* minNum,int* index);
//DS运动补偿
void motionEstDS(unsigned char *imgP, unsigned char* imgI, int imgWidth, int imgHeight, int motionVect[2][MAX], double* DScomputations);