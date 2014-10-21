#include "stdafx.h"

#include "InternalWebBrowser.cpp"

CUIWebBrowser::CUIWebBrowser( CUIWindowBase* pParent )
	: CUIWindowBase(pParent)
	, m_pInternalWebBrowser(new CInternalWebBrowser(this))
	, m_strUrlHome(_T("about:blank"))
{

}

CUIWebBrowser::~CUIWebBrowser()
{
	if(m_pInternalWebBrowser){
		delete m_pInternalWebBrowser;
		m_pInternalWebBrowser = NULL;
	}
}

LRESULT CUIWebBrowser::dui_OnCreate( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	m_pInternalWebBrowser->Show();
	m_pInternalWebBrowser->Navigate(m_strUrlHome.c_str());
	return TRUE;
}

LRESULT CUIWebBrowser::dui_OnSize( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	m_pInternalWebBrowser->RePos();
	return TRUE;
}

LRESULT CUIWebBrowser::dui_OnMove( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	m_pInternalWebBrowser->RePos();
	return TRUE;
}
