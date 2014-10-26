#pragma once

class CInternalWebBrowser;


class CUIWebBrowser
	: public CUIWindowBase
{
public:
	CUIWebBrowser(CUIWindowBase* pParent);
	~CUIWebBrowser();

	BOOL ParseAttribute( pugi::xml_node& node );

	BEGIN_DUI_MSG_MAP(CUIWebBrowser)
		DUI_MSG_HANDLER(WM_CREATE, dui_OnCreate)
		DUI_MSG_HANDLER(WM_SIZE, dui_OnSize)
		DUI_MSG_HANDLER(WM_MOVE, dui_OnMove)
	END_DUI_MSG_MAP()

	LRESULT dui_OnCreate(const CDuiMSG& duiMSG, BOOL& bHandled);
	LRESULT dui_OnSize(const CDuiMSG& duiMSG, BOOL& bHandled);
	LRESULT dui_OnMove(const CDuiMSG& duiMSG, BOOL& bHandled);
private:
	CInternalWebBrowser* m_pInternalWebBrowser;
	std::wstring m_strUrlHome;
};
