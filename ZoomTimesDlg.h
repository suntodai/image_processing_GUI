#if !defined(AFX_ZOOMTIMESDLG_H__5F0A7080_8A42_4C05_B3D2_4D3B6BC16B52__INCLUDED_)
#define AFX_ZOOMTIMESDLG_H__5F0A7080_8A42_4C05_B3D2_4D3B6BC16B52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomTimesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ZoomTimesDlg dialog

class ZoomTimesDlg : public CDialog
{
// Construction
public:
	ZoomTimesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ZoomTimesDlg)
	enum { IDD = IDD_ZoomTimesDlg };
	int		m_InsertStyle;
	int		m_ZoomTime;
	int		m_InOrOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZoomTimesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ZoomTimesDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMTIMESDLG_H__5F0A7080_8A42_4C05_B3D2_4D3B6BC16B52__INCLUDED_)
