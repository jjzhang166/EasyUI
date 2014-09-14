#pragma once

class EASY_UI_API CWindowBase : public CMessageHandler
{
public:
	CWindowBase(CWindowBase* pParent);
	~CWindowBase();

	virtual BOOL IsContainer(){return FALSE;};
	virtual BOOL IsDUIWindow(){return TRUE;};

	BEGIN_DUI_MSG_MAP(CWindowBase)
	END_DUI_MESSAGE_MAP()

	std::wstring GetName();
	void SetName(LPCTSTR szName);
	CWindowBase* GetParent();
	void SetParent(CWindowBase* pParent);
	CWindowBase* GetRoot();
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
	void GetBgImg(std::wstring& strBgImg);
	void SetBgImg(const std::wstring& strBgImg);
	void GetBgClr(Gdiplus::ARGB& clr);
	void SetBgClr(const Gdiplus::ARGB& clr);
	std::wstring GetText();
	void SetText(LPCTSTR szText);
	bool IsOverCaption();


	virtual BOOL Create(pugi::xml_node& node);
	virtual BOOL ParseAttribute(pugi::xml_node& node);

	//布局
	static bool CalcWindowFloatPos(const CRect& rcParent, const CRect& rcCtrlInit, const std::wstring& strAlign, CRect& rcNew);
	bool CalcWindowFloatPos(CRect& rcWnd);

	//绘制
	virtual void DoPaint(Gdiplus::Graphics* pGraphics);
	virtual void PaintBkGnd(Gdiplus::Graphics* pGraphics);
	virtual void PaintBorder(Gdiplus::Graphics* pGraphics);
	virtual void PaintText(Gdiplus::Graphics* pGraphics);

	void DUIInvalidate();
	
protected:
	std::wstring	m_strName;
	CWindowBase*	m_pParent;
	CWindowBase*	m_pRoot;

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
	Gdiplus::ARGB	m_fontColor;
	bool			m_bBold;
	bool			m_bUnderline;
	bool			m_bStrikout;
	
	bool			m_bEnable;
	bool			m_bOverCaption;	//覆盖HTCAPTION，针对系统菜单中的按钮
};

