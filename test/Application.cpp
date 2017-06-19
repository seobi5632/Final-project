#include "stdafx.h"				// 미리컴파일된헤더
#include "ShootingData.h"

#include "Application.h"
#include "SceneManager.h"
#include "Character.h"			// 게임에서 움직이는 기본물체


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 변수를 초기화 한다.
Application* g_pApplication = NULL;
Application::Application(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR	  lpCmdLine,
	int		  nCmdShow)
{
	_hInstance = hInstance;
	_hPrevInstance = hPrevInstance;
	_lpCmdLine = lpCmdLine;
	_nCmdShow = nCmdShow;

	_hWnd = NULL;
	ZeroMemory(&_wc, sizeof(WNDCLASSEXW));

	_pD3D = NULL;
	_pd3dDevice = NULL;
	ZeroMemory(&_d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	_dwOldTime = 0;



	g_pApplication = this;
	_pSceneManager = NULL;
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : Application을 초기화 한다.
VOID Application::Initialize(VOID)
{
	EventReceiver(this);

	// 시간 리셋
	_dwOldTime = timeGetTime();


	InitWin();
	InitD3D();
	_pSceneManager = new SceneManager;
	_pSceneManager->Initialize();


	// Show the window
	ShowWindow(_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(_hWnd);
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// Window를 초기화 한다.
// 타이머 정밀도를 높인다.
VOID Application::InitWin(VOID)
{
	_wc.cbSize = sizeof(WNDCLASSEXW);
	_wc.style = CS_CLASSDC;
	_wc.lpfnWndProc = ::MsgProc;
	_wc.cbClsExtra = 0L;
	_wc.cbWndExtra = 0L;
	_wc.hInstance = GetModuleHandle(NULL);
	//	m_wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1));
	_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wc.hbrBackground = NULL;
	_wc.lpszMenuName = NULL;
	_wc.lpszClassName = L"D3D Tutorial";
	// _wc.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1));


	RegisterClassExW(&_wc);

	// Create the application's window
	_hWnd = CreateWindowW(L"D3D Tutorial", L"날자고도의 탄막슈팅",
		WS_OVERLAPPEDWINDOW, 50, 50, 600 + 50, 800 + 50,
		NULL, NULL, _wc.hInstance, NULL);


	// 멀티미디어 타이머 정밀도를 높임
	MMRESULT MMR = timeBeginPeriod(1);
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : DirectX를 초기화 한다.
VOID Application::InitD3D(VOID)
{
	_pD3D = Direct3DCreate9(D3D_SDK_VERSION);


	ZeroMemory(&_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	_d3dpp.Windowed = TRUE;
	_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;



	_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&_d3dpp, &_pd3dDevice);


	D3DXCreateSprite(_pd3dDevice, &_pSprite);


	// 흰색빈 텍스쳐 생성
	D3DXCreateTexture(_pd3dDevice, 2, 2, 1, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &_pWhite_texture);

	D3DLOCKED_RECT rcLock;
	_pWhite_texture->LockRect(0, &rcLock, NULL, D3DLOCK_NO_DIRTY_UPDATE);
	DWORD* pColor = (DWORD*)rcLock.pBits;
	*(pColor + 0) = 0xffffffff;
	*(pColor + 1) = 0xffffffff;
	*(pColor + 2) = 0xffffffff;
	*(pColor + 3) = 0xffffffff;
	_pWhite_texture->UnlockRect(0);
}







//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 모든 리소스를 삭제하고, 장치를 해제한다.
VOID Application::Release(VOID)
{
	_pSceneManager->Release();
	delete _pSceneManager;



	if (_pSprite != NULL)
		_pSprite->Release();

	if (_pd3dDevice != NULL)
		_pd3dDevice->Release();

	if (_pD3D != NULL)
		_pD3D->Release();




	// 멀티미디어 정밀도를 원래대로
	MMRESULT MMR = timeEndPeriod(1);

	UnregisterClassW(L"D3D Tutorial", _wc.hInstance);
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 프로그램의 메인루프를 돈다.
VOID Application::Loop(VOID)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Draw();
		}
	}


}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : CPU에서 주로 할일들을 정의한다.
VOID Application::Update(VOID)
{
	t = (timeGetTime() - _dwOldTime) *.001f;
	_dwOldTime = timeGetTime();

#ifdef _DEBUG
	//if ( t >= .5f)
	//	t = .5f;
#endif // _DEBUG



	_pSceneManager->Update();

}






//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : GPU에서 주로 할일들을 정의한다.
VOID Application::Draw(VOID)
{
	// Clear the backbuffer to a blue color
	_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(_pd3dDevice->BeginScene()))
	{
		_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		_pSceneManager->Draw();
		_pSprite->End();


		// End the scene
		_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}



LRESULT Application::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch ((INT)wParam)
		{
		case VK_TAB:
			_bBound_visible = !_bBound_visible;
			break;
		case VK_PRIOR:
			_bPgUp = TRUE;
			break;
		case VK_NEXT:
			_bPgDn = TRUE;
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_pApplication->MsgProc(hWnd, msg, wParam, lParam);
}



