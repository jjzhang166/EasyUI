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

#define DUI_BMCLICK_HANDLER(szCtrlName,func)\
			if(uMsg == BM_CLICK && duiMSG.pSrcCtrl && duiMSG.pSrcCtrl->GetName()==szCtrlName)\
			{\
				func(duiMSG,bHandled);\
				if(bHandled){\
				return TRUE;\
				}\
			}

#define CHAIN_DUI_MSG_MAP(theChainClass)\
			{ \
				if(theChainClass::ProcessDuiWindowMessage(uMsg, duiMSG)) \
					return TRUE; \
			}

#define END_DUI_MESSAGE_MAP()\
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

