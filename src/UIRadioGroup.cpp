#include "stdafx.h"


CUIRadioGroup::CUIRadioGroup( CUIWindowBase* pParent )
	: CUIContainerWindow(pParent)
	, m_pSelectedItem(NULL)
{

}

CUIRadioGroup::~CUIRadioGroup()
{

}

CUIRadio* CUIRadioGroup::SelectItem( CUIRadio* pItem )
{
	ATLASSERT(pItem->GetParent() == this);

	CUIRadio* pOldSelected = m_pSelectedItem;
	if(pItem != m_pSelectedItem){
		if(m_pSelectedItem){
			m_pSelectedItem->ClearSelectedImpl();
		}
		if(pItem){
			m_pSelectedItem = pItem;
			m_pSelectedItem->SetSelectedImpl();
		}
	}
	
	return pOldSelected;
}

