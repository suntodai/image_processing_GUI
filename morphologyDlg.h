#if !defined(AFX_MORPHOLOGYDLG_H__53CDF295_C7FC_4B01_A8F4_4BD5F562AD22__INCLUDED_)
#define AFX_MORPHOLOGYDLG_H__53CDF295_C7FC_4B01_A8F4_4BD5F562AD22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// morphologyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// morphologyDlg dialog

class morphologyDlg : public CDialog
{
// Construction
public:
	morphologyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(morphologyDlg)
	enum { IDD = IDD_MorphologyDlg };
	int		m_maskSelect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(morphologyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(morphologyDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MORPHOLOGYDLG_H__53CDF295_C7FC_4B01_A8F4_4BD5F562AD22__INCLUDED_)
