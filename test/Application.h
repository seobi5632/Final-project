#pragma once

class Application : public GameBase
{
public:
	Application(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPWSTR	  lpCmdLine,
		int		  nCmdShow);
	VOID	Initialize(VOID);
	VOID	Loop(VOID);
	VOID	Release(VOID);
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	VOID	InitWin(VOID);
	VOID	InitD3D(VOID);
	VOID	Update(VOID);
	VOID	Draw(VOID);


	HINSTANCE			_hInstance;
	HINSTANCE			_hPrevInstance;
	LPWSTR				_lpCmdLine;
	int					_nCmdShow;

	HWND				_hWnd;
	WNDCLASSEXW			_wc;

	LPDIRECT3D9         _pD3D;
	D3DPRESENT_PARAMETERS _d3dpp;

	DWORD				_dwOldTime;			// �����ð�,
	SceneManager*		_pSceneManager;
};


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


///////////////////////////////////////////////////////////////
// Ŭ����  �̸� : Application
// ù����  ��¥ : 2009. 7. 5
// ������������ : 2009. 8. 22 ��
//
// Nick : ���ڰ�
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// �ϴ��� : Winȯ���Ͽ��� ������ ���ư����ֵ����Ѵ�.
//

