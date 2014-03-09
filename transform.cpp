#include "stdafx.h"
#include "transform.h"
#include <cmath>
#define PI 3.1415926
float *fftBuf=0;
void fft1D(float *arrayBuf, int n)
{
	int i, j, k, r;
	float *buf1=new float[n*2];
	for(i=0;i<n*2;i++)
		buf1[i]=arrayBuf[i];

	float *buf2=new float[n*2];
	int t1,t2;
	for(r=1;pow(2.0,r)<n;r++){
		t1=pow(2.0,r);
		t2=pow(2.0,r-1);
		for(k=0;k<t1;k++){
			for(i=0;i<n/t1;i++){				
				buf2[k*n/t1*2+i*2+0]=buf1[k/2*n/t2*2+(i*2+k%2)*2+0];
				buf2[k*n/t1*2+i*2+1]=buf1[k/2*n/t2*2+(i*2+k%2)*2+1];
			}
		}
		for(i=0;i<n*2;i++)
			buf1[i]=buf2[i];
	}
	float c,s,sh,xu;
	for(r=1;pow(2.0,r)<=n;r++){
		t1=pow(2.0,r);
		for(k=0;k<n/t1;k++){
			for(i=t1/2;i<t1;i++){
			//	c=cos(-2*PI*(i-t1/2)/t1);
			//	s=sin(-2*PI*(i-t1/2)/t1);
				c=cos(2*PI*(-i+t1/2+n/2)/t1);				
				s=sin(2*PI*(-i+t1/2+n/2)/t1);
				buf1[k*t1*2+i*2+0]= buf2[k*t1*2+i*2+0]*c - buf2[k*t1*2+i*2+1]*s;				
				buf1[k*t1*2+i*2+1]=buf2[k*t1*2+i*2+1]*c+buf2[k*t1*2+i*2+0]*s;
			}
		}
		
		for(k=0; k<n/t1; k++){
			for(i=0;i<t1/2;i++){
				buf2[k*t1*2+i*2+0]= buf1[k*t1*2+i*2+0]+buf1[k*t1*2+(i+t1/2)*2+0];
				buf2[k*t1*2+i*2+1]= buf1[k*t1*2+i*2+1]+buf1[k*t1*2+(i+t1/2)*2+1];
			}
			for(i=t1/2;i<t1;i++){
				buf2[k*t1*2+i*2+0]= buf1[k*t1*2+(i-t1/2)*2+0]-buf1[k*t1*2+i*2+0];
				buf2[k*t1*2+i*2+1]= buf1[k*t1*2+(i-t1/2)*2+1]-buf1[k*t1*2+i*2+1];
			}
		}

		for(i=0;i<n*2;i++)
			buf1[i]=buf2[i];
	}
	
	for(i=0;i<n*2;i++)
			arrayBuf[i]=buf2[i];

	delete[]buf2;
	delete[]buf1;
}

void fft2D(unsigned char* imgBuf, int width, int height)
{
	int i, j, u, v;
	float *buf=new float[width*height*2];
	for(i=0;i<width*height;i++){
		buf[i*2+0]=imgBuf[i];
		buf[i*2+1]=0;
	}

	float *array=new float[height*2];
	for(u=0;u<width;u++){
		for(v=0;v<height;v++){
			array[v*2+0]=buf[v*width*2+u*2+0];
			array[v*2+1]=buf[v*width*2+u*2+1];
		}
		fft1D(array, width);
		for(v=0;v<height;v++){
			buf[v*width*2+u*2+0]=array[v*2+0];
			buf[v*width*2+u*2+1]=array[v*2+1];
		}
	}
	delete []array;

	for(v=0;v<height;v++){
		fft1D(buf+v*width*2, width);
	}

	float *buf1=new float[width*height];
	for(i=0;i<width*height;i++)
		buf1[i]= sqrt(buf[i*2+0]*buf[i*2+0]+buf[i*2+1]*buf[i*2+1]);

	for(i=0;i<width*height;i++){
		if(buf1[i]/2500>255)
		   imgBuf[i]= 255;
		else imgBuf[i]=buf1[i]/2500;
	}
	fftBuf=buf;

	delete[]buf1;

}


void ifft1D(float *arrayBuf, int n)
{
	int i, j, k, r;
	float *buf1=new float[n*2];
	for(i=0;i<n*2;i++)
		buf1[i]=arrayBuf[i];

	float *buf2=new float[n*2];
	int t1,t2;
	for(r=1;pow(2.0,r)<n;r++){
		t1=pow(2.0,r);
		t2=pow(2.0,r-1);
		for(k=0;k<t1;k++){
			for(i=0;i<n/t1;i++){				
				buf2[k*n/t1*2+i*2+0]=buf1[k/2*n/t2*2+(i*2+k%2)*2+0];
				buf2[k*n/t1*2+i*2+1]=buf1[k/2*n/t2*2+(i*2+k%2)*2+1];
			}
		}
		for(i=0;i<n*2;i++)
			buf1[i]=buf2[i];
	}
	float c,s,sh,xu;
	for(r=1;pow(2.0,r)<=n;r++){
		t1=pow(2.0,r);
		for(k=0;k<n/t1;k++){
			for(i=t1/2;i<t1;i++){
			//	c=cos(-2*PI*(i-t1/2)/t1);
			//	s=sin(-2*PI*(i-t1/2)/t1);
				c=cos(2*PI*(-i+t1/2)/t1);				
				s=sin(2*PI*(-i+t1/2)/t1);
				buf1[k*t1*2+i*2+0]= buf2[k*t1*2+i*2+0]*c - buf2[k*t1*2+i*2+1]*s;				
				buf1[k*t1*2+i*2+1]=buf2[k*t1*2+i*2+1]*c+buf2[k*t1*2+i*2+0]*s;
			}
		}
		
		for(k=0; k<n/t1; k++){
			for(i=0;i<t1/2;i++){
				buf2[k*t1*2+i*2+0]= buf1[k*t1*2+i*2+0]+buf1[k*t1*2+(i+t1/2)*2+0];
				buf2[k*t1*2+i*2+1]= buf1[k*t1*2+i*2+1]+buf1[k*t1*2+(i+t1/2)*2+1];
			}
			for(i=t1/2;i<t1;i++){
				buf2[k*t1*2+i*2+0]= buf1[k*t1*2+(i-t1/2)*2+0]-buf1[k*t1*2+i*2+0];
				buf2[k*t1*2+i*2+1]= buf1[k*t1*2+(i-t1/2)*2+1]-buf1[k*t1*2+i*2+1];
			}
		}

		for(i=0;i<n*2;i++)
			buf1[i]=buf2[i];
	}
	
	for(i=0;i<n*2;i++)
			arrayBuf[i]=buf2[i];

	delete[]buf2;
	delete[]buf1;
}

void ifft2D(unsigned char* imgBuf, int width, int height)
{	
	if(!fftBuf)
		return;

//	cutNoise(fftBuf, width, height);
	int i, j, u, v;
	float *buf=fftBuf;
	for(i=0;i<width*height;i++)
		buf[i*2+1] = -buf[i*2+1];

	float *array=new float[height*2];
	for(u=0;u<width;u++){
		for(v=0;v<height;v++){
			array[v*2+0]=buf[v*width*2+u*2+0];
			array[v*2+1]=buf[v*width*2+u*2+1];
		}
		ifft1D(array, width);
		for(v=0;v<height;v++){
			buf[v*width*2+u*2+0]=array[v*2+0];
			buf[v*width*2+u*2+1]=array[v*2+1];
		}
	}
	delete []array;

	for(v=0;v<height;v++){
		ifft1D(buf+v*width*2, width);
	}

	float *buf1=new float[width*height];
	for(i=0;i<width*height;i++){
		int j=sqrt(buf[i*2+0]*buf[i*2+0]+buf[i*2+1]*buf[i*2+1]);
		buf1[i]= j/(width*height);
	}
	int max=buf1[0], min=buf1[0];
	for(i=0;i<width*height;i++){
		if(buf1[i]>max) max=buf1[i];
		if(buf1[i]<min) min=buf1[i];
	}
	if(max<255){
		for(i=0;i<width*height;i++)
		   imgBuf[i]=buf1[i];
	}
	else{
		for(i=0;i<width*height;i++){
			if(buf1[i]>255)
				imgBuf[i]=255;
	    	else imgBuf[i]=buf1[i];//*255/max;
		}
	}

	delete[]buf;
	delete[]buf1;

}




//Ğı×ª

//Ë«ÏßĞÔ²åÖµĞı×ª
//»Ò¶ÈÍ¼ÏE
void rotateGrey(unsigned char *imgBuf, int width, int height, int mean,
            float slope, float orgX, float orgY,
             unsigned char *rotateBuf, int outImgW, int outImgH)
{
  float alfa = atan(slope);
  float SIN=	sin(alfa);
  float COS= cos(alfa);	
  //È·¶¨Ğı×ªµE
  int dx =width/2*(1-cos(alfa)) + height/2*sin(alfa);
  int dy =width/2*(0-sin(alfa)) + height/2*(1-cos(alfa));

  //Ğı×ªºóµÄĞÂÍ¼³¤¡¢¿E
  int rotateW =outImgW;
  int rotateH =outImgH;
  int insertBeginX=width/2- rotateW/2;
  int insertBeginY=height/2- rotateH/2;

  //²åÖµ¹«Ê½ËùĞè²ÎÊı
  double ku=insertBeginX*COS-insertBeginY * SIN+orgX+dx;
  double kv=insertBeginX*SIN+insertBeginY * COS+orgY+dy;
  double cu1=COS, cu2=SIN;
  double cv1=SIN, cv2=COS;

  int Line, Pixel;
  double fu, fv, a, b, F1, F2;
  int Iu,Iv;
  //Ë«ÏßĞÔ²åÖµ
  for(Line=0; Line< rotateH; Line++)
  {
		for(Pixel=0; Pixel< rotateW ; Pixel++)
		{     
          fu=Pixel*cu1 - Line*cu2 + ku;//Éú³ÉĞı×ªºóµÄĞÂ×ø±ê£¬fuÊÇĞĞ£¬fvÊÇÁĞ
          fv = Pixel*cv1 + Line*cv2 + kv;
          if((fv<1)||(fv>height-1) || (fu<1)||(fu>width-1)) //fv fuÊÇĞı×ªºóµÄĞÂ×ø±EÎ¿¼
            *(rotateBuf + Line * rotateW + Pixel) = mean;
          else  
		  {
            Iu=(int)fu,  Iv=(int)fv;//Ğı×ªºóĞĞÁĞµÄÕûÊı×ø±E
            a=fu-Iu,  b=fv-Iv;       
            F1 = (1-b)**(imgBuf+ Iv*width+ Iu) + b**(imgBuf+ (Iv+1)*width+ Iu);
            F2 = (1-b)**(imgBuf+ Iv*width+ Iu+1) + b**(imgBuf+ (Iv+1)*width+ Iu+1);
            *(rotateBuf + Line * rotateW + Pixel) = (unsigned char)((1-a)*F1 + a*F2);       
		  }
		}
	}

  //Ğı×ªºóµÄĞÂÍ¼³¤¡¢¿E

}

//²ÊÉ«Í¼ÏñĞı×ª¡¢Æ½ÒÆºÍËõ·Å
//·µ»ØÖµ£ºĞı×ª¡¢Æ½ÒÆ¡¢Ëõ·ÅºóµÄÊı¾İÖ¸ÕE¬ÈôÎª0ÔòÊ§°Ü
void rotateRGB(unsigned char *colorBuf, int width, int height, int mean,
            float slope, float orgX, float orgY,
             unsigned char *rotateBuf, int outImgW, int outImgH)
{
  float alfa= atan(slope);
  float SIN= sin(alfa);
  float COS= cos(alfa);	
  //È·¶¨Ğı×ªµE
  //È·¶¨Ğı×ªµE
  int dx =width/2*(1-cos(alfa)) + height/2*sin(alfa);
  int dy =width/2*(0-sin(alfa)) + height/2*(1-cos(alfa));

  //Ğı×ªºóµÄĞÂÍ¼³¤¡¢¿E
  int rotateW =outImgW;
  int rotateH =outImgH;

  int insertBeginX=width/2- rotateW/2;
  int insertBeginY=height/2- rotateH/2;

  //²åÖµ¹«Ê½ËùĞè²ÎÊı
  double ku=insertBeginX*COS-insertBeginY * SIN+orgX+dx;
  double kv=insertBeginX*SIN+insertBeginY * COS+orgY+dy;
  double cu1=COS, cu2=SIN;
  double cv1=SIN, cv2=COS;

  int Line, Pixel, k;
  float fu, fv, a, b, F1, F2;
  int Iu,Iv;
  //Ë«ÏßĞÔ²åÖµ
  for(Line=0; Line< rotateH; Line++){
		for(Pixel=0; Pixel< rotateW ; Pixel++){
      fu=Pixel*cu1 - Line*cu2 + ku;
      fv = Pixel*cv1 + Line*cv2 + kv;
      if((fv<1)||(fv>height-1) || (fu<1)||(fu>width-1)){
        for(k=0;k<3;k++)
          *(rotateBuf + Line * rotateW*3 + Pixel*3 + k) = mean;
      }
      else   
      {
        Iu=(int)fu;
        Iv=(int)fv;
        a=fu-Iu;
        b=fv-Iv;
        for(k=0;k<3;k++)
        {
          F1 = (1-b)**(colorBuf+ Iv*width*3+ Iu*3 + k) + b**(colorBuf+ (Iv+1)*width*3+ Iu*3 + k);
          F2 = (1-b)**(colorBuf+ Iv*width*3+ (Iu+1)*3 + k) + b**(colorBuf+ (Iv+1)*width*3+ (Iu+1)*3 + k);
          *(rotateBuf + Line * rotateW*3 + Pixel*3+k) =(unsigned char)((1-a)*F1 + a*F2);
        }
          
      }
     
		}
	}

}
//*****************************************************************************************************
//»Ò¶ÈÍ¼ÏóËõ·Å-----ÖØÒªÉú³É»º³åÇøÃ»ÓĞÀ©Õ¹³É±ß³¤Îª4µÄ±¶Êı£¬ËùÒÔÔÚ³ÌĞòÍâÃæÒªÀ©Õ¹
//---ÖØÒª£¬ÕâÀEidthÓ¦¸ÃÊÇÊäÈE¼ÏñÊı¾İµÄlinebytes
void zoomGray2(unsigned char *imgBuf, int width, int height, float zoomTimew, float zoomTimeh,
             unsigned char *zoomBuf, int zoomW, int zoomH)
{

  int Line, Pixel;
  double fu, fv, a, b, F1, F2;
  int Iu,Iv;
  //Ë«ÏßĞÔ²åÖµ
  for(Line=0; Line< zoomH; Line++){
		for(Pixel=0; Pixel< zoomW ; Pixel++){     
      fu=Pixel/zoomTimew;
      fv=Line/zoomTimeh;
      if((fv<1)||(fv>height-1) || (fu<1)||(fu>width-1)) 
          *(zoomBuf + Line * zoomW + Pixel) = 255;
      else  
      {
        Iu=(int)fu,  Iv=(int)fv;
        a=fu-Iu,  b=fv-Iv;       
        F1 = (1-b)**(imgBuf+ Iv*width+ Iu) + b**(imgBuf+ (Iv+1)*width+ Iu);
        F2 = (1-b)**(imgBuf+ Iv*width+ Iu+1) + b**(imgBuf+ (Iv+1)*width+ Iu+1);
        *(zoomBuf + Line * zoomW + Pixel) = (unsigned char)((1-a)*F1 + a*F2);       
      }
		}
	}

}

//½EÚËõ·Å
void zoomNeighbor2(unsigned char *imgBuf, int width, int height, int biBitCount, float zoomTimew, float zoomTimeh,
             unsigned char *zoomBuf, int zoomW, int zoomH)
{
  int Line, Pixel, k;
  int fu, fv;
  //Ë«ÏßĞÔ²åÖµ
  for(Line=0; Line< zoomH; Line++){
		for(Pixel=0; Pixel< zoomW ; Pixel++){   
      fu=Pixel/zoomTimew+0.5;
      fv=Line/zoomTimeh+0.5;
      if((fv<0)||(fv>height-1) || (fu<0)||(fu>width-1)){
        for(k=0;k<biBitCount;k++)
          *(zoomBuf + Line * zoomW*biBitCount + Pixel*biBitCount + k) = 255;
      }
      else   
      {
        for(k=0;k<biBitCount;k++)
          *(zoomBuf + Line * zoomW*biBitCount + Pixel*biBitCount+k) =*(imgBuf+ fv*width*biBitCount+ fu*biBitCount + k);
      }
     
		}
	}
  
}

void zoomRGB2(unsigned char *imgBuf, int width, int height, float zoomTimew, float zoomTimeh,
             unsigned char *zoomBuf, int zoomW, int zoomH)
{
  int Line, Pixel, k;
  double fu, fv, a, b, F1, F2;
  int Iu,Iv;
  //Ë«ÏßĞÔ²åÖµ
  for(Line=0; Line< zoomH; Line++){
		for(Pixel=0; Pixel< zoomW ; Pixel++){   
      fu=Pixel/zoomTimew;
      fv=Line/zoomTimeh;
      if((fv<1)||(fv>height-1) || (fu<1)||(fu>width-1)){
        for(k=0;k<3;k++)
          *(zoomBuf + Line * zoomW*3 + Pixel*3 + k) = 255;
      }
      else   
      {
        Iu=(int)fu;
        Iv=(int)fv;
        a=fu-Iu;
        b=fv-Iv;
        for(k=0;k<3;k++)
        {
          F1 = (1-b)**(imgBuf+ Iv*width*3+ Iu*3 + k) + b**(imgBuf+ (Iv+1)*width*3+ Iu*3 + k);
          F2 = (1-b)**(imgBuf+ Iv*width*3+ (Iu+1)*3 + k) + b**(imgBuf+ (Iv+1)*width*3+ (Iu+1)*3 + k);
          *(zoomBuf + Line * zoomW*3 + Pixel*3+k) =(unsigned char)((1-a)*F1 + a*F2);
        }
          
      }
     
		}
	}
  
}
//*************************************************************************************************
//»Ò¶ÈÍ¼ÏóËõ·Å
void zoomGray(unsigned char *imgBuf, int width, int height, float zoomTime,
             unsigned char *zoomBuf, int zoomW, int zoomH)
{

  int Line, Pixel;
  double fu, fv, a, b, F1, F2;
  int Iu,Iv;
  //Ë«ÏßĞÔ²åÖµ
  for(Line=0; Line< zoomH; Line++){
		for(Pixel=0; Pixel< zoomW ; Pixel++){     
      fu=Pixel/zoomTime;
      fv=Line/zoomTime;
      if((fv<1)||(fv>height-1) || (fu<1)||(fu>width-1)) 
          *(zoomBuf + Line * zoomW + Pixel) = 255;
      else  
      {
        Iu=(int)fu,  Iv=(int)fv;
        a=fu-Iu,  b=fv-Iv;       
        F1 = (1-b)**(imgBuf+ Iv*width+ Iu) + b**(imgBuf+ (Iv+1)*width+ Iu);
        F2 = (1-b)**(imgBuf+ Iv*width+ Iu+1) + b**(imgBuf+ (Iv+1)*width+ Iu+1);
        *(zoomBuf + Line * zoomW + Pixel) = (unsigned char)((1-a)*F1 + a*F2);       
      }
		}
	}

}

//²ÊÉ«Í¼ÏñËõ·Å
void zoomRGB(unsigned char *imgBuf, int width, int height, float zoomTime,
             unsigned char *zoomBuf, int zoomW, int zoomH)
{
  int Line, Pixel, k;
  double fu, fv, a, b, F1, F2;
  int Iu,Iv;
  //Ë«ÏßĞÔ²åÖµ
  for(Line=0; Line< zoomH; Line++){
		for(Pixel=0; Pixel< zoomW ; Pixel++){   
      fu=Pixel/zoomTime;
      fv=Line/zoomTime;
      if((fv<1)||(fv>height-1) || (fu<1)||(fu>width-1)){
        for(k=0;k<3;k++)
          *(zoomBuf + Line * zoomW*3 + Pixel*3 + k) = 255;
      }
      else   
      {
        Iu=(int)fu;
        Iv=(int)fv;
        a=fu-Iu;
        b=fv-Iv;
        for(k=0;k<3;k++)
        {
          F1 = (1-b)**(imgBuf+ Iv*width*3+ Iu*3 + k) + b**(imgBuf+ (Iv+1)*width*3+ Iu*3 + k);
          F2 = (1-b)**(imgBuf+ Iv*width*3+ (Iu+1)*3 + k) + b**(imgBuf+ (Iv+1)*width*3+ (Iu+1)*3 + k);
          *(zoomBuf + Line * zoomW*3 + Pixel*3+k) =(unsigned char)((1-a)*F1 + a*F2);
        }
          
      }
     
		}
	}
  
}

//½EÚËõ·Å
void zoomNeighbor(unsigned char *imgBuf, int width, int height, int biBitCount, float zoomTime,
             unsigned char *zoomBuf, int zoomW, int zoomH)
{
  int Line, Pixel, k;
  int fu, fv;
  //Ë«ÏßĞÔ²åÖµ
  for(Line=0; Line< zoomH; Line++){
		for(Pixel=0; Pixel< zoomW ; Pixel++){   
      fu=Pixel/zoomTime+0.5;
      fv=Line/zoomTime+0.5;
      if((fv<0)||(fv>height-1) || (fu<0)||(fu>width-1)){
        for(k=0;k<biBitCount;k++)
          *(zoomBuf + Line * zoomW*biBitCount + Pixel*biBitCount + k) = 255;
      }
      else   
      {
        for(k=0;k<biBitCount;k++)
          *(zoomBuf + Line * zoomW*biBitCount + Pixel*biBitCount+k) =*(imgBuf+ fv*width*biBitCount+ fu*biBitCount + k);
      }
     
		}
	}
  
}