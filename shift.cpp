#include "stdafx.h"
#include "shift.h"
#include "math.h"
//-----��Ҫ���ɻ�����û����չ�ɱ߳�Ϊ4�ı����������ڳ�������Ҫ��չ 
void shift(LPBYTE lpIn,LPBYTE lpOut,int width, int height, float shiftX, float shiftY)
{

	// ��������DIB�е�����
	LONG	i;
	LONG	j;
	
	// ������ԴDIB�е�����
	LONG	i0;
	LONG	j0;
	
	// ͼ��ÿ�е��ֽ���
//	LONG lineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
//	lineBytes = (width+3)/4*4;

	// ÿ��
	for(i = 0; i < height; i++)
	{
		// ÿ��
		for(j = 0; j < width; j++)//��������ڴ��С��ԭ��һ���󣬲���չ�ܱ�Ϊ4�ı���
		{
			// �����������ԴDIB�е�����
			i0 = i - shiftY;
			j0 = j - shiftX;
			// �ж��Ƿ���Դͼ��Χ��
			if( (j0 >= 0) && (j0 < width) && (i0 >= 0) && (i0 < height))
			{
				lpOut[width * i + j] = lpIn[width * i0 + j0];	
			}
			else
			{
				// ����Դͼ��û�е����أ�ֱ�Ӹ�ֵΪ255
				lpOut[width * i + j] = 255;
			}
			
		}
	}
	
}