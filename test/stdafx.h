
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#define WIN32_LEAN_AND_MEAN			  // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define _CRT_SECURE_NO_WARNINGS		  // 보안함수 미사용경고 제거
#define _CRT_NON_CONFORMING_SWPRINTFS // swprintf 보안함수 미사용경고 제거 


// Windows 헤더 파일:
#include <windows.h>

// C의 런타임 헤더 파일입니다.
#include <Mmsystem.h>			// timeGetTime

// C++ 헤더
#include <vector>


// DX9
#include <d3dx9.h>



