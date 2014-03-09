#if !defined(AFX_THRESHDLG_H__C527494B_85F8_4773_8E7C_FB3BDF196B04__INCLUDED_)
#define AFX_THRESHDLG_H__C527494B_85F8_4773_8E7C_FB3BDF196B04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// threshDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// threshDlg dialog

class threshDlg : public CDialog
{
// Construction
public:
	threshDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(threshDlg)
	enum { IDD = IDD_ThreshDlg };
	int		m_Thresh;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(threshDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(threshDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THRESHDLG_H__C527494B_85F8_4773_8E7C_FB3BDF196B04__INCLUDED_)
