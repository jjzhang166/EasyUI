#include "stdafx.h"

using namespace pugi;


CTopHWNDWindow::CTopHWNDWindow(void)
	: CContainerWindowBase(NULL)
	, m_pFocusWindow(NULL)
	, m_pHoverWindow(NULL)
	, m_pCaptureWindow(NULL)
	, m_nCaption(0)
	, m_bTrackLeave(false)
	, m_bSizeBox(false)
{
	m_pRoot = this;
}

CTopHWNDWindow::~CTopHWNDWindow(void)
{
	m_pFocusWindow = NULL;
	m_pHoverWindow = NULL;
}

LRESULT CTopHWNDWindow::dui_OnSize( const CDuiMSG& duiMsg, BOOL bHandled )
{
	CSize szWnd(GET_X_LPARAM(duiMsg.lParam),GET_Y_LPARAM(duiMsg.lParam));
	m_rcWnd.SetRect(0,0,szWnd.cx,szWnd.cy);
	return TRUE;
}

LRESULT CTopHWNDWindow::OnCreate( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
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

LRESULT CTopHWNDWindow::OnClose( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	::PostQuitMessage(0);

	return true;
}

LRESULT CTopHWNDWindow::OnMouseMove( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled )
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
		CWindowBase* pNewHoverWindow = FindChild(ptCursor,eFindChild_Backward|eFindChild_Recursive);
		CWindowBase* pOldHoverWindow = GetHoverWindow();
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

LRESULT CTopHWNDWindow::OnMouseLeave( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	if(m_bTrackLeave){
		m_bTrackLeave = false;
	}

	//if top window
	CTopHWNDWindow* pTopWindow = dynamic_cast<CTopHWNDWindow*>(this);
	ATLASSERT(pTopWindow);
	CWindowBase* pOldHoverWindow = pTopWindow->GetHoverWindow();
	if(pOldHoverWindow){
		pTopWindow->SetHoverWindow(NULL);
		pOldHoverWindow->SendDuiMessage(WM_MOUSELEAVE);
	}

	return TRUE;
}

LRESULT CTopHWNDWindow::OnLButtonDown( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;

	if(GetCaptureWindow()){
		GetCaptureWindow()->SendDuiMessage(WM_LBUTTONDOWN);
	}
	else{
		CWindowBase* pNewFocusWindow = GetHoverWindow();
		CWindowBase* pOldFocusWindow = GetFocusWindow();

		if(pNewFocusWindow != pOldFocusWindow){
			SetFocusWindow(pNewFocusWindow);
			if(pOldFocusWindow)
				pOldFocusWindow->SendDuiMessage(WM_KILLFOCUS);
			if(pNewFocusWindow)
				pNewFocusWindow->SendDuiMessage(WM_SETFOCUS);
		}

		if(pNewFocusWindow)pNewFocusWindow->SendDuiMessage(WM_LBUTTONDOWN);
	}
	

	return TRUE;
}

LRESULT CTopHWNDWindow::OnLButtonUp( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	if(GetCaptureWindow()){
		GetCaptureWindow()->SendDuiMessage(WM_LBUTTONUP,this);
	}
	else{
		CWindowBase* pFocusWindow = GetFocusWindow();
		if(pFocusWindow){
			pFocusWindow->SendDuiMessage(WM_LBUTTONUP);
		}
	}

	return TRUE;
}

LRESULT CTopHWNDWindow::OnLButtonDbClk( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled )
{
	bHandled = FALSE;

	if(GetCaptureWindow()){
		GetCaptureWindow()->SendDuiMessage(WM_LBUTTONDBLCLK);
	}
	else{
		CWindowBase* pNewFocusWindow = GetHoverWindow();
		CWindowBase* pOldFocusWindow = GetFocusWindow();

		if(pNewFocusWindow != pOldFocusWindow){
			SetFocusWindow(pNewFocusWindow);
			if(pOldFocusWindow)
				pOldFocusWindow->SendDuiMessage(WM_KILLFOCUS);
			if(pNewFocusWindow)
				pNewFocusWindow->SendDuiMessage(WM_SETFOCUS);
		}

		if(pNewFocusWindow)pNewFocusWindow->SendDuiMessage(WM_LBUTTONDBLCLK);
	}

	return TRUE;
}

LRESULT CTopHWNDWindow::OnEraseBkgnd( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return TRUE;
}

LRESULT CTopHWNDWindow::OnPaint( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
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

LRESULT CTopHWNDWindow::OnNcCalcSize( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return TRUE;
}

LRESULT CTopHWNDWindow::OnNcActive( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return TRUE;
}

LRESULT CTopHWNDWindow::OnNcPaint( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	return TRUE;
}

LRESULT CTopHWNDWindow::OnSize( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/ )
{
	SendDuiMessage(WM_SIZE,this,wParam,lParam);
	return TRUE;
}

LRESULT CTopHWNDWindow::OnGetMinMaxInfo( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/ )
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

LRESULT CTopHWNDWindow::OnNcHitTest( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
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
		CWindowBase* pCtrl = FindChild(pt,eFindChild_Backward|eFindChild_Recursive);
		if(pCtrl && pCtrl->IsOverCaption()){
			lRtn = HTCLIENT;
		}
	}

	return lRtn;
}

BOOL CTopHWNDWindow::MoveWindow( LPRECT lprc )
{
	CContainerWindowBase::MoveWindow(lprc);
	CWindowImpl<CTopHWNDWindow>::MoveWindow(lprc);

	return TRUE;
}

BOOL CTopHWNDWindow::MoveWindow( int nLeft, int nTop, int nWidth, int nHeight )
{
	CContainerWindowBase::MoveWindow(nLeft,nTop,nWidth,nHeight);
	CWindowImpl<CTopHWNDWindow>::MoveWindow(nLeft,nTop,nWidth,nHeight);

	return TRUE;
}

BOOL CTopHWNDWindow::CreateHWND( HWND hWndParent, LPRECT lprc /* = NULL*/, UINT uStyle/* = 0*/, UINT uStyleEx/* = 0*/)
{
	CWindowImpl<CTopHWNDWindow>::Create(hWndParent,lprc, NULL, uStyle, uStyleEx);
	return TRUE;
}

CWindowBase* CTopHWNDWindow::GetFocusWindow()
{
	return m_pFocusWindow;
}

void CTopHWNDWindow::SetFocusWindow( CWindowBase* pWindow )
{
	m_pFocusWindow = pWindow;
}

CWindowBase* CTopHWNDWindow::GetHoverWindow()
{
	return m_pHoverWindow;
}

void CTopHWNDWindow::SetHoverWindow( CWindowBase* pWindow )
{
	m_pHoverWindow = pWindow;
}

CWindowBase* CTopHWNDWindow::GetCaptureWindow()
{
	return m_pCaptureWindow;
}

void CTopHWNDWindow::SetCaptureWindow( CWindowBase* pWindow )
{
	m_pCaptureWindow = pWindow;

	if(pWindow!=NULL){
		::SetCapture(m_hWnd);
	}
	else{
		::ReleaseCapture();
	}
}

BOOL CTopHWNDWindow::ParseAttribute( pugi::xml_node& node )
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

BOOL CTopHWNDWindow::Create(HWND hWndParent, LPCTSTR szPath )
{
	m_strSkinPath = szPath;
	CreateHWND(hWndParent,CRect(0,0,0,0),WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_SIZEBOX);

	return TRUE;;
}
