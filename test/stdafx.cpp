// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// ferfefer.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"
// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.


// Windows
#pragma comment( lib, "winmm" )		// timeGetTime


// DX9
#pragma comment( lib, "d3d9" )
#ifdef _DEBUG
#pragma comment(lib, "d3dx9d")
#else
#pragma comment(lib, "d3dx9")
#endif


