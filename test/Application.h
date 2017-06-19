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

	DWORD				_dwOldTime;			// 예전시간,
	SceneManager*		_pSceneManager;
};


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


///////////////////////////////////////////////////////////////
// 클래스  이름 : Application
// 첫만든  날짜 : 2009. 7. 5
// 마지막갱신일 : 2009. 8. 22 토
//
// Nick : 날자고도
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// 하는일 : Win환경하에서 게임이 돌아갈수있도록한다.
//

