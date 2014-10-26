#include "stdafx.h"

CUIContainerWindowBase::CUIContainerWindowBase(CUIWindowBase* pParent)
	: CUIWindowBase(pParent)
{
}


CUIContainerWindowBase::~CUIContainerWindowBase(void)
{
}

LRESULT CUIContainerWindowBase::dui_OnSize( const CDuiMSG& duiMsg, BOOL& bHandled )
{
	ATLASSERT(FALSE);

	return TRUE;
}

CUIWindowBase* CUIContainerWindowBase::ForwardFindChild(const std::function<bool(CUIWindowBase*)>& pred )
{
	CUIWindowBase* pWindow = NULL;
	IterChildWndList iter = std::find_if(m_childWndList.begin(),m_childWndList.end(),pred);
	if(iter!=m_childWndList.end()){
		pWindow = (*iter);
	}

	return pWindow;
}

CUIWindowBase* CUIContainerWindowBase::BackwardFindChild(const std::function<bool(CUIWindowBase*)>& pred )
{
	CUIWindowBase* pWindow = NULL;
	TypeChildWndList::reverse_iterator iter = std::find_if(m_childWndList.rbegin(),m_childWndList.rend(),pred);
	if(iter!=m_childWndList.rend()){
		pWindow = (*iter);
	}

	return pWindow;
}

CUIWindowBase* CUIContainerWindowBase::FindChild( LPCTSTR szName,int nFindFlag )
{
	std::function<bool(CUIWindowBase*)> pred = [szName](CUIWindowBase* pWindow)->bool{return pWindow->GetName()==szName;};
	if(!(nFindFlag&eFindChild_Backward)){
		if(!(nFindFlag&eFindChild_Recursive)){
			return ForwardFindChild(pred);
		}
		else{
			CUIWindowBase* pWindow = this;
			CUIWindowBase* pFindRes = NULL;
			while(pWindow->IsContainer() && 
				(pFindRes = dynamic_cast<CUIContainerWindowBase*>(pWindow)->ForwardFindChild(pred))
				)
			{
				pWindow = pFindRes;
			}

			if(this == pWindow){
				pWindow = NULL;
			}

			return pWindow;
		}
	}
	else{
		if(!(nFindFlag&eFindChild_Recursive)){
			return BackwardFindChild(pred);
		}
		else
		{
			CUIWindowBase* pWindow = this;
			CUIWindowBase* pFindRes = NULL;
			while(pWindow->IsContainer() && 
					(pFindRes = dynamic_cast<CUIContainerWindowBase*>(pWindow)->BackwardFindChild(pred))
				)
			{
				pWindow = pFindRes;
			}

			if(this == pWindow){
				pWindow = NULL;
			}

			return pWindow;
		}
	}
}

CUIWindowBase* CUIContainerWindowBase::FindChild( const CPoint& pt,int nFindFlag )
{
	std::function<bool(CUIWindowBase*)> pred = 
		[&pt](CUIWindowBase* pWindow)->bool{CRect rcCtrl;pWindow->GetRect(rcCtrl);return (rcCtrl.PtInRect(pt)==TRUE);};

	if(!(nFindFlag&eFindChild_Backward)){
		if(!(nFindFlag&eFindChild_Recursive)){
			return ForwardFindChild(pred);
		}
		else{
			CUIWindowBase* pWindow = this;
			CUIWindowBase* pFindRes = NULL;
			while(pWindow->IsContainer() && 
				(pFindRes = dynamic_cast<CUIContainerWindowBase*>(pWindow)->ForwardFindChild(pred))
				)
			{
				pWindow = pFindRes;
			}

			if(this == pWindow){
				pWindow = NULL;
			}

			return pWindow;
		}
	}
	else{
		if(!(nFindFlag&eFindChild_Recursive)){
			return BackwardFindChild(pred);
		}
		else
		{
			CUIWindowBase* pWindow = this;
			CUIWindowBase* pFindRes = NULL;
			while(pWindow->IsContainer() && 
				(pFindRes = dynamic_cast<CUIContainerWindowBase*>(pWindow)->BackwardFindChild(pred))
				)
			{
				pWindow = pFindRes;
			}

			if(this == pWindow){
				pWindow = NULL;
			}

			return pWindow;
		}
	}
}

BOOL CUIContainerWindowBase::ParseAttribute( pugi::xml_node& node )
{
	__super::ParseAttribute(node);

	pugi::xml_attribute attr = node.attribute(_T("child_align"));
	if(attr){
		m_strChildAlign = attr.as_string();
	}

	return TRUE;
}

BOOL CUIContainerWindowBase::Create( pugi::xml_node& node )
{
	__super::Create(node);

	return CreateChilds(node);
}

BOOL CUIContainerWindowBase::CreateChilds( pugi::xml_node& node )
{
	pugi::xml_node childNode = node.first_child();
	while (childNode)
	{
		CUIWindowBase* pWindow = CWindowFactory::GetWindow(childNode.name(), this);
		pWindow->Create(childNode);
		m_childWndList.push_back(pWindow);
		SendDuiMessage(pWindow,WM_CREATE,this);
		childNode = childNode.next_sibling();
	}
	return TRUE;
}

void CUIContainerWindowBase::DoPaint( Gdiplus::Graphics* pGraphics )
{
	__super::DoPaint(pGraphics);
	DoPaintChilds(pGraphics);
}

void CUIContainerWindowBase::DoPaintChilds( Gdiplus::Graphics* pGraphics )
{
	Gdiplus::RectF rcCtrlClip;
	pGraphics->GetClipBounds(&rcCtrlClip);
	for(IterChildWndList iter = m_childWndList.begin(); iter != m_childWndList.end(); ++iter){
		CRect rcCtrl;
		(*iter)->GetRect(rcCtrl);
		pGraphics->IntersectClip(GdiplusHelper::Rect2GPRectF(rcCtrl));

		(*iter)->DoPaint(pGraphics);

		pGraphics->SetClip(rcCtrlClip);
	}
}

