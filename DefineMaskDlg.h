#if !defined(AFX_DEFINEMASKDLG_H__0CDC473B_BDC3_4254_8AE7_57323BD9D85E__INCLUDED_)
#define AFX_DEFINEMASKDLG_H__0CDC473B_BDC3_4254_8AE7_57323BD9D85E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DefineMaskDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DefineMaskDlg dialog

class DefineMaskDlg : public CDialog
{
// Construction
public:
	DefineMaskDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DefineMaskDlg)
	enum { IDD = IDD_DefineMask };
	int		m_maskEdit1;
	int		m_maskEdit10;
	int		m_maskEdit11;
	int		m_maskEdit12;
	int		m_maskEdit13;
	int		m_maskEdit14;
	int		m_maskEdit15;
	int		m_maskEdit16;
	int		m_maskEdit17;
	int		m_maskEdit18;
	int		m_maskEdit19;
	int		m_maskEdit2;
	int		m_maskEdit20;
	int		m_maskEdit21;
	int		m_maskEdit22;
	int		m_maskEdit23;
	int		m_maskEdit24;
	int		m_maskEdit25;
	int		m_maskEdit3;
	int		m_maskEdit4;
	int		m_maskEdit5;
	int		m_maskEdit6;
	int		m_maskEdit7;
	int		m_maskEdit8;
	int		m_maskEdit9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DefineMaskDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DefineMaskDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEFINEMASKDLG_H__0CDC473B_BDC3_4254_8AE7_57323BD9D85E__INCLUDED_)
