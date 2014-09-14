#include "StdAfx.h"

using namespace Gdiplus;

CPenFactory* CPenFactory::GetInst()
{
	static CPenFactory* pInst = NULL;
	if(pInst == NULL){
		pInst = new CPenFactory;
	}
	return pInst;
}

Gdiplus::Pen* CPenFactory::GetPen( Gdiplus::ARGB argb /*= 0xFF000000*/, DWORD dwWidth /*= 3*/ )
{
	return CPenFactory::GetInst()->GetObject(argb,dwWidth);
}

Pen* CPenFactory::GetObject( ARGB argb /*= 0xFF000000*/, DWORD dwWidth /*= 3*/ )
{
	return GetObject(PenID(argb,dwWidth));
}

Pen* CPenFactory::GetObject( const PenID& penID )
{
	Pen* pPen = NULL;
	IterMapPen iter = m_mapPen.find(penID);
	if(iter == m_mapPen.end()){
		pPen = new Pen(penID.m_argb, (Gdiplus::REAL)penID.m_dwWidth);
		m_mapPen[penID] = pPen;
	}
	else{
		pPen = iter->second;
	}
	return pPen;
}
