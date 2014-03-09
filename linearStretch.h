#if !defined(AFX_LINEARSTRETCH_H__9F16BADC_7CFE_4222_982F_A6B9AD6E2B9A__INCLUDED_)
#define AFX_LINEARSTRETCH_H__9F16BADC_7CFE_4222_982F_A6B9AD6E2B9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// linearStretch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// linearStretch dialog

class linearStretch : public CDialog
{
// Construction
public:
	linearStretch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(linearStretch)
	enum { IDD = IDD_LinearStrech };
	int		m_point1X;
	int		m_point1Y;
	int		m_point2X;
	int		m_point2Y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(linearStretch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(linearStretch)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEARSTRETCH_H__9F16BADC_7CFE_4222_982F_A6B9AD6E2B9A__INCLUDED_)
