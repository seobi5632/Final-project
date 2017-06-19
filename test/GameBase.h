#pragma once

class GameBase
{
public:
	GameBase();
	VOID	EventReceiver(GameBase* pReceiver);		// 이벤트를 받을 클래스를 지정

protected:
	VOID	Event(UINT uMsg, WPARAM wParam = NULL, LPARAM lParam = NULL);				// 이벤트를 보낼때
	virtual VOID OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam);	// 이벤트를 받을때

	GameBase*				  _pReceiver;

	static FLOAT			  t;
	static LPDIRECT3DDEVICE9  _pd3dDevice;
	static LPD3DXSPRITE		  _pSprite;

	static BOOL				  _bBound_visible;
	static LPDIRECT3DTEXTURE9 _pWhite_texture;
	static ObjectPool*		  _pPool;

	static BOOL				  _bPgUp;
	static BOOL				  _bPgDn;
};


///////////////////////////////////////////////////////////////
// 클래스  이름 : GameBase
// 첫만든  날짜 : 2009. 7. 5
// 마지막갱신일 : 2009. 9. 24(목)
//
// Nick : 날자고도
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// 하는일 : 클래스가 가지고 있어야할 기본함수와 정보를 가지고 있다.