#include "StdAfx.h"

CHoriLayout::CHoriLayout(CWindowBase* pParent)
	: CContainerWindowBase(pParent)
{
}


CHoriLayout::~CHoriLayout(void)
{
}

LRESULT CHoriLayout::dui_OnSize( const CDuiMSG& duiMSG, BOOL& bHandled )
{
	bHandled = TRUE;

	if(m_childWndList.empty()){
		return true;
	}

	if(!IsVisible()){
		return TRUE;
	}

	int nAdjustItemCount = 0;
	int nMinWidthCount = m_rcPadding.left + m_rcPadding.right;
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
		if(rcInit.Width() == 0){
			nMinWidthCount += minSize.cx;
			nAdjustItemCount++;
		}
		else{
			nMinWidthCount += rcInit.Width();
		}
	}

	const int nAdjustWidthPerCtrl = (nAdjustItemCount==0) ? 0:(max(m_rcWnd.Width()-nMinWidthCount,0)/nAdjustItemCount);
	int nLeft = m_rcWnd.left+m_rcPadding.left;

	if(nAdjustItemCount==0 && m_rcWnd.Width()-nMinWidthCount>0){
		if(m_strChildAlign == _T("center")){
			nLeft += (m_rcWnd.Width()-nMinWidthCount)/2;
		}
		else if(m_strChildAlign == _T("right")){
			nLeft += (m_rcWnd.Width()-nMinWidthCount);
		}
	}

	for(IterChildWndList iter = m_childWndList.begin(); iter != m_childWndList.end(); ++iter){
		CWindowBase* pCtrl = (*iter);
		if(pCtrl->IsFloat()){
			CRect rcResult;
			pCtrl->CalcWindowFloatPos(rcResult);
			pCtrl->MoveWindow(&rcResult);
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
				nCtrlWidth = minSize.cx + nAdjustWidthPerCtrl;
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
				nCtrlHeight = m_rcWnd.Height()-m_rcPadding.top-m_rcPadding.bottom-rcMargin.top - rcMargin.bottom;
			}
			else{
				nCtrlHeight = rcInit.Height();
			}

			if(minSize.cy > 0 && nCtrlHeight < minSize.cy)
				nCtrlHeight = minSize.cy;
			if(maxSize.cy > 0 && nCtrlHeight > maxSize.cy)
				nCtrlHeight = maxSize.cy;
		}

		nLeft += rcMargin.left;
		rcResult.left = nLeft;
		rcResult.top = m_rcWnd.top + m_rcPadding.top + rcMargin.top;
		rcResult.right = rcResult.left + nCtrlWidth;
		rcResult.bottom = rcResult.top + nCtrlHeight;

		pCtrl->MoveWindow(rcResult);
		nLeft = rcResult.right + rcMargin.right;
	}

	return TRUE;
}
