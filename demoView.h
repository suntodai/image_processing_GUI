// demoView.h : interface of the CDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOVIEW_H__DE734DBE_1CB6_4B2F_862C_8C090198DB38__INCLUDED_)
#define AFX_DEMOVIEW_H__DE734DBE_1CB6_4B2F_862C_8C090198DB38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDemoView : public CScrollView
{
protected: // create from serialization only
	CDemoView();
	DECLARE_DYNCREATE(CDemoView)

// Attributes
public:
	CDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoView)
	afx_msg void OnSobel();
	afx_msg void OnFft();
	afx_msg void OnIfft();
	afx_msg void OnZoom();
	afx_msg void OnRotateTrans();
	afx_msg void OnRobot();
	afx_msg void Onprewitt();
	afx_msg void OnLaplacian();
	afx_msg void OnMeanFilter();
	afx_msg void OnMidleFilter();
	afx_msg void OnThreshSegment();
	afx_msg void OnDajinThresh();
	afx_msg void OnImgReverse();
	afx_msg void OnRGBToGray();
	afx_msg void OnlinearTrans();
	afx_msg void OnhistAver();
	afx_msg void OnErosionErzhi();
	afx_msg void OnErzhiExpand();
	afx_msg void OnErzhiOpen();
	afx_msg void OnErzhClose();
	afx_msg void OnGrayErose();
	afx_msg void OnGrayExpand();
	afx_msg void OnGrayOpen();
	afx_msg void OnGreyClose();
	afx_msg void OnMorphologyGrad();
	afx_msg void OnTopHatPeak();
	afx_msg void OnTopHatVally();
	afx_msg void OnTophatPeakVally();
	afx_msg void OnZoomSmall();
	afx_msg void OnZoomLarge();
	afx_msg void OnGaussNoise();
	afx_msg void OnRotate();
	afx_msg void OnShift();
	afx_msg void OnGenLR();
	afx_msg void OnTss();
	afx_msg void OnDs();
	afx_msg void OnPocs();
	afx_msg void OnBlur();
	afx_msg void OnOpenSeq();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in demoView.cpp
inline CDemoDoc* CDemoView::GetDocument()
   { return (CDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOVIEW_H__DE734DBE_1CB6_4B2F_862C_8C090198DB38__INCLUDED_)
