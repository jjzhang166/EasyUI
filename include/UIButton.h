#pragma once

class EASYUI_API CUIButton : public CUIWindowBase{
public:
	CUIButton(CUIWindowBase* pParent);		

	BEGIN_DUI_MSG_MAP(CButton)
		DUI_MSG_HANDLER(WM_MOUSEENTER,dui_OnMouseEnter)
		DUI_MSG_HANDLER(WM_MOUSELEAVE,dui_OnMouseLeave)
		DUI_MSG_HANDLER(WM_LBUTTONDOWN,dui_OnLButtonDown)
		DUI_MSG_HANDLER(WM_LBUTTONDBLCLK,dui_OnLButtonDown)
		DUI_MSG_HANDLER(WM_LBUTTONUP,dui_OnLButtonUp)
	END_DUI_MESSAGE_MAP()

	virtual BOOL ParseAttribute( pugi::xml_node& node );

	LRESULT dui_OnMouseEnter(const CDuiMSG& duiMsg, BOOL bHandled);
	LRESULT dui_OnMouseLeave(const CDuiMSG& duiMsg,  BOOL bHandled);
	LRESULT dui_OnLButtonDown(const CDuiMSG& duiMsg,  BOOL bHandled);
	//LRESULT dui_OnLButtonDbClk(const CDuiMSG& duiMsg,  BOOL bHandled);
	LRESULT dui_OnLButtonUp(const CDuiMSG& duiMsg,  BOOL bHandled);

	virtual void PaintBkGnd(Gdiplus::Graphics* pGraphics);

protected:
	bool m_bHover;
	bool m_bPress;

	std::wstring m_str3StateImg;
};


