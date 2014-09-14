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
			if(msg == BM_CLICK && duiMSG.pSrcCtrl && duiMSG.pSrcCtrl->GetName()==szCtrlName)\
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

class EASY_UI_API CDuiMSG{
public:
	CDuiMSG(CWindowBase* pSrcCtrl, WPARAM wParam = 0, LPARAM lParam = 0){
		this->pSrcCtrl = pSrcCtrl;
		this->wParam = wParam;
		this->lParam = lParam;
	}

	CWindowBase* pSrcCtrl;
	WPARAM wParam;
	LPARAM lParam;
};

#define WM_MOUSEENTER (WM_USER+1)

class EASY_UI_API CMessageHandler
{
public:
	CMessageHandler(void){};
	~CMessageHandler(void){};

	virtual LRESULT SendDuiMessage(UINT uMsg, const CDuiMSG& duiMSG);

	virtual LRESULT SendDuiMessage(UINT uMsg, CWindowBase* pSrcCtrl = NULL, WPARAM wParam = 0, LPARAM lParam = 0);

	static LRESULT SendDuiMessage(CWindowBase* pWindow, UINT uMsg, const CDuiMSG& duiMSG);

	static LRESULT SendDuiMessage(CWindowBase* pWindow, INT uMsg, CWindowBase* pSrcCtrl = NULL, WPARAM wParam = 0, LPARAM lParam = 0);

	DECLARE_DUI_MSG_MAP(CMessageHandler);
};

