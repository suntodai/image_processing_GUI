
#include <complex>
using namespace std;

void CustomModel(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask,int dis);
void FakeColor1(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight);
void Roberts(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight);
void Kirch(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight);
void GaussSmth(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int size);
void FakeColor2(LPRGBQUAD lpPalette);
void DistortionSphere(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *data);
void RestoreSphere(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *data);
void NearNeighbor(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clrNum,float zoom);
void BilinearIn(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clrNum,float zoom);
void CubeCovolution(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clrNum,float zoom);

//正交变换
void FFT(complex<double> * TD, complex<double> * FD, int power);
void IFFT(complex<double> * FD, complex<double> * TD, int power);

//
void GeometryRecify(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight);
//作业---图像的几何配准

void ReverseClr(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int clr);
void ConvertGray(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight);
void ConvertTwo(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int threshold);

/***********************红外图像的处理**************************/
//预处理
void RowMean(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight);