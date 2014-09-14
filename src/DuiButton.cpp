#include "stdafx.h"

using namespace Gdiplus;

CDuiButton::CDuiButton(CWindowBase* pParent)
	: CWindowBase(pParent)
	, m_bHover(false)
	, m_bPress(false)
{

}

BOOL CDuiButton::ParseAttribute( pugi::xml_node& node )
{
	__super::ParseAttribute(node);

	pugi::xml_attribute attr;
	attr = node.attribute(_T("three_state_img"));
	if(attr){
		m_str3StateImg = attr.as_string();
	}

	return TRUE;
}

LRESULT CDuiButton::dui_OnMouseEnter(const CDuiMSG& duiMsg,  BOOL bHandled)
{
	ATLASSERT(!m_bHover && !m_bPress);

	m_bHover = true;

	DUIInvalidate();

	return TRUE;
}

LRESULT CDuiButton::dui_OnMouseLeave(const CDuiMSG& duiMsg ,  BOOL bHandled)
{
	ATLASSERT(m_bHover);

	m_bHover = false;
	DUIInvalidate();

	return TRUE;
}

LRESULT CDuiButton::dui_OnLButtonDown( const CDuiMSG& duiMsg,  BOOL bHandled)
{
	ATLASSERT(m_bHover && !m_bPress);

	m_bPress = true;
	(SetCapture());
	DUIInvalidate();

	return TRUE;
}

LRESULT CDuiButton::dui_OnLButtonUp( const CDuiMSG& duiMsg,  BOOL bHandled)
{
	ATLASSERT(m_bPress);

	m_bPress = false;
	ReleaseCapture();
	DUIInvalidate();

	return TRUE;
}

void CDuiButton::PaintBkGnd( Gdiplus::Graphics* pGraphics)
{
	int nState = 0;
	if(!m_bEnable){
		nState = 1;
	}
	else if(m_bHover){
		if(m_bPress){
			nState = 2;
		}
		else{
			nState = 1;
		}
	}

	Image* pImage = CImageFactory::GetImage(m_str3StateImg.c_str());
	const int nCXImg = pImage->GetWidth()/3;
	const int nCYImg = pImage->GetHeight();
	
	//pGraphics->FillRectangle(CBrushFactory::GetInst()->GetObject(Color::Green),EasyRect(m_rcWnd));
	pGraphics->DrawImage(pImage, GdiplusHelper::EasyRect(m_rcWnd), nCXImg*nState,0,nCXImg,nCYImg,UnitPixel);

}

