#pragma once
class EASY_UI_API GdiplusHelper
{
private:
	GdiplusHelper();

public:
	static Gdiplus::Rect EasyRect(const CRect& rc){
		return Gdiplus::Rect(rc.left,rc.top,rc.Width(),rc.Height());
	}

	static CRect EasyRect(const Gdiplus::Rect& rc){
		return CRect(rc.X,rc.Y,rc.GetRight(),rc.GetBottom());
	}

	static Gdiplus::RectF EasyRectF(const CRect& rc){
		return Gdiplus::RectF((Gdiplus::REAL)rc.left,(Gdiplus::REAL)rc.top,(Gdiplus::REAL)rc.Width(),(Gdiplus::REAL)rc.Height());
	}

	static CRect EasyRectF(const Gdiplus::RectF& rc){
		return CRect((int)rc.X,(int)rc.Y,(int)rc.GetRight(),(int)rc.GetBottom());
	}
};

