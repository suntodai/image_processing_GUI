#include "stdafx.h"
#include "morphology.h" 
void Terode(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask)
//��ֵ��̬ѧ��ʴ����,����Ϊ��ɫ,��ɫΪĿ��
{
	int i,j,k,l;
	int lineByte=(imgWidth+3)/4*4;
	int dis,dis0,judge;

	for(i=0;i<imgHeight;i++)//ȫͼcopy
	{
		for(j=0;j<lineByte;j++)
		{
			*(lpOut+i*lineByte+j)=*(lpIn+i*lineByte+j);
		}
	}

	for(i=2;i<imgHeight-2;i++)
	{
		for(j=2;j<imgWidth-2;j++)
		{			
			judge=1;
			for(k=-2;k<3;k++)
			{
				for(l=-2;l<3;l++)
				{
					if(mask[5*(2+k)+l+2])
					{
						dis=(i+k)*lineByte+j+l;
						if(!*(lpIn+dis))
							judge=0;	//��־�ṹԪ�ز�ƥ��
					}
				}
			}

			dis0=i*lineByte+j;

			if(judge)
				*(lpOut+dis0)=255;
			else
				*(lpOut+dis0)=0;
		}
	}
}

void Texpand(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask)
//��ֵ��̬ѧ����,����Ϊ��ɫ,��ɫΪĿ��
{
	int i,j,k,l;
	int lineByte=(imgWidth+3)/4*4;
	int dis,tmp;

	for(i=0;i<imgHeight;i++)//ȫͼcopy
	{
		for(j=0;j<lineByte;j++)
		{
			*(lpOut+i*lineByte+j)=*(lpIn+i*lineByte+j);
		}
	}

	for(i=2;i<imgHeight-2;i++)
	{
		for(j=2;j<imgWidth-2;j++)
		{
			tmp=*(lpIn+i*lineByte+j);

			if(tmp)
			{
				for(k=-2;k<3;k++)
				{
					for(l=-2;l<3;l++)
					{
						if(mask[5*(2+k)+l+2])
						{
							dis=(i+k)*lineByte+j+l;
							*(lpOut+dis)=255;
						}
					}
				}
			}
		}
	}
}

void GrayErosion(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask)
//�Ҷȸ�ʴ����
{
	int i,j,k,l;
	int lineByte=(imgWidth+3)/4*4;
	int gray,tmp;

	unsigned char *lpTmp=new unsigned char [(imgHeight+4)*(lineByte+4)];

	for(i=0;i<imgHeight+4;i++)//ȫͼcopy,��2���صĻҶ�Ϊ255������
	{
		for(j=0;j<lineByte+4;j++)
		{
			if(i<3||i>imgHeight+1||j<3||j>lineByte+1)
				*(lpTmp+i*(lineByte+4)+j)=255;
			else
				*(lpTmp+i*(lineByte+4)+j)=*(lpIn+(i-2)*lineByte+j-2);
		}
	}


	for(i=2;i<imgHeight+2;i++)
	{
		for(j=2;j<lineByte+2;j++)
		{
			gray=255;
			for(k=-2;k<3;k++)
			{
				for(l=-2;l<3;l++)
				{
					if(mask[5*(2+k)+l+2])
					{
						tmp=*(lpTmp+(i+k)*(lineByte+4)+j+l)-mask[5*(2+k)+l+2];
						if(tmp<gray)		//����Сֵ
							gray=tmp;
					}
				}
			}
			if(gray<0)
				*(lpOut+(i-2)*lineByte+j-2)=0;
			else
				*(lpOut+(i-2)*lineByte+j-2)=gray;
		}
	}
  	delete []lpTmp;
}

void GrayDilation(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask)
//�Ҷ���������
{
	int i,j,k,l;
	int lineByte=(imgWidth+3)/4*4;
	int gray,tmp;
	unsigned char *lpTmp=new unsigned char [(imgHeight+4)*(lineByte+4)];


	for(i=0;i<imgHeight+4;i++)//ȫͼcopy,��2���صĻҶ�Ϊ0�ĺڱ�
	{
		for(j=0;j<lineByte+4;j++)
		{
			if(i<3||i>imgHeight+1||j<3||j>lineByte+1)
				*(lpTmp+i*(lineByte+4)+j)=0;
			else
				*(lpTmp+i*(lineByte+4)+j)=*(lpIn+(i-2)*lineByte+j-2);
		}
	}


	for(i=2;i<imgHeight+2;i++)
	{
		for(j=2;j<imgWidth+2;j++)
		{
			gray=0;
			for(k=-2;k<3;k++)
			{
				for(l=-2;l<3;l++)
				{
					if(mask[5*(2+k)+l+2])
					{
						tmp=*(lpTmp+(i+k)*(lineByte+4)+j+l)+mask[5*(2+k)+l+2];
						if(tmp>gray)		//�����ֵ
							gray=tmp;
					}
				}
			}
			if(gray>255)
				*(lpOut+(i-2)*lineByte+j-2)=255;
			else
				*(lpOut+(i-2)*lineByte+j-2)=gray;
		}
	}
	delete []lpTmp;
}
void MorphGrad(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask)
{
	int i,j;
	int lineByte=(imgWidth+3)/4*4;
	int dis,result;

	unsigned char *lpGrad1=new unsigned char [imgHeight*lineByte];
	unsigned char *lpGrad2=new unsigned char [imgHeight*lineByte];

	//��ʴ����
	GrayErosion((LPBYTE)lpIn,(LPBYTE)lpGrad1,imgWidth,imgHeight,mask);

	//��������
	GrayDilation((LPBYTE)lpIn,(LPBYTE)lpGrad2,imgWidth,imgHeight,mask);

	for(i=0;i<imgHeight;i++)//������̬ѧ�ݶ�
	{
		for(j=0;j<lineByte;j++)
		{
			dis=i*lineByte+j;
			result=*(lpGrad2+dis)-*(lpGrad1+dis);
			if(result)
				*(lpOut+dis)=result;
			else
				*(lpOut+dis)=0;
		}
	}
  delete []lpGrad1;
  delete []lpGrad2;
}

void TopHatPeak(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask)
{
  int i,j;
	int lineByte=(imgWidth+3)/4*4;
	int dis,result;

	unsigned char *lpGrad=new unsigned char [imgHeight*lineByte];

	//��ʴ����
	GrayErosion((LPBYTE)lpIn,(LPBYTE)lpGrad,imgWidth,imgHeight,mask);
  GrayDilation((LPBYTE)lpGrad,(LPBYTE)lpOut,imgWidth,imgHeight,mask);

	for(i=0;i<imgHeight;i++)//���㲨��
	{
		for(j=0;j<lineByte;j++)
		{
			dis=i*lineByte+j;
				*(lpOut+dis)=*(lpIn+dis)-*(lpOut+dis);
		}
	}
  delete[]lpGrad;
}

void TopHatVally(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask)
{
  int i,j;
	int lineByte=(imgWidth+3)/4*4;
	int dis,result;

	unsigned char *lpGrad=new unsigned char [imgHeight*lineByte];

	//��ʴ����
	GrayDilation((LPBYTE)lpIn,(LPBYTE)lpGrad,imgWidth,imgHeight,mask);
  GrayErosion((LPBYTE)lpGrad,(LPBYTE)lpOut,imgWidth,imgHeight,mask);

	for(i=0;i<imgHeight;i++)//���㲨��
	{
		for(j=0;j<lineByte;j++)
		{
			dis=i*lineByte+j;
				*(lpOut+dis)=*(lpOut+dis)-*(lpIn+dis);
		}
	}
  delete[]lpGrad;
}

void TopHatPeakVally(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask)
{
  int i,j;
	int lineByte=(imgWidth+3)/4*4;
	int dis,result;

	unsigned char *lpGrad1=new unsigned char [imgHeight*lineByte];
  unsigned char *lpGrad2=new unsigned char [imgHeight*lineByte];

	//������
	GrayDilation((LPBYTE)lpIn,(LPBYTE)lpGrad1,imgWidth,imgHeight,mask);
  GrayErosion((LPBYTE)lpGrad1,(LPBYTE)lpOut,imgWidth,imgHeight,mask);

  //������
  GrayErosion((LPBYTE)lpIn,(LPBYTE)lpGrad1,imgWidth,imgHeight,mask);
  GrayDilation((LPBYTE)lpGrad1,(LPBYTE)lpGrad2,imgWidth,imgHeight,mask);

	for(i=0;i<imgHeight;i++)//���㲨��
	{
		for(j=0;j<lineByte;j++)
		{
			dis=i*lineByte+j;
				*(lpOut+dis)=*(lpOut+dis)-*(lpGrad2+dis);
		}
	}
  delete[]lpGrad1;
  delete[]lpGrad2;
}