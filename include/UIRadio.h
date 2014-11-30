#pragma once

class CUIRadio:
	public CUIButton
{
public:
	CUIRadio(CUIWindowBase* pParent);
	~CUIRadio();

	//判断是否选中
	bool IsSelected();
	//设置选中
	bool SetSelected();
	//清除选中
	bool ClearSelected();

	virtual BOOL ParseAttribute( pugi::xml_node& node );

	virtual void PaintBkGnd(Gdiplus::Graphics* pGraphics, const CRect& rcArea);
	virtual void PaintText(Gdiplus::Graphics* pGraphics, const CRect& rcArea);

	BEGIN_DUI_MSG_MAP(CUIRadio)
		DUI_MSG_HANDLER(WM_LBUTTONDOWN,dui_OnLButtonDown)
		CHAIN_DUI_MSG_MAP(CUIButton)
	END_DUI_MSG_MAP()

	LRESULT dui_OnLButtonDown(const CDuiMSG& duiMsg,  BOOL& bHandled);

	friend class CUIRadioGroup;

protected:
	bool SetSelectedImpl();
	bool ClearSelectedImpl();
protected:
	bool m_bSelected;
	std::wstring m_strSelectedImg;
	int m_nInitTextLeftPos;	//布局文件中的文字左边距，负数相当有没有配置，最终会使用计算得出的结果
	int m_nTextLeftPos;	//计算得出的左边距

	const static int RADIO_TEXT_LEFT_MARGIN = 4;//单选框文字与图片的左边距
};

