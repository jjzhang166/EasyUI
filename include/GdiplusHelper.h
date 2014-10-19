#pragma once

namespace  GdiplusHelper
{
	inline Gdiplus::Rect Rect2GPRect(const CRect& rc){
		return Gdiplus::Rect(rc.left,rc.top,rc.Width(),rc.Height());
	}

	inline CRect GPRect2Rect(const Gdiplus::Rect& rc){
		return CRect(rc.X,rc.Y,rc.GetRight(),rc.GetBottom());
	}

	inline Gdiplus::RectF Rect2GPRectF(const CRect& rc){
		return Gdiplus::RectF((Gdiplus::REAL)rc.left,(Gdiplus::REAL)rc.top,(Gdiplus::REAL)rc.Width(),(Gdiplus::REAL)rc.Height());
	}

	inline CRect GPRectF2Rect(const Gdiplus::RectF& rc){
		return CRect((int)rc.X,(int)rc.Y,(int)rc.GetRight(),(int)rc.GetBottom());
	}

	inline BYTE GPGetAValue(const Gdiplus::ARGB argb){
		return (argb>>Gdiplus::Color::AlphaShift)&0xFF;
	}

	inline BYTE GPGetRValue(const Gdiplus::ARGB argb){
		return (argb>>Gdiplus::Color::RedShift)&0xFF;
	}

	inline BYTE GPGetGValue(const Gdiplus::ARGB argb){
		return (argb>>Gdiplus::Color::GreenShift)&0xFF;
	}

	inline BYTE GPGetBValue(const Gdiplus::ARGB argb){
		return (argb>>Gdiplus::Color::BlueShift)&0xFF;
	}

	inline COLORREF GPARGB2RGB(const Gdiplus::ARGB argb){
		return RGB(GPGetRValue(argb),GPGetGValue(argb),GPGetBValue(argb));
	}

	inline Gdiplus::ARGB RGB2GPARGB(const COLORREF clr){
		return Gdiplus::Color::MakeARGB(0xFF,GetRValue(clr),GetGValue(clr),GetBValue(clr));
	}
};

