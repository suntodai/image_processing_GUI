// MutiOpenDocManager.cpp: implementation of the CMutiOpenDocManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo.h"
#include "MutiOpenDocManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMutiOpenDocManager::CMutiOpenDocManager()
{

}

CMutiOpenDocManager::~CMutiOpenDocManager()
{

}

void CMutiOpenDocManager::OnFileOpen()
{
	CStringList newNames;
	if(!DoPromptFileNames(newNames,AFX_IDS_OPENFILE,OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT,TRUE,NULL))
		return;
	POSITION pos=newNames.GetHeadPosition();
	while(pos)
	{
		CString newName=newNames.GetNext(pos);
		AfxGetApp()->OpenDocumentFile(newName);
	}

}

BOOL CMutiOpenDocManager::DoPromptFileNames(CStringList& fileNames, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate *pTemplate)
{
	CFileDialog dlgFile(bOpenFileDialog);

	CString title;
	VERIFY(title.LoadString(nIDSTitle));

	dlgFile.m_ofn.Flags |= lFlags;

	CString strFilter;
	CString strDefault;
	if (pTemplate != NULL)
	{
		ASSERT_VALID(pTemplate);
		AppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate, &strDefault);
	}
	else
	{
		// do for all doc template
		POSITION pos = m_templateList.GetHeadPosition();
		BOOL bFirst = TRUE;
		while (pos != NULL)
		{
			CDocTemplate* pTemplate = (CDocTemplate*)m_templateList.GetNext(pos);
			AppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate,
				bFirst ? &strDefault : NULL);
			bFirst = FALSE;
		}
	}

	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
    #ifndef _MAC
	strFilter += _T("*.*");
    #else
	strFilter += _T("****");
    #endif
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;
	dlgFile.m_ofn.lpstrFilter = strFilter;

	#ifndef _MAC
	dlgFile.m_ofn.lpstrTitle = title;
    #else
	dlgFile.m_ofn.lpstrPrompt = title;
    #endif

	CString strFileNames;
	dlgFile.m_ofn.lpstrFile=strFileNames.GetBuffer(2048);
	dlgFile.m_ofn.nMaxFile=2048;
	BOOL bResult=dlgFile.DoModal()==IDOK?TRUE:FALSE;
	strFileNames.ReleaseBuffer();
	if(!bResult)
		return FALSE;//取消打开文件操作
	//将文件名拷贝到一个字符串列表中
	POSITION pos=dlgFile.GetStartPosition();
	while(pos)
	{
		fileNames.AddTail(dlgFile.GetNextPathName(pos));
	}
	return
		TRUE;
}

//下面的函数是DoPromptFileNames函数中需要调用的模块函数
void CMutiOpenDocManager::AppendFilterSuffix(CString &filter, OPENFILENAME &ofn, CDocTemplate *pTemplate, CString *pstrDefaultExt)
{
	ASSERT_VALID(pTemplate);
	ASSERT_KINDOF(CDocTemplate, pTemplate);

	CString strFilterExt, strFilterName;
	if (pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt) &&
	 !strFilterExt.IsEmpty() &&
	 pTemplate->GetDocString(strFilterName, CDocTemplate::filterName) &&
	 !strFilterName.IsEmpty())
	{
		// a file based document template - add to filter list
		ASSERT(strFilterExt[0] == '.');
		if (pstrDefaultExt != NULL)
		{
			// set the default extension
			*pstrDefaultExt = ((LPCTSTR)strFilterExt) + 1;  // skip the '.'
			ofn.lpstrDefExt = (LPTSTR)(LPCTSTR)(*pstrDefaultExt);
			ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
		}

		// add to filter
		filter += strFilterName;
		ASSERT(!filter.IsEmpty());  // must have a file type name
		filter += (TCHAR)'\0';  // next string please
		filter += (TCHAR)'*';
		filter += strFilterExt;
		filter += (TCHAR)'\0';  // next string please
		ofn.nMaxCustFilter++;
	}
}


