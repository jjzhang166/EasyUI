#pragma once

class CInternalWebBrowser;


class EASYUI_API CUIWebBrowser
	: public CUIWindowBase
{
public:
	CUIWebBrowser(CUIWindowBase* pParent);
	~CUIWebBrowser();

	virtual bool IsDUIWindow() const { return false; }
	BOOL ParseAttribute( pugi::xml_node& node );
	void SetVisible(bool bVisible, bool bAlwaysCreate = false);
	void DelayCreate();
	BOOL Navigate(LPCTSTR szUrl, bool bAlwaysCreate = true);

	BEGIN_DUI_MSG_MAP(CUIWebBrowser)
		DUI_MSG_HANDLER(WM_CREATE, dui_OnCreate)
		DUI_MSG_HANDLER(WM_SIZE, dui_OnSize)
		DUI_MSG_HANDLER(WM_MOVE, dui_OnMove)
	END_DUI_MSG_MAP()

	LRESULT dui_OnCreate(const CDuiMSG& duiMSG, BOOL& bHandled);
	LRESULT dui_OnSize(const CDuiMSG& duiMSG, BOOL& bHandled);
	LRESULT dui_OnMove(const CDuiMSG& duiMSG, BOOL& bHandled);

protected:

private:
	CInternalWebBrowser* m_pInternalWebBrowser;
	std::wstring m_strHomeUrl;
	std::wstring m_strCurrentUrl;
	bool m_bDelayCreate;
};
