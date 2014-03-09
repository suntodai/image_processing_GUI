#include "stdafx.h"
#include <math.h>
#include <complex>
using namespace std;

#define pai  3.1415926535898

void CustomModel(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask,int displmt)
{	
	int i,j,k,l;
	int lineByte=imgWidth;//(imgWidth+3)/4*4;

	double tmp,sum;
	
	for(i=2;i<imgHeight-2;i++)
	{
		for(j=2;j<imgWidth-2;j++)
		{
			sum=0;
			for(k=-2;k<3;k++)
			{
				for(l=-2;l<3;l++)
				{
					if(mask[5*(2+k)+l+2])
					{
						tmp=*(lpIn+(i+k)*lineByte+j+l)*mask[5*(2+k)+l+2];
						sum+=tmp;
					}
				}
			}

			sum+=displmt;
			if(sum>255)
				sum=255;
			else if(sum<0)
				sum=0;
			*(lpOut+i*lineByte+j)=(int)(sum+0.5);
		}
	}	
}

void maskProcess(unsigned char *imgBuf, int width, int height, int biBitCount, int *mask)
{
	int i, j, k;
	unsigned char *buf=new unsigned char[width*height];
	unsigned char *outBuf=new unsigned char[width*height];
	for(k=0;k<biBitCount;k++){
		for(i=0;i<width*height;i++)
			buf[i]=*(imgBuf+i*k);		
		CustomModel(buf,outBuf,width,height, mask,0);
		for(i=0;i<width*height;i++)
			*(imgBuf+i*k)=outBuf[i];
	}
	delete []outBuf;
	delete []buf;
}

void Roberts(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight)
//边缘检测,Roberts算子
{
	int i,j;
	int linewidth=(imgWidth+3)/4*4;
	int sum1,sum2,sum;

	for(i=0;i<imgHeight-1;i++)
	{
		for(j=0;j<imgWidth-1;j++)
		{
			sum1=*(lpIn+i*linewidth+j)-*(lpIn+(i+1)*linewidth+j+1);
			sum2=*(lpIn+i*linewidth+j+1)-*(lpIn+(i+1)*linewidth+j);
			sum=(int)sqrt(sum1*sum1+sum2*sum2);
			if(sum>255)
				sum=255;
			*(lpOut+i*linewidth+j)=sum;
		}
	}
}
void Kirch(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight)
//边缘检测,Kirch算子
{
	int i,j,k;
	int linewidth=(imgWidth+3)/4*4;
	int gray[8],sum1,sum2,sum,result;

	for(i=1;i<imgHeight-1;i++)
	{
		for(j=1;j<imgWidth-1;j++)
		{
			gray[0]=*(lpIn+(i-1)*linewidth+j-1);
			gray[1]=*(lpIn+(i-1)*linewidth+j);
			gray[2]=*(lpIn+(i-1)*linewidth+j+1);
			gray[3]=*(lpIn+i*linewidth+j+1);
			gray[4]=*(lpIn+(i+1)*linewidth+j+1);
			gray[5]=*(lpIn+(i+1)*linewidth+j);
			gray[6]=*(lpIn+(i+1)*linewidth+j-1);
			gray[7]=*(lpIn+i*linewidth+j-1);

			result=0;

			for(k=0;k<8;k++)
			{
				sum1=gray[k]+gray[(k+1)%8]+gray[(k+2)%8];
				sum2=gray[(k+3)%8]+gray[(k+4)%8]+gray[(k+5)%8]+gray[(k+6)%8]+gray[(k+7)%8];
				sum=5*sum1-3*sum2;
				if(sum>result)
					result=sum;
			}
			if(result>255)
				result=255;
			*(lpOut+i*linewidth+j)=result;
		}
	}
}

void GaussSmth(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int size)
{
	int i,j,k,l;
	int linewidth=(imgWidth+3)/4*4;
	int sum;
	int dis=(size-1)/2,si=size*size;

	for(i=dis;i<imgHeight-dis;i++)
	{
		for(j=dis;j<imgWidth-dis;j++)
		{
			sum=0;
			for(k=-dis;k<=dis;k++)
			{
				for(l=-dis;l<=dis;l++)
				{
					sum+=*(lpIn+(i+k)*linewidth+j+l);
				}
			}
			*(lpOut+i*linewidth+j)=sum/si;
		}
	}
}


void FakeColor1(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight)
//灰度——>彩图,8位——>24位
{
	int i,j;
	int red[256],green[256],blue[256],gray;
	int linewidthnew=(imgWidth*3+3)/4*4,
		linewidth=(imgWidth+3)/4*4;

	for(i=0;i<255;i++)//计算颜色映射表
	{
		if(i<64)
			{
				red[i]=0;
				green[i]=(int)(((float)i)/64*255+0.5);
				blue[i]=255;
			}else if(i<128)
			{
				red[i]=0;
				green[i]=255;
				blue[i]=(int)(((float)(127-i))/64*255+0.5);
			}
			else if(i<192)
			{
				red[i]=(int)(((float)(i-127))/64*255+0.5);
				green[i]=255;
				blue[i]=0;
			}else
			{
				red[i]=255;
				green[i]=(int)(((float)(255-i))/64*255+0.5);
				blue[i]=0;
			}
	}

	for(i=0;i<imgHeight;i++)//重新赋值
	{
		for(j=0;j<linewidth;j++)
		{
			gray=*(lpIn+i*linewidth+j);

			*(lpOut+i*linewidthnew+3*j)=blue[gray];
			*(lpOut+i*linewidthnew+3*j+1)=green[gray];
			*(lpOut+i*linewidthnew+3*j+2)=red[gray];
		}
	}
}

void FakeColor2(LPRGBQUAD lpPalette)
//灰度——>伪彩图,8位——>8位
{
	int i;

	for(i=0;i<255;i++)//修改调色板
	{
		/*	if(i<64)
			{
				(lpPalette+i)->rgbRed=0;
				(lpPalette+i)->rgbGreen=(int)(((float)i)/64*255);
				(lpPalette+i)->rgbBlue=255;
			}else if(i<128)
			{
				(lpPalette+i)->rgbRed=0;
				(lpPalette+i)->rgbGreen=255;
				(lpPalette+i)->rgbBlue=(int)(((float)(127-i))/64*255);
			}
			else if(i<192)
			{
				(lpPalette+i)->rgbRed=(int)(((float)(i-127))/64*255);
				(lpPalette+i)->rgbGreen=255;
				(lpPalette+i)->rgbBlue=0;
			}else
			{
				(lpPalette+i)->rgbRed=255;
				(lpPalette+i)->rgbGreen=(int)(((float)(255-i))/64*255);
				(lpPalette+i)->rgbBlue=0;
			}*/
		if(i<128)//使用升余弦函数代替直线
		{
			(lpPalette+i)->rgbRed=0;
			(lpPalette+i)->rgbGreen=(int)(255*(1+cos((2*(float)i/255-1)*pai))+0.5);
			(lpPalette+i)->rgbBlue=(int)(255*(1+cos((2*(float)i/255)*pai))+0.5);
		}else
		{
			(lpPalette+i)->rgbRed=(int)(255*(1+cos((2*(float)i/255)*pai))+0.5);
			(lpPalette+i)->rgbGreen=(int)(255*(1+cos((2*(float)i/255-1)*pai))+0.5);
			(lpPalette+i)->rgbBlue=0;
			}
	}
}


void DistortionSphere(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *data)
//球面变形
{
	int i,j,k,count;

	int radius=data[0],deep=data[1],x=data[2],y=data[3],clrNum=data[4];//输入参量

	int lineByte=(imgWidth*clrNum+3)/4*4;
	int dis0=radius*radius-deep*deep,dis,org;
	unsigned char *lpTmp=new unsigned char [imgHeight*lineByte];

	double radtmp,tmp,sita,arcLen;
	double *dDis=new double [2*radius];

	for(i=0;i<imgHeight;i++)//全图copy
	{
		for(j=0;j<lineByte;j++)
		{
			*(lpTmp+i*lineByte+j)=*(lpIn+i*lineByte+j);
		}
	}
	//先做x方向的变形,再做y方向的变形
	for(i=y-radius;i<y+radius;i++)
	{
		count=0;
		if(i<0||i>=imgHeight)
		{
			continue;
		}
		for(j=x-radius;j<x+radius;j++)
		{
			dis=(i-y)*(i-y)+(j-x)*(j-x);
			if(dis<=dis0)	//如果像素在球冠底面内部
			{
				if(count==0)//记住初始位置
					org=j;
				count++;
			}
		}
		if(count>2)
		{
			tmp=(double)count/2;			//半弦长
			radtmp=sqrt(tmp*tmp+deep*deep); //切面的半径
			sita=acos(tmp/radtmp);			//初始角
			arcLen=2*(pai-2*sita);			//*radtmp=弧长
			for(k=0;k<count;k++)
			{
				if(k+org>=0&&k+org<imgWidth)
				{
					dDis[k]=2*(acos((tmp-k)/radtmp)-sita)*count/arcLen+0.5;
					//计算映射表

					if(clrNum==1)
					{
						*(lpTmp+i*lineByte+org+k)=*(lpIn+i*lineByte+org+
														(int)dDis[k]);
					}else
					{
						*(lpTmp+i*lineByte+3*(org+k))=*(lpIn+i*lineByte+
							3*(org+(int)dDis[k]));
						*(lpTmp+i*lineByte+3*(org+k)+1)=*(lpIn+i*lineByte+
							3*(org+(int)dDis[k])+1);
						*(lpTmp+i*lineByte+3*(org+k)+2)=*(lpIn+i*lineByte+
							3*(org+(int)dDis[k])+2);
					}
					//修改相应的像素值
				}
			}
		}
	}
	//x方向的变形完成,下面做y方向的变形

	for(i=0;i<imgHeight;i++)//全图copy
	{
		for(j=0;j<lineByte;j++)
		{
			*(lpOut+i*lineByte+j)=*(lpTmp+i*lineByte+j);
		}
	}

	for(i=x-radius;i<x+radius;i++)
	{
		count=0;
		if(i<0||i>=imgHeight)
		{
			continue;
		}
		for(j=y-radius;j<y+radius;j++)
		{
			dis=(i-x)*(i-x)+(j-y)*(j-y);
			if(dis<=dis0)	//如果像素在球冠底面内部
			{
				if(count==0)//记住初始位置
					org=j;
				count++;
			}
		}
		if(count>2)
		{
			tmp=(double)count/2;			//半弦长
			radtmp=sqrt(tmp*tmp+deep*deep); //切面的半径
			sita=acos(tmp/radtmp);			//初始角
			arcLen=2*(pai-2*sita);			//*radtmp=弧长
			for(k=0;k<count;k++)
			{
				if(k+org>=0&&k+org<imgHeight)
				{
					dDis[k]=2*(acos((tmp-k)/radtmp)-sita)*count/arcLen+0.5;
					//计算映射表

					if(clrNum==1)
					{
						*(lpOut+(org+k)*lineByte+i)=*(lpTmp+
							(org+(int)dDis[k])*lineByte+i);
					}else
					{
						*(lpOut+(org+k)*lineByte+3*i)=*(lpTmp+
							(org+(int)dDis[k])*lineByte+3*i);
						*(lpOut+(org+k)*lineByte+3*i+1)=*(lpTmp+
							(org+(int)dDis[k])*lineByte+3*i+1);
						*(lpOut+(org+k)*lineByte+3*i+2)=*(lpTmp+
							(org+(int)dDis[k])*lineByte+3*i+2);
					}
					//修改相应的像素值
				}
			}
		}
	}
}

void RestoreSphere(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *data)
//恢复球面变形的图像
{	
	int i,j,k,count;

	int radius=data[0],deep=data[1],x=data[2],y=data[3],clrNum=data[4];//输入参量

	int lineByte=(imgWidth*clrNum+3)/4*4;
	int dis0=radius*radius-deep*deep,dis,org;
	unsigned char *lpTmp=new unsigned char[imgHeight*lineByte];

	double radtmp,tmp,sita,bowLen,mAngle,judge,delta;
	double *dDis=new double [2*radius];
	//先做y方向的变形,再做x方向的变形

	for(i=0;i<imgHeight;i++)//全图copy
	{
		for(j=0;j<lineByte;j++)
		{
			*(lpTmp+i*lineByte+j)=*(lpIn+i*lineByte+j);
		}
	}

	for(i=x-radius;i<x+radius;i++)
	{
		count=0;
		if(i<0||i>=imgHeight)
		{
			continue;
		}
		tmp=(i-x)*(i-x);
		for(j=y-radius;j<y+radius;j++)
		{
			dis=(int)tmp+(j-y)*(j-y);
			if(dis<=dis0)	//如果像素在球冠底面内部
			{
				if(count==0)//记住初始位置
					org=j;
				count++;
			}
		}
		radtmp=sqrt(radius*radius-tmp);				//切面的半径
		sita=asin((double)deep/radtmp);				//初始角
		delta=(1-count/radtmp/2);				//初始位置的偏移量
		mAngle=(pai-2*sita)/((double)count-1);		//等分的角度
		bowLen=2*cos(sita);							//*radtmp=弦长
		if(count>2)
		{
			for(k=0;k<count;k++)
			{
				if(k+org>=0&&k+org<imgHeight)
				{tmp=sin((k*mAngle+sita)/2);
					judge=2*tmp*tmp-delta;
					dDis[k]=judge/bowLen*count+0.5;
					//计算映射表
					
					if(clrNum==1)
					{
						if(org+dDis[k]<0||org+dDis[k]>imgHeight)
							*(lpTmp+(org+k)*lineByte+i)=0;
						else
							*(lpTmp+(org+k)*lineByte+i)=*(lpIn+
								(org+(int)dDis[k])*lineByte+i);
					}else
					{
						if(org+dDis[k]<0||org+dDis[k]>imgHeight)
						{
							*(lpTmp+(org+k)*lineByte+3*i)=0;
							*(lpTmp+(org+k)*lineByte+3*i+1)=0;
							*(lpTmp+(org+k)*lineByte+3*i+2)=0;
						}else
						{
							*(lpTmp+(org+k)*lineByte+3*i)=*(lpIn+
								(org+(int)dDis[k])*lineByte+3*i);
							*(lpTmp+(org+k)*lineByte+3*i+1)=*(lpIn+
								(org+(int)dDis[k])*lineByte+3*i+1);
							*(lpTmp+(org+k)*lineByte+3*i+2)=*(lpIn+
								(org+(int)dDis[k])*lineByte+3*i+2);
						}
					}
					//修改相应的像素值
				}
			}
		}
	}
	//上面已经做好了y方向的变形,下面做x方向的变形

	for(i=0;i<imgHeight;i++)//全图copy
	{
		for(j=0;j<lineByte;j++)
		{
			*(lpOut+i*lineByte+j)=*(lpTmp+i*lineByte+j);
		}
	}

	for(i=y-radius;i<y+radius;i++)
	{
		count=0;
		if(i<0||i>=imgHeight)
		{
			continue;
		}
		tmp=(i-y)*(i-y);
		for(j=x-radius;j<x+radius;j++)
		{
			dis=(int)tmp+(j-x)*(j-x);
			if(dis<=dis0)	//如果像素在球冠底面内部
			{
				if(count==0)//记住初始位置
					org=j;
				count++;
			}
		}
		radtmp=sqrt(radius*radius-tmp);				//切面的半径
		sita=asin((double)deep/radtmp);				//初始角
		delta=(1-count/radtmp/2);					//初始位置的偏移量
		mAngle=(pai-2*sita)/((double)count-1);		//等分的角度
		bowLen=2*cos(sita);							//*radtmp=弦长
		if(count>2)
		{
			for(k=0;k<count;k++)
			{
				if(k+org>=0&&k+org<imgWidth)
				{
					tmp=sin((k*mAngle+sita)/2);
					judge=2*tmp*tmp-delta;
					dDis[k]=judge/bowLen*count+0.5;
					//计算映射表
					
					if(clrNum==1)
					{
						if(org+dDis[k]<0||org+dDis[k]>imgWidth)
							*(lpOut+i*lineByte+org+k)=0;
						else
							*(lpOut+i*lineByte+org+k)=*(lpTmp+i*lineByte+org+
														(int)dDis[k]);
					}else
					{
						if(org+dDis[k]<0||org+dDis[k]>imgWidth)
						{
							*(lpOut+i*lineByte+3*(org+k))=0;
							*(lpOut+i*lineByte+3*(org+k)+1)=0;
							*(lpOut+i*lineByte+3*(org+k)+2)=0;
						}else
						{
							*(lpOut+i*lineByte+3*(org+k))=*(lpTmp+i*lineByte+
								3*(org+(int)dDis[k]));
							*(lpOut+i*lineByte+3*(org+k)+1)=*(lpTmp+i*lineByte+
								3*(org+(int)dDis[k])+1);
							*(lpOut+i*lineByte+3*(org+k)+2)=*(lpTmp+i*lineByte+
								3*(org+(int)dDis[k])+2);
						}
					}
					//修改相应的像素值
				}
			}
		}
	}

}




void ConvertTwo(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int threshold)
//转为二值图像--目前用一刀切,其它方法慢慢加
{
	int i,j;
	int lineByte=(imgWidth+3)/4*4;
	int dis;
	

	for(i=0;i<imgHeight;i++)
	{
		for(j=0;j<lineByte;j++)
		{
			dis=i*lineByte+j;
			if(*(lpIn+dis)<threshold)
			{
				*(lpOut+dis)=0;
			}else
			{
				*(lpOut+dis)=255;
			}
		}
	}
}



void RowMean(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight)
//行均值相减
{
	int i,j;
	int lineByte=(imgWidth+3)/4*4;
	int rowSum,rowMean,tmp,position;


	for(i=0;i<imgHeight;i++)
	{
		if(i!=0)
		{
			rowMean=rowSum/imgWidth;
		}
		rowSum=0;
		for(j=0;j<imgWidth;j++)
		{
			position=i*lineByte+j;
			if(i!=0)
			{
				tmp=*(lpIn+position)-rowMean+100;
				if(tmp<0)
					tmp=0;
				if(tmp>255)
					tmp=255;
				*(lpOut+position)=tmp;
				
			}
			rowSum+=*(lpIn+position);
		}
	}			

}

void ReverseClr(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clr)
//反色
{
	int i,j;
	int lineByte=(imgWidth*clr+3)/4*4;

	for(i=0;i<imgHeight;i++)
	{
		for(j=0;j<lineByte;j++)
		{
			*(lpOut+i*lineByte+j)=255-*(lpIn+i*lineByte+j);
		}
	}
}

void ConvertGray(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight)
//24位RGB-->8位灰度图
{
	int i,j;
	int lineByte1=(imgWidth  +3)/4*4,
		lineByte3=(imgWidth*3+3)/4*4;
	LPBYTE point;
	double Y;

	for(i=0;i<imgHeight;i++)
	{
		for(j=0;j<imgWidth;j++)
		{
			point=lpIn+i*lineByte3+3*j;
			Y=0.299*(double)*(point+2)+0.587*(double)*(point+1)
						+0.114*(double)*point+0.1;
			*(lpOut+i*lineByte1+j)=(BYTE)Y;
		}
	}
}

void NearNeighbor(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clrNum,float zoom)
//最近邻缩放
{
	int i,j;
	int heightNew=(int)(imgHeight*zoom),widthNew=(int)(imgWidth*zoom);
	int lineByte=(imgWidth*clrNum+3)/4*4,lineByteNew=(widthNew*clrNum+3)/4*4;
	int xPos,yPos;

	for(i=0;i<heightNew;i++)
	{
		for(j=0;j<widthNew;j++)
		{
			yPos=(int)(i/zoom+0.5);
			xPos=(int)(j/zoom+0.5);
			if(xPos>=imgWidth)
				xPos=imgWidth-1;
			if(yPos>=imgHeight)
				yPos=imgHeight-1;
			if(clrNum==1)
			{
				*(lpOut+i*lineByteNew+j)=*(lpIn+yPos*lineByte+xPos);
			}else
			{
				*(lpOut+i*lineByteNew+3*j  )=*(lpIn+yPos*lineByte+3*xPos);
				*(lpOut+i*lineByteNew+3*j+1)=*(lpIn+yPos*lineByte+3*xPos+1);
				*(lpOut+i*lineByteNew+3*j+2)=*(lpIn+yPos*lineByte+3*xPos+2);
			}
		}
	}
}


void BilinearIn(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clrNum,float zoom)
//双线性插值
{
	int i,j,k;
	int heightNew=(int)(imgHeight*zoom),widthNew=(int)(imgWidth*zoom);
	int lineByte=(imgWidth*clrNum+3)/4*4,lineByteNew=(widthNew*clrNum+3)/4*4;
	double xTmp,yTmp,f00,f01,f10,f11,gray,xDelta,yDelta;
	int xn,yn;

	if(clrNum==1)
	{
		for(i=0;i<heightNew;i++)
		{
			for(j=0;j<widthNew;j++)
			{
				xTmp=j/zoom;
				yTmp=i/zoom;

				xn=(int)xTmp;
				yn=(int)yTmp;

				xDelta=(xTmp-xn);
				yDelta=(yTmp-yn);

				f00=*(lpIn+yn*lineByte+xn);
				f01=*(lpIn+(yn+1)*lineByte+xn);
				f10=*(lpIn+yn*lineByte+xn+1);
				f11=*(lpIn+(yn+1)*lineByte+xn+1);
				gray=f00+(f10-f00)*xDelta+(f01-f00)*yDelta+
					(f11+f00-f01-f10)*xDelta*yDelta+0.5;

				*(lpOut+i*lineByteNew+j)=(int)gray;
			}
		}
	}else
	{
		for(i=0;i<heightNew;i++)
		{
			for(j=0;j<widthNew;j++)
			{
				xTmp=j/zoom;
				yTmp=i/zoom;

				xn=(int)xTmp;
				yn=(int)yTmp;

				xDelta=(xTmp-xn);
				yDelta=(yTmp-(int)yTmp);
				for(k=0;k<3;k++)
				{
					f00=*(lpIn+yn*lineByte+xn*3+k);
					f01=*(lpIn+(yn+1)*lineByte+xn*3+k);
					f10=*(lpIn+yn*lineByte+(xn+1)*3+k);
					f11=*(lpIn+(yn+1)*lineByte+(xn+1)*3+k);
					gray=f00+(f10-f00)*xDelta+(f01-f00)*yDelta+
						(f11+f00-f01-f10)*xDelta*yDelta+0.5;

					*(lpOut+i*lineByteNew+j*3+k)=(int)gray;
				}
			}
		}
	}	
}

double InterPolation(double x,double *xsh)//sinc(x)函数的三次多项式逼近
{
	double sum=0;
	double x2=x*x;
	double x3=x2*x;

	sum=(xsh[3]-xsh[2]+xsh[1]-xsh[0])*x3;
	sum-=(xsh[3]-xsh[2]+2*(xsh[1]-xsh[0]))*x2;
	sum+=(xsh[2]-xsh[0])*x+xsh[1];
	
	return sum;
		
}
void CubeCovolution(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clrNum,float zoom)
// 立方卷积缩放
{
	int i,j,k,l,n;
	int heightNew=(int)(imgHeight*zoom),widthNew=(int)(imgWidth*zoom);
	int lineByte=(imgWidth*clrNum+3)/4*4,lineByteNew=(widthNew*clrNum+3)/4*4;
	double xTmp,yTmp,xDelta,yDelta,gray;
	double xsh1[4],xsh2[4];
	int xn,yn,xnTmp,ynTmp;

	if(clrNum==1)
	{
		for(i=1;i<heightNew-2;i++)
		{
			for(j=1;j<widthNew-2;j++)
			{
				xTmp=j/zoom;
				yTmp=i/zoom;

				xn=(int)xTmp;
				yn=(int)yTmp;

				xDelta=(xTmp-xn);
				yDelta=(yTmp-yn);
				for(k=-1;k<3;k++)
				{
					for(l=-1;l<3;l++)
					{
						xnTmp=xn+k;
						ynTmp=yn+l;
						if(ynTmp<0)
							ynTmp=0;
						else if(xnTmp<0)
							xnTmp=0;
						else if(yn>=imgHeight)
							ynTmp=imgHeight-1;
						else if(xnTmp>=imgWidth)
							ynTmp=imgWidth-1;
						xsh1[l+1]=*(lpIn+ynTmp*lineByte+xnTmp);
					}
					xsh2[k+1]=InterPolation(yDelta,xsh1);
				}
				
				gray=(int)InterPolation(xDelta,xsh2);
				if(gray<0)
					gray=0;
				else if(gray>255)
					gray=255;
				*(lpOut+i*lineByteNew+j)=(int)gray;
			}
		}
	}else
	{
		for(i=1;i<heightNew-2;i++)
		{
			for(j=1;j<widthNew-2;j++)
			{
				xTmp=j/zoom;
				yTmp=i/zoom;

				xn=(int)xTmp;
				yn=(int)yTmp;

				xDelta=(xTmp-xn);
				yDelta=(yTmp-yn);
				for(n=0;n<3;n++)
				{
					for(k=-1;k<3;k++)
					{
						for(l=-1;l<3;l++)
						{							
							xnTmp=xn+k;
							ynTmp=yn+l;
							if(ynTmp<0)
								ynTmp=0;
							else if(xnTmp<0)
								xnTmp=0;
							else if(yn>=imgHeight)
								ynTmp=imgHeight-1;
							else if(xnTmp>=imgWidth)
								ynTmp=imgWidth-1;

							xsh1[l+1]=*(lpIn+ynTmp*lineByte+xnTmp*3+n);
						}
						xsh2[k+1]=InterPolation(yDelta,xsh1);
					}
				
					gray=(int)InterPolation(xDelta,xsh2);
					if(gray<0)
						gray=0;
					else if(gray>255)
						gray=255;
					*(lpOut+i*lineByteNew+j*3+n)=(int)gray;
				}
			}
		}
	}
}

void GeometryRecify(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight)
{
	int i,j,k;

/********************最小二乘法求变换系数K1,K2*********************/
	double sum;
	double U[7][6],M[6][6];
	double u[7]={98,68,253,120,326,381,510},v[7]={450,372,339,201,182,115,421};
	double x[7]={298,386,292,498,369,384,51},y[7]={30,72,227,225,387,476,375};

	for(i=0;i<7;i++)//matrix U
	{
		U[i][0]=1;
		U[i][1]=u[i];
		U[i][2]=v[i];
		U[i][3]=u[i]*u[i];
		U[i][4]=v[i]*v[i];
		U[i][5]=u[i]*v[i];
	}

	for(i=0;i<6;i++)//matrix UT*U
	{
		for(j=0;j<6;j++)
		{
			sum=0;
			for(k=0;k<7;k++)
				sum+=U[k][i]*U[k][j];
			M[i][j]=sum;
		}
	}
/*******************************************************************************/
//k1=M-1*UT*x       k2=M-1*UT*y
//矩阵求逆好麻烦,用Matlab算出结果

	double k1[6]={751.8484,-0.7165,-0.8433, -0.0000397,-0.0000584,0.0001877};
	double k2[6]={261.0038,0.6170,-0.4973,0.0002856,-0.00033934,-0.000025157};

	int lineByte=(imgWidth*3+3)/4*4;
	double xNew,yNew;
	int xInt,yInt;

	for(i=0;i<imgHeight;i++)
	{
		for(j=0;j<imgWidth;j++)
		{
			xNew=k1[0]+k1[1]*j+k1[2]*i+k1[3]*j*j+k1[4]*i*i+k1[5]*i*j;
			yNew=k2[0]+k2[1]*j+k2[2]*i+k2[3]*j*j+k2[4]*i*i+k2[5]*i*j;
			xInt=(int)xNew;
			yInt=(int)yNew;
			if(xInt<0||yInt<0||xInt>=imgWidth||yInt>=imgHeight)
				continue;
			for(k=0;k<3;k++)
				*(lpOut+i*lineByte+j*3+k)=*(lpIn+yInt*lineByte+xInt*3+k);
		}
	}
}

void FFT(complex<double> * TD, complex<double> * FD, int power)
//基2时域抽取蝶形流图算法(一维)
{
	int i,j,k;
	int tmp,size;
	double angle;
	LONG count=1<<power;

	complex<double> *W,*M,*X;

	W=new complex<double>[count/2];//权值
	M=new complex<double>[count];

	angle=2*pai/count;		//旋转因子的基数角度

	for(i=0;i<count/2;i++)
		W[i]=complex<double>(cos(-i*angle),sin(-i*angle));

	for(k=0;k<power;k++)
	{
		for(j=0;j<1<<k;j++)
		{
			size=1<<(power-k);

			for(i=0;i<size/2;i++)
			{
				tmp=j*size;

				//蝶形算法
				M[i+tmp]=TD[i+tmp]+TD[i+tmp+size/2];
				M[i+tmp+size/2]=(TD[i+tmp]-TD[i+tmp+size/2])*W[i*(1<<k)];
			}
		}

		//交换地址
		X=TD;
		TD=M;
		M=X;
	}

	//对码位倒序重新排序
	for(i=0;i<count;i++)
	{
		tmp=0;

		//重新排序
		for(j=0;j<power;j++)
		{
			if(i&(1<<j))
				tmp+=1<<(power-j-1);
		}

		//排序结果
		FD[i]=TD[tmp];
	}

	delete W;
	delete M;
}

void IFFT(complex<double> * FD, complex<double> * TD, int power)
//逆变换得蝶形流图算法(一维)
{
	int i;
	LONG count=1<<power;
	
	//求共轭
	for(i=0;i<count;i++)
		FD[i]=complex<double>(FD[i].real(),-FD[i].imag());

	//调用蝶形算法
	FFT(FD,TD,power);

	for(i=0;i<count;i++)
		TD[i]=complex<double>(TD[i].real()/count,-TD[i].imag()/count);
}
