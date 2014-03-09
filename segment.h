//边缘检测
void sobel(unsigned char *imgBuf, int width, int height, int biBitCount);
void robot(unsigned char *imgBuf, int width, int height, int biBitCount);
void prewitt(unsigned char *imgBuf, int width, int height, int biBitCount);
void laplacian(unsigned char *imgBuf, int width, int height, int biBitCount);

//二值分割
void ErZhiSegment(unsigned char *imgBuf, int width, int height, int thresh);

//大津阈值分割
void autoThreshSegment(unsigned char *imgBuf, int width, int height);
//均值平滑
void meanFilter(unsigned char *imgBuf, int width, int height, int biBitCount, 
                int *mask, int masksize);
//中值平滑
void midFilter(unsigned char *imgBuf, int width, int height, int biBitCount,
               int *mask, int masksize);
//模板
void Filter(unsigned char *imgBuf, int width, int height, int biBitCount,
               double *mask, int masksize);