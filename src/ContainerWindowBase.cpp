#include "stdafx.h"

CContainerWindowBase::CContainerWindowBase(CWindowBase* pParent)
	: CWindowBase(pParent)
{
}


CContainerWindowBase::~CContainerWindowBase(void)
{
}

LRESULT CContainerWindowBase::dui_OnSize( const CDuiMSG& duiMsg, BOOL bHandled )
{
	for(IterChildWndList iter = m_childWndList.begin(); iter != m_childWndList.end(); ++iter){
		CRect rcWnd;
		(*iter)->CalcWindowFloatPos(rcWnd);
		(*iter)->MoveWindow(rcWnd);
	}

	return TRUE;
}

CWindowBase* CContainerWindowBase::ForwardFindChild(const std::function<bool(CWindowBase*)>& pred )
{
	CWindowBase* pWindow = NULL;
	IterChildWndList iter = std::find_if(m_childWndList.begin(),m_childWndList.end(),pred);
	if(iter!=m_childWndList.end()){
		pWindow = (*iter);
	}

	return pWindow;
}

CWindowBase* CContainerWindowBase::BackwardFindChild(const std::function<bool(CWindowBase*)>& pred )
{
	CWindowBase* pWindow = NULL;
	TypeChildWndList::reverse_iterator iter = std::find_if(m_childWndList.rbegin(),m_childWndList.rend(),pred);
	if(iter!=m_childWndList.rend()){
		pWindow = (*iter);
	}

	return pWindow;
}

CWindowBase* CContainerWindowBase::FindChild( LPCTSTR szName,int nFindFlag )
{
	std::function<bool(CWindowBase*)> pred = [szName](CWindowBase* pWindow)->bool{return pWindow->GetName()==szName;};
	if(!(nFindFlag&eFindChild_Backward)){
		if(!(nFindFlag&eFindChild_Recursive)){
			return ForwardFindChild(pred);
		}
		else{
			CWindowBase* pWindow = this;
			CWindowBase* pFindRes = NULL;
			while(pWindow->IsContainer() && 
				(pFindRes = dynamic_cast<CContainerWindowBase*>(pWindow)->ForwardFindChild(pred))
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
			CWindowBase* pWindow = this;
			CWindowBase* pFindRes = NULL;
			while(pWindow->IsContainer() && 
					(pFindRes = dynamic_cast<CContainerWindowBase*>(pWindow)->BackwardFindChild(pred))
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

CWindowBase* CContainerWindowBase::FindChild( const CPoint& pt,int nFindFlag )
{
	std::function<bool(CWindowBase*)> pred = 
		[&pt](CWindowBase* pWindow)->bool{CRect rcCtrl;pWindow->GetRect(rcCtrl);return (rcCtrl.PtInRect(pt)==TRUE);};

	if(!(nFindFlag&eFindChild_Backward)){
		if(!(nFindFlag&eFindChild_Recursive)){
			return ForwardFindChild(pred);
		}
		else{
			CWindowBase* pWindow = this;
			CWindowBase* pFindRes = NULL;
			while(pWindow->IsContainer() && 
				(pFindRes = dynamic_cast<CContainerWindowBase*>(pWindow)->ForwardFindChild(pred))
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
			CWindowBase* pWindow = this;
			CWindowBase* pFindRes = NULL;
			while(pWindow->IsContainer() && 
				(pFindRes = dynamic_cast<CContainerWindowBase*>(pWindow)->BackwardFindChild(pred))
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

BOOL CContainerWindowBase::ParseAttribute( pugi::xml_node& node )
{
	__super::ParseAttribute(node);

	pugi::xml_attribute attr = node.attribute(_T("child_align"));
	if(attr){
		m_strChildAlign = attr.as_string();
	}

	return TRUE;
}

BOOL CContainerWindowBase::Create( pugi::xml_node& node )
{
	__super::Create(node);

	return CreateChilds(node);
}

BOOL CContainerWindowBase::CreateChilds( pugi::xml_node& node )
{
	pugi::xml_node childNode = node.first_child();
	while (childNode)
	{
		CWindowBase* pWindow = CWindowFactory::GetWindow(childNode.name(), this);
		pWindow->Create(childNode);
		m_childWndList.push_back(pWindow);
		SendDuiMessage(pWindow,WM_CREATE,this);
		childNode = childNode.next_sibling();
	}
	return TRUE;
}

void CContainerWindowBase::DoPaint( Gdiplus::Graphics* pGraphics )
{
	__super::DoPaint(pGraphics);
	DoPaintChilds(pGraphics);
}

void CContainerWindowBase::DoPaintChilds( Gdiplus::Graphics* pGraphics )
{
	Gdiplus::RectF rcCtrlClip;
	pGraphics->GetClipBounds(&rcCtrlClip);
	for(IterChildWndList iter = m_childWndList.begin(); iter != m_childWndList.end(); ++iter){
		CRect rcCtrl;
		(*iter)->GetRect(rcCtrl);
		pGraphics->IntersectClip(GdiplusHelper::EasyRectF(rcCtrl));

		(*iter)->DoPaint(pGraphics);

		pGraphics->SetClip(rcCtrlClip);
	}
}

