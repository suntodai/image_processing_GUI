//形态学处理
//二值腐蚀
void Terode(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//二值膨胀
void Texpand(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//灰值腐蚀
void GrayErosion(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//灰值膨胀
void GrayDilation(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//形态学梯度
void MorphGrad(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//波锋检测
void TopHatPeak(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//波谷检测
void TopHatVally(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);

