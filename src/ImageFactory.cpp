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

Gdiplus::Image* CImageFactory::GetImage( LPCTSTR strPath, CWindowInfo* pWindowInfo )
{
	return GetInst()->GetObject(strPath,pWindowInfo);
}

Image* CImageFactory::GetObject( LPCTSTR szPath, CWindowInfo* pWindowInfo )
{
	Image* pImage = NULL;

	if(pWindowInfo){
		std::wstring strFullPath = pWindowInfo->GetSkinDir() + szPath;
			
		IterMapImage iter = m_mapImage.find(strFullPath);
		if(m_mapImage.end() == iter){
			pImage = Image::FromFile(strFullPath.c_str());
			m_mapImage[strFullPath] = pImage;
		}
		else{
			pImage = iter->second;
		}
	}
	else{
		ATLASSERT(pWindowInfo);
	}

	return pImage;
}
