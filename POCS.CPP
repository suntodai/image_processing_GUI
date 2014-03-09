#include "POCS.h"
#include "segment.h"// filter
#include "transform.h"//zoom
#include "motionES.h"// motion estimation
#include "GenLR.h"// generate LR series
#include "math.h"
#define  MAXLRNUM 50
#define  R  6// 全局残差R---对结果有影响，大点去噪效果比较好
//#define  MAX 65536
#define  MAX 262144

//**************************POCS superresolution restoration algorithm************************************//
//function: 实现POCS超分辨率复原
//input: 
//imgIn:      输入图像的指针，理想的HR图
//imgWidth:   输入图像的宽度
//imgHeight:  输入图像的高度
//LRNum:      产生的低分辨率图像的数目
//iterNum:    复原迭代次数
//output:
//imgOut:     输出图像的指针
void pocs(unsigned char* imgIn,int imgWidth,int imgHeight,int LRNum,int iterNum, unsigned char* imgOut, bool noiseAuto, double noiseVar)
{
   //生成LRNum数目的LR图像
	//LRNum 数目的LR图像指针
	unsigned char *p[MAXLRNUM];
	int newHeight = imgHeight/2;
	int newWidth  = imgWidth/2;
	int masksize  = 5;
	int k;
/*	blur =[.25 0 1 0 .25;...
        0  1 2 1  0;...
        1  2 4 2  1;...
        0  1 2 1  0;...
       .25 0 1 0 .25];
	double blur[25] = {0.25,0,1.0,0,0.25,
		           0,1.0,2.0,1.0,
				   1.0,2.0,4.0,2.0,1.0,
				   0,1.0,2.0,1.0,0,
				   0.25,0,1.0,0,0.25};//21
    for(k=0;k<masksize*masksize;k++)
	{
		blur[k]=blur[k]/21;
	}
*/
	double blur[25] = {0.00296901674395050,	0.0133062098910137,	0.0219382312797146,	0.0133062098910137,	0.00296901674395050,
                       0.0133062098910137,	0.0596342954361801,	0.0983203313488458,	0.0596342954361801,	0.0133062098910137,
                       0.0219382312797146,	0.0983203313488458,	0.162102821637127,	0.0983203313488458,	0.0219382312797146,
                       0.0133062098910137,	0.0596342954361801,	0.0983203313488458, 0.0596342954361801,	0.0133062098910137,
                       0.00296901674395050,	0.0133062098910137,	0.0219382312797146,	0.0133062098910137,	0.00296901674395050
};

	int seqNum[9] = {1,5,7,9,2,3,6,4,8};
	double sigmaHtr=0;

	for(k=0;k<masksize*masksize;k++)
	{
		sigmaHtr=sigmaHtr+pow(*(blur+k),2);
	}

	for(k=0;k<LRNum;k++)
	{
		int s1_rand, s2_rand, s3_rand, s4_rand;
		s1_rand = seqNum[k];
		s2_rand = seqNum[k];
		s3_rand = seqNum[k];
		s4_rand = seqNum[k];
		unsigned char *LRtmp[MAXLRNUM];
    	LRtmp[k] = new unsigned char [newHeight*newWidth];
		 p[k] = new unsigned char [imgWidth*imgHeight];
				//产生低分辨率图像
		GenLR(imgIn,LRtmp[k],imgWidth,imgHeight,noiseAuto,noiseVar,s1_rand,s2_rand,s3_rand,s4_rand);
		//在此处直接进行双线性插值
		zoomGray2(LRtmp[k], newWidth, newHeight, 2, 2,p[k], imgWidth, imgHeight);
		delete []LRtmp[k];
	}
	//生成参考HR，p[0]第一幅图为参考图像---------------------------------到此为止算法正常实现

	//开始迭代
    for(int iter=0;iter<iterNum;iter++)
	{
		int err_acc;
        for(int picNum=1;picNum<LRNum;picNum++)
		{     
			int i,j;
			//读入下一幅图，并与参考帧进行运动估计,通过运动补偿获得估计的运动图像f^
			int motionVect[2][MAX];
	        double DScomputations[1]; 
           //分配内存
			unsigned char* imgComp = new unsigned char[imgWidth*imgHeight];
			unsigned char* residual= new unsigned char[imgWidth*imgHeight];
 //           unsigned char residual;
		    motionEstDS( p[0],p[picNum], imgWidth, imgHeight, motionVect, DScomputations);
            motionComp(p[picNum],16,imgWidth,imgHeight,motionVect,imgComp);//补偿向p[0]估计

			//************************imgComp是对参考图像的估计********************************//
			//乘上模糊PSF后算作估计值
            Filter(imgComp,imgWidth,imgHeight,1,blur,masksize);
			// 循环遍历每一个像素
			
			for(i=0;i<imgHeight;i++)
			{
				for(j=0;j<imgWidth;j++)
                {
                    int m,n;
					unsigned char res;
					//得出估计的残差数据块
                    res = *(imgComp+i*imgWidth+j)-*(p[0]+i*imgWidth+j);
                    //根据残差反向迭代每一个像素
					err_acc += res;
					 if(res>R)
					 {					
					    for(m=0;m<5;m++)
							for(n=0;n<5;n++)
							{
								if((i+m-2<0)||(j+n-2)<0||(i+m-2>=imgHeight)||(j+n-2>=imgWidth))
								   continue;
								else
								*(residual+(i+m-2)*imgWidth+(j+n-2))+=(unsigned char)((res-R)**(blur+m*5+n)/sigmaHtr);
							}
					 }

					 else if(res<-R)
					 { 
					    for(m=0;m<5;m++)
							for(n=0;n<5;n++)
							{
								if((i+m-2<0)||(j+n-2)<0||(i+m-2>=imgHeight)||(j+n-2>=imgWidth))
								   continue;
								else
								*(residual+(i+m-2)*imgWidth+(j+n-2))+=(unsigned char)((res+R)**(blur+m*5+n)/sigmaHtr);
							}
					 }  
					 else
                          *(residual+i*imgWidth+j)=0;

				}
			}
			if(err_acc=255*R)
			break;

		    for(i=0;i<imgHeight;i++)
			{
				for(j=0;j<imgWidth;j++)
                {
                     *(p[0]+i*imgWidth+j)=*(p[0]+i*imgWidth+j)+*(residual+i*imgWidth+j);//残差的权重对图像复原效果有较大的影响
				}
			}
			delete []imgComp;
			delete []residual;
/*
            for(i=0;i<imgHeight;i++)
			{
				for(j=0;j<imgWidth;j++)
                {
					//初始化误差和
					err_acc = 0;
					unsigned char res;
					//得出估计的残差数据块
                    res = *(imgComp+i*imgWidth+j)-*(p[0]+i*imgWidth+j);
					err_acc += res;
                    //根据残差反向迭代每一个像素
					 if(res>R)
                        *(residual+i*imgWidth+j)=res-R;
					 else if(res<-R)
                        *(residual+i*imgWidth+j)=res+R;
					 else
                        *(residual+i*imgWidth+j)=0;

				}
			}
            Filter(residual,imgWidth,imgHeight,1,blur,masksize);
			//反向迭代，对参考图像做修正，下一次循环使用的是修正后的参考图像
			if(err_acc=255*R)
			break;
            for(i=0;i<imgHeight;i++)
			{
				for(j=0;j<imgWidth;j++)
                {
                     *(p[0]+i*imgWidth+j)=*(p[0]+i*imgWidth+j)+*(residual+i*imgWidth+j)*1.9649;
				}
			}
			delete []imgComp;
			delete []residual;
			*/
		}

	}

 
    //复制图像输出
    for(int i=0;i<imgHeight;i++)
	{
		for(int j=0;j<imgWidth;j++)
        {
            *(imgOut+i*imgWidth+j)=*(p[0]+i*imgWidth+j);
		}
	}
    //清空内存
	for(k=0;k<LRNum;k++)
	{
		delete []p[k];
	}
}  