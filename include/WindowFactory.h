#pragma once

class EASYUI_API CWindowFactory{
private:
	CWindowFactory(){};

public:
	static CWindowFactory* GetInst();
	static CUIWindowBase* GetWindow(LPCTSTR szType, CUIWindowBase* pParent);
	CUIWindowBase* GetObject(LPCTSTR szType, CUIWindowBase* pParent);
};