#include "stdafx.h"				// 미리컴파일된헤더
#include "ShootingData.h"

#include "Character.h"
#include "Application.h"




int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{

	// 평상시에는 이것으로 있는지 여부만 검사
	// 있으면 Visual Leak Detector를 사용
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



	// Low-Fragmentation Heap의 사용
	BOOL bLFH = CheckLFH();




	Application Shooting(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	Shooting.Initialize();
	Shooting.Loop();
	Shooting.Release();


	return NULL;
}