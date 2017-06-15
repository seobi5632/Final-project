#include "stdafx.h"					// �̸������ϵ����
#include "ShootingData.h"			// class����, ����ü���ǵ��� ����
#include "GameBase.h"				// class�� �⺻�� �Ǵ� class

#include "Character.h"				// ���ӿ��� �����̴� �⺻��ü


LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device

GameBase* g_pGameBase = NULL;
WNDCLASSEX g_wc;
HWND g_hWnd;


// �ð�
DWORD		dwOldTime = 0;		// �����ð�,





Character g_Bullet[200];
Character g_Enemy;
Character g_Player;




LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT InitD3D(HWND hWnd);



void InitWin(void)
{
	// Register the window class
	WNDCLASSEXW g_wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL };
	RegisterClassEx(&g_wc);

	// Create the application's window
	g_hWnd = CreateWindowW(L"D3D Tutorial", L"D3D Tutorial 02: Vertices",
		WS_OVERLAPPEDWINDOW, 50, 50, 600 + 50, 800 + 50,
		NULL, NULL, g_wc.hInstance, NULL);


	// ��Ƽ�̵�� Ÿ�̸� ���е��� ����
	MMRESULT MMR = timeBeginPeriod(1);
}

void InitDX(void)
{
	InitD3D(g_hWnd);
	D3DXCreateSprite(g_pd3dDevice, &g_pGameBase->_pSprite);
}


VOID InitCharacter(VOID)
{
	// �Ѿ� �ʱ�ȭ
	ImageVec2 vBulletImage;
	vBulletImage.resize(1);

	Image BulletImage;
	ZeroMemory(&BulletImage, sizeof(Image));
	BulletImage.Source.left = 0;
	BulletImage.Source.top = 0;
	BulletImage.Source.right = 400;
	BulletImage.Source.bottom = 400;
	BulletImage.Sec = 1.0f;


	Property BulletProperty;
	ZeroMemory(&BulletProperty, sizeof(Property));
	BulletProperty.Speed = 250.0f;
	BulletProperty.AttackDamage = 1.0f;

	// �̹��� �θ���
	D3DXCreateTextureFromFileExW(g_pd3dDevice, L"1.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &BulletImage.Texture);


	// ������ ����
	Image* pBulletImage = NULL;
	vBulletImage[0].push_back(NULL);

	for (INT i = 0; i<100; ++i)
	{
		pBulletImage = new Image;
		*pBulletImage = BulletImage;
		vBulletImage[0][0] = pBulletImage;
		g_Bullet[i].setAnimation(&vBulletImage);
		g_Bullet[i].setProperty(&BulletProperty);
	}




	// �� �ʱ�ȭ
	ImageVec2 vEnemyImage;
	vEnemyImage.resize(1);

	Image* EnemyImage = new Image;
	ZeroMemory(EnemyImage, sizeof(Image));
	EnemyImage->Source.left = 0;
	EnemyImage->Source.top = 0;
	EnemyImage->Source.right = 179;
	EnemyImage->Source.bottom = 238;
	EnemyImage->Sec = 1.0f;


	EnemyImage->Position.x = 150.0f;
	EnemyImage->Position.y = 10.0f;


	Property EnemyProperty;
	ZeroMemory(&EnemyProperty, sizeof(Property));
	EnemyProperty.HP = 200.0f;


	// �̹��� �θ���
	D3DXCreateTextureFromFileExW(g_pd3dDevice, L"cirno.jpg",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &EnemyImage->Texture);

	// ������ ����
	vEnemyImage[0].push_back(EnemyImage);
	g_Enemy.setAnimation(&vEnemyImage);
	g_Enemy.setProperty(&EnemyProperty);









	ImageVec2 vPlayerImage;
	vPlayerImage.resize(3);

	Image PlayerImage;
	ZeroMemory(&PlayerImage, sizeof(Image));

	// �̹��� �θ���
	D3DXCreateTextureFromFileExW(g_pd3dDevice, L"player.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &PlayerImage.Texture);



	PlayerImage.Source.left = 0;
	PlayerImage.Source.top = 0;
	PlayerImage.Source.right = 80;
	PlayerImage.Source.bottom = 160;
	PlayerImage.Sec = .40f;

	PlayerImage.Position.x = 300.0f;
	PlayerImage.Position.y = 450.0f;

	Image* pPlayerImage = NULL;

	// ����
	pPlayerImage = new Image;
	*pPlayerImage = PlayerImage;
	vPlayerImage[0].push_back(pPlayerImage);

	pPlayerImage = new Image;
	*pPlayerImage = PlayerImage;
	pPlayerImage->Source.left = 80;
	pPlayerImage->Source.right = 160;
	vPlayerImage[0].push_back(pPlayerImage);


	// �߰�
	pPlayerImage = new Image;
	*pPlayerImage = PlayerImage;
	pPlayerImage->Source.left = 160;
	pPlayerImage->Source.right = 240;
	vPlayerImage[1].push_back(pPlayerImage);

	pPlayerImage = new Image;
	*pPlayerImage = PlayerImage;
	pPlayerImage->Source.left = 240;
	pPlayerImage->Source.right = 320;
	vPlayerImage[1].push_back(pPlayerImage);


	// ������
	pPlayerImage = new Image;
	*pPlayerImage = PlayerImage;
	pPlayerImage->Source.left = 320;
	pPlayerImage->Source.right = 400;
	vPlayerImage[2].push_back(pPlayerImage);

	pPlayerImage = new Image;
	*pPlayerImage = PlayerImage;
	pPlayerImage->Source.left = 400;
	pPlayerImage->Source.right = 480;
	vPlayerImage[2].push_back(pPlayerImage);



	Property PlayerProperty;
	ZeroMemory(&PlayerProperty, sizeof(Property));
	PlayerProperty.Speed = 500.0f;
	PlayerProperty.HP = 1000.0f;


	// ������ ����
	g_Player.setAnimation(&vPlayerImage);
	g_Player.selAnimation(1);
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
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
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


VOID Update()
{
	g_pGameBase->t = (timeGetTime() - dwOldTime) *.001f;
	dwOldTime = timeGetTime();



	if (GetKeyState(VK_LEFT) & 0x80000000)
	{
		g_Player.moveLeft();
		g_Player.selAnimation(PLAYER_Left);
	}

	if (GetKeyState(VK_RIGHT) & 0x80000000)
	{
		g_Player.moveRight();
		g_Player.selAnimation(PLAYER_Right);
	}

	if (GetKeyState(VK_UP) & 0x80000000)
	{
		g_Player.moveUp();
		g_Player.selAnimation(PLAYER_Center);
	}

	if (GetKeyState(VK_DOWN) & 0x80000000)
	{
		g_Player.moveDown();
		g_Player.selAnimation(PLAYER_Center);
	}




	// �浹üũ
	const Image* imgEnemy = g_Enemy.getImage();
	Property proEnemy = *g_Enemy.getProperty();

	BOOL bVisible = FALSE;
	Image imgBullet;
	const Property* proBullet = NULL;

	for (INT i = 0; i<100; ++i)
	{
		bVisible = g_Bullet[i].getVisible();
		imgBullet = *g_Bullet[i].getImage();
		proBullet = g_Bullet[i].getProperty();

		// ���̴� �Ѿ� �߿�
		if (bVisible == TRUE)
		{

			// �浹 �Ǿ�����
			if (imgBullet.Position.x < imgEnemy->Position.x + imgEnemy->Source.right
				&&imgEnemy->Position.x < imgBullet.Position.x + imgBullet.Source.right
				&&imgBullet.Position.y < imgEnemy->Position.y + imgEnemy->Source.bottom
				&&imgEnemy->Position.y < imgBullet.Position.y + imgBullet.Source.bottom
				)
			{

				// �浹�� �Ѿ��� �Ⱥ��̰�, ������ ���
				if (proEnemy.HP >= .0f)
				{
					//imgBullet.Visible = FALSE;
					g_Bullet[i].setVisible(FALSE);
					//g_Bullet[i].setImage(&imgBullet);
					proEnemy.HP -= proBullet->AttackDamage;
				}
			}

		}


	}

	// ���� �ɷ�ġ ������Ʈ
	g_Enemy.setProperty(&proEnemy);






	// �Ѿ˹߻�
	BOOL bVisibleFire = FALSE;
	if (GetKeyState(0x5a) & 0x80000000)
	{
		for (INT i = 0; i<100; ++i)
		{
			bVisibleFire = g_Bullet[i].getVisible();
			//imgBullet = *g_Bullet[i].getImage();
			if (bVisibleFire == FALSE)
			{
				//imgBullet.Visible = TRUE;
				g_Bullet[i].setVisible(TRUE);
				imgBullet.Position.x = g_Player.getImage()->Position.x + 60.0f - 6.0f;
				imgBullet.Position.y = g_Player.getImage()->Position.y;
				//				g_Bullet[i].setImage(&imgBullet);
				g_Bullet[i].setPosition(&imgBullet.Position);
				break;
			}
		}
	}





	for (INT i = 0; i<100; ++i)
	{
		bVisible = g_Bullet[i].getVisible();
		imgBullet = *g_Bullet[i].getImage();
		//proBullet = g_Bullet[i].getProperty();

		if (bVisible == TRUE)
		{
			g_Bullet[i].moveUp();
		}

		if (imgBullet.Position.y < -40.0f)
		{
			//imgBullet.Visible = FALSE;
			//g_Bullet[i].setImage( &imgBullet );
			g_Bullet[i].setVisible(FALSE);
		}

	}


}



//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{

	// Clear the backbuffer to a blue color
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pGameBase->_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		g_Enemy.Draw();

		for (INT i = 0; i<100; ++i)
			g_Bullet[i].Draw();


		g_Player.Update();
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
			Render();
		}
	}



	// ��Ƽ�̵�� ���е��� �������
	MMRESULT MMR = timeEndPeriod(1);

	UnregisterClassW(L"D3D Tutorial", g_wc.hInstance);
	return 0;
}




