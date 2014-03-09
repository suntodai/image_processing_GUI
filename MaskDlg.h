#if !defined(AFX_MASKDLG_H__26B2B764_E986_4285_BBCC_1C440B61715A__INCLUDED_)
#define AFX_MASKDLG_H__26B2B764_E986_4285_BBCC_1C440B61715A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaskDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MaskDlg dialog

class MaskDlg : public CDialog
{
// Construction
public:
	MaskDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MaskDlg)
	enum { IDD = IDD_MaskDlg };
	int		m_MaskStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MaskDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MaskDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASKDLG_H__26B2B764_E986_4285_BBCC_1C440B61715A__INCLUDED_)
