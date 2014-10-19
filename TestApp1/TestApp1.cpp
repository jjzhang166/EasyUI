// TestApp1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "MainWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CEasyUIApp* easyApp = CEasyUIApp::GetInst();
	easyApp->InitApp();

	CMainWnd mainWnd;
	mainWnd.Create(NULL,_T("D:\\Project\\EasyUI\\TestApp1\\test.xml"));
	mainWnd.ShowWindow(SW_SHOW);
	mainWnd.UpdateWindow();

	return easyApp->Run();
}
