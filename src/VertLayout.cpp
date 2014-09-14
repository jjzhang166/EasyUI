#include "StdAfx.h"

CVertLayout::CVertLayout(CWindowBase* pParent)
	: CContainerWindowBase(pParent)
{
}


CVertLayout::~CVertLayout(void)
{
}

LRESULT CVertLayout::dui_OnSize( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	bHandled = TRUE;

	if(m_childWndList.empty()){
		return TRUE;
	}

	if(!IsVisible()){
		return TRUE;
	}

	int nAdjustItemCount = 0;
	int nMinHeightCount = m_rcPadding.top + m_rcPadding.bottom;
	for(IterChildWndList iter = m_childWndList.begin(); iter != m_childWndList.end(); ++iter){
		CWindowBase* pCtrl = (*iter);
		if(pCtrl->IsFloat()){
			continue;
		}

		if(!pCtrl->IsVisible()){
			continue;
		}

		CRect rcInit;
		CSize minSize;
		pCtrl->GetInitRect(rcInit);
		pCtrl->GetMinSize(minSize);
		if(rcInit.Height() == 0){
			nMinHeightCount += minSize.cy;
			nAdjustItemCount++;
		}
		else{
			nMinHeightCount += rcInit.Height();
		}
	}

	const int nAdjustHeightPerCtrl = (nAdjustItemCount==0) ? 0:(max(m_rcWnd.Height()-nMinHeightCount,0)/nAdjustItemCount);
	int nTop = m_rcWnd.top + m_rcPadding.top;

	for(IterChildWndList iter = m_childWndList.begin(); iter != m_childWndList.end(); ++iter){
		CWindowBase* pCtrl = (*iter);
		if(pCtrl->IsFloat()){
			CRect rcResult;
			pCtrl->CalcWindowFloatPos(rcResult);
			pCtrl->MoveWindow(rcResult);
			continue;
		}

		if(!pCtrl->IsVisible()){
			continue;
		}

		CRect rcResult;
		CRect rcInit;
		CRect rcMargin;
		CSize minSize;
		CSize maxSize;
		pCtrl->GetInitRect(rcInit);
		pCtrl->GetMargin(rcMargin);
		pCtrl->GetMinSize(minSize);
		pCtrl->GetMaxSize(maxSize);

		int nCtrlWidth = 0;
		int nCtrlHeight = 0;
		//width
		{
			if(rcInit.Width() == 0){
				nCtrlWidth = m_rcWnd.Width()-m_rcPadding.left-m_rcPadding.right-rcMargin.left-rcMargin.right;
			}
			else{
				nCtrlWidth = rcInit.Width();
			}

			if(minSize.cx > 0 && nCtrlWidth < minSize.cx)
				nCtrlWidth = minSize.cx;
			if(maxSize.cx > 0 && nCtrlWidth > maxSize.cx)
				nCtrlWidth = maxSize.cx;
		}
		//height
		{
			if(rcInit.Height() == 0){
				nCtrlHeight = minSize.cy + nAdjustHeightPerCtrl;
			}
			else{
				nCtrlHeight = rcInit.Height();
			}

			if(minSize.cy > 0 && nCtrlHeight < minSize.cy)
				nCtrlHeight = minSize.cy;
			if(maxSize.cy > 0 && nCtrlHeight > maxSize.cy)
				nCtrlHeight = maxSize.cy;
		}

		nTop += rcMargin.top;
		rcResult.left = m_rcWnd.left + m_rcPadding.left + rcMargin.left;
		rcResult.top = nTop;
		rcResult.right = rcResult.left + nCtrlWidth;
		rcResult.bottom = rcResult.top + nCtrlHeight;

		pCtrl->MoveWindow(rcResult);
		nTop = rcResult.bottom + rcMargin.bottom;
	}
	return TRUE;
}
