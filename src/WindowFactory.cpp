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
	else if(_tcsicmp(szType, _T("container")) == 0){
		pWindow = new CUIContainerWindow(pParent);
	}
	else if(_tcsicmp(szType, _T("edit")) == 0){
		pWindow = new CUIEdit(pParent);
	}
	else if(_tcsicmp(szType, _T("web_browser")) == 0){
		pWindow = new CUIWebBrowser(pParent);
	}
	else if(_tcsicmp(szType, _T("radio_group")) == 0){
		pWindow = new CUIRadioGroup(pParent);
	}
	else if(_tcsicmp(szType, _T("radio")) == 0){
		pWindow = new CUIRadio(pParent);
	}

	ATLASSERT(pWindow);

	return pWindow;
}

