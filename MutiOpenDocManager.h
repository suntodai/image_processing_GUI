// MutiOpenDocManager.h: interface for the CMutiOpenDocManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUTIOPENDOCMANAGER_H__8E7F5957_C207_4C9E_BA92_979203C32025__INCLUDED_)
#define AFX_MUTIOPENDOCMANAGER_H__8E7F5957_C207_4C9E_BA92_979203C32025__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMutiOpenDocManager : public CDocManager  
{
public:
	virtual BOOL DoPromptFileNames(CStringList& fileNames,UINT nIDSTitle,DWORD lFlags,BOOL bOpenFileDialog,CDocTemplate* pTemplate);
	virtual void OnFileOpen();
	CMutiOpenDocManager();
	virtual ~CMutiOpenDocManager();
    void AppendFilterSuffix(CString &filter, OPENFILENAME &ofn, CDocTemplate *pTemplate, CString *pstrDefaultExt);

};

#endif // !defined(AFX_MUTIOPENDOCMANAGER_H__8E7F5957_C207_4C9E_BA92_979203C32025__INCLUDED_)
