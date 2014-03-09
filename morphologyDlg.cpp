// morphologyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "morphologyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// morphologyDlg dialog


morphologyDlg::morphologyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(morphologyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(morphologyDlg)
	m_maskSelect = 0;
	//}}AFX_DATA_INIT
}


void morphologyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(morphologyDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_maskSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(morphologyDlg, CDialog)
	//{{AFX_MSG_MAP(morphologyDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// morphologyDlg message handlers
