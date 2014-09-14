#include "stdafx.h"

using namespace Gdiplus;

CBrushFactory* CBrushFactory::GetInst()
{
	static CBrushFactory* pInst = NULL;
	if(NULL == pInst){
		pInst = new CBrushFactory;
	}

	return pInst;
}

Brush* CBrushFactory::GetBrush( Gdiplus::ARGB argb )
{
	return CBrushFactory::GetInst()->GetObject(argb);
}

Gdiplus::Brush* CBrushFactory::GetObject( Gdiplus::ARGB argb )
{
	Brush* pBrush = NULL;
	IterMapBrush iter = m_mapBrush.find(argb);
	if(m_mapBrush.end() == iter){
		pBrush = new SolidBrush(Color(argb));
		m_mapBrush[argb] = pBrush;
	}
	else{
		pBrush = iter->second;
	}

	return pBrush;
}

