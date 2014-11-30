#pragma once

class CUICheckBox;

class EASYUI_API CUICheckBoxGroup
	: public CUIContainerWindow
{
public:
	CUICheckBoxGroup(CUIWindowBase* pParent);
	~CUICheckBoxGroup();

	bool CheckAllItem();
	bool ClearAllItemCheck();
	bool IsAllChecked();
	bool IsAllUnChecked();

	friend class CUICheckBox;
protected:
	bool InternalItemChecked();	//有一项被check
	bool InternalItemUnChecked(); //有一项被uncheck
	int m_nCheckItemCount;
};

