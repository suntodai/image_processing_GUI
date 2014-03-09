#ifndef _INC_DIBRAW_H
#define _INC_DIBRAW_H

#include "dibapi.h"

unsigned char *DibToRaw(HGLOBAL hdib, int *width, int *height, int *biBitCount);

HDIB RawToDib(unsigned char *dataBuf, int width, int height, int biBitCount);

bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount);


unsigned char *ColorToGrey(unsigned char *colorBuf, int width, int height);


unsigned char *DibToRawZXK(HGLOBAL hdib, int *width, int *height, int *biBitCount);

HDIB RawToDibZXK(unsigned char *dataBuf, int width, int height, int biBitCount);

//����һ��ͼ���ļ�����·��������ͼ�����ݡ� 
unsigned char *readBmp(char *bmpName, int *width, int *height, int *biBitCount);
#endif