#include "stdafx.h"

CUIRadio::CUIRadio( CUIWindowBase* pParent )
	: CUIButton(pParent)
	, m_bSelected(false)
	, m_nInitTextLeftPos(-1)//这里用负数，以防布局文件中是0的情况
	, m_nTextLeftPos(0)
{

}

CUIRadio::~CUIRadio()
{

}

bool CUIRadio::IsSelected()
{
	return m_bSelected;
}

bool CUIRadio::SetSelected()
{
	//already selected, just return 
	if(m_bSelected){
		return true;
	}

	//notify contianer, which will call setSelectedImpl
	CUIRadioGroup* group = dynamic_cast<CUIRadioGroup*>(GetParent());
	if(group){
		return group->SelectItem(this);
	}
	//contianer is not exist, we must call SelectItemImpl
	else{
		return SetSelectedImpl();
	}
}

bool CUIRadio::ClearSelected()
{
	//already not selected, just return 
	if(!m_bSelected){
		return true;
	}

	//notify contianer, which will call ClearSelectedImpl
	CUIRadioGroup* group = dynamic_cast<CUIRadioGroup*>(GetParent());
	if(group){
		ATLASSERT(this == group->GetSelectedItem());
		if(this == group->GetSelectedItem()){
			return group->SelectItem(NULL);
		}
		else{
			return true;
		}
	}
	//contianer is not exist, we must call ClearSelectedImpl
	else{
		return ClearSelectedImpl();
	}
}

BOOL CUIRadio::ParseAttribute( pugi::xml_node& node )
{
	__super::ParseAttribute(node);

	pugi::xml_attribute attr;
	attr = node.attribute(_T("selected_img"));
	if(attr){
		m_strSelectedImg = attr.as_string();
	}

	attr = node.attribute(_T("text_left_margin"));
	if(attr){
		m_nInitTextLeftPos = attr.as_int();
	}

	return TRUE;
}

void CUIRadio::PaintBkGnd( Gdiplus::Graphics* pGraphics, const CRect& rcArea )
{
	Gdiplus::Image* pStateImage = NULL;
	if( !m_strStateImg.empty() && m_nStateCount!=0 &&
		( pStateImage = CImageFactory::GetImage(m_strStateImg.c_str(), GetWindowInfo())) 
		){

		//get per state size
		const int nCxPerState = pStateImage->GetWidth()/m_nStateCount;
		const int nCyPerState = pStateImage->GetHeight();

		//perpare text left margin
		m_nTextLeftPos = nCxPerState + RADIO_TEXT_LEFT_MARGIN;

		//draw state img
		CRect rcPaintArea(m_rcWnd);
		rcPaintArea.top += (rcPaintArea.Height() - nCyPerState)/2;
		rcPaintArea.bottom = rcPaintArea.top + nCyPerState;
		rcPaintArea.right = rcPaintArea.left + nCxPerState;
		CUIButton::PaintBkGnd(pGraphics, rcPaintArea);

		//draw selected img
		Gdiplus::Image* pSelectedImg = NULL;
		if(m_bSelected && !m_strSelectedImg.empty() && 
			( pSelectedImg = CImageFactory::GetImage(m_strSelectedImg.c_str(), GetWindowInfo()) ) 
			){
				const int nCx = pSelectedImg->GetWidth();
				const int nCy = pSelectedImg->GetHeight();
				CRect rcSelectedImg(rcPaintArea);
				rcSelectedImg.left += (rcSelectedImg.Width() - nCx)/2;
				rcSelectedImg.right = rcSelectedImg.left + nCx;
				rcSelectedImg.top += (rcSelectedImg.Height() - nCy)/2;
				rcSelectedImg.bottom = rcSelectedImg.top + nCy;
				pGraphics->DrawImage(pSelectedImg, GdiplusHelper::Rect2GPRectF(rcSelectedImg), 0,0,nCx,nCy,Gdiplus::UnitPixel);
		}
	}	
}

void CUIRadio::PaintText( Gdiplus::Graphics* pGraphics, const CRect& rcArea )
{
	CRect rcDrawArea(rcArea);
	if(m_nInitTextLeftPos != -1){
		rcDrawArea.left += m_nInitTextLeftPos;
	}
	else{
		rcDrawArea.left += m_nTextLeftPos;
	}
	rcDrawArea.right = max(rcDrawArea.right, rcDrawArea.left);

	__super::PaintText(pGraphics, rcDrawArea);
}

LRESULT CUIRadio::dui_OnLButtonDown( const CDuiMSG& duiMsg, BOOL& bHandled )
{
	BOOL bRes = CUIButton::dui_OnLButtonDown(duiMsg, bHandled);
	bHandled = TRUE;

	//noly can become to selected, not become to unselected
	if(!m_bSelected){
		SetSelected();
	}

	return bRes;
}

bool CUIRadio::SetSelectedImpl()
{
	if(!m_bSelected){
		m_bSelected = true;
		SendDuiMessage(GetRoot(), DUIMSG_RADIO_SELECTED, this);
		UIInvalidate();
	}

	return true;
}

bool CUIRadio::ClearSelectedImpl()
{
	if(m_bSelected){
		m_bSelected = false;
		SendDuiMessage(GetRoot(), DUIMSG_RADIO_UNSELECTED, this);
		UIInvalidate();
	}

	return true;
}
