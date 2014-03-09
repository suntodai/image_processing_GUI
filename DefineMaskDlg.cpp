// DefineMaskDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "DefineMaskDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DefineMaskDlg dialog


DefineMaskDlg::DefineMaskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DefineMaskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DefineMaskDlg)
	m_maskEdit1 = 0;
	m_maskEdit10 = 0;
	m_maskEdit11 = 0;
	m_maskEdit12 = 1;
	m_maskEdit13 = 1;
	m_maskEdit14 = 1;
	m_maskEdit15 = 0;
	m_maskEdit16 = 0;
	m_maskEdit17 = 0;
	m_maskEdit18 = 1;
	m_maskEdit19 = 0;
	m_maskEdit2 = 0;
	m_maskEdit20 = 0;
	m_maskEdit21 = 0;
	m_maskEdit22 = 0;
	m_maskEdit23 = 0;
	m_maskEdit24 = 0;
	m_maskEdit25 = 0;
	m_maskEdit3 = 0;
	m_maskEdit4 = 0;
	m_maskEdit5 = 0;
	m_maskEdit6 = 0;
	m_maskEdit7 = 0;
	m_maskEdit8 = 1;
	m_maskEdit9 = 0;
	//}}AFX_DATA_INIT
}


void DefineMaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DefineMaskDlg)
	DDX_Text(pDX, IDC_EDIT1, m_maskEdit1);
	DDX_Text(pDX, IDC_EDIT10, m_maskEdit10);
	DDX_Text(pDX, IDC_EDIT11, m_maskEdit11);
	DDX_Text(pDX, IDC_EDIT12, m_maskEdit12);
	DDX_Text(pDX, IDC_EDIT13, m_maskEdit13);
	DDX_Text(pDX, IDC_EDIT14, m_maskEdit14);
	DDX_Text(pDX, IDC_EDIT15, m_maskEdit15);
	DDX_Text(pDX, IDC_EDIT16, m_maskEdit16);
	DDX_Text(pDX, IDC_EDIT17, m_maskEdit17);
	DDX_Text(pDX, IDC_EDIT18, m_maskEdit18);
	DDX_Text(pDX, IDC_EDIT19, m_maskEdit19);
	DDX_Text(pDX, IDC_EDIT2, m_maskEdit2);
	DDX_Text(pDX, IDC_EDIT20, m_maskEdit20);
	DDX_Text(pDX, IDC_EDIT21, m_maskEdit21);
	DDX_Text(pDX, IDC_EDIT22, m_maskEdit22);
	DDX_Text(pDX, IDC_EDIT23, m_maskEdit23);
	DDX_Text(pDX, IDC_EDIT24, m_maskEdit24);
	DDX_Text(pDX, IDC_EDIT25, m_maskEdit25);
	DDX_Text(pDX, IDC_EDIT3, m_maskEdit3);
	DDX_Text(pDX, IDC_EDIT4, m_maskEdit4);
	DDX_Text(pDX, IDC_EDIT5, m_maskEdit5);
	DDX_Text(pDX, IDC_EDIT6, m_maskEdit6);
	DDX_Text(pDX, IDC_EDIT7, m_maskEdit7);
	DDX_Text(pDX, IDC_EDIT8, m_maskEdit8);
	DDX_Text(pDX, IDC_EDIT9, m_maskEdit9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DefineMaskDlg, CDialog)
	//{{AFX_MSG_MAP(DefineMaskDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DefineMaskDlg message handlers
