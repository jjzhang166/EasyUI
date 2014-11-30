#pragma once

class CUIRadio:
	public CUIButton
{
public:
	CUIRadio(CUIWindowBase* pParent);
	~CUIRadio();

	//�ж��Ƿ�ѡ��
	bool IsSelected();
	//����ѡ��
	bool SetSelected();
	//���ѡ��
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
	int m_nInitTextLeftPos;	//�����ļ��е�������߾࣬�����൱��û�����ã����ջ�ʹ�ü���ó��Ľ��
	int m_nTextLeftPos;	//����ó�����߾�

	const static int RADIO_TEXT_LEFT_MARGIN = 4;//��ѡ��������ͼƬ����߾�
};

