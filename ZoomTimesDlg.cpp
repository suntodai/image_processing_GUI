// ZoomTimesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "ZoomTimesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZoomTimesDlg dialog


ZoomTimesDlg::ZoomTimesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ZoomTimesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ZoomTimesDlg)	
	m_ZoomTime = 1;
	m_InOrOut = 0;//0 ËõÐ¡
	m_InsertStyle = 1;//0 Ë«ÏßÐÔ
	//}}AFX_DATA_INIT
}


void ZoomTimesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZoomTimesDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_InsertStyle);
	DDX_Text(pDX, IDC_EDIT1, m_ZoomTime);
	DDX_Radio(pDX, IDC_RADIO3, m_InOrOut);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ZoomTimesDlg, CDialog)
	//{{AFX_MSG_MAP(ZoomTimesDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ZoomTimesDlg message handlers
