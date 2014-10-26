#pragma once

class CUIRadio;

class CUIRadioGroup
	: public CUIContainerWindow
{
public:
	CUIRadioGroup(CUIWindowBase* pParent);
	~CUIRadioGroup();

	//选中一个单选框，返回原来选中的项
	CUIRadio* SelectItem(CUIRadio* pItem);
	CUIRadio* GetSelectedItem() const { return m_pSelectedItem; };

	//do not paint anything,(transparent)
	virtual void DoPaint(Gdiplus::Graphics* pGraphics){DoPaintChilds(pGraphics);};

private:
	CUIRadio* m_pSelectedItem;
};
