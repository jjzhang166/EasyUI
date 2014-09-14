#pragma once

class EASY_UI_API CGdiplusInit{
public:
	CGdiplusInit(){	
		Gdiplus::GdiplusStartupInput startupInfo;
		Gdiplus::GdiplusStartup(&m_ulGdiplusToken, &startupInfo, NULL);
	}
	~CGdiplusInit(){
		Gdiplus::GdiplusShutdown(m_ulGdiplusToken);
	}

private:
	ULONG_PTR m_ulGdiplusToken;
};

