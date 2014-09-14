#pragma once

class EASY_UI_API CContainerWindowBase : public CWindowBase
{
public:
	CContainerWindowBase(CWindowBase* pParent);
	~CContainerWindowBase(void);

	virtual BOOL IsContainer(){return TRUE;};

	BEGIN_DUI_MSG_MAP(CContainerWindowBase)
		DUI_MSG_HANDLER(WM_SIZE, dui_OnSize)
		CHAIN_DUI_MSG_MAP(CWindowBase)
	END_DUI_MESSAGE_MAP()

	LRESULT dui_OnSize(const CDuiMSG& duiMsg, BOOL bHandled);

	//find function
	CWindowBase* ForwardFindChild(const std::function<bool(CWindowBase*)>& pred);
	CWindowBase* BackwardFindChild(const std::function<bool(CWindowBase*)>& pred);
	enum eFindChild{
		eFindChild_NULL = 0,
		eFindChild_Backward = 1,
		eFindChild_Recursive = 2,
	};
	virtual CWindowBase* FindChild(LPCTSTR szName,int nFindFlag);
	virtual CWindowBase* FindChild(const CPoint& pt,int nFindFlag);	

	virtual BOOL ParseAttribute(pugi::xml_node& node);
	virtual BOOL Create(pugi::xml_node& node);
	virtual BOOL CreateChilds(pugi::xml_node& node);

	virtual void DoPaint(Gdiplus::Graphics* pGraphics);
	virtual void DoPaintChilds(Gdiplus::Graphics* pGraphics);
	
protected:
	std::vector<CWindowBase*> m_childWndList;
	typedef std::vector<CWindowBase*> TypeChildWndList;
	typedef std::vector<CWindowBase*>::iterator IterChildWndList;

	std::wstring m_strChildAlign;
};

