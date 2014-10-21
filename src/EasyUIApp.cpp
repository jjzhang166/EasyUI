#include "stdafx.h"

#include "EasyUIApp.h"

CEasyUIApp::CEasyUIApp()
	: m_hResourceModule(NULL)
{
	::OleInitialize(NULL);
}

CEasyUIApp::~CEasyUIApp()
{
	::OleUninitialize();
}

CEasyUIApp* CEasyUIApp::GetInst()
{
	static CEasyUIApp* pInst = NULL;
	if(pInst == NULL){
		pInst = new CEasyUIApp;
	}

	return pInst;
}

void CEasyUIApp::SetResourceModule( HMODULE hModule )
{
	m_hResourceModule = hModule;
}

HMODULE CEasyUIApp::GetResourceModule()
{
	return m_hResourceModule;
}

int CEasyUIApp::Run()
{
	MSG msg;
	while(::GetMessage(&msg,NULL,0,0)){
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return msg.wParam;
}

