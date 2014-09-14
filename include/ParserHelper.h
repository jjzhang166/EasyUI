#pragma once

class EASY_UI_API ParserHelper{
private:
	ParserHelper();//no impl

public:
	static bool String2Rect(LPCTSTR sz, CRect& rc);
	static bool String2Size(LPCTSTR sz, CSize& size);
	static bool String2ARGB(LPCTSTR sz, Gdiplus::ARGB& argb);
};