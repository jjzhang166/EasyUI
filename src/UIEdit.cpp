#include "stdafx.h"

class CInternalEdit : public CWindowImpl<CInternalEdit, CEdit>{
public:
	CInternalEdit(CUIEdit* pUIEdit)
		: m_pUIEdit(pUIEdit)
	{
		ATLASSERT(m_pUIEdit);
	}

	BOOL Show(){
		CRect rcWnd;
		m_pUIEdit->GetRect(rcWnd);

		if(!m_hWnd){
			Create(m_pUIEdit->GetRootHandle(),rcWnd,m_pUIEdit->GetText().c_str(),
					WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS |
					( m_pUIEdit->IsMultiLine()?ES_MULTILINE:0 ) | 
					( m_pUIEdit->IsPasswordMode()?ES_PASSWORD:0 )
				);
			CheckAndCreateFont(m_pUIEdit);
			SetFont(m_font.m_hFont);
		}

		SetWindowPos(NULL,rcWnd,SWP_SHOWWINDOW);
		return TRUE;
	}

	BOOL RePos(){
		if(m_hWnd && IsWindowVisible()){
			CRect rcWnd;
			m_pUIEdit->GetRect(rcWnd);
			SetWindowPos(NULL,rcWnd,SWP_SHOWWINDOW);
		}

		return TRUE;
	}

	BOOL Hide(){
		if(m_hWnd){
			return ShowWindow(SW_HIDE);
		}
		else{
			return TRUE;
		}
	}

	BEGIN_MSG_MAP(CInternalEdit)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		MESSAGE_HANDLER(OCM_CTLCOLOREDIT, OnCtlColorEdit)
		MESSAGE_HANDLER(OCM_CTLCOLORSTATIC, OnCtlColorEdit)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled){
		Hide();
		m_pUIEdit->SendDuiMessage(WM_KILLFOCUS,NULL);
		bHandled = FALSE;
		return TRUE;
	}

	LRESULT OnCtlColorEdit(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/){
		HDC hDC = (HDC)wParam;
		if(hDC){
			::SetTextColor(hDC,GdiplusHelper::GPARGB2RGB(m_pUIEdit->GetTextColor()));
			::SetBkMode(hDC,TRANSPARENT);
			CheckAndCreateBkBrush(m_pUIEdit);
		}
		return (LRESULT)m_brBk.m_hBrush;
	}

protected:
	BOOL CheckAndCreateFont(CUIEdit* pUIEdit){
		if(m_font.IsNull()){
			ATLASSERT(pUIEdit);
			std::wstring strName = pUIEdit->GetFontFamily();
			if(strName.empty()){
				strName = _T("Arial");
			}
			m_font.CreateFont(0-m_pUIEdit->GetFontSize(),0,0,0,
				pUIEdit->IsBold()?FW_BOLD:FW_NORMAL,
				pUIEdit->IsItalic()?TRUE:FALSE,
				pUIEdit->IsUnderline()?TRUE:FALSE,
				pUIEdit->IsStrikout()?TRUE:FALSE,
				DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,
				strName.c_str());
		}

		return TRUE;
	}

	BOOL CheckAndCreateBkBrush(CUIEdit* pUIEdit){
		if(m_brBk.IsNull()){
			ATLASSERT(pUIEdit);
			m_brBk.CreateSolidBrush(GdiplusHelper::GPARGB2RGB(pUIEdit->GetBkClr()));
		}
		return TRUE;
	}

private:
	CUIEdit* m_pUIEdit;
	CFont m_font;
	CBrush m_brBk;
};


CUIEdit::CUIEdit( CUIWindowBase* pParent )
	: CUILabel(pParent)
	, m_pInternalEdit(new CInternalEdit(this))
{
}

LRESULT CUIEdit::dui_OnLButtonDown( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	bHandled = TRUE;
	
	return TRUE;
}

LRESULT CUIEdit::dui_OnSetFocus( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	BOOL bRes = m_pInternalEdit->Show();
	m_pInternalEdit->SetFocus();
	return TRUE;
}

LRESULT CUIEdit::dui_OnKillFocus( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	if( ((CUITopWindow*)GetRoot())->GetFocusWindow() == this){
		((CUITopWindow*)GetRoot())->SetFocusWindow(NULL);
	}

	BOOL bRes = m_pInternalEdit->Hide();
	CString strText;
	m_pInternalEdit->GetWindowText(strText);
	SetText(strText);
	UIInvalidate();

	return bRes;
}

LRESULT CUIEdit::dui_OnSize( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	m_pInternalEdit->RePos();
	return TRUE;
}

LRESULT CUIEdit::dui_OnMove( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	m_pInternalEdit->RePos();
	return TRUE;
}

