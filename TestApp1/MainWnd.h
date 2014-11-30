#pragma once
class CMainWnd
	: public CUITopWindow
{
public:
	CMainWnd(){};

	BEGIN_DUI_MSG_MAP(CMainWnd)
		DUI_BUTTON_CLICK_HANDLER(_T("sys_btn_close"),dui_OnBtnClose)
		DUI_RADIO_SELECTED_HANDLER(_T("radio1"),dui_OnRadio1)
		DUI_RADIO_SELECTED_HANDLER(_T("radio2"),dui_OnRadio2)
		DUI_RADIO_SELECTED_HANDLER(_T("radio3"),dui_OnRadio3)
		CHAIN_DUI_MSG_MAP(CUITopWindow)
	END_DUI_MSG_MAP()

	LRESULT dui_OnBtnClose(const CDuiMSG& duiMSG, BOOL& bHandled){
		DestroyWindow();

		return TRUE;
	}

	LRESULT dui_OnRadio1(const CDuiMSG& duiMSG, BOOL& bHandled){
		bHandled = TRUE;

		CUIWebBrowser* pwb1 = (CUIWebBrowser*)((CUIContainerWindowBase*)GetRoot())->FindChild(_T("wb1"), eFindChild_Recursive);
		CUIWebBrowser* pwb2 = (CUIWebBrowser*)((CUIContainerWindowBase*)GetRoot())->FindChild(_T("wb2"), eFindChild_Recursive);
		CUIWebBrowser* pwb3 = (CUIWebBrowser*)((CUIContainerWindowBase*)GetRoot())->FindChild(_T("wb3"), eFindChild_Recursive);
		pwb1->SetVisible(true);
		pwb2->SetVisible(false);
		pwb3->SetVisible(false);

		return TRUE;
	}

	LRESULT dui_OnRadio2(const CDuiMSG& duiMSG, BOOL& bHandled){
		bHandled = TRUE;

		CUIWebBrowser* pwb1 = (CUIWebBrowser*)((CUIContainerWindowBase*)GetRoot())->FindChild(_T("wb1"), eFindChild_Recursive);
		CUIWebBrowser* pwb2 = (CUIWebBrowser*)((CUIContainerWindowBase*)GetRoot())->FindChild(_T("wb2"), eFindChild_Recursive);
		CUIWebBrowser* pwb3 = (CUIWebBrowser*)((CUIContainerWindowBase*)GetRoot())->FindChild(_T("wb3"), eFindChild_Recursive);
		pwb1->SetVisible(false);
		pwb2->SetVisible(true);
		pwb3->SetVisible(false);

		return TRUE;
	}

	LRESULT dui_OnRadio3(const CDuiMSG& duiMSG, BOOL& bHandled){
		bHandled = TRUE;

		CUIWebBrowser* pwb1 = (CUIWebBrowser*)((CUIContainerWindowBase*)GetRoot())->FindChild(_T("wb1"), eFindChild_Recursive);
		CUIWebBrowser* pwb2 = (CUIWebBrowser*)((CUIContainerWindowBase*)GetRoot())->FindChild(_T("wb2"), eFindChild_Recursive);
		CUIWebBrowser* pwb3 = (CUIWebBrowser*)((CUIContainerWindowBase*)GetRoot())->FindChild(_T("wb3"), eFindChild_Recursive);

		pwb1->SetVisible(false);
		pwb2->SetVisible(false);
		pwb3->SetVisible(true);
		

		return TRUE;
	}
};
