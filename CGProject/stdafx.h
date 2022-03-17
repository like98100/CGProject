#pragma once
#pragma once

#define _WIN32_WINNT 0x0600                // <== CreateFile2  KERNEL32.dll error �ذ�

//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
//#include "DxDefine.h"


/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
//#include "DDSTextureLoader.h"    // DDS ���� ó��
using namespace DirectX;

///////////////////////////
//  warning C4316 ó����  //
///////////////////////////
#include "AlignedAllocationPolicy.h"