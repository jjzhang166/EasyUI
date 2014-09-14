#pragma once

class EASY_UI_API CWindowFactory{
private:
	CWindowFactory(){};

public:
	static CWindowFactory* GetInst();
	static CWindowBase* GetWindow(LPCTSTR szType, CWindowBase* pParent);
	CWindowBase* GetObject(LPCTSTR szType, CWindowBase* pParent);
};