#include "stdafx.h"
#include "noise.h"
#include "math.h"
#define PI 3.1415926

void GaussNoise(LPBYTE lpIn, LPBYTE lpOut, int width, int height, float mean, float variance)
{

//	LPBYTE lpTmp;
//	int lineBytes = (width +3)/4*4;
	//ѭ������
	long i;
	long j;
	//ת��Ϊͼ�񣬼���
	double NoisePoint;
	//��ʱ����
	unsigned char temp, MaxNum;
    double rand1,rand2;

	//ȷ����һ������
    MaxNum = 0.0;
	for (j = 0;j < height ;j++)
	{
		for(i = 0;i < width ;i++)
		{
			temp = *(lpIn + width * j + i);
			//ѡ���һ������
			if( MaxNum < temp)
				MaxNum = temp;
		}
	}
	
	//����α���������
	srand((unsigned)time(NULL));


	unsigned char lptmp;
	//ת��Ϊͼ�񣬲�����α�������
	for (j = 0;j < height ;j++)
	{
		for(i = 0;i < width ;i++)
		{
			// ����������
			rand1=rand()/32767.0;   /*[0��1]���ȷֲ������ */
            rand2=rand()/32767.0;   /*[0��1]���ȷֲ������ */
            NoisePoint=sqrt(-2*log(rand1))*cos(2*3.1415926*rand2);  /*��˹�ֲ������*/
			NoisePoint = NoisePoint*sqrt(variance) + mean;

			// ָ��Դͼ������j�У���i�����ص�ָ��			
 			lptmp = *((unsigned char *)lpIn + width * j + i);
	
			// ʱ����룬�洢����ֵ
	//	    *lpOut = (unsigned char)(*lpOut)*255.0/(double)MaxNum + NoisePoint*255.0/(double)MaxNum;
//			*lpOut = (unsigned char)(((double)*lpOut + NoisePoint));// enlarge the noise 100 times
			lpOut[width * j + i] = (unsigned char)(((double)lptmp + NoisePoint));// enlarge the noise 100 times
			//�������ֵ����ֱ�Ӹ�ֵ255
			if(lpOut[width * j + i] > 255)
				lpOut[width * j + i] = 255 ;
			if(lpOut[width * j + i] < 0)
                lpOut[width * j + i] = 0;

		}
	}


}