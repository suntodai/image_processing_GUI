#if !defined(AFX_NOISEDLG_H__AD29EED4_0C01_4F6E_B64A_40C9817DC973__INCLUDED_)
#define AFX_NOISEDLG_H__AD29EED4_0C01_4F6E_B64A_40C9817DC973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// noiseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// noiseDlg dialog

class noiseDlg : public CDialog
{
// Construction
public:
	noiseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(noiseDlg)
	enum { IDD = IDD_NoiseDlg };
	BOOL	m_noiseAuto;
	double	m_NoiseVar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(noiseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(noiseDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOISEDLG_H__AD29EED4_0C01_4F6E_B64A_40C9817DC973__INCLUDED_)
