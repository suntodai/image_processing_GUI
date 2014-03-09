//灰度线性拉伸
void Graytransition(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *data);
//彩色线性拉伸
void RGBtransition(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *data);
//直方图均衡
void PointEqual(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clrNum);
