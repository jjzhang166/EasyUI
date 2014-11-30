#include "stdafx.h"

using namespace Gdiplus;

CUIWindowBase::CUIWindowBase(CUIWindowBase* pParent)
	: m_pParent(pParent)
	, m_pRoot(pParent?pParent->m_pRoot:this)
	, m_bFloat(false)
	, m_wndAlign(eAlign_NULL)
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
	m_strTextAlign = szTextAlign?szTextAlign:_T("");
	CvtTextAlign(m_strTextAlign, m_stringFormat);
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
		m_wndAlign = CvtAlign(attr.as_string());
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

HWND CUIWindowBase::GetRootHandle() const 
{
	CUITopWindow* pTop = dynamic_cast<CUITopWindow*>(GetRoot());
	return pTop ? pTop->m_hWnd : NULL;
}

CWindowInfo* CUIWindowBase::GetWindowInfo() const 
{
	CUITopWindow* pTop = dynamic_cast<CUITopWindow*>(GetRoot());
	if(pTop){
		return pTop->GetWindowInfo();
	}
	else{
		ATLASSERT(FALSE);
		return NULL;
	}
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

BOOL CUIWindowBase::MoveWindow( const LPRECT lprc )
{
	return MoveWindow(lprc->left,lprc->top,lprc->right-lprc->left,lprc->bottom-lprc->top);
}

BOOL CUIWindowBase::MoveWindow( const int nLeft, const int nTop, const int nWidth, const int nHeight )
{
	const CRect rcOld = m_rcWnd;

	m_rcWnd.left = nLeft;
	m_rcWnd.top = nTop;
	m_rcWnd.right = m_rcWnd.left + nWidth;
	m_rcWnd.bottom = m_rcWnd.top + nHeight;

	if(rcOld != m_rcWnd)
	{
		SendDuiMessage(WM_SIZE, this);
		SendDuiMessage(WM_MOVE, this);
	}

	return TRUE;
}

void CUIWindowBase::SetVisible( bool bVisible )
{
	bool bNeedRedraw = (bVisible != m_bVisible);
	m_bVisible = bVisible;
	if(bNeedRedraw){
		UIInvalidate();
	}
}

int CUIWindowBase::CvtAlign( const std::wstring& strAlign )
{
	//lefttop,left,leftfull,leftbottom,bottom,bottomfull,rightbottom,right,rightfull,righttop,top,topfull,center,full
	const int nLen = strAlign.size();

	int nAlign = eAlign_NULL;
	switch(nLen){

	case 0://null
		nAlign = eAlign_NULL;
		break;

	case 3://top
		assert(strAlign==_T("top"));
		nAlign = eAlign_Top;
		break;

	case 4://left,full
		if(strAlign.at(0)==_T('l')){
			assert(strAlign==_T("left"));
			nAlign = eAlign_Left;
		}
		else{
			assert(strAlign==_T("full"));
			nAlign = eAlign_Full;
		}
		break;

	case 5://right
		assert(strAlign==_T("right"));
		nAlign = eAlign_Right;
		break;

	case 6://bottom,center
		if(strAlign.at(0) == _T('b')){
			assert(strAlign==_T("bottom"));
			nAlign = eAlign_Bottom;
		}
		else{
			assert(strAlign==_T("center"));
			nAlign = eAlign_Center;
		}
		break;

	case 7://lefttop,topfull
		if(strAlign.at(0) == _T('l')){
			assert(strAlign==_T("lefttop"));
			nAlign = eAlign_Left|eAlign_Top;
		}
		else{
			assert(strAlign==_T("topfull"));
			nAlign = eAlign_Top|eAlign_Full;
		}
		break;

	case 8://leftfull,righttop
		if(strAlign.at(0)==_T('l')){
			assert(strAlign==_T("leftfull"));
			nAlign = eAlign_Left|eAlign_Full;
		}
		else{
			assert(strAlign==_T("righttop"));
			nAlign = eAlign_Right|eAlign_Top;
		}
		break;

	case 9://rightfull
		assert(strAlign==_T("rightfull"));
		nAlign = eAlign_Right|eAlign_Full;
		break;

	case 10://leftbottom,bottomfull
		if(strAlign.at(0) == _T('l')){
			assert(strAlign==_T("leftbottom"));
			nAlign = eAlign_Left|eAlign_Bottom;
		}
		else{
			assert(strAlign==_T("bottomfull"));
			nAlign = eAlign_Bottom|eAlign_Full;
		}
		break;

	case 11://rightbottom
		assert(strAlign==_T("rightbottom"));
		nAlign = eAlign_Right|eAlign_Bottom;
		break;
	default:
		assert(false);
		break;
	}

	return nAlign;
}

bool CUIWindowBase::CalcWindowFloatPos( const CRect& rcParent, const CRect& rcCtrlInit, const int wndAlign, CRect& rcRes)
{
	const int nWidth = rcCtrlInit.Width()>0 ? rcCtrlInit.Width() : rcParent.Width() + rcCtrlInit.Width();
	const int nHeight = rcCtrlInit.Height()>0 ? rcCtrlInit.Height() : rcParent.Height() + rcCtrlInit.Height();
	switch(wndAlign){

	case eAlign_NULL:
		rcRes.left = (rcCtrlInit.left>=0 ? rcParent.left : rcParent.right)+rcCtrlInit.left;
		rcRes.top = (rcCtrlInit.top>=0 ? rcParent.top : rcParent.bottom)+rcCtrlInit.top;
		rcRes.right = rcRes.left + nWidth;
		rcRes.bottom = rcRes.top + nHeight;
		break;

	case eAlign_Left|eAlign_Top:
		rcRes.left = rcParent.left;
		rcRes.top = rcParent.top;
		rcRes.right = rcRes.left + nWidth;
		rcRes.bottom = rcRes.top + nHeight;
		break;

	case eAlign_Left:
		rcRes.left = rcParent.left;
		rcRes.top = rcParent.top + (rcParent.Height()-nHeight)/2;
		rcRes.right = rcRes.left + nWidth;
		rcRes.bottom = rcRes.top + nHeight;	
		break;

	case eAlign_Left|eAlign_Full:
		rcRes.left = rcParent.left;
		rcRes.top = rcParent.top;
		rcRes.right = rcRes.left + nWidth;
		rcRes.bottom = rcParent.bottom;
		break;

	case eAlign_Left|eAlign_Bottom:
		rcRes.left = rcCtrlInit.left;
		rcRes.bottom = rcParent.bottom;
		rcRes.right = rcRes.left + nWidth;
		rcRes.top = rcRes.bottom - nHeight;
		break;

	case eAlign_Bottom:
		rcRes.left = rcParent.left + (rcParent.Width()-nWidth)/2;
		rcRes.bottom = rcParent.bottom;
		rcRes.right = rcRes.left + nWidth;
		rcRes.top = rcRes.bottom - nHeight;
		break;

	case eAlign_Bottom|eAlign_Full:
		rcRes.left = rcParent.left;
		rcRes.right = rcParent.right;
		rcRes.bottom = rcParent.bottom;
		rcRes.top = rcRes.bottom - nHeight;
		break;

	case eAlign_Right|eAlign_Bottom:
		rcRes.right = rcParent.right;
		rcRes.bottom = rcParent.bottom;
		rcRes.left = rcRes.right - nWidth;
		rcRes.top = rcRes.bottom - nHeight;
		break;

	case eAlign_Right:
		rcRes.right = rcParent.right;
		rcRes.left = rcRes.right - nWidth;
		rcRes.top = rcParent.top + (rcParent.Height()-nHeight)/2;
		rcRes.bottom = rcRes.top + nHeight;
		break;

	case eAlign_Right|eAlign_Full:
		rcRes.top = rcParent.top;
		rcRes.bottom = rcParent.bottom;
		rcRes.right = rcParent.right;
		rcRes.left = rcRes.right - nWidth;
		break;

	case eAlign_Right|eAlign_Top:
		rcRes.top = rcParent.top;
		rcRes.right = rcParent.right;
		rcRes.left = rcRes.right - nWidth;
		rcRes.bottom = rcRes.top + nHeight;
		break;

	case eAlign_Top:
		rcRes.top = rcParent.top;
		rcRes.left = rcParent.left + (rcParent.Width()-nWidth)/2;
		rcRes.right = rcRes.left + nWidth;
		rcRes.bottom = rcRes.top + nHeight;
		break;

	case eAlign_Top|eAlign_Full:
		rcRes.left = rcParent.left;
		rcRes.top = rcParent.top;
		rcRes.right = rcParent.right;
		rcRes.bottom = rcRes.top + nHeight;
		break;

	case eAlign_Center:
		rcRes.left = rcParent.left + (rcParent.Width()-nWidth)/2;
		rcRes.top = rcParent.top + (rcParent.Height()-nHeight)/2;
		rcRes.right = rcRes.left + nWidth;
		rcRes.bottom = rcRes.top + nHeight;
		break;

	case eAlign_Full:
		rcRes = rcParent;
		break;

	default:
		assert(false);
	}
	
	return true;
}

bool CUIWindowBase::CalcWindowFloatPos(CRect& rcRes) const
{
	CRect rcParent;
	if(m_pParent){
		m_pParent->GetRect(rcParent);
	}
	else{
		ATLASSERT(false);
	}
	return CalcWindowFloatPos(rcParent, m_rcInit, m_wndAlign, rcRes);
}

bool CUIWindowBase::CalcWindowPos( const CRect& rcSpace, CRect& rcRes ) const
{
	rcRes = rcSpace;
	int nWidth = rcSpace.Width();
	int nHeight = rcSpace.Height();
	if(m_rcInit.Width()!=0){
		nWidth = m_rcInit.Width();
	}
	if(m_rcInit.Height()!=0){
		nHeight = m_rcInit.Height();
	}
	
	if((m_maxSize.cx|m_maxSize.cy) != 0){
		nWidth = max(nWidth, m_maxSize.cx);
		nHeight = max(nHeight, m_maxSize.cy);
	}
	
	rcRes.right = rcRes.left + nWidth;
	rcRes.bottom = rcRes.top + nHeight;

	return true;
}

bool CUIWindowBase::CvtTextAlign( const std::wstring strTextAlign, Gdiplus::StringFormat& format )
{
	//lefttop,left,leftbottom,bottom,rightbottom,right£¨righttop£¨top£¨center
	const int nLen = strTextAlign.length();

	switch(nLen){

	case 7://lefttop
		assert(strTextAlign == _T("lefttop"));
		//break;//countinue
	case 0://null
		format.SetAlignment(Gdiplus::StringAlignmentNear);
		format.SetLineAlignment(Gdiplus::StringAlignmentNear);
		break;

	case 3://top
		assert(strTextAlign == _T("top"));
		format.SetAlignment(Gdiplus::StringAlignmentCenter);
		format.SetLineAlignment(Gdiplus::StringAlignmentNear);
		break;

	case 4://left,
		assert(strTextAlign == _T("left"));
		format.SetAlignment(Gdiplus::StringAlignmentNear);
		format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		break;

	case 5://right
		assert(strTextAlign == _T("right"));
		format.SetAlignment(Gdiplus::StringAlignmentFar);
		format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		break;

	case 6://bottom,center
		if(strTextAlign.at(0) == _T('b')){
			assert(strTextAlign == _T("bottom"));
			format.SetAlignment(Gdiplus::StringAlignmentCenter);
			format.SetLineAlignment(Gdiplus::StringAlignmentFar);
		}
		else{
			assert(strTextAlign == _T("center"));
			format.SetAlignment(Gdiplus::StringAlignmentCenter);
			format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
		}
		break;
	
	case 8://righttop
		assert(strTextAlign == _T("righttop"));
		format.SetAlignment(Gdiplus::StringAlignmentFar);
		format.SetLineAlignment(Gdiplus::StringAlignmentNear);
		break;

	case 10://leftbottom
		assert(strTextAlign == _T("leftbottom"));
		format.SetAlignment(Gdiplus::StringAlignmentNear);
		format.SetLineAlignment(Gdiplus::StringAlignmentFar);
		break;

	case 11://rightbottom
		assert(strTextAlign == _T("rightbottom"));
		format.SetAlignment(Gdiplus::StringAlignmentFar);
		format.SetLineAlignment(Gdiplus::StringAlignmentFar);
		break;

	default:
		assert(false);
	}

	return true;
}

void CUIWindowBase::DoPaint( Gdiplus::Graphics* pGraphics )
{
	PaintBkGnd(pGraphics, m_rcWnd);
	PaintBorder(pGraphics, m_rcWnd);
	PaintText(pGraphics, m_rcWnd);
}

void CUIWindowBase::PaintBkGnd( Gdiplus::Graphics* pGraphics , const CRect& rcArea)
{
	if(!m_strBkImg.empty()){
		Image* pImage = CImageFactory::GetInst()->GetObject(m_strBkImg.c_str(), GetWindowInfo());
		pGraphics->DrawImage(pImage,GdiplusHelper::Rect2GPRectF(rcArea),
			0,0,(Gdiplus::REAL)pImage->GetWidth(),(Gdiplus::REAL)pImage->GetHeight(),UnitPixel);
	}
	else{
		pGraphics->FillRectangle(CBrushFactory::GetInst()->GetObject(m_bkColor),GdiplusHelper::Rect2GPRectF(rcArea));
	}
}

void CUIWindowBase::PaintBorder( Gdiplus::Graphics* pGraphics , const CRect& rcArea)
{
	if(m_nBorderWidth){
		Pen* pPen = CPenFactory::GetPen(m_borderColor,m_nBorderWidth);
		pPen->SetAlignment(PenAlignmentInset);
		pGraphics->DrawRectangle(pPen,GdiplusHelper::Rect2GPRectF(rcArea));
		pPen->SetAlignment(PenAlignmentCenter);
	}
}

void CUIWindowBase::PaintText( Gdiplus::Graphics* pGraphics , const CRect& rcArea)
{
	if(!m_strText.empty()){
		Font* pFont = CFontFactory::GetFont(m_strFontFamily.c_str(),m_nFontSize,m_bBold,m_bUnderline,m_bStrikout);
		Brush* pBrush = CBrushFactory::GetBrush(m_textColor);
		pGraphics->DrawString( m_strText.c_str(), -1,pFont, GdiplusHelper::Rect2GPRectF(rcArea), &m_stringFormat, pBrush);
	}
}

void CUIWindowBase::UIInvalidate()
{
	InvalidateRect(GetRootHandle(),&m_rcWnd,TRUE);
}
