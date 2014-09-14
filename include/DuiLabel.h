#pragma once 

class EASY_UI_API CDuiLabel : public CWindowBase{
public:
	CDuiLabel(CWindowBase* pParent);

	virtual BOOL ParseAttribute(pugi::xml_node& node);

protected:
	bool m_bWidthFollowText;
	bool m_bHeightFollowText;
};



