#pragma once

#define DECLARE_DUI_MSG_MAP(thisClass)\
	public:\
		virtual BOOL ProcessDuiWindowMessage(UINT uMsg, const CDuiMSG& duiMSG) = 0;

#define BEGIN_DUI_MSG_MAP(thisClass)\
	public:\
		virtual BOOL ProcessDuiWindowMessage(UINT uMsg, const CDuiMSG& duiMSG){\
			BOOL bHandled = TRUE;\

#define DUI_MSG_HANDLER(msg,func)\
			if(msg == uMsg){\
				bHandled = FALSE;\
				func(duiMSG,bHandled);\
				if(bHandled){\
					return TRUE;\
				}\
			}

#define DUI_BUTTON_CLICK_HANDLER(szCtrlName,func)\
			if(uMsg == BM_CLICK && duiMSG.pSrcCtrl && duiMSG.pSrcCtrl->GetName()==szCtrlName)\
			{\
				func(duiMSG,bHandled);\
				if(bHandled){\
				return TRUE;\
				}\
			}

#define DUI_RADIO_SELECTED_HANDLER(szCtrlName,func)\
			if(uMsg == DUIMSG_RADIO_SELECTED && duiMSG.pSrcCtrl && duiMSG.pSrcCtrl->GetName()==szCtrlName)\
			{\
				func(duiMSG, bHandled);\
				if(bHandled){\
					return TRUE;\
				}\
			}

#define CHAIN_DUI_MSG_MAP(theChainClass)\
			{ \
				if(theChainClass::ProcessDuiWindowMessage(uMsg, duiMSG)) \
					return TRUE; \
			}

#define END_DUI_MSG_MAP()\
			return FALSE;\
		}

class EASYUI_API CDuiMSG{
public:
	CDuiMSG(CUIWindowBase* pSrcCtrl, WPARAM wParam = 0, LPARAM lParam = 0){
		this->pSrcCtrl = pSrcCtrl;
		this->wParam = wParam;
		this->lParam = lParam;
	}

	CUIWindowBase* pSrcCtrl;
	WPARAM wParam;
	LPARAM lParam;
};

#define WM_UIMESSAGE_START (WM_USER+1)
#define WM_MOUSEENTER (WM_UIMESSAGE_START+1)

#define DUIMSG_RADIO_SELECTED WM_UIMESSAGE_START+100
#define DUIMSG_RADIO_UNSELECTED WM_UIMESSAGE_START+101

class EASYUI_API CMessageHandler
{
public:
	CMessageHandler(void){};
	~CMessageHandler(void){};

	virtual LRESULT SendDuiMessage(UINT uMsg, const CDuiMSG& duiMSG);

	virtual LRESULT SendDuiMessage(UINT uMsg, CUIWindowBase* pSrcCtrl = NULL, WPARAM wParam = 0, LPARAM lParam = 0);

	static LRESULT SendDuiMessage(CUIWindowBase* pWindow, UINT uMsg, const CDuiMSG& duiMSG);

	static LRESULT SendDuiMessage(CUIWindowBase* pWindow, INT uMsg, CUIWindowBase* pSrcCtrl = NULL, WPARAM wParam = 0, LPARAM lParam = 0);

	DECLARE_DUI_MSG_MAP(CMessageHandler);
};

