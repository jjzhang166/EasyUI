#pragma once

class CInternalEdit;

class EASYUI_API CUIEdit
	: public CUILabel
{
public:
	CUIEdit(CUIWindowBase* pParent);

	bool IsPasswordMode(){return m_bPasswordMode;}

	BEGIN_DUI_MSG_MAP(CUIEdit)
		DUI_MSG_HANDLER(WM_LBUTTONDOWN, dui_OnLButtonDown)
		DUI_MSG_HANDLER(WM_SETFOCUS, dui_OnSetFocus)
		DUI_MSG_HANDLER(WM_KILLFOCUS, dui_OnKillFocus)
		DUI_MSG_HANDLER(WM_SIZE, dui_OnSize)
		DUI_MSG_HANDLER(WM_MOVE, dui_OnMove)
	END_DUI_MESSAGE_MAP()

	LRESULT dui_OnLButtonDown(const CDuiMSG& duiMSG, BOOL& bHandled);
	LRESULT dui_OnSetFocus(const CDuiMSG& duiMSG, BOOL& bHandled);
	LRESULT dui_OnKillFocus(const CDuiMSG& duiMSG, BOOL& bHandled);
	LRESULT dui_OnSize(const CDuiMSG& duiMSG, BOOL& bHandled);
	LRESULT dui_OnMove(const CDuiMSG& duiMSG, BOOL& bHandled);

;
private:
	CInternalEdit*	m_pInternalEdit;
	bool			m_bPasswordMode;
};