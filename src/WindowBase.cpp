#include "stdafx.h"

using namespace Gdiplus;

CWindowBase::CWindowBase(CWindowBase* pParent)
	: m_pParent(pParent)
	, m_pRoot(pParent?pParent->m_pRoot:NULL)
	, m_bFloat(false)
	, m_bVisible(true)
	, m_bPlaceHolder(false)
	, m_bkColor(Gdiplus::Color::Red)
	, m_borderColor(Gdiplus::Color::Black)
	, m_nBorderWidth(0)
	, m_nFontSize(16)
	, m_strFontFamily(_T("Arial"))
	, m_fontColor(Color::Black)
	, m_bBold(false)
	, m_bUnderline(false)
	, m_bStrikout(false)
	, m_bEnable(true)
	, m_bOverCaption(false)
{
}


CWindowBase::~CWindowBase(void)
{
	m_pParent = NULL;
}

std::wstring CWindowBase::GetName()
{
	return m_strName;
}

void CWindowBase::SetName( LPCTSTR szName )
{
	m_strName = szName;
}

bool CWindowBase::IsFloat()
{
	return m_bFloat;
}

bool CWindowBase::IsPlaceHolder()
{
	return m_bPlaceHolder;
}

void CWindowBase::GetRect(CRect& rcWnd)
{
	rcWnd = m_rcWnd;
}

void CWindowBase::SetRect( const CRect& rcWnd )
{
	m_rcWnd = rcWnd;
}

bool CWindowBase::IsVisible()
{
	return m_bVisible;
}

void CWindowBase::GetBgImg( std::wstring& strBgImg )
{
	strBgImg = m_strBkImg;
}

void CWindowBase::SetBgImg( const std::wstring& strBgImg )
{
	m_strBkImg = strBgImg;
}

void CWindowBase::GetBgClr( Gdiplus::ARGB& clr )
{
	clr = m_bkColor;
}

void CWindowBase::SetBgClr( const Gdiplus::ARGB& clr )
{
	m_bkColor = clr;
}

bool CWindowBase::IsOverCaption()
{
	return m_bOverCaption;
}

BOOL CWindowBase::Create( pugi::xml_node& node )
{
	ParseAttribute(node);
	return TRUE;
}

BOOL CWindowBase::ParseAttribute( pugi::xml_node& node )
{
	pugi::xml_attribute attr;
	attr = node.attribute(_T("name"));
	if(attr){
		m_strName = attr.as_string();
	}

	attr = node.attribute(_T("rect"));
	if(attr){
		ParserHelper::String2Rect(attr.as_string(),m_rcInit);
	}

	attr = node.attribute(_T("x"));
	if(attr){
		m_rcInit.left = _ttoi(attr.as_string());
	}

	attr = node.attribute(_T("y"));
	if(attr){
		m_rcInit.top = _ttoi(attr.as_string());
	}

	attr = node.attribute(_T("size"));
	if(attr){
		CSize szWnd;
		if(ParserHelper::String2Size(attr.as_string(),szWnd)){
			m_rcInit.right = m_rcInit.left + szWnd.cx;
			m_rcInit.bottom = m_rcInit.top + szWnd.cy;
		}
	}

	attr = node.attribute(_T("width"));
	if(attr){
		m_rcInit.right = m_rcInit.left + _ttoi(attr.as_string());
	}

	attr = node.attribute(_T("height"));
	if(attr){
		m_rcInit.bottom = m_rcInit.top + _ttoi(attr.as_string());
	}

	attr = node.attribute(_T("minsize"));
	if(attr){
		ParserHelper::String2Size(attr.as_string(),m_minSize);
	}

	attr = node.attribute(_T("maxsize"));
	if(attr){
		ParserHelper::String2Size(attr.as_string(),m_maxSize);
	}

	attr = node.attribute(_T("float"));
	if(attr){
		m_bFloat = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	attr = node.attribute(_T("align"));
	if(attr){
		m_strAlign = attr.as_string();
	}

	attr = node.attribute(_T("padding"));
	if(attr){
		ParserHelper::String2Rect(attr.as_string(),m_rcPadding);
		m_rcPadding.right -= m_rcPadding.left;
		m_rcPadding.bottom -= m_rcPadding.top;
	}

	attr = node.attribute(_T("margin"));
	if(attr){
		ParserHelper::String2Rect(attr.as_string(),m_rcMargin);
		m_rcMargin.right -= m_rcMargin.left;
		m_rcMargin.bottom -= m_rcMargin.top;
	}

	//////////////////////////////////////////////////////////////////////////
	//»æÖÆ
	attr = node.attribute(_T("placeholder"));
	if(attr){
		m_bPlaceHolder = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	attr = node.attribute(_T("visible"));
	if(attr){
		m_bVisible = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	attr = node.attribute(_T("placeholder"));
	if(attr){
		m_bPlaceHolder = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	attr = node.attribute(_T("bk_img"));
	if(attr){
		m_strBkImg = attr.as_string();
	}

	attr = node.attribute(_T("bk_color"));
	if(attr){
		ParserHelper::String2ARGB(attr.as_string(),m_bkColor);
	}

	attr = node.attribute(_T("border_color"));
	if(attr){
		ParserHelper::String2ARGB(attr.as_string(),m_borderColor);
	}

	attr = node.attribute(_T("border_width"));
	if(attr){
		m_nBorderWidth = _ttoi(attr.as_string());
	}

	attr = node.attribute(_T("text"));
	if(attr){
		m_strText = attr.as_string();
	}

	attr = node.attribute(_T("font_family"));
	if(attr){
		m_strFontFamily = attr.as_string();
	}

	attr = node.attribute(_T("font_size"));
	if(attr){
		m_nFontSize = _ttoi(attr.as_string());
	}

	attr = node.attribute(_T("font_color"));
	if(attr){
		ParserHelper::String2ARGB(attr.as_string(),m_fontColor);
	}

	attr = node.attribute(_T("bold"));
	if(attr){
		m_bBold = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	attr = node.attribute(_T("underline"));
	if(attr){
		m_bUnderline = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	attr = node.attribute(_T("strikout"));
	if(attr){
		m_bStrikout = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	attr = node.attribute(_T("enable"));
	if(attr){
		m_bEnable = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	attr = node.attribute(_T("over_caption"));
	if(attr){
		m_bOverCaption = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	return TRUE;
}

void CWindowBase::GetInitRect( CRect& rcInit )
{
	rcInit = m_rcInit;
}

void CWindowBase::SetInitRect( const CRect& rcInit )
{
	m_rcInit = rcInit;
}

void CWindowBase::GetPadding( CRect& rcPadding )
{
	rcPadding = m_rcPadding;
}

void CWindowBase::SetPadding( const CRect& rcPadding )
{
	m_rcPadding = rcPadding;
}

void CWindowBase::GetMargin( CRect& rcMargin )
{
	rcMargin = m_rcMargin;
}

void CWindowBase::SetMargin( const CRect& rcMargin )
{
	m_rcMargin = rcMargin;
}

void CWindowBase::GetMinSize( CSize& minSz )
{
	minSz = m_minSize;
}

void CWindowBase::GetMaxSize( CSize& maxSz )
{
	maxSz = m_maxSize;
}

CWindowBase* CWindowBase::GetParent()
{
	return m_pParent;
}

void CWindowBase::SetParent( CWindowBase* pParent )
{
	m_pParent = pParent;
}

CWindowBase* CWindowBase::GetRoot()
{
	return m_pRoot;
}

HWND CWindowBase::GetRootHandle()
{
	CTopHWNDWindow* pTop = dynamic_cast<CTopHWNDWindow*>(GetRoot());
	return pTop ? pTop->m_hWnd : NULL;
}

bool CWindowBase::SetCapture()
{
	bool bOk = false;
	if(!GetCapture()){
		CTopHWNDWindow* pTop = dynamic_cast<CTopHWNDWindow*>(GetRoot());
		if(pTop){
			pTop->SetCaptureWindow(this);
			bOk = true;
		}
	}

	return bOk;
}

bool CWindowBase::ReleaseCapture()
{
	bool bOk = false;
	CTopHWNDWindow* pTop = dynamic_cast<CTopHWNDWindow*>(GetRoot());
	if(pTop && pTop->GetCaptureWindow()==this){
		pTop->SetCaptureWindow(NULL);
		bOk = true;
	}

	return bOk;
}

BOOL CWindowBase::MoveWindow( LPRECT lprc )
{
	return MoveWindow(lprc->left,lprc->top,lprc->right-lprc->left,lprc->bottom-lprc->top);
}

BOOL CWindowBase::MoveWindow( int nLeft, int nTop, int nWidth, int nHeight )
{
	CRect rcOld = m_rcWnd;

	m_rcWnd.left = nLeft;
	m_rcWnd.top = nTop;
	m_rcWnd.right = m_rcWnd.left + nWidth;
	m_rcWnd.bottom = m_rcWnd.top + nHeight;

	SendDuiMessage(WM_SIZE, this);

	return TRUE;
}

bool CWindowBase::CalcWindowFloatPos( const CRect& rcParent, const CRect& rcCtrlInit, const std::wstring& strAlign, CRect& rcNew)
{
	const int nWidth = rcCtrlInit.Width()>=0 ? rcCtrlInit.Width() : rcParent.Width() + rcCtrlInit.Width();
	const int nHeight = rcCtrlInit.Height()>=0 ? rcCtrlInit.Height() : rcParent.Height() + rcCtrlInit.Height();
	if(strAlign.empty()){
		rcNew.left = (rcCtrlInit.left>=0 ? rcParent.left : rcParent.right)+rcCtrlInit.left;
		rcNew.top = (rcCtrlInit.top>=0 ? rcParent.top : rcParent.bottom)+rcCtrlInit.top;
		rcNew.right = rcNew.left + nWidth;
		rcNew.bottom = rcNew.top + nHeight;
	}
	else if(strAlign == _T("lefttop")){
		rcNew.left = rcParent.left;
		rcNew.top = rcParent.top;
		rcNew.right = rcNew.left + nWidth;
		rcNew.bottom = rcNew.top + nHeight;
	}
	else if(strAlign == _T("left")){
		rcNew.left = rcParent.left;
		rcNew.top = rcParent.top + (rcParent.Height()-nHeight)/2;
		rcNew.right = rcNew.left + nWidth;
		rcNew.bottom = rcNew.top + nHeight;		
	}
	else if(strAlign == _T("leftfull")){
		rcNew.left = rcParent.left;
		rcNew.top = rcParent.top;
		rcNew.right = rcNew.left + nWidth;
		rcNew.bottom = rcParent.bottom;
	}
	else if(strAlign == _T("leftbottom")){
		rcNew.left = rcCtrlInit.left;
		rcNew.bottom = rcParent.bottom;
		rcNew.right = rcNew.left + nWidth;
		rcNew.top = rcNew.bottom - nHeight;
	}
	else if(strAlign == _T("bottom")){
		rcNew.left = rcParent.left + (rcParent.Width()-nWidth)/2;
		rcNew.bottom = rcParent.bottom;
		rcNew.right = rcNew.left + nWidth;
		rcNew.top = rcNew.bottom - nHeight;
	}
	else if(strAlign == _T("bottomfull")){
		rcNew.left = rcParent.left;
		rcNew.right = rcParent.right;
		rcNew.bottom = rcParent.bottom;
		rcNew.top = rcNew.bottom - nHeight;
	}
	else if(strAlign == _T("rightbottom")){
		rcNew.right = rcParent.right;
		rcNew.bottom = rcParent.bottom;
		rcNew.left = rcNew.right - nWidth;
		rcNew.top = rcNew.bottom - nHeight;
	}
	else if(strAlign == _T("right")){
		rcNew.right = rcParent.right;
		rcNew.left = rcNew.right - nWidth;
		rcNew.top = rcParent.top + (rcParent.Height()-nHeight)/2;
		rcNew.bottom = rcNew.top + nHeight;
	}
	else if(strAlign == _T("rightfull")){
		rcNew.top = rcParent.top;
		rcNew.bottom = rcParent.bottom;
		rcNew.right = rcParent.right;
		rcNew.left = rcNew.right - nWidth;
	}
	else if(strAlign == _T("righttop")){
		rcNew.top = rcParent.top;
		rcNew.right = rcParent.right;
		rcNew.left = rcNew.right - nWidth;
		rcNew.bottom = rcNew.top + nHeight;
	}
	else if(strAlign == _T("top")){
		rcNew.top = rcParent.top;
		rcNew.left = rcParent.left + (rcParent.Width()-nWidth)/2;
		rcNew.right = rcNew.left + nWidth;
		rcNew.bottom = rcNew.top + nHeight;
	}
	else if(strAlign == _T("topfull")){
		rcNew.left = rcParent.left;
		rcNew.top = rcParent.top;
		rcNew.right = rcParent.right;
		rcNew.bottom = rcNew.top + nHeight;
	}
	else if(strAlign == _T("center")){
		rcNew.left = rcParent.left + (rcParent.Width()-nWidth)/2;
		rcNew.top = rcParent.top + (rcParent.Height()-nHeight)/2;
		rcNew.right = rcNew.left + nWidth;
		rcNew.bottom = rcNew.top + nHeight;
	}
	else if(strAlign == _T("full")){
		rcNew = rcParent;
	}
	
	return true;
}

bool CWindowBase::CalcWindowFloatPos(CRect& rcWnd)
{
	CRect rcParent;
	if(m_pParent){
		m_pParent->GetRect(rcParent);
	}
	else{
		ATLASSERT(false);
	}
	return CalcWindowFloatPos(rcParent, m_rcInit, m_strAlign, rcWnd);
}

void CWindowBase::DoPaint( Gdiplus::Graphics* pGraphics )
{
	PaintBkGnd(pGraphics);
	PaintBorder(pGraphics);
	PaintText(pGraphics);
}

void CWindowBase::PaintBkGnd( Gdiplus::Graphics* pGraphics )
{
	if(!m_strBkImg.empty()){
		Image* pImage = CImageFactory::GetInst()->GetObject(m_strBkImg.c_str());
		pGraphics->DrawImage(pImage,GdiplusHelper::EasyRect(m_rcWnd),0,0,pImage->GetWidth(),pImage->GetHeight(),UnitPixel);
	}
	else{
		pGraphics->FillRectangle(CBrushFactory::GetInst()->GetObject(m_bkColor),GdiplusHelper::EasyRect(m_rcWnd));
	}
}

void CWindowBase::PaintBorder( Gdiplus::Graphics* pGraphics )
{
	if(m_nBorderWidth){
		Pen* pPen = CPenFactory::GetPen(m_borderColor,m_nBorderWidth);
		pPen->SetAlignment(PenAlignmentInset);
		pGraphics->DrawRectangle(pPen,GdiplusHelper::EasyRect(m_rcWnd));
		pPen->SetAlignment(PenAlignmentCenter);
	}
}

void CWindowBase::PaintText( Gdiplus::Graphics* pGraphics )
{
	if(!m_strText.empty()){
		Font* pFont = CFontFactory::GetFont(m_strFontFamily.c_str(),m_nFontSize,m_bBold,m_bUnderline,m_bStrikout);
		Brush* pBrush = CBrushFactory::GetBrush(m_fontColor);
		pGraphics->DrawString(m_strText.c_str(),-1,pFont,GdiplusHelper::EasyRectF(m_rcWnd),NULL,pBrush);
	}
}

void CWindowBase::DUIInvalidate()
{
	InvalidateRect(GetRootHandle(),&m_rcWnd,TRUE);
}
