#include "stdafx.h"
#include "segment.h"
#include "math.h"
//ｱﾟﾔｵｼ・・
void sobel(unsigned char *imgBuf, int width, int height, int biBitCount)
{
	unsigned char *buf=new unsigned char[width*height*biBitCount];
	int i, j, k, x, y, lineByte=width*biBitCount;
	for(i=1; i<height-1;i++){
		for(j=1; j<width-1;j++){
			for(k=0;k<biBitCount; k++){
				x=*(imgBuf+(i+1)*lineByte+(j-1)*biBitCount +k)
				  +2**(imgBuf+(i)*lineByte+(j-1)*biBitCount+ k)
				  +*(imgBuf+(i-1)*lineByte+(j-1)*biBitCount+ k)
				  -*(imgBuf+(i+1)*lineByte+(j+1)*biBitCount+ k)
				  -2**(imgBuf+(i)*lineByte+(j+1)*biBitCount+ k)
				  -*(imgBuf+(i-1)*lineByte+(j+1)*biBitCount+ k);
				y=*(imgBuf+(i+1)*lineByte+(j-1)*biBitCount +k)
					+2**(imgBuf+(i+1)*lineByte+j*biBitCount +k)
					+*(imgBuf+(i+1)*lineByte+(j+1)*biBitCount +k)
					-*(imgBuf+(i-1)*lineByte+(j-1)*biBitCount +k)
					-2**(imgBuf+(i-1)*lineByte+j*biBitCount +k)
					-*(imgBuf+(i-1)*lineByte+(j+1)*biBitCount +k);
				if(sqrt(double(x*x+y*y))<=255)
					*(buf+i*lineByte+j*biBitCount+k)=sqrt(double(x*x+y*y));
				else
					*(buf+i*lineByte+j*biBitCount+k)=255;
			}
		}
	}

	for(i=0;i<lineByte*height;i++)
		*(imgBuf+i)=*(buf+i);
	delete []buf;
}

//robot
void robot(unsigned char *imgBuf, int width, int height, int biBitCount)
{
	unsigned char *buf=new unsigned char[width*height*biBitCount];
	int i, j, k, x, y, lineByte=width*biBitCount;
	int max=0;
	for(i=1; i<height-1;i++){
		for(j=1; j<width-1;j++){
			for(k=0;k<biBitCount; k++){
				x=*(imgBuf+i*lineByte+j*biBitCount +k)
				  -*(imgBuf+(i-1)*lineByte+(j+1)*biBitCount+ k);			 
				y=*(imgBuf+i*lineByte+(j+1)*biBitCount +k)
					-*(imgBuf+(i-1)*lineByte+j*biBitCount +k);
					
				if(sqrt(double(x*x+y*y))<=255)
					*(buf+i*lineByte+j*biBitCount+k)=sqrt(double(x*x+y*y));
				else
					*(buf+i*lineByte+j*biBitCount+k)=255;
				if(*(buf+i*lineByte+j*biBitCount+k)>max)
					max=*(buf+i*lineByte+j*biBitCount+k);
			}
		}
	}

	for(i=0;i<lineByte*height;i++)
		*(imgBuf+i)=*(buf+i)*255/max;
	delete []buf;
}

//prewitt
void prewitt(unsigned char *imgBuf, int width, int height, int biBitCount)
{
unsigned char *buf=new unsigned char[width*height*biBitCount];
	int i, j, k, x, y, lineByte=width*biBitCount;
	for(i=1; i<height-1;i++){
		for(j=1; j<width-1;j++){
			for(k=0;k<biBitCount; k++){
				x=*(imgBuf+(i+1)*lineByte+(j-1)*biBitCount +k)
				  +*(imgBuf+(i)*lineByte+(j-1)*biBitCount+ k)
				  +*(imgBuf+(i-1)*lineByte+(j-1)*biBitCount+ k)
				  -*(imgBuf+(i+1)*lineByte+(j+1)*biBitCount+ k)
				  -*(imgBuf+(i)*lineByte+(j+1)*biBitCount+ k)
				  -*(imgBuf+(i-1)*lineByte+(j+1)*biBitCount+ k);
				y=*(imgBuf+(i+1)*lineByte+(j-1)*biBitCount +k)
					+*(imgBuf+(i+1)*lineByte+j*biBitCount +k)
					+*(imgBuf+(i+1)*lineByte+(j+1)*biBitCount +k)
					-*(imgBuf+(i-1)*lineByte+(j-1)*biBitCount +k)
					-*(imgBuf+(i-1)*lineByte+j*biBitCount +k)
					-*(imgBuf+(i-1)*lineByte+(j+1)*biBitCount +k);
				if(sqrt(double(x*x+y*y))<=255)
					*(buf+i*lineByte+j*biBitCount+k)=sqrt(double(x*x+y*y));
				else
					*(buf+i*lineByte+j*biBitCount+k)=255;
			}
		}
	}

	for(i=0;i<lineByte*height;i++)
		*(imgBuf+i)=*(buf+i);
	delete []buf;
}

//laplacian
void laplacian(unsigned char *imgBuf, int width, int height, int biBitCount)
{
  unsigned char *buf=new unsigned char[width*height*biBitCount];
	int i, j, k, x, lineByte=width*biBitCount;
	for(i=1; i<height-1;i++){
		for(j=1; j<width-1;j++){
			for(k=0;k<biBitCount; k++){
				x=4**(imgBuf+i*lineByte+j*biBitCount +k)
				  -*(imgBuf+(i+1)*lineByte+j*biBitCount+ k)
				  -*(imgBuf+(i-1)*lineByte+j*biBitCount+ k)
				  -*(imgBuf+i*lineByte+(j+1)*biBitCount+ k)
				  -*(imgBuf+i*lineByte+(j-1)*biBitCount+ k)	;			  
				if(x>255)
					x=255;
				if(x<0)
					x=0;			
					*(buf+i*lineByte+j*biBitCount+k)=x;
			}
		}
	}

	for(i=0;i<lineByte*height;i++)
		*(imgBuf+i)=*(buf+i);
	delete []buf;
}

//耙ﾖｵｷﾖｸ・
void ErZhiSegment(unsigned char *imgBuf, int width, int height, int thresh)
{
  for(int i=0;i<width*height;i++){
    if(*(imgBuf+i)<thresh)
      *(imgBuf+i)=0;
    else
      *(imgBuf+i)=255;
  }
	
}

//ｴ･耙ﾖｵ
int Threshold(long HistBuf[256])      /* return the threshold value   */
{
        float PHS[256];
        float A,B,D,P,RH,RM,RMEAN,RI,BMAX;
        long Tab=0;
        float EPS = (float)1.0E-10;
        int Line;
        int JTHD;

        for(Line=0;Line<=255;Line++)
            Tab+=HistBuf[Line];
		if(Tab==0)
			return 0;

        for(Line=0;Line<=255;Line++)
           PHS[Line]=(float)HistBuf[Line]/Tab;

        RM=0.0;
        for(Line=0;Line<=255;Line++){
           RI=(float)Line;
           RH=RI*PHS[Line];
           RM=RM+RH;
        }
        RMEAN=RM;
        BMAX=0.0;
        P=0.0;
        A=0.0;
        for(Line=0;Line<=254;Line++){
           RH=PHS[Line];
           P=P+RH;
           A=A+(float)Line*RH;
           B=RM*P-A;
           D = P * ((float)1.0 - P);
           if(D<EPS) continue;
           B=B*B/D;
           if(B>=BMAX){
              BMAX=B;
              JTHD=Line;
           }
        }
        JTHD=(int)((float)JTHD*1.0);
        return(JTHD);
}

//ﾓﾃｴ･耙ﾖｵﾗﾔｶｯｷﾖｸ・
void autoThreshSegment(unsigned char *imgBuf, int width, int height)
{
	int i;
	long hist[256];
	for(i=0;i<256;i++)
		hist[i]=0;
	for(i=0;i<height*width;i++)
		hist[*(imgBuf+i)]++;
	int t=Threshold(hist);
	for(i=0;i<width*height;i++){
		if(*(imgBuf+i)<t)
	    	*(imgBuf+i)=0;
		else
			*(imgBuf+i)=255;
	}
}
///ﾂﾋｲｨ
//ｾｵﾂﾋｲｨ
void meanFilter(unsigned char *imgBuf, int width, int height, int biBitCount, 
                int *mask, int masksize)
{
  unsigned char *buf=new unsigned char[width*height*biBitCount];
	int i, j, k, l, t,  x, lineByte=width*biBitCount;

  int count=0;
  for(i=0;i<masksize*masksize;i++){
    if(mask[i]==1)
      count++;
  }

	for(i=0; i<height-masksize;i++){
		for(j=0; j<width-masksize;j++){
			for(k=0;k<biBitCount; k++){
        x=0;
        for(t=0; t<masksize;t++){
          for(l=0;l<masksize;l++){
            x += mask[t*masksize+l] * *(imgBuf+(i+t)*lineByte+(j+l)*biBitCount +k);
          }
        }
					  
				*(buf+(i+masksize/2)*lineByte+(j+masksize/2)*biBitCount+k)=x/count;		
			}
		}
	}

	for(i=0;i<lineByte*height;i++)
		*(imgBuf+i)=*(buf+i);
	delete []buf;
}

//ﾖﾐﾖｵﾂﾋｲｨ
void midFilter(unsigned char *imgBuf, int width, int height, int biBitCount,
               int *mask, int masksize)
{
  unsigned char *buf=new unsigned char[width*height*biBitCount];
	int i, j, k, t, l, x, min, pos, count, lineByte=width*biBitCount;
  int array[49];
	for(i=0; i<height-masksize;i++){
		for(j=0; j<width-masksize;j++){
			for(k=0;k<biBitCount; k++){
        count=0;
        for(t=0;t<masksize;t++){
          for(l=0;l<masksize;l++)
            if(mask[t*masksize+l]==1){
              array[count]=*(imgBuf+(i+t)*lineByte+(j+l)*biBitCount +k);
              count++;
            }
        }
        //ﾅﾅﾐ・
        for(t=0;t<count-1;t++){
          min=array[t], pos=0;
          for(l=t;l<count;l++){
            if(min>array[l]){
              min=array[l];
              pos=l;
            }
          }
          if(pos!=t){
            x=array[t];
            array[t]=array[pos];
            array[pos]=x;
          }
        }
				*(buf+(i+masksize/2)*lineByte+(j+masksize/2)*biBitCount+k)=array[count/2];
				
			}
		}
	}

	for(i=0;i<lineByte*height;i++)
		*(imgBuf+i)=*(buf+i);
	delete []buf;
}

//ﾄ｣ｰ蠶ﾋｲｨ  maskﾊ菠・ｸｾｭｹ鰓ｻｻｯ
void Filter(unsigned char *imgBuf, int width, int height, int biBitCount,
               double *mask, int masksize)
{
    unsigned char *buf=new unsigned char[width*height*biBitCount];
	int i, j, k, l, t,  lineByte=width*biBitCount;
	double x;

	for(i=0; i<height-masksize;i++){
		for(j=0; j<width-masksize;j++){
			for(k=0;k<biBitCount; k++){
        x=0;
        for(t=0; t<masksize;t++){
          for(l=0;l<masksize;l++){
            x += mask[t*masksize+l] * *(imgBuf+(i+t)*lineByte+(j+l)*biBitCount +k);
          }
        }
		//ﾍｼﾏﾄﾖﾜｱﾟﾔｵﾃｻﾓﾐﾖｵ
				*(buf+(i+masksize/2)*lineByte+(j+masksize/2)*biBitCount+k)=(unsigned char)x;		
			}
		}
	}

	for(i=0;i<lineByte*height;i++)
	{
		*(imgBuf+i)=*(buf+i);
	}	
	delete []buf;
}