#include "stdafx.h"
#include "noise.h"
#include "math.h"
#define PI 3.1415926

void GaussNoise(LPBYTE lpIn, LPBYTE lpOut, int width, int height, float mean, float variance)
{

//	LPBYTE lpTmp;
//	int lineBytes = (width +3)/4*4;
	//循环变量
	long i;
	long j;
	//转换为图像，加噪
	double NoisePoint;
	//临时变量
	unsigned char temp, MaxNum;
    double rand1,rand2;

	//确定归一化因子
    MaxNum = 0.0;
	for (j = 0;j < height ;j++)
	{
		for(i = 0;i < width ;i++)
		{
			temp = *(lpIn + width * j + i);
			//选择归一化因子
			if( MaxNum < temp)
				MaxNum = temp;
		}
	}
	
	//生成伪随机数种子
	srand((unsigned)time(NULL));


	unsigned char lptmp;
	//转换为图像，并加入伪随机噪声
	for (j = 0;j < height ;j++)
	{
		for(i = 0;i < width ;i++)
		{
			// 产生的噪声
			rand1=rand()/32767.0;   /*[0，1]均匀分布随机数 */
            rand2=rand()/32767.0;   /*[0，1]均匀分布随机数 */
            NoisePoint=sqrt(-2*log(rand1))*cos(2*3.1415926*rand2);  /*高斯分布随机数*/
			NoisePoint = NoisePoint*sqrt(variance) + mean;

			// 指向源图像倒数第j行，第i个象素的指针			
 			lptmp = *((unsigned char *)lpIn + width * j + i);
	
			// 时域加噪，存储象素值
	//	    *lpOut = (unsigned char)(*lpOut)*255.0/(double)MaxNum + NoisePoint*255.0/(double)MaxNum;
//			*lpOut = (unsigned char)(((double)*lpOut + NoisePoint));// enlarge the noise 100 times
			lpOut[width * j + i] = (unsigned char)(((double)lptmp + NoisePoint));// enlarge the noise 100 times
			//如果象素值过大，直接赋值255
			if(lpOut[width * j + i] > 255)
				lpOut[width * j + i] = 255 ;
			if(lpOut[width * j + i] < 0)
                lpOut[width * j + i] = 0;

		}
	}


}