#pragma once

class CWindowInfo;

class EASYUI_API CImageFactory
{
private:
	CImageFactory(void){};
public:
	static CImageFactory* GetInst();
	static Gdiplus::Image* GetImage(LPCTSTR strPath, CWindowInfo* pWindowInfo);

	Gdiplus::Image* GetObject(LPCTSTR strPath, CWindowInfo* pWindowInfo);

protected:
	std::map<std::wstring, Gdiplus::Image*> m_mapImage;
	typedef std::map<std::wstring, Gdiplus::Image*>::iterator IterMapImage;
};

