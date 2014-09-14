#pragma once

class EASY_UI_API CBrushFactory{
private:
	CBrushFactory(){}
public:
	static CBrushFactory* GetInst();
	static Gdiplus::Brush* GetBrush(Gdiplus::ARGB argb);

	Gdiplus::Brush* GetObject(Gdiplus::ARGB argb);

protected:
	std::map<Gdiplus::ARGB,Gdiplus::Brush*> m_mapBrush;
	typedef std::map<Gdiplus::ARGB,Gdiplus::Brush*>::iterator IterMapBrush;
};