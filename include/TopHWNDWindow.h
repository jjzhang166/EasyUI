#pragma once

class EASY_UI_API CTopHWNDWindow	: public CWindowImpl<CTopHWNDWindow>
						, public CContainerWindowBase
{
public:
	CTopHWNDWindow(void);
	~CTopHWNDWindow(void);

	virtual BOOL IsDUIWindow(){return TRUE;};

	DECLARE_WND_CLASS(_T("SkinUI_HWND"))

	BEGIN_MSG_MAP(CTopHWNDWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDbClk);
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_NCCALCSIZE, OnNcCalcSize)
		MESSAGE_HANDLER(WM_NCACTIVATE, OnNcActive)
		MESSAGE_HANDLER(WM_NCPAINT, OnNcPaint)
		MESSAGE_HANDLER(WM_SIZE,OnSize)
		MESSAGE_HANDLER(WM_GETMINMAXINFO,OnGetMinMaxInfo)
		MESSAGE_HANDLER(WM_NCHITTEST,OnNcHitTest)
	END_MSG_MAP()

	BEGIN_DUI_MSG_MAP(CTopHWNDWindow)
		DUI_MSG_HANDLER(WM_SIZE, dui_OnSize)
		CHAIN_DUI_MSG_MAP(CContainerWindowBase)
	END_DUI_MESSAGE_MAP()

	LRESULT dui_OnSize(const CDuiMSG& duiMsg, BOOL bHandled);

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonDbClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNcCalcSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNcActive(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNcPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnNcHitTest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	

	virtual BOOL MoveWindow(LPRECT lprc);
	virtual BOOL MoveWindow(int nLeft, int nTop, int nWidth, int nHeight);
	BOOL CreateHWND(HWND hWndParent, LPRECT lprc = NULL, UINT uStyle = 0, UINT uStyleEx = 0);

	//¿Ø¼þ¹ÜÀí
	CWindowBase* GetFocusWindow();
	void SetFocusWindow(CWindowBase* pWindow);
	CWindowBase* GetHoverWindow();
	void SetHoverWindow(CWindowBase* pWindow);
	CWindowBase* GetCaptureWindow();
	void SetCaptureWindow(CWindowBase* pWindow);

	virtual BOOL ParseAttribute(pugi::xml_node& node);
	virtual BOOL Create(HWND hWndParent, LPCTSTR szPath);
	
protected:
	CWindowBase* m_pFocusWindow;
	CWindowBase* m_pHoverWindow;
	CWindowBase* m_pCaptureWindow;

	bool			m_bTrackLeave;
	bool			m_bSizeBox;
	int				m_nCaption;
	CRect			m_rcThickFrame;
	std::wstring	m_strSkinPath;

};

