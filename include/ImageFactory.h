#pragma once

class EASYUI_API CImageFactory
{
private:
	CImageFactory(void){};
public:
	static CImageFactory* GetInst();
	static Gdiplus::Image* GetImage(LPCTSTR strPath);

	Gdiplus::Image* GetObject(LPCTSTR strPath);

protected:
	std::map<std::wstring, Gdiplus::Image*> m_mapImage;
	typedef std::map<std::wstring, Gdiplus::Image*>::iterator IterMapImage;
};

