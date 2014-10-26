#include "stdafx.h"

CUIContainerWindow::CUIContainerWindow( CUIWindowBase* pParent )
	: CUIContainerWindowBase(pParent)
{

}

CUIContainerWindow::~CUIContainerWindow()
{

}

BOOL CUIContainerWindow::ParseAttribute( pugi::xml_node& node )
{
	__super::ParseAttribute(node);

	pugi::xml_attribute attr;
	attr = node.attribute(_T("layout"));
	if(attr){
		m_strLayout = attr.as_string();
	}
	return TRUE;
}

LRESULT CUIContainerWindow::dui_OnSize( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	if(m_strLayout.empty()|| m_strLayout == _T("float")){
		bHandled = LayoutFloat()?TRUE:FALSE;
	}
	else if(m_strLayout == _T("vertical")){
		bHandled = LayoutVertical()?TRUE:FALSE;
	}
	else if(m_strLayout == _T("horizontal")){
		bHandled = LayoutHotizontal()?TRUE:FALSE;
	}

	return TRUE;
}

bool CUIContainerWindow::LayoutVertical()
{
	if(m_childWndList.empty()){
		return TRUE;
	}

	if(!IsVisible()){
		return TRUE;
	}

	CRect rcRemain(m_rcWnd);
	rcRemain.DeflateRect(m_rcPadding);

	CRect rcRes;
	CRect rcMargin;
	IterChildWndList iter;

	for( iter = m_childWndList.begin(); iter != m_childWndList.end(); ++iter ){
		CUIWindowBase* pItem = (*iter);
		if(!pItem || !pItem->IsVisible()){
			continue;
		}

		//is float
		if(pItem->IsFloat()){
			pItem->CalcWindowFloatPos(rcRes);
		}
		//not float
		//exhaust space
		else if(rcRemain.top >= rcRemain.bottom){
			//set rect empty
			rcRes = rcRemain;
			rcRes.top = rcRes.bottom;
		}
		else{
			//add maring-top
			pItem->GetMargin(rcMargin);
			rcRemain.top += rcMargin.top;

			//calc window pos
			pItem->CalcWindowPos(rcRemain, rcRes);

			//keep margin-bottom room
			if(rcRemain.bottom - rcRes.bottom < rcMargin.bottom){
				rcRes.bottom = max(rcRes.top, rcRemain.bottom - rcMargin.bottom);
			}

			//modify remain space
			rcRemain.top += rcRes.Height() + rcMargin.bottom;
		}

		//repos wnd
		pItem->MoveWindow(&rcRes);
	}

	return true;
}

bool CUIContainerWindow::LayoutHotizontal()
{
	if(m_childWndList.empty()){
		return TRUE;
	}

	if(!IsVisible()){
		return TRUE;
	}

	CRect rcRemain(m_rcWnd);
	rcRemain.DeflateRect(m_rcPadding);

	CRect rcRes;
	CRect rcMargin;
	IterChildWndList iter;

	for( iter = m_childWndList.begin(); iter != m_childWndList.end(); ++iter ){
		CUIWindowBase* pItem = (*iter);
		if(!pItem || !pItem->IsVisible()){
			continue;
		}

		//is float
		if(pItem->IsFloat()){
			pItem->CalcWindowFloatPos(rcRes);
		}
		//not float
		//exhaust space
		else if(rcRemain.left >= rcRemain.right){
			//set rect empty
			rcRes = rcRemain;
			rcRes.left= rcRes.top;
		}
		else{
			//add maring-top
			pItem->GetMargin(rcMargin);
			rcRemain.left += rcMargin.left;

			//calc window pos
			pItem->CalcWindowPos(rcRemain, rcRes);

			//keep margin-bottom room
			if(rcRemain.right - rcRes.right < rcMargin.right){
				rcRes.right = max(rcRes.top, rcRemain.right - rcMargin.right);
			}

			//modify remain space
			rcRemain.left += rcRes.Width() + rcMargin.left;
		}

		//repos wnd
		pItem->MoveWindow(&rcRes);
	}

	return true;
}

bool CUIContainerWindow::LayoutFloat()
{
	for(IterChildWndList iter = m_childWndList.begin(); iter != m_childWndList.end(); ++iter){
		CRect rcWnd;
		(*iter)->CalcWindowFloatPos(rcWnd);
		(*iter)->MoveWindow(rcWnd);
	}
	return true;
}
