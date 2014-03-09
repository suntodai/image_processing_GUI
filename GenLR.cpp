#include "stdafx.h"
#include "math.h"
#include "GenLR.h"
#include "shift.h"
#include "noise.h"
#include "transform.h"
#include "segment.h"
#include <stdlib.h>


//void GenLR(unsigned char* lpIn,unsigned char* lpOut,int width, int height, bool noiseAuto,double noiseVar)
void GenLR(unsigned char* lpIn,unsigned char* lpOut,int width, int height, bool noiseAuto,double noiseVar, int s1_rand,int s2_rand, int s3_rand, int s4_rand)
{
//先形变，然后模糊处理，再下采样，最后加噪

	int lineBytes = (width +3)/4*4;
	//循环变量
	long i,j;
	//随机参数生成
//	srand((unsigned)time(NULL));
//    int s1_rand=rand()%10;
//	int s2_rand=rand()%20;
//	int s3_rand=rand()%20;
//	int s4_rand=rand()%20;

	float mean = 0;
	float Pvariance[] = {0.00005,0.00015,0.00025,0.00035,0.00045,0.00055,0.00065,0.00075,0.000087,0.00095};
	float Pangle[]    = {0.005,0.015,0.025,0.035,0.045,0.055,0.065,0.075,0.085,0.095,
                        -0.005,-0.015,-0.025,-0.035,-0.045,-0.055,-0.065,-0.075,-0.085,-0.095};
    float PshiftX[]   = {0.05,0.15,0.25,0.35,0.45,0.55,0.65,0.75,0.85,0.95,
                        -0.05,-0.15,-0.25,-0.35,-0.45,-0.55,-0.65,-0.75,-0.85,-0.95};
	float PshiftY[]   = {0.05,0.15,0.25,0.35,0.45,0.55,0.65,0.75,0.85,0.95,
                        -0.05,-0.15,-0.25,-0.35,-0.45,-0.55,-0.65,-0.75,-0.85,-0.95};
	float variance;
	if(noiseAuto)
     	variance    = Pvariance[s1_rand];
	else
        variance    = noiseVar;

	float angle       = Pangle[s2_rand];
	float shiftX      = PshiftX[s3_rand];
	float shiftY      = PshiftY[s4_rand];
	//附生参数计算
	float slope=angle/180.0*3.1415926;
	int outImgW=width*fabs(cos(slope))+height*fabs(sin(slope)), outImgH=height*fabs(cos(slope))+width*fabs(sin(slope));


	float skew=tan(slope);
	float zoomTimew=(width/(float)outImgW)/2.0, zoomTimeh = (height/(float)outImgH)/2.0;
	int zoomW=width/2, zoomH=height/2;

	//滤波参数
	int masksize = 3;
	double mask[9] ={1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9};
//    int mask[9] = {1,1,1,1,1,1,1,1,1};
    int lineWBt = (outImgW+3)/4*4;
    int lineZBt = (zoomW+3)/4*4;

        //分配内存
	unsigned char *rotateBuf=new unsigned char[outImgW*outImgH];//函数生成
	unsigned char *shiftBuf =new unsigned char[outImgW*outImgH];//多空了点缓冲区出来，程序运行OK，但是可能有潜在的问题
	unsigned char *zoomBuf  =new unsigned char[zoomW*zoomH];
    unsigned char *NoiseBuf =new unsigned char[zoomW*zoomH];
	unsigned char *LRBuf    =new unsigned char[zoomW*zoomH];

        //处理
   		//旋转  --输入图像用lineBytes???  应该是，都用了双线性插值 
	rotateGrey(lpIn, lineBytes, height, 0,skew, 0, 0, rotateBuf,outImgW, outImgH);// 从width*height 转到 outImgW*outImgH

        //位移
	shift(rotateBuf, shiftBuf, outImgW, outImgH, shiftX,shiftY);//保持大小不变outImgW*outImgH

    //双线性缩放--输入图像用lineBytes
    zoomGray2(shiftBuf, outImgW, outImgH, zoomTimew, zoomTimeh, zoomBuf, zoomW, zoomH);//由outImgW*outImgH缩放至zoomW*zoomH

        //加噪
    GaussNoise(zoomBuf,LRBuf,zoomW,zoomH,mean, variance);//保持大小不变zoomW*zoomH

	    //滤波
//    Filter(LRBuf,zoomW,zoomH,1,mask,masksize);
//	midFilter(LRBuf,zoomW,zoomH,1, mask,masksize);损失很多细节

	//删除内存
	delete []rotateBuf;
 	delete []shiftBuf;
	delete []zoomBuf;

	 //复制数据区
    for(i=0;i<zoomH;i++)
	{
		for(j=0;j<zoomW;j++)
		{
			lpOut[i*zoomW+j]= LRBuf[i*zoomW+j];
 //           lpOut[i*zoomW+j]= zoomBuf[i*zoomW+j];
      //      lpOut[i*lineZBt+j]= lpIn[2*i*2*lineZBt+2*j];  好使--说明外部显示正常
		}
	}
	delete []LRBuf;
//	delete []zoomBuf;

}
