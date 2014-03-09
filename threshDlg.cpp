// threshDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "threshDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// threshDlg dialog


threshDlg::threshDlg(CWnd* pParent /*=NULL*/)
	: CDialog(threshDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(threshDlg)
	m_Thresh = 128;
	//}}AFX_DATA_INIT
}


void threshDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(threshDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Thresh);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(threshDlg, CDialog)
	//{{AFX_MSG_MAP(threshDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// threshDlg message handlers
