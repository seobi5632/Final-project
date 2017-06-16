
#include <d3d9.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 

#include "ShootingData.h"			// class선언, 구조체정의등의 정보
#include "GameBase.h"				// class의 기본이 되는 class
#include "Character.h"				// 게임에서 움직이는 기본물체


LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device

GameBase* g_pGameBase = NULL;
WNDCLASSEX g_wc;
HWND g_hWnd;


// 시간
DWORD		dwOldTime = 0;		// 예전시간,





Character g_Bullet[100];
Character g_Enemy;
Character g_Player;




LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT InitD3D(HWND hWnd);



void InitWin(void)
{
	// Register the window class
	WNDCLASSEX g_wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL };
	RegisterClassEx(&g_wc);

	// Create the application's window
	g_hWnd = CreateWindow(L"D3D Tutorial", L"D3D Tutorial 02: Vertices",
		WS_OVERLAPPEDWINDOW, 100, 100, 1250, 704,
		NULL, NULL, g_wc.hInstance, NULL);
}

void InitDX(void)
{
	InitD3D(g_hWnd);
	D3DXCreateSprite(g_pd3dDevice, &g_pGameBase->_pSprite);
}


VOID InitCharacter(VOID)
{
	// 총알 초기화
	Image BulletImage;
	ZeroMemory(&BulletImage, sizeof(BulletImage));
	BulletImage.Source.left = 0;
	BulletImage.Source.top = 0;
	BulletImage.Source.right = 40;
	BulletImage.Source.bottom = 20;

	Property BulletProperty;
	ZeroMemory(&BulletProperty, sizeof(BulletProperty));
	BulletProperty.Speed = 250.0f;
	BulletProperty.AttackDamage = 1.0f;

	// 이미지 부르기
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"1.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &BulletImage.Texture);

	// 데이터 적용
	for (INT i = 0; i<100; ++i)
	{
		g_Bullet[i].setImage(&BulletImage);
		g_Bullet[i].setProperty(&BulletProperty);
	}




	// 적 초기화
	Image EnemyImage;
	ZeroMemory(&EnemyImage, sizeof(EnemyImage));
	EnemyImage.Source.left = 0;
	EnemyImage.Source.top = 0;
	EnemyImage.Source.right = 179;
	EnemyImage.Source.bottom = 238;
	EnemyImage.Visible = TRUE;

	EnemyImage.Position.x = 1000.0f;
	EnemyImage.Position.y = 150.0f;


	Property EnemyProperty;
	ZeroMemory(&EnemyProperty, sizeof(EnemyProperty));
	EnemyProperty.HP = 200.0f;


	// 이미지 부르기
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"cirno.jpg",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &EnemyImage.Texture);

	// 데이터 적용
	g_Enemy.setImage(&EnemyImage);
	g_Enemy.setProperty(&EnemyProperty);





	Image PlayerImage;
	ZeroMemory(&PlayerImage, sizeof(PlayerImage));
	PlayerImage.Source.left = 0;
	PlayerImage.Source.top = 0;
	PlayerImage.Source.right = 174;
	PlayerImage.Source.bottom = 85;
	PlayerImage.Visible = TRUE;

	PlayerImage.Position.x = 150.0f;
	PlayerImage.Position.y = 150.0f;

	Property PlayerProperty;
	ZeroMemory(&PlayerProperty, sizeof(PlayerProperty));
	PlayerProperty.Speed = 500.0f;
	PlayerProperty.HP = 1000.0f;


	// 이미지 부르기
	D3DXCreateTextureFromFileEx(g_pd3dDevice, L"player.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &PlayerImage.Texture);

	// 데이터 적용
	g_Player.setImage(&PlayerImage);
	g_Player.setProperty(&PlayerProperty);



}



void Initilize(void)
{
	InitWin();
	InitDX();
	InitCharacter();

	// Show the window
	ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hWnd);
}





//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);


	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;


	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice);

	return S_OK;
}








//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pGameBase != NULL)
		g_pGameBase->_pSprite->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}



//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	g_pGameBase->t = (timeGetTime() - dwOldTime) *.001f;
	dwOldTime = timeGetTime();



	if (GetKeyState(VK_LEFT) & 0x80000000)
	{
		g_Player.moveLeft();
	}

	if (GetKeyState(VK_RIGHT) & 0x80000000)
	{
		g_Player.moveRight();
	}

	if (GetKeyState(VK_UP) & 0x80000000)
	{
		g_Player.moveUp();
	}

	if (GetKeyState(VK_DOWN) & 0x80000000)
	{
		g_Player.moveDown();
	}




	// 충돌체크
	const Image* imgEnemy = g_Enemy.getImage();
	Property proEnemy = *g_Enemy.getProperty();
	Image imgBullet;
	const Property* proBullet = NULL;

	for (INT i = 0; i<100; ++i)
	{
		imgBullet = *g_Bullet[i].getImage();
		proBullet = g_Bullet[i].getProperty();

		// 보이는 총알 중에
		if (imgBullet.Visible == TRUE)
		{

			// 충돌 되었으면
			if (imgBullet.Position.x < imgEnemy->Position.x + imgEnemy->Source.right
				&&imgEnemy->Position.x < imgBullet.Position.x + imgBullet.Source.right
				&&imgBullet.Position.y < imgEnemy->Position.y + imgEnemy->Source.bottom
				&&imgEnemy->Position.y < imgBullet.Position.y + imgBullet.Source.bottom
				)
			{

				// 충돌한 총알은 안보이고, 게이지 깍기
				if (proEnemy.HP >= .0f)
				{
					imgBullet.Visible = FALSE;
					g_Bullet[i].setImage(&imgBullet);
					proEnemy.HP -= proBullet->AttackDamage;
				}
			}

		}


	}

	// 적의 능력치 업데이트
	g_Enemy.setProperty(&proEnemy);






	// 총알발사
	if (GetKeyState(VK_SPACE) & 0x80000000)
	{
		for (INT i = 0; i<100; ++i)
		{
			imgBullet = *g_Bullet[i].getImage();
			if (imgBullet.Visible == FALSE)
			{
				imgBullet.Visible = TRUE;
				imgBullet.Position.x = g_Player.getImage()->Position.x + 160.0f - 6.0f;
				imgBullet.Position.y = g_Player.getImage()->Position.y;
				g_Bullet[i].setImage(&imgBullet);
				break;
			}
		}
	}





	for (INT i = 0; i<100; ++i)
	{
		imgBullet = *g_Bullet[i].getImage();
		proBullet = g_Bullet[i].getProperty();

		if (imgBullet.Visible == TRUE)
		{
			g_Bullet[i].moveRight();
		}

		if (imgBullet.Position.x > 1300)
		{
			imgBullet.Visible = FALSE;
			g_Bullet[i].setImage(&imgBullet);
		}

	}




	// Clear the backbuffer to a blue color
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pGameBase->_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		g_Enemy.Draw();

		for (INT i = 0; i<100; ++i)
			g_Bullet[i].Draw();


		g_Player.Draw();
		g_pGameBase->_pSprite->End();

		// End the scene
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}





	return DefWindowProc(hWnd, msg, wParam, lParam);
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{

	Initilize();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			Render();
	}


	UnregisterClass(L"D3D Tutorial", g_wc.hInstance);
	return 0;
}




