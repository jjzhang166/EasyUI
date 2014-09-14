#include "stdafx.h"

using namespace Gdiplus;

CImageFactory* CImageFactory::GetInst()
{
	static CImageFactory* pInst = NULL;
	if(pInst == NULL){
		pInst = new CImageFactory;
	}
	return pInst;
}

Gdiplus::Image* CImageFactory::GetImage( LPCTSTR strPath )
{
	return GetInst()->GetObject(strPath);
}

Image* CImageFactory::GetObject( LPCTSTR strPath )
{
	Image* pImage = NULL;
	IterMapImage iter = m_mapImage.find(std::wstring(strPath));
	if(m_mapImage.end() == iter){
		pImage = Image::FromFile(strPath);
		m_mapImage[strPath] = pImage;
	}
	else{
		pImage = iter->second;
	}
	return pImage;
}
