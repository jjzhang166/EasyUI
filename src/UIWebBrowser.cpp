#include "stdafx.h"

#include "InternalWebBrowser.cpp"

CUIWebBrowser::CUIWebBrowser( CUIWindowBase* pParent )
	: CUIWindowBase(pParent)
	, m_pInternalWebBrowser(new CInternalWebBrowser(this))
	, m_strHomeUrl(_T("about:blank"))
	, m_bDelayCreate(false)
{
}

CUIWebBrowser::~CUIWebBrowser()
{
	if(m_pInternalWebBrowser){
		delete m_pInternalWebBrowser;
		m_pInternalWebBrowser = NULL;
	}
}

BOOL CUIWebBrowser::ParseAttribute( pugi::xml_node& node )
{
	__super::ParseAttribute(node);

	pugi::xml_attribute attr;
	attr = node.attribute(_T("home_page"));
	if(attr){
		m_strHomeUrl = attr.as_string();
	}

	attr = node.attribute(_T("delay_create"));
	if(attr){
		m_bDelayCreate = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	return TRUE;
}


void CUIWebBrowser::SetVisible( bool bVisible , bool bAlwaysCreate/* = false*/) 
{
	if(bAlwaysCreate){
		DelayCreate();
	}

	bVisible?m_pInternalWebBrowser->Show():m_pInternalWebBrowser->Hide();
	__super::SetVisible(bVisible);
}

void CUIWebBrowser::DelayCreate()
{
	if(m_bDelayCreate && m_pInternalWebBrowser && !m_pInternalWebBrowser->m_hWnd){
		m_pInternalWebBrowser->Create();
		if(m_bVisible){
			m_pInternalWebBrowser->Show();
		}

		if(!m_strCurrentUrl.empty()){
			m_pInternalWebBrowser->Navigate(m_strCurrentUrl.c_str());
		}
	}
}

BOOL CUIWebBrowser::Navigate( LPCTSTR szUrl, bool bAlwaysCreate/* = true*/)
{
	assert(m_pInternalWebBrowser);
	if(!szUrl){
		assert(false);
		return FALSE;
	}

	m_strCurrentUrl = szUrl?szUrl:_T("about:blank");

	if(bAlwaysCreate){
		DelayCreate();
	}

	return m_pInternalWebBrowser->Navigate(szUrl);
}

LRESULT CUIWebBrowser::dui_OnCreate( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	if(!m_bDelayCreate){
		m_pInternalWebBrowser->Create();
		if(IsVisible()){
			m_pInternalWebBrowser->Show();
		}
	}
	Navigate(m_strHomeUrl.c_str(), false);

	return TRUE;
}

LRESULT CUIWebBrowser::dui_OnSize( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	if(IsVisible()){
		m_pInternalWebBrowser->RePos(true);
	}
	
	return TRUE;
}

LRESULT CUIWebBrowser::dui_OnMove( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	if(IsVisible()){
		m_pInternalWebBrowser->RePos(true);
	}
	return TRUE;
}
