#include "stdafx.h"

using namespace Gdiplus;

CUIButton::CUIButton(CUIWindowBase* pParent)
	: CUIWindowBase(pParent)
	, m_bHover(false)
	, m_bPress(false)
	, m_nStateCount(0)
{

}

BOOL CUIButton::ParseAttribute( pugi::xml_node& node )
{
	__super::ParseAttribute(node);

	pugi::xml_attribute attr;
	attr = node.attribute(_T("three_state_img"));
	if(attr){
		m_strStateImg = attr.as_string();
		m_nStateCount = 3;
	}
	
	attr = node.attribute(_T("four_state_img"));
	if(attr){
		m_strStateImg = attr.as_string();
		m_nStateCount = 4;
	}

	return TRUE;
}

LRESULT CUIButton::dui_OnMouseEnter(const CDuiMSG& duiMsg,  BOOL& bHandled)
{
	ATLASSERT(!m_bHover && !m_bPress);

	m_bHover = true;

	UIInvalidate();

	return TRUE;
}

LRESULT CUIButton::dui_OnMouseLeave(const CDuiMSG& duiMsg ,  BOOL& bHandled)
{
	ATLASSERT(m_bHover);

	m_bHover = false;
	UIInvalidate();

	return TRUE;
}

LRESULT CUIButton::dui_OnLButtonDown( const CDuiMSG& duiMsg,  BOOL& bHandled)
{
	//ATLASSERT(m_bHover && !m_bPress);

	m_bPress = true;
	SetCapture();
	UIInvalidate();

	return TRUE;
}

LRESULT CUIButton::dui_OnLButtonUp( const CDuiMSG& duiMsg,  BOOL& bHandled)
{
	ATLASSERT(m_bPress);

	//has pressed and not move out of it
	if(m_bPress && 
		m_rcWnd.PtInRect( CPoint(GET_X_LPARAM(duiMsg.lParam), GET_Y_LPARAM(duiMsg.lParam)) )
		){
			SendDuiMessage(GetRoot(),BM_CLICK,this);
	}
	m_bPress = false;
	ReleaseCapture();
	UIInvalidate();

	return TRUE;
}

void CUIButton::PaintBkGnd( Gdiplus::Graphics* pGraphics, const CRect& rcArea)
{
	//if no bk img, return immdiate
	if(m_strStateImg.empty() || m_nStateCount==0){
		return ;
	}

	int nState = 0;
	if(!m_bEnable){
		if(m_nStateCount == 4){//4state, have disable state
			nState = 3;
		}
		else{	//3state, have not disable state, just show normal state
			nState = 1;
		}
		
	}
	else if(m_bHover){
		if(m_bPress){
			nState = 2;
		}
		else{
			nState = 1;
		}
	}

	Image* pImage = CImageFactory::GetImage(m_strStateImg.c_str(), GetWindowInfo());
	const int nCXImg = pImage->GetWidth()/m_nStateCount;
	const int nCYImg = pImage->GetHeight();
	
	pGraphics->DrawImage(pImage, GdiplusHelper::Rect2GPRectF(rcArea), nCXImg*nState,0,nCXImg,nCYImg,UnitPixel);
}

