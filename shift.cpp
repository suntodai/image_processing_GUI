#include "stdafx.h"
#include "shift.h"
#include "math.h"
//-----重要生成缓冲区没有扩展成边长为4的倍数，所以在程序外面要扩展 
void shift(LPBYTE lpIn,LPBYTE lpOut,int width, int height, float shiftX, float shiftY)
{

	// 象素在新DIB中的坐标
	LONG	i;
	LONG	j;
	
	// 象素在源DIB中的坐标
	LONG	i0;
	LONG	j0;
	
	// 图像每行的字节数
//	LONG lineBytes;
	
	// 计算图像每行的字节数
//	lineBytes = (width+3)/4*4;

	// 每行
	for(i = 0; i < height; i++)
	{
		// 每列
		for(j = 0; j < width; j++)//保持输出内存大小和原来一样大，不扩展周边为4的倍数
		{
			// 计算该象素在源DIB中的坐标
			i0 = i - shiftY;
			j0 = j - shiftX;
			// 判断是否在源图范围内
			if( (j0 >= 0) && (j0 < width) && (i0 >= 0) && (i0 < height))
			{
				lpOut[width * i + j] = lpIn[width * i0 + j0];	
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				lpOut[width * i + j] = 255;
			}
			
		}
	}
	
}