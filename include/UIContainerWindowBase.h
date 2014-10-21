#pragma once

class EASYUI_API CUIContainerWindowBase : public CUIWindowBase
{
public:
	CUIContainerWindowBase(CUIWindowBase* pParent);
	~CUIContainerWindowBase(void);

	virtual BOOL IsContainer(){return TRUE;};

	BEGIN_DUI_MSG_MAP(CUIContainerWindowBase)
		DUI_MSG_HANDLER(WM_SIZE, dui_OnSize)
		CHAIN_DUI_MSG_MAP(CUIWindowBase)
	END_DUI_MSG_MAP()

	LRESULT dui_OnSize(const CDuiMSG& duiMsg, BOOL bHandled);

	//find function
	CUIWindowBase* ForwardFindChild(const std::function<bool(CUIWindowBase*)>& pred);
	CUIWindowBase* BackwardFindChild(const std::function<bool(CUIWindowBase*)>& pred);
	enum eFindChild{
		eFindChild_NULL = 0,
		eFindChild_Backward = 1,
		eFindChild_Recursive = 2,
	};
	virtual CUIWindowBase* FindChild(LPCTSTR szName,int nFindFlag);
	virtual CUIWindowBase* FindChild(const CPoint& pt,int nFindFlag);	

	virtual BOOL ParseAttribute(pugi::xml_node& node);
	virtual BOOL Create(pugi::xml_node& node);
	virtual BOOL CreateChilds(pugi::xml_node& node);

	virtual void DoPaint(Gdiplus::Graphics* pGraphics);
	virtual void DoPaintChilds(Gdiplus::Graphics* pGraphics);
	
protected:
	std::vector<CUIWindowBase*> m_childWndList;
	typedef std::vector<CUIWindowBase*> TypeChildWndList;
	typedef std::vector<CUIWindowBase*>::iterator IterChildWndList;

	std::wstring m_strChildAlign;
};

