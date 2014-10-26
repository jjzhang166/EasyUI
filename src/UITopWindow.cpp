#include "stdafx.h"

using namespace pugi;


CUITopWindow::CUITopWindow(void)
	: CUIContainerWindow(NULL)
	, m_pFocusWindow(NULL)
	, m_pHoverWindow(NULL)
	, m_pCaptureWindow(NULL)
	, m_nCaption(0)
	, m_bTrackLeave(false)
	, m_bSizeBox(false)
{
	m_pRoot = this;
}

CUITopWindow::~CUITopWindow(void)
{
	m_pFocusWindow = NULL;
	m_pHoverWindow = NULL;
}

LRESULT CUITopWindow::dui_OnSize( const CDuiMSG& duiMsg, BOOL& bHandled )
{
	CSize szWnd(GET_X_LPARAM(duiMsg.lParam),GET_Y_LPARAM(duiMsg.lParam));
	m_rcWnd.SetRect(0,0,szWnd.cx,szWnd.cy);
	return TRUE;
}

LRESULT CUITopWindow::OnCreate( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	xml_document document;
	document.load_file(m_strSkinPath.c_str());
	xml_node rootNode = document.root();
	xml_node childNode = rootNode.first_child();
	__super::Create(childNode);

	//modify style
	DWORD dwRemoveStyle = WS_VISIBLE|WS_BORDER|WS_CAPTION;
	if(!m_bSizeBox){
		dwRemoveStyle |= WS_SIZEBOX;
	}
	ModifyStyle(dwRemoveStyle,0);

	//reset position
	HMONITOR hMonitor = ::MonitorFromWindow(NULL,MONITOR_DEFAULTTOPRIMARY);
	MONITORINFO monitorInfo = {sizeof(MONITORINFO)};
	::GetMonitorInfo(hMonitor,&monitorInfo);
	CRect rcWork = monitorInfo.rcWork;
	CRect rcWnd;
	CalcWindowFloatPos(rcWork,m_rcInit,m_strAlign,rcWnd);

	m_rcWnd = rcWnd;
	m_rcWnd.MoveToXY(0,0);
	SendDuiMessage(WM_CREATE,this);

	MoveWindow(rcWnd);

	return TRUE;
}

LRESULT CUITopWindow::OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	SendDuiMessage(WM_CLOSE,this);
	//DestroyWindow();

	return true;
}

LRESULT CUITopWindow::OnDestroy( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	SendDuiMessage(WM_DESTROY,this);
	::PostQuitMessage(0);
	return TRUE;
}

LRESULT CUITopWindow::OnMouseMove( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled )
{
	if(!m_bTrackLeave){
		TRACKMOUSEEVENT tme = {sizeof(TRACKMOUSEEVENT)};
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		TrackMouseEvent(&tme);
	}

	if(GetCaptureWindow()){
		GetCaptureWindow()->SendDuiMessage(WM_MOUSEMOVE,this);
	}
	else{
		CPoint ptCursor;
		GetCursorPos(&ptCursor);
		ScreenToClient(&ptCursor);
		CUIWindowBase* pNewHoverWindow = FindChild(ptCursor,eFindChild_Backward|eFindChild_Recursive);
		CUIWindowBase* pOldHoverWindow = GetHoverWindow();
		if(pNewHoverWindow != pOldHoverWindow){
			SetHoverWindow(pNewHoverWindow);
			if(pOldHoverWindow)
				pOldHoverWindow->SendDuiMessage(WM_MOUSELEAVE,this);
			if(pNewHoverWindow)
				pNewHoverWindow->SendDuiMessage(WM_MOUSEENTER,this);
		}

		if(pNewHoverWindow)
			pNewHoverWindow->SendDuiMessage(WM_MOUSEMOVE,this);
	}	

	return TRUE;
}

LRESULT CUITopWindow::OnMouseLeave( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	if(m_bTrackLeave){
		m_bTrackLeave = false;
	}

	//if top window
	CUITopWindow* pTopWindow = dynamic_cast<CUITopWindow*>(this);
	ATLASSERT(pTopWindow);
	CUIWindowBase* pOldHoverWindow = pTopWindow->GetHoverWindow();
	if(pOldHoverWindow){
		pTopWindow->SetHoverWindow(NULL);
		pOldHoverWindow->SendDuiMessage(WM_MOUSELEAVE);
	}

	return TRUE;
}

LRESULT CUITopWindow::OnLButtonDown( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;

	if(GetCaptureWindow()){
		GetCaptureWindow()->SendDuiMessage(WM_LBUTTONDOWN,this, wParam, lParam);
	}
	else{
		CUIWindowBase* pNewFocusWindow = GetHoverWindow();
		CUIWindowBase* pOldFocusWindow = GetFocusWindow();

		if(pNewFocusWindow != pOldFocusWindow){
			SetFocusWindow(pNewFocusWindow);
			if(pOldFocusWindow)
				pOldFocusWindow->SendDuiMessage(WM_KILLFOCUS, this, wParam, lParam);
			if(pNewFocusWindow)
				pNewFocusWindow->SendDuiMessage(WM_SETFOCUS, this, wParam, lParam);
		}

		if(pNewFocusWindow)pNewFocusWindow->SendDuiMessage(WM_LBUTTONDOWN, this, wParam, lParam);
	}

	return TRUE;
}

LRESULT CUITopWindow::OnLButtonUp( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/ )
{
	if(GetCaptureWindow()){
		GetCaptureWindow()->SendDuiMessage(WM_LBUTTONUP,this, wParam, lParam);
	}
	else{
		CUIWindowBase* pFocusWindow = GetFocusWindow();
		if(pFocusWindow){
			pFocusWindow->SendDuiMessage(WM_LBUTTONUP,this, wParam, lParam);
		}
	}

	return TRUE;
}

LRESULT CUITopWindow::OnLButtonDbClk( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	bHandled = FALSE;

	if(GetCaptureWindow()){
		GetCaptureWindow()->SendDuiMessage(WM_LBUTTONDBLCLK,this, wParam, lParam);
	}
	else{
		CUIWindowBase* pNewFocusWindow = GetHoverWindow();
		CUIWindowBase* pOldFocusWindow = GetFocusWindow();

		if(pNewFocusWindow != pOldFocusWindow){
			SetFocusWindow(pNewFocusWindow);
			if(pOldFocusWindow)
				pOldFocusWindow->SendDuiMessage(WM_KILLFOCUS,this, wParam, lParam);
			if(pNewFocusWindow)
				pNewFocusWindow->SendDuiMessage(WM_SETFOCUS,this, wParam, lParam);
		}

		if(pNewFocusWindow)pNewFocusWindow->SendDuiMessage(WM_LBUTTONDBLCLK,this, wParam, lParam);
	}

	return TRUE;
}

LRESULT CUITopWindow::OnEraseBkgnd( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return TRUE;
}

LRESULT CUITopWindow::OnPaint( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	CPaintDC paintDC(*this);
	CRect rcWnd;
	GetClientRect(&rcWnd);
	CSmartDC smartDC(paintDC.m_hDC,rcWnd);

	Gdiplus::Graphics graphics(smartDC.GetDC());
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
	//Gdiplus::SolidBrush redBrush(Gdiplus::Color::Red);
	//graphics.FillRectangle(&redBrush,0,0,rcWnd.Width(),rcWnd.Height());
	DoPaint(&graphics);


	smartDC.BitBlt();

	return TRUE;
}

LRESULT CUITopWindow::OnNcCalcSize( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return TRUE;
}

LRESULT CUITopWindow::OnNcActive( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return TRUE;
}

LRESULT CUITopWindow::OnNcPaint( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return TRUE;
}

LRESULT CUITopWindow::OnSize( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/ )
{
	SendDuiMessage(WM_SIZE,this,wParam,lParam);
	return TRUE;
}

LRESULT CUITopWindow::OnGetMinMaxInfo( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/ )
{
	LPMINMAXINFO pInfo = (LPMINMAXINFO)lParam;
	if(pInfo){
		if(m_maxSize.cx > 0){
			pInfo->ptMaxTrackSize.x = m_maxSize.cx;
		}
		if(m_maxSize.cy > 0){
			pInfo->ptMaxTrackSize.y = m_maxSize.cy;
		}

		pInfo->ptMinTrackSize.x = m_minSize.cx;
		pInfo->ptMinTrackSize.y = m_minSize.cy;

		HMONITOR hMonitor = ::MonitorFromWindow(m_hWnd,MONITOR_DEFAULTTOPRIMARY);
		MONITORINFO mInfo = {sizeof(MONITORINFO)};
		if(GetMonitorInfo(hMonitor,&mInfo)){
			pInfo->ptMaxPosition.x = mInfo.rcWork.left;
			pInfo->ptMaxPosition.y = mInfo.rcWork.top;
			pInfo->ptMaxSize.x = mInfo.rcWork.right - mInfo.rcWork.left;
			pInfo->ptMaxSize.y = mInfo.rcWork.bottom - mInfo.rcWork.top;
		}
	}
	return TRUE;
}

LRESULT CUITopWindow::OnNcHitTest( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	if(m_nCaption == -1){
		return HTCAPTION;
	}

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	CPoint ptCursor;
	GetCursorPos(&ptCursor);

	LRESULT lRtn = HTCLIENT;

	if(m_nCaption > 0 && ptCursor.y < rcWnd.top+m_nCaption){
		lRtn = HTCAPTION;
	}

	if(!IsZoomed()){
		if(ptCursor.x < rcWnd.left+m_rcThickFrame.left){
			if(ptCursor.y < rcWnd.top+m_rcThickFrame.top){
				lRtn = HTTOPLEFT;
			}
			else if(ptCursor.y > rcWnd.bottom - m_rcThickFrame.bottom){
				lRtn = HTBOTTOMLEFT;
			}
			else{
				lRtn = HTLEFT;
			}
		}
		else if(ptCursor.x > rcWnd.right-m_rcThickFrame.right){
			if(ptCursor.y < rcWnd.top+m_rcThickFrame.top){
				lRtn = HTTOPRIGHT;
			}
			else if(ptCursor.y > rcWnd.bottom - m_rcThickFrame.bottom){
				lRtn = HTBOTTOMRIGHT;
			}
			else{
				lRtn = HTRIGHT;
			}
		}
		else{
			if(ptCursor.y < rcWnd.top+m_rcThickFrame.top){
				lRtn = HTTOP;
			}
			else if(ptCursor.y > rcWnd.bottom - m_rcThickFrame.bottom){
				lRtn = HTBOTTOM;
			}
		}
	}

	if(HTCAPTION == lRtn){
		CPoint pt(ptCursor);
		ScreenToClient(&pt);
		CUIWindowBase* pCtrl = FindChild(pt,eFindChild_Backward|eFindChild_Recursive);
		if(pCtrl && pCtrl->IsOverCaption()){
			lRtn = HTCLIENT;
		}
	}

	return lRtn;
}

LRESULT CUITopWindow::OnKillFocus( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;

	return TRUE;
}

BOOL CUITopWindow::MoveWindow( LPRECT lprc )
{
	CUIContainerWindow::MoveWindow(lprc);
	CWindowImpl<CUITopWindow>::MoveWindow(lprc);

	return TRUE;
}

BOOL CUITopWindow::MoveWindow( int nLeft, int nTop, int nWidth, int nHeight )
{
	CUIContainerWindow::MoveWindow(nLeft,nTop,nWidth,nHeight);
	CWindowImpl<CUITopWindow>::MoveWindow(nLeft,nTop,nWidth,nHeight);

	return TRUE;
}

BOOL CUITopWindow::CreateHWND( HWND hWndParent, LPRECT lprc /* = NULL*/, UINT uStyle/* = 0*/, UINT uStyleEx/* = 0*/)
{
	CWindowImpl<CUITopWindow>::Create(hWndParent,lprc, NULL, uStyle, uStyleEx);
	return TRUE;
}

CUIWindowBase* CUITopWindow::GetFocusWindow()
{
	return m_pFocusWindow;
}

void CUITopWindow::SetFocusWindow( CUIWindowBase* pWindow )
{
	m_pFocusWindow = pWindow;
}

CUIWindowBase* CUITopWindow::GetHoverWindow()
{
	return m_pHoverWindow;
}

void CUITopWindow::SetHoverWindow( CUIWindowBase* pWindow )
{
	m_pHoverWindow = pWindow;
}

CUIWindowBase* CUITopWindow::GetCaptureWindow()
{
	return m_pCaptureWindow;
}

void CUITopWindow::SetCaptureWindow( CUIWindowBase* pWindow )
{
	CUIWindowBase* pOldCaptureWnd = m_pCaptureWindow;
	m_pCaptureWindow = pWindow;
	if(pWindow!=NULL){
		::SetCapture(m_hWnd);
	}
	else{
		::ReleaseCapture();
	}
}

BOOL CUITopWindow::ParseAttribute( pugi::xml_node& node )
{
	__super::ParseAttribute(node);

	pugi::xml_attribute attr;
	attr = node.attribute(_T("caption"));
	if(attr){
		m_nCaption = _ttoi(attr.as_string());
	}

	attr = node.attribute(_T("thickframe"));
	if(attr){
		ParserHelper::String2Rect(attr.as_string(),m_rcThickFrame);
	}

	attr = node.attribute(_T("sizebox"));
	if(attr){
		m_bSizeBox = _tcsicmp(attr.as_string(),_T("true"))==0;
	}

	return TRUE;
}

BOOL CUITopWindow::Create(HWND hWndParent, LPCTSTR szPath )
{
	m_strSkinPath = szPath;
	CreateHWND(hWndParent,CRect(0,0,0,0),WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SIZEBOX);

	return TRUE;;
}
