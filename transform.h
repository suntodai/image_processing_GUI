void fft1D(float *arrayBuf, int n);
void fft2D(unsigned char* imgBuf, int width, int height);

void ifft2D(unsigned char* imgBuf, int width, int height);

//旋转
void rotateGrey(unsigned char *imgBuf, int width, int height, int mean,
            float slope, float orgX, float orgY,
             unsigned char *rotateBuf, int outImgW, int outImgH);
void rotateRGB(unsigned char *colorBuf, int width, int height, int mean,
            float slope, float orgX, float orgY,
             unsigned char *rotateBuf, int outImgW, int outImgH);
//双线性插值缩放
void zoomGray(unsigned char *imgBuf, int width, int height, float zoomTime,
             unsigned char *zoomBuf, int zoomW, int zoomH);
void zoomRGB(unsigned char *imgBuf, int width, int height, float zoomTime,
             unsigned char *zoomBuf, int zoomW, int zoomH);
//近邻缩放
void zoomNeighbor(unsigned char *imgBuf, int width, int height, int biBitCount, float zoomTime,
             unsigned char *zoomBuf, int zoomW, int zoomH);

//宽高均可变缩放
void zoomGray2(unsigned char *imgBuf, int width, int height, float zoomTimew, float zoomTimeh,
             unsigned char *zoomBuf, int zoomW, int zoomH);

void zoomRGB2(unsigned char *imgBuf, int width, int height, float zoomTimew, float zoomTimeh,
             unsigned char *zoomBuf, int zoomW, int zoomH);

void zoomNeighbor2(unsigned char *imgBuf, int width, int height, int biBitCount, float zoomTimew, float zoomTimeh,
             unsigned char *zoomBuf, int zoomW, int zoomH);