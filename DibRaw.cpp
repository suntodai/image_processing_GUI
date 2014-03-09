#include "stdafx.h"
#include "DibRaw.h"

unsigned char *DibToRaw(HGLOBAL hdib, int *width, int *height, int *biBitCount)
{
  LPSTR	lpDIB = (LPSTR)::GlobalLock(hdib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  int w = phead->biWidth;
  int h = phead->biHeight;
  int b = phead->biBitCount/8;
  int lineByte=(w * b+3)/4*4;
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);

  int lineByteNew= w * b;
  unsigned char *dataBuf=new unsigned char[h * lineByteNew];
  unsigned char *p=dataBuf+(h-1) * lineByteNew;

  for(int i=0; i<h;i++)
  {
    for(int j=0;j<lineByteNew;j++)
    {
      *(p+j)=*(lpDIBBits+j);
    }
    p -= lineByteNew;
    lpDIBBits += lineByte;
  }

  ::GlobalUnlock(hdib); 

  *width = w;
  *height = h;
  *biBitCount = b;
  return dataBuf;
}

HDIB RawToDib(unsigned char *dataBuf, int width, int height, int biBitCount)
{
	int palettesize;
  if(biBitCount==1) palettesize=1024;
  else palettesize=0; 

  int lineByte=(width*biBitCount+3)/4*4;

  HANDLE hdib=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palettesize+height*lineByte);
  LPSTR lpDIB = (LPSTR) ::GlobalLock(hdib);

  // 填写文件头
  LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  phead->biBitCount=biBitCount*8;
  phead->biClrImportant=0;
  phead->biClrUsed=0;
  phead->biCompression=0;
  phead->biHeight=height;
  phead->biPlanes=1;
  phead->biSize=40;
  phead->biSizeImage=0;
  phead->biWidth=width;
  phead->biXPelsPerMeter=7872;
  phead->biYPelsPerMeter=7872;

  //调色板拷贝
  unsigned char *pPalette=(unsigned char*)(lpDIB+sizeof(BITMAPINFOHEADER));
  if(palettesize==1024){
    for(int i=0;i<256;i++)
    {
      *(pPalette+0)=i;
      *(pPalette+1)=i;
      *(pPalette+2)=i;
      *(pPalette+3)=0;
      pPalette += 4;
    }
  }
  //数据拷贝
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
  unsigned char* pData=dataBuf+(height-1)*width*biBitCount;
  for(int i=0; i<height;i++)
  {
    for(int j=0; j<width*biBitCount;j++)
    {
      *(lpDIBBits+j)=*(pData+j);
    }
    lpDIBBits+=lineByte;
    pData -= width*biBitCount;
  }

  ::GlobalUnlock(hdib);
  return (HDIB)hdib;

}


unsigned char *DibToRawZXK(HGLOBAL hdib, int *width, int *height, int *biBitCount)
{
  LPSTR	lpDIB = (LPSTR)::GlobalLock(hdib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  int w = phead->biWidth;
  int h = phead->biHeight;
	int b = phead->biBitCount/8;
  int lineByte=(w * b+3)/4*4;
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);

  int lineByteNew= w * b;
  unsigned char *dataBuf=new unsigned char[h * lineByteNew];
  unsigned char *p=dataBuf+(h-1) * lineByteNew;

  if (b == 1)
  {
	for(int i=0; i<h;i++)
	{
		for(int j=0;j<w;j++)
		{
			*(p+j)=*(lpDIBBits+j);
		}
		p -= lineByteNew;
		lpDIBBits += lineByte;
	}
  }
  else if (b == 3)
  {
	for(int i=0; i<h;i++)
	{
		for(int j=0;j<w;j++)
		{
			*(p+j*3)=*(lpDIBBits+j*3+2);
			*(p+j*3+1)=*(lpDIBBits+j*3+1);
			*(p+j*3+2)=*(lpDIBBits+j*3);
		}
		p -= lineByteNew;
		lpDIBBits += lineByte;
	}
  }
  else
  {
	  ::GlobalUnlock(hdib); 
	  return NULL;
  }

  ::GlobalUnlock(hdib); 

  *width = w;
  *height = h;
  *biBitCount = b;
  return dataBuf;
}

HDIB RawToDibZXK(unsigned char *dataBuf, int width, int height, int biBitCount)
{
	int palettesize;
  if(biBitCount==1) palettesize=1024;
  else palettesize=0; 

  int lineByte=(width*biBitCount+3)/4*4;

  HANDLE hdib=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palettesize+height*lineByte);
  LPSTR lpDIB = (LPSTR) ::GlobalLock(hdib);

  // 填写文件头
  LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  phead->biBitCount=biBitCount*8;
  phead->biClrImportant=0;
  phead->biClrUsed=0;
  phead->biCompression=0;
  phead->biHeight=height;
  phead->biPlanes=1;
  phead->biSize=40;
  phead->biSizeImage=0;
  phead->biWidth=width;
  phead->biXPelsPerMeter=7872;
  phead->biYPelsPerMeter=7872;

  //调色板拷贝
  unsigned char *pPalette=(unsigned char*)(lpDIB+sizeof(BITMAPINFOHEADER));
  if(palettesize==1024){
    for(int i=0;i<256;i++)
    {
      *(pPalette+0)=i;
      *(pPalette+1)=i;
      *(pPalette+2)=i;
      *(pPalette+3)=0;
      pPalette += 4;
    }
  }
  //数据拷贝
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
  unsigned char* pData=dataBuf+(height-1)*width*biBitCount;
  if (biBitCount == 1)
  {
	for(int i=0; i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
	      *(lpDIBBits+j)=*(pData+j);
		}
	    lpDIBBits+=lineByte;
		pData -= width*biBitCount;
	}
  }
  else
  {
	int i;
	for(i=0; i<2;i++)
	{
		for(int j=0;j<width;j++)
		{
	      //*(lpDIBBits+j*3)=*(pData+j*3+1);
	      //*(lpDIBBits+j*3+1)=*(pData+j*3);
	      //*(lpDIBBits+j*3+2)=*(pData+j*3+2);
		  if (j == width -1)
		  {
			*(lpDIBBits+j*3)=*(pData+(j-1)*3+4);
			*(lpDIBBits+j*3+1)=*(pData+(j-1)*3+3);
			*(lpDIBBits+j*3+2)=*(pData+(j-1)*3+2);
		  }
		  else
		  {
			*(lpDIBBits+j*3)=*(pData+j*3+4);
			*(lpDIBBits+j*3+1)=*(pData+j*3+3);
			*(lpDIBBits+j*3+2)=*(pData+j*3+2);
		  }
		}
	    lpDIBBits+=lineByte;
	}
	for(i=2; i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
	      //*(lpDIBBits+j*3)=*(pData+j*3+1);
	      //*(lpDIBBits+j*3+1)=*(pData+j*3);
	      //*(lpDIBBits+j*3+2)=*(pData+j*3+2);
		  if (j == width -1)
		  {
			*(lpDIBBits+j*3)=*(pData+(j-1)*3+4);
			*(lpDIBBits+j*3+1)=*(pData+(j-1)*3+3);
			*(lpDIBBits+j*3+2)=*(pData+(j-1)*3+2);
		  }
		  else
		  {
			*(lpDIBBits+j*3)=*(pData+j*3+4);
			*(lpDIBBits+j*3+1)=*(pData+j*3+3);
			*(lpDIBBits+j*3+2)=*(pData+j*3+2);
		  }
		}
	    lpDIBBits+=lineByte;
		pData -= width*biBitCount;
	}
  }

  ::GlobalUnlock(hdib);
  return (HDIB)hdib;

}

//给定一个图像文件及其路径，读入图像数据。 
unsigned char *readBmp(char *bmpName, int *width, int *height, int *biBitCount)
{
  FILE *fp=fopen(bmpName,"rb");
  if(fp==0) return 0;
  fseek(fp, sizeof(BITMAPFILEHEADER),0);

  int w, h, b;
  BITMAPINFOHEADER head;
  fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); 
  w = head.biWidth;
  h = head.biHeight;
	b = head.biBitCount/8;
  int lineByte=(w * b+3)/4*4;

  if(b==1)
    fseek(fp, 1024,1);
  unsigned char *imgBuf=new unsigned char[w * h * b];
  for(int i=0;i<h;i++)
  {
    fread(imgBuf+(h-i-1)*w*b,w*b, 1,fp);
    fseek(fp, lineByte-w*b, 1);
  }
  fclose(fp);

  *width=w,  *height=h, *biBitCount=b;

  return imgBuf;
}


bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount)
{
  
  int palettesize=0;
  if(biBitCount==1) palettesize=1024;

  int lineByte=(width * biBitCount+3)/4*4;
  FILE *fp=fopen(bmpName,"wb");
  if(fp==0) return 0;

  BITMAPFILEHEADER fileHead;
  fileHead.bfType = 0x4D42;
  fileHead.bfSize= 
    sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ palettesize + lineByte*height;
  fileHead.bfReserved1 = 0;
  fileHead.bfReserved2 = 0;
  fileHead.bfOffBits=54+palettesize;
  fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
 
  // 填写文件头
  BITMAPINFOHEADER head; 
  head.biBitCount=biBitCount*8;
  head.biClrImportant=0;
  head.biClrUsed=0;
  head.biCompression=0;
  head.biHeight=height;
  head.biPlanes=1;
  head.biSize=40;
  head.biSizeImage=lineByte*height;
  head.biWidth=width;
  head.biXPelsPerMeter=0;
  head.biYPelsPerMeter=0;
  int yy=sizeof(BITMAPINFOHEADER);
  fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);

  //调色板拷贝  
  if(palettesize==1024)
  {
    unsigned char palette[1024];
    for(int i=0;i<256;i++)
    {
      *(palette+i*4+0)=i;
      *(palette+i*4+1)=i;
      *(palette+i*4+2)=i;
      *(palette+i*4+3)=0;     
    }
    fwrite(palette, 1024,1, fp);
  }
  
  unsigned char *buf=new unsigned char[height*lineByte];
  for(int i=0;i<height;i++)
  {
    for(int j=0;j<width*biBitCount; j++)
      *(buf+i*lineByte+j)=*(imgBuf+(height-1-i)*width*biBitCount+j);
  }
  
  fwrite(buf, height*lineByte, 1, fp);
    
  delete []buf;

  fclose(fp);

 return 1;
}
