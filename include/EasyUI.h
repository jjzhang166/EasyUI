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
#define EASY_UI_API
#else	//EASY_UI_STATIC_LIBRARY
#ifdef EASY_UI_EXPORT
#define EASY_UI_API __declspec(dllexport)
#else
#define EASY_UI_API __declspec(dllimport)
#endif
#endif	//EASY_UI_STATIC_LIBRARY


//pre declear 
class EASY_UI_API CWindowBase;

//depends header
#include "../src/pugixml/pugixml.hpp"

//easy ui header
#include <GdiplusHelper.h>
#include <GdiPlusInit.h>
#include <ParserHelper.h>
#include <MessageHandler.h>
#include <SmartDC.h>
#include <WindowBase.h>
#include <ContainerWindowBase.h>

#include <BrushFactory.h>
#include <PenFactory.h>
#include <FontFactory.h>
#include <ImageFactory.h>

#include <WindowFactory.h>
#include <TopHWNDWindow.h>
#include <HoriLayout.h>
#include <VertLayout.h>
#include <DuiLabel.h>
#include <DuiButton.h>

