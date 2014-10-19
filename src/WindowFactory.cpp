#include "stdafx.h"

CWindowFactory* CWindowFactory::GetInst()
{
	CWindowFactory* pInst = NULL;
	if(pInst == NULL){
		pInst = new CWindowFactory;
	}

	return pInst;
}

CUIWindowBase* CWindowFactory::GetWindow( LPCTSTR szType, CUIWindowBase* pParent )
{
	return GetInst()->GetObject(szType, pParent);
}

CUIWindowBase* CWindowFactory::GetObject( LPCTSTR szType, CUIWindowBase* pParent)
{
	CUIWindowBase* pWindow = NULL;
	if(_tcsicmp(szType, _T("label")) == 0){
		pWindow = new CUILabel(pParent);
	}
	else if(_tcsicmp(szType, _T("button")) == 0){
		pWindow = new CUIButton(pParent);
	}
	else if(_tcsicmp(szType, _T("hori_layout")) == 0){
		pWindow = new CUIHoriLayout(pParent);
	}
	else if(_tcsicmp(szType, _T("vert_layout")) == 0){
		pWindow = new CUIVertLayout(pParent);
	}
	else if(_tcsicmp(szType, _T("edit")) == 0){
		pWindow = new CUIEdit(pParent);
	}
	ATLASSERT(pWindow);

	return pWindow;
}

