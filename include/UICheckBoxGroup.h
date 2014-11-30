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
	bool InternalItemChecked();	//��һ�check
	bool InternalItemUnChecked(); //��һ�uncheck
	int m_nCheckItemCount;
};

