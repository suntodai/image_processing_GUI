// noiseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "noiseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// noiseDlg dialog


noiseDlg::noiseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(noiseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(noiseDlg)
	m_noiseAuto = FALSE;
	m_NoiseVar = 0.0;
	//}}AFX_DATA_INIT
}


void noiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(noiseDlg)
	DDX_Text(pDX, IDC_NioseAuto, m_noiseAuto);
	DDX_Text(pDX, IDC_NoiseVar, m_NoiseVar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(noiseDlg, CDialog)
	//{{AFX_MSG_MAP(noiseDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// noiseDlg message handlers
