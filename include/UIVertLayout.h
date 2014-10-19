#pragma once

class EASYUI_API CUIVertLayout : public CUIContainerWindowBase
{
public:
	CUIVertLayout(CUIWindowBase* pParent);
	~CUIVertLayout(void);

	BEGIN_DUI_MSG_MAP(CUIContainerWindowBase)
		DUI_MSG_HANDLER(WM_SIZE,dui_OnSize)
		CHAIN_DUI_MSG_MAP(CUIContainerWindowBase)
	END_DUI_MESSAGE_MAP()

	LRESULT dui_OnSize(const CDuiMSG& duiMSG, BOOL& bHandled);
};

