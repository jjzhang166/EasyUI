#pragma once

// Windows Header Files:
#include <windows.h>

//atl headers
#include <atlbase.h>
#include <atlstr.h>
#include <atltypes.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlctrls.h>

//gdiplus
#include <objbase.h>
#include <GdiPlus.h>
#pragma comment(lib,"gdiplus.lib")

//stl headers
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

//////////////////////////////////////////////////////////////////////////
#ifdef	EASY_UI_STATIC_LIBRARY
#define EASYUI_API
#else	//EASY_UI_STATIC_LIBRARY
#ifdef EASY_UI_EXPORT
#define EASYUI_API __declspec(dllexport)
#else
#define EASYUI_API __declspec(dllimport)
#endif
#endif	//EASY_UI_STATIC_LIBRARY


//pre declear 
class EASYUI_API CUIWindowBase;

//depends header
#include "../src/pugixml/pugixml.hpp"

//easy ui header
#include <GdiplusHelper.h>
#include <GdiPlusInit.h>
#include <ParserHelper.h>
#include <MessageHandler.h>
#include <SmartDC.h>
#include <UIWindowBase.h>
#include <UIContainerWindowBase.h>
#include <EasyUIApp.h>

#include <BrushFactory.h>
#include <PenFactory.h>
#include <FontFactory.h>
#include <ImageFactory.h>

#include <WindowFactory.h>
#include <UITopWindow.h>
#include <UIHoriLayout.h>
#include <UIVertLayout.h>
#include <UILabel.h>
#include <UIButton.h>
#include <UIEdit.h>
#include <UIWebBrowser.h>

