#include "stdafx.h"

using namespace Gdiplus;

CUIWindowBase::CUIWindowBase(CUIWindowBase* pParent)
	: m_pParent(pParent)
	, m_pRoot(pParent?pParent->m_pRoot:this)
	, m_bFloat(false)
	, m_bVisible(true)
	, m_bPlaceHolder(false)
	, m_bkColor(Gdiplus::Color::Red)
	, m_borderColor(Gdiplus::Color::Black)
	, m_nBorderWidth(0)
	, m_nFontSize(16)
	, m_strFontFamily(_T("Arial"))
	, m_textColor(Color::Black)
	, m_bBold(false)
	, m_bItalic(false)
	, m_bUnderline(false)
	, m_bStrikout(false)
	, m_bMultiLine(true)
	, m_bEnable(true)
	, m_bOverCaption(false)
{
}


CUIWindowBase::~CUIWindowBase(void)
{
	m_pParent = NULL;
}

std::wstring CUIWindowBase::GetName()
{
	return m_strName;
}

void CUIWindowBase::SetName( LPCTSTR szName )
{
	m_strName = szName;
}

bool CUIWindowBase::IsFloat()
{
	return m_bFloat;
}

bool CUIWindowBase::IsPlaceHolder()
{
	return m_bPlaceHolder;
}

void CUIWindowBase::GetRect(CRect& rcWnd)
{
	rcWnd = m_rcWnd;
}

void CUIWindowBase::SetRect( const CRect& rcWnd )
{
	m_rcWnd = rcWnd;
}

bool CUIWindowBase::IsVisible()
{
	return m_bVisible;
}

void CUIWindowBase::GetBkImg( std::wstring& strBgImg )
{
	strBgImg = m_strBkImg;
}

void CUIWindowBase::SetBkImg( const std::wstring& strBgImg )
{
	m_strBkImg = strBgImg;
}

Gdiplus::ARGB CUIWindowBase::GetBkClr()
{
	return m_bkColor;
}

void CUIWindowBase::SetBkClr( const Gdiplus::ARGB& clr )
{
	m_bkColor = clr;
}

void CUIWindowBase::SetMultiLine( bool bMultiLine )
{
	if(!bMultiLine){
		m_stringFormat.SetFormatFlags(StringFormatFlagsNoWrap);
	}
	else{
		m_stringFormat.SetFormatFlags(m_stringFormat.GetFormatFlags()&(~StringFormatFlagsNoWrap));
	}

	m_bMultiLine = bMultiLine;
}

void CUIWindowBase::SetTextAlign(LPCTSTR szTextAlign)
{
	m_strTextAlign = szTextAlign;
	CalcTextFormat(m_strTextAlign, m_stringFormat);
}

bool CUIWindowBase::IsOverCaption()
{
	return m_bOverCaption;
}

BOOL CUIWindowBase::Create( pugi::xml_node& node )
{
	ParseAttribute(node);
	return TRUE;
}

BOOL CUIWindowBase::ParseAttribute( pugi::xml_node& node )
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
	//ªÊ÷∆
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

	attr = node.attribute(_T("text_color"));
	if(attr){
		ParserHelper::String2ARGB(attr.as_string(),m_textColor);
	}

	attr = node.attribute(_T("bold"));
	if(attr){
		m_bItalic = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
	}

	attr = node.attribute(_T("italic"));
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

	//‘§≥ı ºªØstringformat
	{
		attr = node.attribute(_T("text_align"));
		if(attr){
			m_strTextAlign = attr.as_string();
		}

		attr = node.attribute(_T("multi_line"));
		if(attr){
			m_bMultiLine = ( _tcsicmp(attr.as_string(),_T("true"))==0 );
		}

		SetMultiLine(m_bMultiLine);
		SetTextAlign(m_strTextAlign.c_str());
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

void CUIWindowBase::GetInitRect( CRect& rcInit )
{
	rcInit = m_rcInit;
}

void CUIWindowBase::SetInitRect( const CRect& rcInit )
{
	m_rcInit = rcInit;
}

void CUIWindowBase::GetPadding( CRect& rcPadding )
{
	rcPadding = m_rcPadding;
}

void CUIWindowBase::SetPadding( const CRect& rcPadding )
{
	m_rcPadding = rcPadding;
}

void CUIWindowBase::GetMargin( CRect& rcMargin )
{
	rcMargin = m_rcMargin;
}

void CUIWindowBase::SetMargin( const CRect& rcMargin )
{
	m_rcMargin = rcMargin;
}

void CUIWindowBase::GetMinSize( CSize& minSz )
{
	minSz = m_minSize;
}

void CUIWindowBase::GetMaxSize( CSize& maxSz )
{
	maxSz = m_maxSize;
}

CUIWindowBase* CUIWindowBase::GetParent()
{
	return m_pParent;
}

void CUIWindowBase::SetParent( CUIWindowBase* pParent )
{
	m_pParent = pParent;
}

CUIWindowBase* CUIWindowBase::GetRoot()
{
	return m_pRoot;
}

HWND CUIWindowBase::GetRootHandle()
{
	CUITopWindow* pTop = dynamic_cast<CUITopWindow*>(GetRoot());
	return pTop ? pTop->m_hWnd : NULL;
}

bool CUIWindowBase::SetCapture()
{
	bool bOk = false;
	if(!GetCapture()){
		CUITopWindow* pTop = dynamic_cast<CUITopWindow*>(GetRoot());
		if(pTop){
			pTop->SetCaptureWindow(this);
			bOk = true;
		}
	}

	return bOk;
}

bool CUIWindowBase::ReleaseCapture()
{
	bool bOk = false;
	CUITopWindow* pTop = dynamic_cast<CUITopWindow*>(GetRoot());
	if(pTop && pTop->GetCaptureWindow()==this){
		pTop->SetCaptureWindow(NULL);
		bOk = true;
	}

	return bOk;
}

BOOL CUIWindowBase::MoveWindow( LPRECT lprc )
{
	return MoveWindow(lprc->left,lprc->top,lprc->right-lprc->left,lprc->bottom-lprc->top);
}

BOOL CUIWindowBase::MoveWindow( int nLeft, int nTop, int nWidth, int nHeight )
{
	CRect rcOld = m_rcWnd;

	m_rcWnd.left = nLeft;
	m_rcWnd.top = nTop;
	m_rcWnd.right = m_rcWnd.left + nWidth;
	m_rcWnd.bottom = m_rcWnd.top + nHeight;

	SendDuiMessage(WM_SIZE, this);

	return TRUE;
}

bool CUIWindowBase::CalcWindowFloatPos( const CRect& rcParent, const CRect& rcCtrlInit, const std::wstring& strAlign, CRect& rcNew)
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

bool CUIWindowBase::CalcWindowFloatPos(CRect& rcWnd)
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

bool CUIWindowBase::CalcTextFormat( const std::wstring strTextAlign, Gdiplus::StringFormat& format )
{
	if(strTextAlign.empty() || strTextAlign == _T("lefttop")){
		format.SetAlignment(Gdiplus::StringAlignmentNear);
		format.SetLineAlignment(Gdiplus::StringAlignmentNear);
	}
	else if(strTextAlign == _T("left")){
		format.SetAlignment(Gdiplus::StringAlignmentNear);
		format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	}
	else if(strTextAlign == _T("leftbottom")){
		format.SetAlignment(Gdiplus::StringAlignmentNear);
		format.SetLineAlignment(Gdiplus::StringAlignmentFar);
	}
	else if(strTextAlign == _T("bottom")){
		format.SetAlignment(Gdiplus::StringAlignmentCenter);
		format.SetLineAlignment(Gdiplus::StringAlignmentFar);
	}
	else if(strTextAlign == _T("rightbottom")){
		format.SetAlignment(Gdiplus::StringAlignmentFar);
		format.SetLineAlignment(Gdiplus::StringAlignmentFar);
	}
	else if(strTextAlign == _T("right")){
		format.SetAlignment(Gdiplus::StringAlignmentFar);
		format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	}
	else if(strTextAlign == _T("righttop")){
		format.SetAlignment(Gdiplus::StringAlignmentFar);
		format.SetLineAlignment(Gdiplus::StringAlignmentNear);
	}
	else if(strTextAlign == _T("top")){
		format.SetAlignment(Gdiplus::StringAlignmentCenter);
		format.SetLineAlignment(Gdiplus::StringAlignmentNear);
	}
	else if(strTextAlign == _T("center")){
		format.SetAlignment(Gdiplus::StringAlignmentCenter);
		format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	}
	else{
		ATLASSERT(FALSE);
	}

	return true;
}

void CUIWindowBase::DoPaint( Gdiplus::Graphics* pGraphics )
{
	PaintBkGnd(pGraphics);
	PaintBorder(pGraphics);
	PaintText(pGraphics);
}

void CUIWindowBase::PaintBkGnd( Gdiplus::Graphics* pGraphics )
{
	if(!m_strBkImg.empty()){
		Image* pImage = CImageFactory::GetInst()->GetObject(m_strBkImg.c_str());
		pGraphics->DrawImage(pImage,GdiplusHelper::Rect2GPRect(m_rcWnd),0,0,pImage->GetWidth(),pImage->GetHeight(),UnitPixel);
	}
	else{
		pGraphics->FillRectangle(CBrushFactory::GetInst()->GetObject(m_bkColor),GdiplusHelper::Rect2GPRect(m_rcWnd));
	}
}

void CUIWindowBase::PaintBorder( Gdiplus::Graphics* pGraphics )
{
	if(m_nBorderWidth){
		Pen* pPen = CPenFactory::GetPen(m_borderColor,m_nBorderWidth);
		pPen->SetAlignment(PenAlignmentInset);
		pGraphics->DrawRectangle(pPen,GdiplusHelper::Rect2GPRect(m_rcWnd));
		pPen->SetAlignment(PenAlignmentCenter);
	}
}

void CUIWindowBase::PaintText( Gdiplus::Graphics* pGraphics )
{
	if(!m_strText.empty()){
		Font* pFont = CFontFactory::GetFont(m_strFontFamily.c_str(),m_nFontSize,m_bBold,m_bUnderline,m_bStrikout);
		Brush* pBrush = CBrushFactory::GetBrush(m_textColor);
		pGraphics->DrawString( m_strText.c_str(), -1,pFont, GdiplusHelper::Rect2GPRectF(m_rcWnd), &m_stringFormat, pBrush);
	}
}

void CUIWindowBase::UIInvalidate()
{
	InvalidateRect(GetRootHandle(),&m_rcWnd,TRUE);
}
