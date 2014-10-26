#pragma once

class CUIContainerWindow
	: public CUIContainerWindowBase
{
public:
	CUIContainerWindow(CUIWindowBase* pParent);
	~CUIContainerWindow();

	virtual BOOL ParseAttribute( pugi::xml_node& node );

	BEGIN_DUI_MSG_MAP(CUIContainerWindow)
		DUI_MSG_HANDLER(WM_SIZE,dui_OnSize)
		CHAIN_DUI_MSG_MAP(CUIContainerWindowBase)
	END_DUI_MSG_MAP()

	LRESULT dui_OnSize(const CDuiMSG& duiMSG, BOOL& bHandled);

protected:
	//return val means size message handled
	bool LayoutVertical();
	bool LayoutHotizontal();
	bool LayoutFloat();

protected:
	std::wstring m_strLayout;//vertical,hotizontal,or float
};
