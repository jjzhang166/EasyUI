#include "StdAfx.h"

CFontFactory* CFontFactory::GetInst()
{
	static CFontFactory* pInst = NULL;
	if(pInst == NULL){
		pInst = new CFontFactory;
	}

	return pInst;
}

Gdiplus::Font* CFontFactory::GetFont( LPCTSTR szFamily, int nSize,bool bBold /*= false*/, bool bUnderline /*= false*/, bool bStrikout /*= false*/ )
{
	return CFontFactory::GetInst()->GetObject(szFamily,nSize,bBold,bUnderline,bStrikout);
}

Gdiplus::Font* CFontFactory::GetObject( LPCTSTR szFamily, int nSize,bool bBold /*= false*/, bool bUnderline /*= false*/, bool bStrikout /*= false*/ )
{
	return GetObject(FontID(szFamily,nSize,bBold,bUnderline,bStrikout));
}

Gdiplus::Font* CFontFactory::GetObject( const FontID& fontID )
{
	Gdiplus::Font* pFont = NULL;

	IterMapFont iter = m_mapFont.find(fontID);
	if(iter == m_mapFont.end()){
		pFont = new Gdiplus::Font(fontID.m_strFamily.c_str(),(Gdiplus::REAL)fontID.m_nSize,fontID.m_nStyle,Gdiplus::UnitPixel);
		m_mapFont[fontID] = pFont;
	}
	else{
		pFont = iter->second;
	}

	return pFont;
}
