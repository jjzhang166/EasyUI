#pragma once
class CMainWnd
	: public CUITopWindow
{
public:
	CMainWnd(){};

	BEGIN_DUI_MSG_MAP(CMainWnd)
		DUI_BMCLICK_HANDLER(_T("sys_btn_close"),dui_OnBtnClose)
		CHAIN_DUI_MSG_MAP(CUITopWindow)
	END_DUI_MESSAGE_MAP()

	LRESULT dui_OnBtnClose(const CDuiMSG& duiMSG, BOOL& bHandled){
		DestroyWindow();

		return TRUE;
	}
};
