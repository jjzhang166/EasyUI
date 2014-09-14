#include "stdafx.h"

bool ParserHelper::String2Rect( LPCTSTR sz, CRect& rc )
{
	bool bRes = false;

	CRect rcTemp;
	LPCTSTR ptr = sz;
	do{
		if(!ptr)break;
		rcTemp.left = _ttoi(ptr);

		ptr = _tcschr(ptr,_T(','));
		if(!ptr || !(*(++ptr)))break;
		rcTemp.top = _ttoi(ptr);

		ptr = _tcschr(ptr,_T(','));
		if(!ptr || !(*(++ptr)))break;
		const int nWidth = _ttoi(ptr);
		rcTemp.right = rcTemp.left + nWidth;

		ptr = _tcschr(ptr,_T(','));
		if(!ptr || !(*(++ptr)))break;
		const int nHeight = _ttoi(ptr);
		rcTemp.bottom = rcTemp.top + nHeight;

		rc  =rcTemp;
		bRes = true;
	} while (0);

	ATLASSERT(bRes);
	return bRes;
}

bool ParserHelper::String2Size( LPCTSTR sz, CSize& size )
{
	bool bRes = false;

	CSize szTemp;
	LPCTSTR ptr = sz;
	do{
		if(!ptr)break;
		szTemp.cx = _ttoi(ptr);

		ptr = _tcschr(ptr,_T(','));
		if(!ptr || !(*(++ptr)))break;
		szTemp.cy = _ttoi(ptr);

		size  =szTemp;
		bRes = true;
	} while (0);

	ATLASSERT(bRes);
	return bRes;
}

bool ParserHelper::String2ARGB( LPCTSTR sz, Gdiplus::ARGB& argb )
{
	bool bRes = false;

	LPCTSTR ptr = sz;
	do 
	{
		if(!ptr){
			break;
		}
		if((*ptr)!=_T('#') || !(*(++ptr)))break;
		argb = _tcstoul(ptr,NULL,16);
		bRes = true;
	} while (0);

	ATLASSERT(bRes);
	return bRes;
}
