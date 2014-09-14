#pragma once

class EASY_UI_API CVertLayout : public CContainerWindowBase
{
public:
	CVertLayout(CWindowBase* pParent);
	~CVertLayout(void);

	BEGIN_DUI_MSG_MAP(CContainerWindowBase)
		DUI_MSG_HANDLER(WM_SIZE,dui_OnSize)
		CHAIN_DUI_MSG_MAP(CContainerWindowBase)
	END_DUI_MESSAGE_MAP()

	LRESULT dui_OnSize(const CDuiMSG& duiMSG, BOOL& bHandled);
};

