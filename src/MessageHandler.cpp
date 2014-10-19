#include "stdafx.h"

LRESULT CMessageHandler::SendDuiMessage( UINT uMsg, const CDuiMSG& duiMSG )
{
	return ProcessDuiWindowMessage(uMsg,duiMSG);
}

LRESULT CMessageHandler::SendDuiMessage( UINT uMsg, CUIWindowBase* pSrcCtrl /*= NULL*/, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/ )
{
	return ProcessDuiWindowMessage(uMsg,CDuiMSG(pSrcCtrl,wParam,lParam));
}

LRESULT CMessageHandler::SendDuiMessage( CUIWindowBase* pWindow, UINT uMsg, const CDuiMSG& duiMSG )
{
	return pWindow->ProcessDuiWindowMessage(uMsg,duiMSG);
}

LRESULT CMessageHandler::SendDuiMessage( CUIWindowBase* pWindow, INT uMsg, CUIWindowBase* pSrcCtrl /*= NULL*/, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/ )
{
	return pWindow->ProcessDuiWindowMessage(uMsg,CDuiMSG(pSrcCtrl,wParam,lParam));
}
