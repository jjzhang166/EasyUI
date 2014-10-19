#pragma once

class EASYUI_API CUIWindowBase : public CMessageHandler
{
public:
	CUIWindowBase(CUIWindowBase* pParent);
	~CUIWindowBase();

	virtual BOOL IsContainer(){return FALSE;};
	virtual BOOL IsDUIWindow(){return TRUE;};

	BEGIN_DUI_MSG_MAP(CUIWindowBase)
	END_DUI_MESSAGE_MAP()

	std::wstring GetName();
	void SetName(LPCTSTR szName);
	CUIWindowBase* GetParent();
	void SetParent(CUIWindowBase* pParent);
	CUIWindowBase* GetRoot();
	HWND GetRootHandle();
	bool SetCapture();
	bool ReleaseCapture();
	virtual BOOL MoveWindow(LPRECT lprc);
	virtual BOOL MoveWindow(int nLeft, int nTop, int nWidth, int nHeight);

	bool IsFloat();
	bool IsPlaceHolder();
	void GetRect(CRect& rcWnd);
	void SetRect(const CRect& rcWnd);
	void GetInitRect(CRect& rcInit);
	void SetInitRect(const CRect& rcInit);
	void GetPadding(CRect& rcPadding);
	void SetPadding(const CRect& rcPadding);
	void GetMargin(CRect& rcMargin);
	void SetMargin(const CRect& rcMargin);
	void GetMinSize(CSize& minSz);
	void GetMaxSize(CSize& maxSz);
	bool IsVisible();
	void GetBkImg(std::wstring& strBgImg);
	void SetBkImg(const std::wstring& strBgImg);
	Gdiplus::ARGB GetBkClr();
	void SetBkClr(const Gdiplus::ARGB& clr);
	std::wstring GetText(){ return m_strText; };
	void SetText(LPCTSTR szText){ m_strText = szText; };
	int GetFontSize(){ return m_nFontSize; };
	void SetFontSize(int nSize){ m_nFontSize = nSize; };
	Gdiplus::ARGB GetTextColor(){ return m_textColor; };
	void SetTextColor(const Gdiplus::ARGB& clr){ m_textColor = clr; };
	std::wstring GetFontFamily(){ return m_strFontFamily; };
	void SetFontFamily(LPCTSTR szFontFamily){ m_strFontFamily=szFontFamily; };
	bool IsBold(){return m_bBold;}
	bool IsItalic(){return m_bItalic;}
	bool IsUnderline(){ return m_bUnderline; }
	bool IsStrikout(){ return m_bStrikout; }
	bool IsMultiLine(){ return m_bMultiLine; }
	void SetMultiLine(bool bMultiLine);
	std::wstring GetTextAlign(){ return m_strTextAlign; }
	void SetTextAlign(LPCTSTR szTextAlign);

	bool IsOverCaption();


	virtual BOOL Create(pugi::xml_node& node);
	virtual BOOL ParseAttribute(pugi::xml_node& node);

	//布局
	static bool CalcWindowFloatPos(const CRect& rcParent, const CRect& rcCtrlInit, const std::wstring& strAlign, CRect& rcNew);
	bool CalcWindowFloatPos(CRect& rcWnd);
	//文字对齐方式
	static bool CalcTextFormat(const std::wstring strTextAlign, Gdiplus::StringFormat& format);

	//绘制
	virtual void DoPaint(Gdiplus::Graphics* pGraphics);
	virtual void PaintBkGnd(Gdiplus::Graphics* pGraphics);
	virtual void PaintBorder(Gdiplus::Graphics* pGraphics);
	virtual void PaintText(Gdiplus::Graphics* pGraphics);

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

