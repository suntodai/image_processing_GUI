// demoView.cpp : implementation of the CDemoView class
//

#include "stdafx.h"
#include "demo.h"

#include "demoDoc.h"
#include "demoView.h"
#include"math.h"
#include "MainFrm.h"

#include "transform.h"
#include "ZoomTimesDlg.h"
#include "RotateDlg.h"
#include "segment.h"
#include "MaskDlg.h"
#include "DefineMaskDlg.h"
#include "threshDlg.h"
#include "imgGrayTrans.h"
#include "linearStretch.h"
#include "morphologyDlg.h"
#include "morphology.h"
#include "noise.h"
#include "shift.h"
#include "GenLR.h"
#include "motionES.h"
#include "POCS.h"
#include "noiseDlg.h"
//#define MAX 65536
#define  MAX 262144

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CDemoView, CScrollView)
	//{{AFX_MSG_MAP(CDemoView)
	ON_COMMAND(ID_SOBEL, OnSobel)
	ON_COMMAND(id_FFT, OnFft)
	ON_COMMAND(id_IFFT, OnIfft)
	ON_COMMAND(id_Zoom, OnZoom)
	ON_COMMAND(id_RotateTrans, OnRotateTrans)
	ON_COMMAND(ID_Robot, OnRobot)
	ON_COMMAND(id_prewitt, Onprewitt)
	ON_COMMAND(id_Laplacian, OnLaplacian)
	ON_COMMAND(id_MeanFilter, OnMeanFilter)
	ON_COMMAND(id_MidleFilter, OnMidleFilter)
	ON_COMMAND(id_ThreshSegment, OnThreshSegment)
	ON_COMMAND(id_DajinThresh, OnDajinThresh)
	ON_COMMAND(id_ImgReverse, OnImgReverse)
	ON_COMMAND(id_RGBToGray, OnRGBToGray)
	ON_COMMAND(id_linearTrans, OnlinearTrans)
	ON_COMMAND(id_histAver, OnhistAver)
	ON_COMMAND(id_ErosionErzhi, OnErosionErzhi)
	ON_COMMAND(id_ErzhiExpand, OnErzhiExpand)
	ON_COMMAND(id_ErzhiOpen, OnErzhiOpen)
	ON_COMMAND(id_ErzhClose, OnErzhClose)
	ON_COMMAND(id_GrayErose, OnGrayErose)
	ON_COMMAND(id_GrayExpand, OnGrayExpand)
	ON_COMMAND(id_GrayOpen, OnGrayOpen)
	ON_COMMAND(id_GreyClose, OnGreyClose)
	ON_COMMAND(id_MorphologyGrad, OnMorphologyGrad)
	ON_COMMAND(id_TopHatPeak, OnTopHatPeak)
	ON_COMMAND(id_TopHatVally, OnTopHatVally)
	ON_COMMAND(id_TophatPeakVally, OnTophatPeakVally)
	ON_COMMAND(ID_ZoomSmall, OnZoomSmall)
	ON_COMMAND(ID_ZoomLarge, OnZoomLarge)
	ON_COMMAND(ID_GaussNoise, OnGaussNoise)
	ON_COMMAND(ID_Rotate, OnRotate)
	ON_COMMAND(ID_Shift, OnShift)
	ON_COMMAND(ID_GenLR, OnGenLR)
	ON_COMMAND(ID_TSS, OnTss)
	ON_COMMAND(ID_DS, OnDs)
	ON_COMMAND(ID_POCS, OnPocs)
	ON_COMMAND(ID_Blur, OnBlur)
	ON_COMMAND(ID_OPEN_SEQ, OnOpenSeq)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoView construction/destruction

CDemoView::CDemoView()
{
	// TODO: add construction code here

}

CDemoView::~CDemoView()
{
}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView drawing

void CDemoView::OnDraw(CDC* pDC)
{
	CDemoDoc* pDoc = GetDocument();

	HDIB hDIB = pDoc->GetHDIB();
	if (hDIB != NULL)
	{
		LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
		int cxDIB = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
		int cyDIB = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
		::GlobalUnlock((HGLOBAL) hDIB);
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest;
		if (pDC->IsPrinting())   // printer DC
		{
			// get size of printer page (in pixels)
			int cxPage = pDC->GetDeviceCaps(HORZRES);
			int cyPage = pDC->GetDeviceCaps(VERTRES);
			// get printer pixels per inch
			int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

			//
			// Best Fit case -- create a rectangle which preserves
			// the DIB's aspect ratio, and fills the page horizontally.
			//
			// The formula in the "->bottom" field below calculates the Y
			// position of the printed bitmap, based on the size of the
			// bitmap, the width of the page, and the relative size of
			// a printed pixel (cyInch / cxInch).
			//
			rcDest.top = rcDest.left = 0;
			rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch)
					/ ((double)cxDIB * cxInch));
			rcDest.right = cxPage;

      // º∆À„¥Ú”°ÕºœÒŒª÷√£®¥π÷±æ”÷–£©
			int temp = cyPage - (rcDest.bottom - rcDest.top);
			rcDest.bottom += temp/2;
			rcDest.top += temp/2;
		}
		else   // not printer DC
		{
			rcDest = rcDIB;
		}
		::PaintDIB(pDC->m_hDC, &rcDest, pDoc->GetHDIB(),
			&rcDIB, pDoc->GetDocPalette());
	}
}

void CDemoView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	ASSERT(GetDocument() != NULL);
	SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());

	/*
	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	*/
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView printing

BOOL CDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView diagnostics

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoView message handlers

void CDemoView::OnSobel() 
{
  CDemoDoc *pDoc=GetDocument();
  HDIB dib=pDoc->GetHDIB();

  LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
  LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  int w = ::DIBWidth(lpDIB);
  int h = phead->biHeight;
  int b = phead->biBitCount/8;

  int lineByte=(w * b+3)/4*4;
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);

  int  i, j;
  unsigned char *buf=new unsigned char[w*h*b];
  for(i=0;i<h;i++){
	  for(j=0;j<w*b;j++){
		  *(buf+i*w*b+j)=*(lpDIBBits+i*lineByte+j);
	  }
  }
  sobel(buf, w, h, b);
  for(i=0;i<h;i++){
	  for(j=0;j<w*b;j++){
		  *(lpDIBBits+i*lineByte+j)=*(buf+i*w*b+j);
	  }
  }

  ::GlobalUnlock(dib); 
  
  delete []buf;
  Invalidate();
}

void CDemoView::OnFft() 
{
	
CDemoDoc *pDoc=GetDocument();
  HDIB dib=pDoc->GetHDIB();

  LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
  LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  int w = phead->biWidth;
  int h = phead->biHeight;
  int b = phead->biBitCount/8;
  if(b==3)
  {
	  ::MessageBox(0,"÷ª¥¶¿˙◊“∂»ÕºœÛ£°",NULL,MB_OK);
	  ::GlobalUnlock(dib); 
	  return;
  }
  int lineByte=(w * b+3)/4*4;
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
  
  int bufLong=w;
  if(h>bufLong)
	  bufLong=h;
  unsigned char *buf=new unsigned char[bufLong*bufLong];
  int i, j;
  for(i=0;i<h;i++){
	  for(j=0;j<w;j++)
		  buf[i*w+j]=*(lpDIBBits+i*lineByte+j);
	  for(j=w;j<bufLong;j++)
		  buf[i*w+j]=0;
  }
  for(i=h;i<bufLong;i++){
	  for(j=w;j<bufLong;j++)
		  buf[i*w+j]=0;
  }

  fft2D(buf, bufLong, bufLong);
  
  for(i=0;i<h;i++){
	  for(j=0;j<w;j++){
		  *(lpDIBBits+i*lineByte+j)=buf[i*bufLong+j];
	  }
  }
  delete []buf;
  
  ::GlobalUnlock(dib); 
  
  Invalidate();
}

void CDemoView::OnIfft() 
{
CDemoDoc *pDoc=GetDocument();
  HDIB dib=pDoc->GetHDIB();

  LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
  LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  int w = phead->biWidth;
  int h = phead->biHeight;
  int b = phead->biBitCount/8;
  if(b==3)
  {
	  ::GlobalUnlock(dib); 
	  return;
  }
  int lineByte=(w * b+3)/4*4;
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
  
  int bufLong=w;
  if(h>bufLong)
	  bufLong=h;
  unsigned char *buf=new unsigned char[bufLong*bufLong];
  int i, j;
  for(i=0;i<h;i++){
	  for(j=0;j<w;j++)
		  buf[i*w+j]=*(lpDIBBits+i*lineByte+j);
	  for(j=w;j<bufLong;j++)
		  buf[i*w+j]=0;
  }
  for(i=h;i<bufLong;i++){
	  for(j=w;j<bufLong;j++)
		  buf[i*w+j]=0;
  }

  ifft2D(buf, bufLong, bufLong);
  
  for(i=0;i<h;i++){
	  for(j=0;j<w;j++){
		  *(lpDIBBits+i*lineByte+j)=buf[i*w+j];
	  }
  }
  delete []buf;
  
  ::GlobalUnlock(dib); 
  
  Invalidate();	
}

void CDemoView::OnZoom() 
{
   ZoomTimesDlg	dlg;
   if(dlg.DoModal()==IDOK){
	   CDemoDoc *pDoc=GetDocument();
	   HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		unsigned char *buf=new unsigned char[w*h*b];
		int i, j;
		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				buf[i*w*b+j]=*(lpDIBBits+i*lineByte+j);
			}
		}

		int insertStyle=dlg.m_InsertStyle;
	   float zoomTime;
	   if(dlg.m_InOrOut==0)
		   zoomTime=1.0/dlg.m_ZoomTime;
	   else
		   zoomTime=dlg.m_ZoomTime;

		int zoomW=w*zoomTime, zoomH=h*zoomTime;
		unsigned char *zoomBuf=new unsigned char[zoomW*zoomH*b];
		if(insertStyle==0)//ΩÅE⁄Àı∑≈
			zoomNeighbor(buf, w, h, b, zoomTime,zoomBuf, zoomW, zoomH);
		else{//À´œﬂ–‘Àı∑≈
			if(b==1)
				zoomGray(buf, w, h, zoomTime, zoomBuf, zoomW, zoomH);
			else if(b==3)
				zoomRGB(buf, w, h, zoomTime, zoomBuf, zoomW, zoomH);
		}
		delete []buf;
		
		int newLineByte=(zoomW * b+3)/4*4;
		int palSize=::PaletteSize((LPSTR)lpDIB);
		HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+zoomH*newLineByte);
		LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
		
		::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
		BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
		info->biHeight=zoomH;
		info->biWidth=zoomW;
		unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
		for(i=0;i<zoomH;i++){
			for(j=0;j<zoomW*b;j++){
				*(lpDIBBitsNew+i*newLineByte+j)=zoomBuf[i*zoomW*b+j];
			}
		}
		delete []zoomBuf;
		::GlobalUnlock(dib); 
		::GlobalUnlock(dibNew); 
		
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		
		CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
		CDemoDoc* pDocNew=pView->GetDocument();
		pDocNew->ReplaceHDIB((HDIB)dibNew);
		pDocNew->InitDIBData();
		pDocNew->UpdateAllViews(pView);
		Invalidate();


   }
}

void CDemoView::OnRotateTrans() 
{
	RotateDlg dlg;
	if(dlg.DoModal()==IDOK){
		int angle=dlg.m_RotateAngle;
		CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		unsigned char *buf=new unsigned char[w*h*b];
		int i, j;
		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				buf[i*w*b+j]=*(lpDIBBits+i*lineByte+j);
			}
		}
		float slope=angle/180.0*3.1415926;
		int outImgW=w+h*fabs(sin(slope)), outImgH=h+w*fabs(sin(slope));
		if(outImgW<sqrt(double (w*w+h*h)))   outImgW=sqrt(double (w*w+h*h));
		if(outImgH<sqrt(double (w*w+h*h)))   outImgH=sqrt(double (w*w+h*h));
		float skew=tan(slope);
		unsigned char *rotateBuf=new unsigned char[outImgW*outImgH*b];
		if(b==1)
			rotateGrey(buf, w, h, 0,skew, 0, 0, rotateBuf,outImgW, outImgH);
		else if(b==3)
			rotateRGB(buf, w, h, 0,skew, 0, 0, rotateBuf,outImgW, outImgH);
		delete []buf;
		
		int newLineByte=(outImgW * b+3)/4*4;
		int palSize=::PaletteSize((LPSTR)lpDIB);
		HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+outImgH*newLineByte);
		LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
		
		::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
		BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
		info->biHeight=outImgH;
		info->biWidth=outImgW;
		unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
		for(i=0;i<outImgH;i++){
			for(j=0;j<outImgW*b;j++){
				*(lpDIBBitsNew+i*newLineByte+j)=rotateBuf[i*outImgW*b+j];
			}
		}
		delete []rotateBuf;
		::GlobalUnlock(dib); 
		::GlobalUnlock(dibNew); 
		
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		
		CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
		CDemoDoc* pDocNew=pView->GetDocument();
		
		pDocNew->ReplaceHDIB((HDIB)dibNew);
		pDocNew->InitDIBData();
		pDocNew->UpdateAllViews(pView);
		Invalidate();
		
	}
	
}

void CDemoView::OnRobot() 
{
	CDemoDoc *pDoc=GetDocument();
  HDIB dib=pDoc->GetHDIB();

  LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
  LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  int w = ::DIBWidth(lpDIB);
  int h = phead->biHeight;
  int b = phead->biBitCount/8;

  int lineByte=(w * b+3)/4*4;
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);

  int  i, j;
  unsigned char *buf=new unsigned char[w*h*b];
  for(i=0;i<h;i++){
	  for(j=0;j<w*b;j++){
		  *(buf+i*w*b+j)=*(lpDIBBits+i*lineByte+j);
	  }
  }
  robot(buf, w, h, b);
  for(i=0;i<h;i++){
	  for(j=0;j<w*b;j++){
		  *(lpDIBBits+i*lineByte+j)=*(buf+i*w*b+j);
	  }
  }

  ::GlobalUnlock(dib); 
  
  delete []buf;
  Invalidate();
}

void CDemoView::Onprewitt() 
{
		CDemoDoc *pDoc=GetDocument();
  HDIB dib=pDoc->GetHDIB();

  LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
  LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  int w = ::DIBWidth(lpDIB);
  int h = phead->biHeight;
  int b = phead->biBitCount/8;

  int lineByte=(w * b+3)/4*4;
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);

  int  i, j;
  unsigned char *buf=new unsigned char[w*h*b];
  for(i=0;i<h;i++){
	  for(j=0;j<w*b;j++){
		  *(buf+i*w*b+j)=*(lpDIBBits+i*lineByte+j);
	  }
  }
  prewitt(buf, w, h, b);
  for(i=0;i<h;i++){
	  for(j=0;j<w*b;j++){
		  *(lpDIBBits+i*lineByte+j)=*(buf+i*w*b+j);
	  }
  }

  ::GlobalUnlock(dib); 
  
  delete []buf;
  Invalidate();
}

void CDemoView::OnLaplacian() 
{
	CDemoDoc *pDoc=GetDocument();
  HDIB dib=pDoc->GetHDIB();

  LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
  LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  int w = ::DIBWidth(lpDIB);
  int h = phead->biHeight;
  int b = phead->biBitCount/8;

  int lineByte=(w * b+3)/4*4;
  unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);

  int  i, j;
  unsigned char *buf=new unsigned char[w*h*b];
  for(i=0;i<h;i++){
	  for(j=0;j<w*b;j++){
		  *(buf+i*w*b+j)=*(lpDIBBits+i*lineByte+j);
	  }
  }
  laplacian(buf, w, h, b);
  for(i=0;i<h;i++){
	  for(j=0;j<w*b;j++){
		  *(lpDIBBits+i*lineByte+j)=*(buf+i*w*b+j);
	  }
  }

  ::GlobalUnlock(dib); 
  
  delete []buf;
  Invalidate();
}

void CDemoView::OnMeanFilter() 
{
	MaskDlg dlg;
	if(dlg.DoModal()==IDOK){
		CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = ::DIBWidth(lpDIB);
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		int  i, j;
		unsigned char *buf=new unsigned char[w*h*b];
		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				*(buf+i*w*b+j)=*(lpDIBBits+i*lineByte+j);
			}
		}
    int maskSize, mask[49];
    if(dlg.m_MaskStyle==3){
      DefineMaskDlg defDlg;
      if(defDlg.DoModal()==IDOK){
        int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
                   defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
                   defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
                   defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
                   defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
        for(i=0;i<25;i++)
          mask[i]=m[i];
        maskSize=5;
      }
      else{
        for(i=0;i<9;i++)
          mask[i]=1;
        maskSize=3;
      }
    }
    else{
      if(dlg.m_MaskStyle==0)
        maskSize=3;
      else if(dlg.m_MaskStyle==1)
        maskSize=5;
      else if(dlg.m_MaskStyle==2)
        maskSize=7;
      for(i=0;i<maskSize;i++)
        for(j=0;j<maskSize;j++)
          mask[i*maskSize+j]=1;
    }
		meanFilter(buf, w, h, b, mask,maskSize);

		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				*(lpDIBBits+i*lineByte+j)=*(buf+i*w*b+j);
			}
		}
		
		::GlobalUnlock(dib); 
		
		delete []buf;
		Invalidate();
	}
 
}

void CDemoView::OnMidleFilter() 
{
	MaskDlg dlg;
	if(dlg.DoModal()==IDOK){
		CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = ::DIBWidth(lpDIB);
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		int  i, j;
		unsigned char *buf=new unsigned char[w*h*b];
		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				*(buf+i*w*b+j)=*(lpDIBBits+i*lineByte+j);
			}
		}
    int maskSize, mask[49];
    if(dlg.m_MaskStyle==3){
      DefineMaskDlg defDlg;
      if(defDlg.DoModal()==IDOK){
        int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
                   defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
                   defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
                   defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
                   defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
        for(i=0;i<25;i++)
          mask[i]=m[i];
        maskSize=5;
      }
      else{
        for(i=0;i<9;i++)
          mask[i]=1;
        maskSize=3;
      }
    }
    else{
      if(dlg.m_MaskStyle==0)
        maskSize=3;
      else if(dlg.m_MaskStyle==1)
        maskSize=5;
      else if(dlg.m_MaskStyle==2)
        maskSize=7;
      for(i=0;i<maskSize;i++)
        for(j=0;j<maskSize;j++)
          mask[i*maskSize+j]=1;
    }
		midFilter(buf, w, h, b, mask,maskSize);

		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				*(lpDIBBits+i*lineByte+j)=*(buf+i*w*b+j);
			}
		}
		
		::GlobalUnlock(dib); 
		
		delete []buf;
		Invalidate();
	}
}

void CDemoView::OnThreshSegment() 
{
	
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	
	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int w = ::DIBWidth(lpDIB);
	int h = phead->biHeight;
	int b = phead->biBitCount/8;
	if(b!=1){
		::MessageBox(0,"÷ª¥¶¿˙◊“∂»ÕºœÛ£°",MB_OK,0);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(w * b+3)/4*4;
	unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
	
	int  i, j;
	unsigned char *buf=new unsigned char[w*h*b];
	for(i=0;i<h;i++){
		for(j=0;j<w*b;j++){
			*(buf+i*w*b+j)=*(lpDIBBits+i*lineByte+j);
		}
	}
	threshDlg dlg;
	if(dlg.DoModal()==IDOK){
		int thresh=dlg.m_Thresh;
		
		ErZhiSegment(buf, w, h, thresh);
	}
	for(i=0;i<h;i++){
		for(j=0;j<w*b;j++){
			*(lpDIBBits+i*lineByte+j)=*(buf+i*w*b+j);
		}
	}
	
	::GlobalUnlock(dib); 
	
	delete []buf;
	Invalidate();
	
}

void CDemoView::OnDajinThresh() 
{
		CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = ::DIBWidth(lpDIB);
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		if(b!=1){
			::MessageBox(0,"÷ª¥¶¿˙◊“∂»ÕºœÛ£°",MB_OK,0);
			::GlobalUnlock(dib); 
			return;
		}
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		int  i, j;
		unsigned char *buf=new unsigned char[w*h*b];
		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				*(buf+i*w*b+j)=*(lpDIBBits+i*lineByte+j);
			}
		}

    autoThreshSegment(buf, w, h);

		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				*(lpDIBBits+i*lineByte+j)=*(buf+i*w*b+j);
			}
		}
		
		::GlobalUnlock(dib); 
		
		delete []buf;
		Invalidate();
}

void CDemoView::OnImgReverse() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	
	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int w = ::DIBWidth(lpDIB);
	int h = phead->biHeight;
	int b = phead->biBitCount/8;
	int lineByte=(w * b+3)/4*4;
	unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
	for(int i=0;i<h*lineByte;i++){			
		*(lpDIBBits+i)=255-*(lpDIBBits+i);
	}
	::GlobalUnlock(dib); 
	Invalidate();
}

void CDemoView::OnRGBToGray() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	
	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int w = ::DIBWidth(lpDIB);
	int h = phead->biHeight;
	int b = phead->biBitCount/8;
	if(b!=3){
		::MessageBox(0,"÷ª¥¶¿˙Œ …´ÕºœÛ£°",MB_OK,0);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(w * b+3)/4*4;
	unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
	
	int i,j, newlineByte=(w+3)/4*4; 
	
	   int palSize=1024;
	   HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+h*newlineByte);
	   LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
	   
	   ::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
	   BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
	   info->biHeight=h;
	   info->biWidth=w;
	   info->biBitCount=8;
	   
	   LPSTR p=lpDIBNew+sizeof(BITMAPINFOHEADER);
	   for(i=0;i<256;i++){
		   for(j=0;j<3;j++)
			   *(p+i*4+j)=i;
       *(p+i*4+3)=0;
	   }
	   unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
	   for(i=0;i<h;i++){
		   for(j=0;j<newlineByte;j++){
         int Y=0.299*(double)*(lpDIBBits+i*lineByte+j*3+2)+0.587*(double)*(lpDIBBits+i*lineByte+j*3+1)
						+0.114*(double)*(lpDIBBits+i*lineByte+j*3+0)+0.1;
			   *(lpDIBBitsNew+i*newlineByte+j)=Y;/*0.30* *(lpDIBBits+i*lineByte+j*3+0)
				   +0.59* *(lpDIBBits+i*lineByte+j*3+1)
				   +0.11* *(lpDIBBits+i*lineByte+j*3+2);*/
		   }
	   }
	   ::GlobalUnlock(dib); 
	   ::GlobalUnlock(dibNew); 
	   
	   CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	   pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);	   
	   CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
	   CDemoDoc* pDocNew=pView->GetDocument();	   
	   pDocNew->ReplaceHDIB((HDIB)dibNew);
	   pDocNew->InitDIBData();
	   pDocNew->UpdateAllViews(pView);
	   Invalidate();
}

void CDemoView::OnlinearTrans() 
{
	linearStretch dlg;
	if(dlg.DoModal()==IDOK){
		CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = ::DIBWidth(lpDIB);
		int h = phead->biHeight;
		int b = phead->biBitCount/8;		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		int  i, j;
		unsigned char *buf=new unsigned char[lineByte*h];
		
		int posData[4];
		posData[0]=dlg.m_point1X;
		posData[1]=dlg.m_point1Y;
		posData[2]=dlg.m_point2X;
		posData[3]=dlg.m_point2Y;

		if(b==1)
	    	Graytransition(lpDIBBits,buf,w,h,posData);
		else
			RGBtransition(lpDIBBits,buf,w,h,posData);

		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				*(lpDIBBits+i*lineByte+j)=*(buf+i*lineByte+j);
			}
		}		
		::GlobalUnlock(dib); 
		
		delete []buf;
		Invalidate();
	}

}

void CDemoView::OnhistAver() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	
	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int w = ::DIBWidth(lpDIB);
	int h = phead->biHeight;
	int b = phead->biBitCount/8;		
	int lineByte=(w * b+3)/4*4;
	unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
	unsigned char*lpIn=lpDIBBits;
	if(b==1)
	{
		int lineByte1=(w * b+3)/4*4;
		unsigned char *lpOut=new unsigned char [h*lineByte1];
		PointEqual((LPBYTE)lpIn,(LPBYTE)lpOut,w,h,256);
		::memcpy(lpIn,lpOut,h*lineByte1);
		::GlobalUnlock(dib);
		pDoc->SetModifiedFlag(TRUE);
		delete []lpOut;
	}
	else if(b==3)
	{
		int lineByte2=(w * b+3)/4*4;
		unsigned char *lpOut1=new unsigned char [h*lineByte2];
		PointEqual((LPBYTE)lpIn,(LPBYTE)lpOut1,w,h,0);
		::memcpy(lpIn,lpOut1,h*lineByte2);
		::GlobalUnlock(dib);
		pDoc->SetModifiedFlag(TRUE);
		delete []lpOut1;
	}
	else{
		::MessageBox(0,"÷ª¥¶¿˙Œ …´ÕºœÛ£°",MB_OK,0);
	}
			
	::GlobalUnlock(dib); 
	
	Invalidate();
}

void CDemoView::OnErosionErzhi() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	int gray;
	for(int i=0;i<height;i++)//≈–∂œ «∑Ò «∂˛÷µÕºœÅE
	{
		for(int j=0;j<lineByte;j++)
		{
			gray=*(lpIn+i*lineByte+j);
			if(gray!=0&&gray!=255)
			{
				::MessageBox(0,"≤ª «∂˛÷µµƒÕºœÅE",NULL,MB_OK);
				::GlobalUnlock(dib); 
				return;
			}
		}
	}

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[7]=1;
			mask[11]=1;
			mask[12]=1;
			mask[13]=1;
			mask[17]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int count=0;
		for(int i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
	Terode((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);

	::memcpy(lpIn,lpOut,height*lineByte);
	::GlobalUnlock(dib);
    delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnErzhiExpand() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	int gray;
	for(int i=0;i<height;i++)//≈–∂œ «∑Ò «∂˛÷µÕºœÅE
	{
		for(int j=0;j<lineByte;j++)
		{
			gray=*(lpIn+i*lineByte+j);
			if(gray!=0&&gray!=255)
			{
				::MessageBox(0,"≤ª «∂˛÷µµƒÕºœÅE",NULL,MB_OK);
				::GlobalUnlock(dib); 
				return;
			}
		}
	}

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[7]=1;
			mask[11]=1;
			mask[12]=1;
			mask[13]=1;
			mask[17]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int count=0;
		for(int i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
	Texpand((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);

	::memcpy(lpIn,lpOut,height*lineByte);
	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnErzhiOpen() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	int gray;
	for(int i=0;i<height;i++)//≈–∂œ «∑Ò «∂˛÷µÕºœÅE
	{
		for(int j=0;j<lineByte;j++)
		{
			gray=*(lpIn+i*lineByte+j);
			if(gray!=0&&gray!=255)
			{
				::MessageBox(0,"≤ª «∂˛÷µµƒÕºœÅE",NULL,MB_OK);
				::GlobalUnlock(dib); 
				return;
			}
		}
	}

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[7]=1;
			mask[11]=1;
			mask[12]=1;
			mask[13]=1;
			mask[17]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int count=0;
		for(int i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
  Terode((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);
	Texpand((LPBYTE)lpOut,(LPBYTE)lpIn,width,height,mask);

	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnErzhClose() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	int gray;
	for(int i=0;i<height;i++)//≈–∂œ «∑Ò «∂˛÷µÕºœÅE
	{
		for(int j=0;j<lineByte;j++)
		{
			gray=*(lpIn+i*lineByte+j);
			if(gray!=0&&gray!=255)
			{
				::MessageBox(0,"≤ª «∂˛÷µµƒÕºœÅE",NULL,MB_OK);
				::GlobalUnlock(dib); 
				return;
			}
		}
	}

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[7]=1;
			mask[11]=1;
			mask[12]=1;
			mask[13]=1;
			mask[17]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int count=0;
		for(int i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
  Texpand((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);
	Terode((LPBYTE)lpOut,(LPBYTE)lpIn,width,height,mask);

	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnGrayErose() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[6]=1, mask[7]=1, mask[8]=1;
			mask[11]=1, mask[12]=1, mask[13]=1;
			mask[16]=1, mask[17]=1, mask[18]=1; 
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int i, count=0;
		for(i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
  GrayErosion((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);
	
	::memcpy(lpIn,lpOut,height*lineByte);

	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnGrayExpand() 
{
		CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[6]=1, mask[7]=1, mask[8]=1;
			mask[11]=1, mask[12]=1, mask[13]=1;
			mask[16]=1, mask[17]=1, mask[18]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int i, count=0;
		for(i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
  GrayDilation((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);
	
	::memcpy(lpIn,lpOut,height*lineByte);

	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnGrayOpen() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[6]=1, mask[7]=1, mask[8]=1;
			mask[11]=1, mask[12]=1, mask[13]=1;
			mask[16]=1, mask[17]=1, mask[18]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int i, count=0;
		for(i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
  GrayErosion((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);
	GrayDilation((LPBYTE)lpOut,(LPBYTE)lpIn,width,height,mask);

	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnGreyClose() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[6]=1, mask[7]=1, mask[8]=1;
			mask[11]=1, mask[12]=1, mask[13]=1;
			mask[16]=1, mask[17]=1, mask[18]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int i, count=0;
		for(i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
  GrayDilation((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);
	GrayErosion((LPBYTE)lpOut,(LPBYTE)lpIn,width,height,mask);
	
	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnMorphologyGrad() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[6]=1, mask[7]=1, mask[8]=1;
			mask[11]=1, mask[12]=1, mask[13]=1;
			mask[16]=1, mask[17]=1, mask[18]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int i, count=0;
		for(i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
   MorphGrad((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);

//	::memcpy(lpIn,lpOut,height*lineByte);
   int newLineByte=lineByte;
		int palSize=::PaletteSize((LPSTR)lpDIB);
		HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+height*newLineByte);
		LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
		
		::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
		BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
		info->biHeight=height;
		info->biWidth=width;
		unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
		for(i=0;i<height*newLineByte;i++){
				*(lpDIBBitsNew+i)=lpOut[i];
		}
		::GlobalUnlock(dib); 
		::GlobalUnlock(dibNew); 
		
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		
		CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
		CDemoDoc* pDocNew=pView->GetDocument();
		
		pDocNew->ReplaceHDIB((HDIB)dibNew);
		pDocNew->InitDIBData();
		pDocNew->UpdateAllViews(pView);
  delete []lpOut;
	Invalidate();
}

void CDemoView::OnTopHatPeak() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[6]=1, mask[7]=1, mask[8]=1;
			mask[11]=1, mask[12]=1, mask[13]=1;
			mask[16]=1, mask[17]=1, mask[18]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int i, count=0;
		for(i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
   TopHatPeak((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);

	::memcpy(lpIn,lpOut,height*lineByte);	
	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnTopHatVally() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[6]=1, mask[7]=1, mask[8]=1;
			mask[11]=1, mask[12]=1, mask[13]=1;
			mask[16]=1, mask[17]=1, mask[18]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int i, count=0;
		for(i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
   TopHatVally((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);

	::memcpy(lpIn,lpOut,height*lineByte);	
	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnTophatPeakVally() 
{
	CDemoDoc *pDoc=GetDocument();
	HDIB dib=pDoc->GetHDIB();
	if(dib==NULL) 
	{
		::MessageBox(0,"«ÅEÚø™‘≠ ºÕºœÒ£°",NULL,MB_OK);
		return;
	}

	LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
	LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
	int width=phead->biWidth;
	int height=phead->biHeight;
	int biBitCount = phead->biBitCount/8;
	if(biBitCount==3)//≤ª¥¶¿˙Œ …´ÕºœÅE
	{
		::MessageBox(0,"≤ª¥¶¿˙Œ …´ÕºœÅE",NULL,MB_OK);
		::GlobalUnlock(dib); 
		return;
	}
	int lineByte=(width * biBitCount+3)/4*4;
	unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);

	morphologyDlg dlg;
	
	if(dlg.DoModal()!=IDOK){
		::GlobalUnlock(dib);
		return;
	}
  int mask[25]={0}, maskSize=5;
		if(dlg.m_maskSelect==0){
			mask[6]=1, mask[7]=1, mask[8]=1;
			mask[11]=1, mask[12]=1, mask[13]=1;
			mask[16]=1, mask[17]=1, mask[18]=1;
		}
		else{
			DefineMaskDlg defDlg;
			if(defDlg.DoModal()==IDOK){
				int m[25]={defDlg.m_maskEdit1, defDlg.m_maskEdit2, defDlg.m_maskEdit3, defDlg.m_maskEdit4, defDlg.m_maskEdit5,
					defDlg.m_maskEdit6, defDlg.m_maskEdit7, defDlg.m_maskEdit8, defDlg.m_maskEdit9, defDlg.m_maskEdit10,
					defDlg.m_maskEdit11, defDlg.m_maskEdit12, defDlg.m_maskEdit13, defDlg.m_maskEdit14, defDlg.m_maskEdit15,
					defDlg.m_maskEdit16, defDlg.m_maskEdit17, defDlg.m_maskEdit18, defDlg.m_maskEdit19, defDlg.m_maskEdit20,
					defDlg.m_maskEdit21, defDlg.m_maskEdit22, defDlg.m_maskEdit23, defDlg.m_maskEdit24, defDlg.m_maskEdit25};
				for(int i=0;i<25;i++)
					mask[i]=m[i];
				maskSize=5;
			}
		}
		int i, count=0;
		for(i=0;i<25;i++){
			if(mask[i]==1)
				count++;
		}
		if(count==0)
			{
				::MessageBox(0," ƒ£∞Â≤Œ ˝≤ªƒ‹»´Œ™0!",NULL,MB_OK);
				return;
			}
		
	unsigned char *lpOut=new unsigned char [height*lineByte];
   TopHatVally((LPBYTE)lpIn,(LPBYTE)lpOut,width,height,mask);

	::memcpy(lpIn,lpOut,height*lineByte);	
	::GlobalUnlock(dib);
  delete []lpOut;
//	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CDemoView::OnZoomSmall() 
{
	// TODO: Add your command handler code here
// TODO: Add your command handler code here
	   CDemoDoc *pDoc=GetDocument();
	   HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		unsigned char *buf=new unsigned char[w*h*b];
		int i, j;
		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				buf[i*w*b+j]=*(lpDIBBits+i*lineByte+j);
			}
		}


	   float zoomTimew=0.5,  zoomTimeh=0.5;


		int zoomW=w*zoomTimew, zoomH=h*zoomTimeh;
		unsigned char *zoomBuf=new unsigned char[zoomW*zoomH*b];

       //À´œﬂ–‘Àı∑≈
		if(b==1)
			zoomGray2(buf, w, h, zoomTimew,zoomTimeh, zoomBuf, zoomW, zoomH);
		else if(b==3)
			zoomRGB2(buf, w, h, zoomTimew,zoomTimeh, zoomBuf, zoomW, zoomH);

		delete []buf;
		
		int newLineByte=(zoomW * b+3)/4*4;
		int palSize=::PaletteSize((LPSTR)lpDIB);
		HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+zoomH*newLineByte);
		LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
		
		::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
		BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
		info->biHeight=zoomH;
		info->biWidth=zoomW;
		unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
		for(i=0;i<zoomH;i++){
			for(j=0;j<zoomW*b;j++){
				*(lpDIBBitsNew+i*newLineByte+j)=zoomBuf[i*zoomW*b+j];
			}
		}
		delete []zoomBuf;
		::GlobalUnlock(dib); 
		::GlobalUnlock(dibNew); 
		
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
//		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		
		CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
		CDemoDoc* pDocNew=pView->GetDocument();
		
		pDocNew->ReplaceHDIB((HDIB)dibNew);
		pDocNew->InitDIBData();
		pDocNew->UpdateAllViews(pView);
		Invalidate();
}


void CDemoView::OnZoomLarge() 
{
	// TODO: Add your command handler code here
	   CDemoDoc *pDoc=GetDocument();
	   HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		unsigned char *buf=new unsigned char[w*h*b];
		int i, j;
		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				buf[i*w*b+j]=*(lpDIBBits+i*lineByte+j);
			}
		}


	   float zoomTimew=2, zoomTimeh = 2;


		int zoomW=w*zoomTimew, zoomH=h*zoomTimeh;
		unsigned char *zoomBuf=new unsigned char[zoomW*zoomH*b];

       //À´œﬂ–‘Àı∑≈
		if(b==1)
			zoomGray2(buf, w, h, zoomTimew, zoomTimeh,zoomBuf, zoomW, zoomH);
    //        zoomNeighbor2(buf, w, h, 1, zoomTimew,zoomTimeh, zoomBuf, zoomW, zoomH);
		else if(b==3)
			zoomRGB2(buf, w, h, zoomTimew, zoomTimeh,zoomBuf, zoomW, zoomH);

		delete []buf;

        ::GlobalUnlock(dib);

		int newLineByte=(zoomW * b+3)/4*4;
		int palSize=::PaletteSize((LPSTR)lpDIB);

		HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+zoomH*newLineByte);
		LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
		
		::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
		BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
		info->biHeight=zoomH;
		info->biWidth=zoomW;
		unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
		for(i=0;i<zoomH;i++){
			for(j=0;j<zoomW*b;j++){
				*(lpDIBBitsNew+i*newLineByte+j)=zoomBuf[i*zoomW*b+j];
			}
		}
		delete []zoomBuf;
 
		::GlobalUnlock(dibNew); 
		
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	//	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);

		CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
		CDemoDoc* pDocNew=pView->GetDocument();
		pDocNew->ReplaceHDIB((HDIB)dibNew);
    	pDocNew->InitDIBData();
    	pDocNew->UpdateAllViews(pView);

		
		Invalidate();
}



void CDemoView::OnGaussNoise() 
{
	// TODO: Add your command handler code here
  CDemoDoc *pDoc=GetDocument();
  HDIB dib=pDoc->GetHDIB();

  LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
  LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
  int w = phead->biWidth;
  int h = phead->biHeight;
  int b = phead->biBitCount/8;
  if(b==3)
  {
	  ::MessageBox(0,"÷ª¥¶¿˙◊“∂»ÕºœÛ£°",NULL,MB_OK);
	  ::GlobalUnlock(dib); 
	  return;
  }
  int lineByte=(w * b+3)/4*4;
  unsigned char *lpIn=(unsigned char *)::FindDIBBits(lpDIB);
  

  unsigned char *lpOut=new unsigned char[h*lineByte];

  GaussNoise((LPBYTE)lpIn,(LPBYTE)lpOut,lineByte,h,0, 0.01);
  int i,j;
	::memcpy(lpIn,lpOut,h*lineByte);


	::GlobalUnlock(dib);
    delete []lpOut;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();


}



void CDemoView::OnRotate() 
{
// TODO: Add your command handler code here
		int angle=-5;// –˝◊™∂» ˝
		CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		unsigned char *buf=new unsigned char[w*h*b];
		int i, j;
		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				buf[i*w*b+j]=*(lpDIBBits+i*lineByte+j);
			}
		}
		float slope=angle/180.0*3.1415926;
		int outImgW=w*fabs(cos(slope))+h*fabs(sin(slope)), outImgH=h*fabs(cos(slope))+w*fabs(sin(slope));
		float skew=tan(slope);
		unsigned char *rotateBuf=new unsigned char[outImgW*outImgH*b];
		if(b==1)
			rotateGrey(buf, w, h, 0,skew, 0, 0, rotateBuf,outImgW, outImgH);
		else if(b==3)
			rotateRGB(buf, w, h, 0,skew, 0, 0, rotateBuf,outImgW, outImgH);
		delete []buf;
		
		int newLineByte=(outImgW * b+3)/4*4;
		int palSize=::PaletteSize((LPSTR)lpDIB);
		HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+outImgH*newLineByte);
		LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
		
		::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
		BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
		info->biHeight=outImgH;
		info->biWidth=outImgW;
		unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
		for(i=0;i<outImgH;i++){
			for(j=0;j<outImgW*b;j++){
				*(lpDIBBitsNew+i*newLineByte+j)=rotateBuf[i*outImgW*b+j];
			}
		}
		delete []rotateBuf;
		::GlobalUnlock(dib); 
		::GlobalUnlock(dibNew); 
		
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		
		CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
		CDemoDoc* pDocNew=pView->GetDocument();
		
		pDocNew->ReplaceHDIB((HDIB)dibNew);
		pDocNew->InitDIBData();
		pDocNew->UpdateAllViews(pView);
		Invalidate();
		
}

void CDemoView::OnShift() 
{	// TODO: Add your command handler code here
  
		CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		

		unsigned char *lpOut=new unsigned char[h*lineByte];
		if(b==1)
			shift(lpDIBBits, lpOut, lineByte, h, 3,4);
		else if(b==3)
			  {
	            ::MessageBox(0,"÷ª¥¶¿˙◊“∂»ÕºœÛ£°",NULL,MB_OK);
	            ::GlobalUnlock(dib); 
	            return;
		}
		long i,j;
		for(i=0;i<h;i++){
			for(j=0;j<lineByte;j++){
				*(lpDIBBits+i*lineByte+j)=lpOut[i*lineByte+j];
			}
		}
	::GlobalUnlock(dib);
    delete []lpOut;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
	
}

void CDemoView::OnGenLR() 
{
	// TODO: Add your command handler code here
	    CDemoDoc *pDoc=GetDocument();
	    HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
        int N=8;//…˙≥…LRÕºœÒ ˝ƒø
        int i,j,k;
		unsigned char *lpOut[10];// ÷∏’ÅE˝◊ÅEN∏ˆ÷∏’ÅE
		unsigned char **p; // ÷∏œÚ÷∏’ÅEƒ÷∏’ÅE
		int seqNum[9] = {1,5,7,9,2,3,6,4,8};
        for(k=0;k<N;k++)
		{
			CString title;
			title.Format("µ⁄%d∑˘LRÕº",k+1);
         //…˙≥…ÕºœÒµƒ≥ﬂ¥ÅE
			int newWidth=w/2;
			int newHeight=h/2;
//			int newWidth=w;
//			int newHeight=h;
            int newLineByte=(newWidth* b+3)/4*4;
			p=lpOut+k;//÷∏œÚµ⁄i∏ˆ÷∏’ÅE
		    unsigned char *p= new unsigned char [newHeight*newWidth];
			int s1_rand,s2_rand,s3_rand,s4_rand;
			s1_rand = seqNum[k];
	    	s2_rand = seqNum[k];
	    	s3_rand = seqNum[k];
	    	s4_rand = seqNum[k];
				//À´œﬂ–‘Àı∑≈
	    	if(b==1)
//		    	GenLR(lpDIBBits,p,w,h,false,0.01);
                GenLR(lpDIBBits,p,w,h,false,0.01,s1_rand,s2_rand,s3_rand,s4_rand);
	    	else if(b==3)
			{
				::MessageBox(0,"÷ª¥¶¿˙◊“∂»ÕºœÛ£°",NULL,MB_OK);
	            ::GlobalUnlock(dib); 
	            return;
			}
			    ::GlobalUnlock(dib);

	     	int palSize=::PaletteSize((LPSTR)lpDIB);


			HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+(newHeight*newLineByte));
	    	LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
	    	::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
			BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
	    	info->biHeight=newHeight;
	    	info->biWidth=newWidth;
	    	unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
	    	for(i=0;i<newHeight;i++)
			{
		    	for(j=0;j<newLineByte;j++)
				{
		    		*(lpDIBBitsNew+i*newLineByte+j)=*(p+i*newWidth+j);
				}
			}
			delete []p;
	        ::GlobalUnlock(dibNew); 
	    	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	    	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	     	CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
			CDemoDoc* pDocNew=pView->GetDocument();	
			pDocNew->SetTitle(title);
	    	pDocNew->ReplaceHDIB((HDIB)dibNew);
	     	pDocNew->InitDIBData();
	    	pDocNew->UpdateAllViews(pView);
	    	Invalidate();

		}



}

void CDemoView::OnTss() 
{
	// TODO: Add your command handler code here
CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		

		unsigned char *lpShift=new unsigned char[h*lineByte];
		if(b==1)
		//	shift(lpDIBBits, lpShift, lineByte, h, 0,0);
		  shift(lpDIBBits, lpShift, lineByte, h, 0.8,0.9);
		else if(b==3)
			  {
	            ::MessageBox(0,"÷ª¥¶¿˙◊“∂»ÕºœÛ£°",NULL,MB_OK);
	            ::GlobalUnlock(dib); 
	            return;
		}
		long i,j;
		/*
		for(i=0;i<h;i++){
			for(j=0;j<lineByte;j++){
				*(lpDIBBits+i*lineByte+j)=lpShift[i*lineByte+j];
			}
		}*/
	::GlobalUnlock(dib);
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();


	int motionVect[2][MAX];
	double TSScomputations[1]; 
    double TSSpsnr;
    CString showPSNR;
	unsigned char* imgComp = new unsigned char[h*lineByte];
    motionEstTSS(lpShift, lpDIBBits, lineByte, h, motionVect, TSScomputations);//’‚¿ÅEË“™”√lineBytes
    motionComp(lpDIBBits,16,lineByte,h,motionVect,imgComp);
    TSSpsnr = psnr(lpShift,imgComp,lineByte,h,255);
	//∂‘ª∞øÚœ‘ æPSNR÷µ
    showPSNR.Format("ÕºœÒPSNR=%f,º∆À„¡ø=%f",TSSpsnr,TSScomputations[0]);
    ::MessageBox(0,showPSNR,"≤π≥•ÕºœÒPSNR",MB_OK);
	

			int newWidth=w;
			int newHeight=h;
            int newLineByte=(newWidth* b+3)/4*4;
		    int palSize=::PaletteSize((LPSTR)lpDIB);
			HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+(newHeight*newLineByte));
	    	LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
	    	::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
			BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
	    	info->biHeight=newHeight;
	    	info->biWidth=newWidth;
	    	unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
	    	for(i=0;i<newHeight;i++)
			{
		    	for(j=0;j<newLineByte;j++)
				{
		    		*(lpDIBBitsNew+i*newLineByte+j)=*(imgComp+i*newWidth+j);
				}
			}
	        ::GlobalUnlock(dibNew); 
	    	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	    	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	     	CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
			CDemoDoc* pDocNew=pView->GetDocument();	 
			pDocNew->SetTitle("TSS‘À∂Ø≤π≥•Ω·πÅE");
	    	pDocNew->ReplaceHDIB((HDIB)dibNew);
	     	pDocNew->InitDIBData();
	    	pDocNew->UpdateAllViews(pView);
	    	Invalidate();

    delete []lpShift;
    delete []imgComp;


}

void CDemoView::OnDs() 
{
	// TODO: Add your command handler code here
     	CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		

		unsigned char *lpShift=new unsigned char[h*lineByte];
		if(b==1)
			shift(lpDIBBits, lpShift, lineByte, h, 0.8,0.9);
//			shift(lpDIBBits, lpShift, lineByte, h, 0,0);
		else if(b==3)
			  {
	            ::MessageBox(0,"÷ª¥¶¿˙◊“∂»ÕºœÛ£°",NULL,MB_OK);
	            ::GlobalUnlock(dib); 
	            return;
		}
		long i,j;
		/*
		for(i=0;i<h;i++){
			for(j=0;j<lineByte;j++){
				*(lpDIBBits+i*lineByte+j)=lpShift[i*lineByte+j];
			}
		}*/
	::GlobalUnlock(dib);
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();


	int motionVect[2][MAX];
	double DScomputations[1]; 
    double DSpsnr;
    CString showPSNR;
	unsigned char* imgComp = new unsigned char[h*lineByte];
    motionEstDS(lpShift, lpDIBBits, lineByte, h, motionVect, DScomputations);//’‚¿ÅEË“™”√lineBytes
    motionComp(lpDIBBits,16,lineByte,h,motionVect,imgComp);
    DSpsnr = psnr(lpShift,imgComp,lineByte,h,255);
	//∂‘ª∞øÚœ‘ æPSNR÷µ
    showPSNR.Format("ÕºœÒPSNR=%f,º∆À„¡ø=%f",DSpsnr,DScomputations[0]);
    ::MessageBox(0,showPSNR,"≤π≥•ÕºœÒPSNR",MB_OK);
	

			int newWidth=w;
			int newHeight=h;
            int newLineByte=(newWidth* b+3)/4*4;
		    int palSize=::PaletteSize((LPSTR)lpDIB);
			HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+(newHeight*newLineByte));
	    	LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
	    	::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
			BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
	    	info->biHeight=newHeight;
	    	info->biWidth=newWidth;
	    	unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
	    	for(i=0;i<newHeight;i++)
			{
		    	for(j=0;j<newLineByte;j++)
				{
		    		*(lpDIBBitsNew+i*newLineByte+j)=*(imgComp+i*newWidth+j);
				}
			}
	        ::GlobalUnlock(dibNew); 
	    	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	    	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	     	CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
			CDemoDoc* pDocNew=pView->GetDocument();	
			pDocNew->SetTitle("DS‘À∂Ø≤π≥•Ω·πÅE");
	    	pDocNew->ReplaceHDIB((HDIB)dibNew);
	     	pDocNew->InitDIBData();
	    	pDocNew->UpdateAllViews(pView);
	    	Invalidate();

    delete []lpShift;
    delete []imgComp;
}


void CDemoView::OnBlur() 
{
	// TODO: Add your command handler code here
		CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = ::DIBWidth(lpDIB);
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);
		
		int  i, j;
		unsigned char *buf=new unsigned char[w*h*b];
		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				*(buf+i*w*b+j)=*(lpDIBBits+i*lineByte+j);
			}
		}
        int maskSize=3;
		double  mask[9]={1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9};
		Filter(buf, w, h, b, mask,maskSize);

		for(i=0;i<h;i++){
			for(j=0;j<w*b;j++){
				*(lpDIBBits+i*lineByte+j)=*(buf+i*w*b+j);
			}
		}
		
		::GlobalUnlock(dib); 
		
		delete []buf;
		Invalidate();
}

void CDemoView::OnPocs() 
{
	// TODO: Add your command handler code here
	    noiseDlg Dlg;
	   	CDemoDoc *pDoc=GetDocument();
		HDIB dib=pDoc->GetHDIB();
		
		LPSTR	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) dib);
		LPBITMAPINFOHEADER phead=(LPBITMAPINFOHEADER)lpDIB;
		int w = phead->biWidth;
		int h = phead->biHeight;
		int b = phead->biBitCount/8;
		
		int lineByte=(w * b+3)/4*4;
		unsigned char *lpDIBBits=(unsigned char *)::FindDIBBits(lpDIB);

    	::GlobalUnlock(dib);
     	pDoc->SetModifiedFlag(TRUE);
    	Invalidate();
        unsigned char *imgOut = new unsigned char[w*h];
		int LRNum = 8;
		int iterNum = 50;
		Dlg.DoModal();
        pocs(lpDIBBits,w,h,LRNum,iterNum, imgOut, Dlg.m_noiseAuto,Dlg.m_NoiseVar);

			int newWidth=w;
			int newHeight=h;
            int newLineByte=(newWidth* b+3)/4*4;
		    int palSize=::PaletteSize((LPSTR)lpDIB);
			HANDLE dibNew=::GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)+ palSize+(newHeight*newLineByte));
	    	LPSTR lpDIBNew = (LPSTR) ::GlobalLock(dibNew);
	    	::memcpy((unsigned char*)lpDIBNew, (unsigned char*)lpDIB, sizeof(BITMAPINFOHEADER)+ palSize);
			BITMAPINFOHEADER *info=(BITMAPINFOHEADER*)lpDIBNew;
	    	info->biHeight=newHeight;
	    	info->biWidth=newWidth;
	    	unsigned char *lpDIBBitsNew=(unsigned char *)::FindDIBBits(lpDIBNew);
	    	for(int i=0;i<newHeight;i++)
			{
		    	for(int j=0;j<newLineByte;j++)
				{
		    		*(lpDIBBitsNew+i*newLineByte+j)=*(imgOut+i*newWidth+j);
				}
			}
	        ::GlobalUnlock(dibNew); 
	    	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	    	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	     	CDemoView* pView=(CDemoView*)pFrame->MDIGetActive()->GetActiveView();
			CDemoDoc* pDocNew=pView->GetDocument();	
			pDocNew->SetTitle("POCS∏¥‘≠Ω·πÅE");
	    	pDocNew->ReplaceHDIB((HDIB)dibNew);
	     	pDocNew->InitDIBData();
	    	pDocNew->UpdateAllViews(pView);
	    	Invalidate();

    delete []imgOut;
	
}

void CDemoView::OnOpenSeq() 
{
	// TODO: Add your command handler code here
	
}
