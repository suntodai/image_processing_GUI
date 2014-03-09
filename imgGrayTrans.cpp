#include "stdafx.h"
#include "imgGrayTrans.h"

void Graytransition(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *data)
//分段灰度拉伸
{
	int i,j;
	int lineByte=(imgWidth+3)/4*4;

	double x1=data[0],y1=data[1],x2=data[2],y2=data[3];//分段点的坐标
	double slop1=y1/x1,slop2=(y2-y1)/(x2-x1),slop3=(255-y2)/(255-x2);//直线斜率
	double dis1=0,dis2=y1-slop2*x1,dis3=y2-slop3*x2;	//计算截距
	int map[256];

	for(i=0;i<256;i++)	//计算映射表
	{
		if(i<x1)
		{
			map[i]=(int)(slop1*i+dis1+0.5);
		}else if(i<x2)
		{
			map[i]=(int)(slop2*i+dis2+0.5);
		}else
		{
			map[i]=(int)(slop3*i+dis3+0.5);
		}
	}

	LPBYTE tmp;

	for(i=0;i<imgHeight;i++)
	{
		for(j=0;j<lineByte;j++)
		{
			tmp=lpIn+i*lineByte+j;
			*(lpOut+i*lineByte+j)=map[*tmp];
		}
	}
}

void RGBtransition(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *data)
{
	int linebyteRGB=(imgWidth*3+3)/4*4;
	int linebyteGrey=(imgWidth+3)/4*4;
	unsigned char *bufIn=new unsigned char[imgHeight*linebyteGrey];
	unsigned char *bufOut=new unsigned char[imgHeight*linebyteGrey];
	int i, j, k;
	for(k=0;k<3;k++){
		for(i=0;i<imgHeight;i++){
			for(j=0;j<imgWidth;j++)
				bufIn[i*linebyteGrey+j]=*(lpIn+i*linebyteRGB+j*3+k);
		}
		Graytransition(bufIn,bufOut,imgWidth,imgHeight,data);

		for(i=0;i<imgHeight;i++){
			for(j=0;j<imgWidth;j++)
				*(lpOut+i*linebyteRGB+j*3+k)=bufOut[i*linebyteGrey+j];
		}
	}
	delete []bufIn;
	delete []bufOut;
}

void PointEqual(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clrNum)
{
	int i,j;
	int linewidth=(imgWidth+3)/4*4;
	int count[256];
	double Y,map[256];
	long sum;

	LPBYTE lpTmp;

	for(i=0;i<256;i++)
	{
		count[i]=0;
		map[i]=0;
	}

	if(clrNum==256)//对每个灰度值计数
	{
		for(i=0;i<imgHeight;i++)
		{
			for(j=0;j<imgWidth;j++)
			{
				lpTmp=lpIn+i*linewidth+j;
				count[*lpTmp]++;
			}
		}
	}else if(clrNum==0)
	{
		linewidth=(3*imgWidth+3)/4*4;
		for(i=0;i<imgHeight;i++)
		{
			for(j=0;j<imgWidth;j++)
			{
				lpTmp=lpIn+i*linewidth+3*j;
				Y=0.299*(float)*(lpTmp+2)+0.587*(float)*(lpTmp+1)
					+0.114*(float)*lpTmp+0.1;
				count[(int)Y]++;
			}
		}
	}

	sum=0;
	for(i=0;i<256;i++)//计算映射表
	{
		sum+=count[i];
		map[i]=(double)sum/imgWidth/imgHeight*255+0.5;
	}
	for(i=0;i<imgHeight;i++)//赋新的灰度值
	{
		for(j=0;j<imgWidth;j++)
		{
			if(clrNum==256)
			{
				lpTmp=lpIn+i*linewidth+j;
				*(lpOut+i*linewidth+j)=(int)map[*lpTmp];
			}else
			{
				lpTmp=lpIn+i*linewidth+3*j;
				*(lpOut+i*linewidth+3*j)=(int)map[*lpTmp];
				*(lpOut+i*linewidth+3*j+1)=(int)map[*(lpTmp+1)];
				*(lpOut+i*linewidth+3*j+2)=(int)map[*(lpTmp+2)];
			}
		}
	}
}
