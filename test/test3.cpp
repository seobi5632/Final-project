#include "stdafx.h"				// �̸������ϵ����
#include "ShootingData.h"

#include "Character.h"
#include "Application.h"




int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{

	// ���ÿ��� �̰����� �ִ��� ���θ� �˻�
	// ������ Visual Leak Detector�� ���
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



	// Low-Fragmentation Heap�� ���
	BOOL bLFH = CheckLFH();




	Application Shooting(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	Shooting.Initialize();
	Shooting.Loop();
	Shooting.Release();


	return NULL;
}