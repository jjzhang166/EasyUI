#include "stdafx.h"

CWindowFactory* CWindowFactory::GetInst()
{
	CWindowFactory* pInst = NULL;
	if(pInst == NULL){
		pInst = new CWindowFactory;
	}

	return pInst;
}

CWindowBase* CWindowFactory::GetWindow( LPCTSTR szType, CWindowBase* pParent )
{
	return GetInst()->GetObject(szType, pParent);
}

CWindowBase* CWindowFactory::GetObject( LPCTSTR szType, CWindowBase* pParent)
{
	CWindowBase* pWindow = NULL;
	if(_tcsicmp(szType,_T("label")) == 0){
		pWindow = new CDuiLabel(pParent);
	}
	else if(_tcsicmp(szType,_T("button")) == 0){
		pWindow = new CDuiButton(pParent);
	}
	else if(_tcsicmp(szType,_T("hori_layout")) == 0){
		pWindow = new CHoriLayout(pParent);
	}
	else if(_tcsicmp(szType,_T("vert_layout")) == 0){
		pWindow = new CVertLayout(pParent);
	}
	ATLASSERT(pWindow);

	return pWindow;
}

