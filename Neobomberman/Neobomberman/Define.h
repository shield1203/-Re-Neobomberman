#pragma once
extern HWND g_hWnd;

/////////////
// LINKING //
/////////////
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "msimg32.lib") // TransparentBlt »ç¿ë
#pragma comment(lib, "fmod_vc.lib")

//////////////
// INCLUDES //
//////////////
#include<Vfw.h>
#include<string>
#include<vector>
#include<list>
#include<ctime>
#include<cstdlib>
using namespace std;

////////////
// Define //
////////////
#include"DefineEnum.h"
#include"DefineAPI.h"

///////////////
//   SOUND   //
///////////////
#include"inc/fmod.hpp"
using namespace FMOD;