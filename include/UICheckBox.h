#pragma once

class EASYUI_API CUICheckBox
	: public CUIButton
{
public:
	CUICheckBox(CUIWindowBase* pParent);
	~CUICheckBox();

	bool SetCheck(bool bCheck);
	bool IsChecked() const ;

protected:
	bool m_bChecked;
};
