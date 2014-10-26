#pragma once

class EASYUI_API CUIWindowBase : public CMessageHandler
{
public:
	CUIWindowBase(CUIWindowBase* pParent);
	~CUIWindowBase();

	virtual BOOL IsContainer(){return FALSE;};
	virtual BOOL IsDUIWindow(){return TRUE;};

	BEGIN_DUI_MSG_MAP(CUIWindowBase)
	END_DUI_MSG_MAP()

	std::wstring GetName() const {return m_strName;};
	void SetName(LPCTSTR szName) { m_strName = szName?szName:_T("NULL"); };
	CUIWindowBase* GetParent()const {return m_pParent;};
	void SetParent(CUIWindowBase* pParent){ m_pParent = pParent; };
	CUIWindowBase* GetRoot()const { return m_pRoot; };
	HWND GetRootHandle() const;
	bool SetCapture();
	bool ReleaseCapture();
	virtual BOOL MoveWindow(const LPRECT lprc);
	virtual BOOL MoveWindow(const int nLeft, const int nTop, const int nWidth, const int nHeight);

	bool IsFloat() const { return m_bFloat; };
	bool IsPlaceHolder() const { return m_bPlaceHolder; };
	void GetRect(CRect& rcWnd) const { rcWnd = m_rcWnd; };
	void SetRect(const CRect& rcWnd) { m_rcWnd = rcWnd; };
	void GetInitRect(CRect& rcInit) const { rcInit = m_rcInit; };
	void SetInitRect(const CRect& rcInit) { m_rcInit = rcInit; };
	void GetPadding(CRect& rcPadding) const { rcPadding = m_rcPadding; };
	void SetPadding(const CRect& rcPadding) { m_rcPadding = rcPadding; };
	void GetMargin(CRect& rcMargin) const { rcMargin = m_rcMargin; };
	void SetMargin(const CRect& rcMargin) { m_rcMargin = rcMargin; };
	void GetMinSize(CSize& minSz) const { minSz = m_minSize; };
	void GetMaxSize(CSize& maxSz) const { maxSz = m_maxSize; };
	bool IsVisible() const { return m_bVisible; };
	void GetBkImg(std::wstring& strBkImg) const { strBkImg = m_strBkImg; };
	void SetBkImg(const std::wstring& strBkImg) { m_strBkImg = strBkImg; };
	Gdiplus::ARGB GetBkClr() const { return m_bkColor; };
	void SetBkClr(const Gdiplus::ARGB& clr) { m_bkColor = clr; };
	std::wstring GetText() const { return m_strText; };
	void SetText(LPCTSTR szText){ m_strText = szText; };
	int GetFontSize() const { return m_nFontSize; };
	void SetFontSize(int nSize){ m_nFontSize = nSize; };
	Gdiplus::ARGB GetTextColor() const { return m_textColor; };
	void SetTextColor(const Gdiplus::ARGB& clr){ m_textColor = clr; };
	std::wstring GetFontFamily() const { return m_strFontFamily; };
	void SetFontFamily(LPCTSTR szFontFamily){ m_strFontFamily=szFontFamily; };
	bool IsBold() const {return m_bBold;}
	bool IsItalic() const {return m_bItalic;}
	bool IsUnderline() const { return m_bUnderline; }
	bool IsStrikout() const { return m_bStrikout; }
	bool IsMultiLine() const { return m_bMultiLine; }
	void SetMultiLine(bool bMultiLine);
	std::wstring GetTextAlign() const { return m_strTextAlign; }
	void SetTextAlign(LPCTSTR szTextAlign);

	bool IsOverCaption() const { return m_bOverCaption; };


	virtual BOOL Create(pugi::xml_node& node);
	virtual BOOL ParseAttribute(pugi::xml_node& node);

	//绝对布局
	static bool CalcWindowFloatPos(const CRect& rcParent, const CRect& rcCtrlInit, const std::wstring& strAlign, CRect& rcRes);
	bool CalcWindowFloatPos(CRect& rcRes) const;
	//相对布局
	bool CalcWindowPos(const CRect& rcSpace, CRect& rcRes) const ;

	//文字对齐方式
	static bool CalcTextFormat(const std::wstring strTextAlign, Gdiplus::StringFormat& format);

	//绘制
	virtual void DoPaint(Gdiplus::Graphics* pGraphics);
	virtual void PaintBkGnd(Gdiplus::Graphics* pGraphics, const CRect& rcArea);
	virtual void PaintBorder(Gdiplus::Graphics* pGraphics, const CRect& rcArea);
	virtual void PaintText(Gdiplus::Graphics* pGraphics, const CRect& rcArea);

	void UIInvalidate();
	
protected:
	std::wstring	m_strName;
	CUIWindowBase*	m_pParent;
	CUIWindowBase*	m_pRoot;

	//位置
	CRect			m_rcWnd;	//计算之后的区域，即窗口实际位置，是相对于主窗口的区域
	CRect			m_rcInit;
	CSize			m_minSize;
	CSize			m_maxSize;
	CRect			m_rcMargin;
	CRect			m_rcPadding;
	bool			m_bFloat;
	std::wstring	m_strAlign;

	//绘制
	bool			m_bVisible;
	bool			m_bPlaceHolder;	//true:该空间仅仅为了布局中启占位作用，无需绘制
	//背景
	std::wstring	m_strBkImg;
	Gdiplus::ARGB	m_bkColor;
	//边框
	Gdiplus::ARGB	m_borderColor;
	int				m_nBorderWidth;
	//字体
	std::wstring	m_strText;
	std::wstring	m_strFontFamily;
	int				m_nFontSize;
	Gdiplus::ARGB	m_textColor;
	bool			m_bBold;
	bool			m_bItalic;
	bool			m_bUnderline;
	bool			m_bStrikout;
	bool			m_bMultiLine;
	std::wstring	m_strTextAlign;
	Gdiplus::StringFormat m_stringFormat;
	
	bool			m_bEnable;
	bool			m_bOverCaption;	//覆盖HTCAPTION，针对系统菜单中的按钮
};

