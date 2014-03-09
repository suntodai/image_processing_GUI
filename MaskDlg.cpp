// MaskDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "MaskDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MaskDlg dialog


MaskDlg::MaskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MaskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MaskDlg)
	m_MaskStyle = 0;
	//}}AFX_DATA_INIT
}


void MaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MaskDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_MaskStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MaskDlg, CDialog)
	//{{AFX_MSG_MAP(MaskDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MaskDlg message handlers
