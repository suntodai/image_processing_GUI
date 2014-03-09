// linearStretch.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "linearStretch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// linearStretch dialog


linearStretch::linearStretch(CWnd* pParent /*=NULL*/)
	: CDialog(linearStretch::IDD, pParent)
{
	//{{AFX_DATA_INIT(linearStretch)
	m_point1X = 50;
	m_point1Y = 30;
	m_point2X = 220;
	m_point2Y = 200;
	//}}AFX_DATA_INIT
}


void linearStretch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(linearStretch)
	DDX_Text(pDX, IDC_EDIT1, m_point1X);
	DDX_Text(pDX, IDC_EDIT2, m_point1Y);
	DDX_Text(pDX, IDC_EDIT3, m_point2X);
	DDX_Text(pDX, IDC_EDIT4, m_point2Y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(linearStretch, CDialog)
	//{{AFX_MSG_MAP(linearStretch)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// linearStretch message handlers
