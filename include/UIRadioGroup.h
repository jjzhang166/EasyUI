#pragma once

class CUIRadio;

class CUIRadioGroup
	: public CUIContainerWindow
{
public:
	CUIRadioGroup(CUIWindowBase* pParent);
	~CUIRadioGroup();

	//ѡ��һ����ѡ�򣬷���ԭ��ѡ�е���
	CUIRadio* SelectItem(CUIRadio* pItem);
	CUIRadio* GetSelectedItem() const { return m_pSelectedItem; };

	//do not paint anything,(transparent)
	virtual void DoPaint(Gdiplus::Graphics* pGraphics){DoPaintChilds(pGraphics);};

private:
	CUIRadio* m_pSelectedItem;
};
