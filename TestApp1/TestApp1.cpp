// TestApp1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CGdiplusInit _gpInit;

	CTopHWNDWindow topWnd;
	topWnd.Create(NULL,_T("D:\\Project\\EasyUI\\TestApp1\\test.xml"));
	topWnd.ShowWindow(SW_SHOW);
	topWnd.UpdateWindow();

	MSG msg;
	while(::GetMessage(&msg,NULL,0,0)){
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

 	return (0);
}
