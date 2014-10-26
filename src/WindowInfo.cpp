#include "stdafx.h"


CWindowInfo::CWindowInfo( CUITopWindow* pTopWindow )
	: m_pTopWindow(pTopWindow)
{

}

void CWindowInfo::SetSkinPath( LPCTSTR szPath )
{
	if(szPath != NULL){
		m_strSkinPath = szPath;
		ATLASSERT(::PathFileExists(szPath));
		const int nRightSlashPos = max ( (int)m_strSkinPath.rfind(_T('/')), (int)m_strSkinPath.rfind(_T('\\')) );
		if(nRightSlashPos >=0 ){
			m_strSkinDir = m_strSkinPath.substr( 0, nRightSlashPos+1 );
		}
		else{
			ATLASSERT(FALSE);
		}
	}
	else{
		ATLASSERT(FALSE);
	}
}

