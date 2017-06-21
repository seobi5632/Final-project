#include "stdafx.h"			// 미리컴파일된헤더
#include "ShootingData.h"



FLOAT GameBase::t = .0f;
LPDIRECT3DDEVICE9  GameBase::_pd3dDevice = NULL;
LPD3DXSPRITE GameBase::_pSprite = NULL;

BOOL GameBase::_bBound_visible = TRUE;
LPDIRECT3DTEXTURE9 GameBase::_pWhite_texture = NULL;
ObjectPool* GameBase::_pPool = NULL;

BOOL GameBase::_bPgUp = FALSE;
BOOL GameBase::_bPgDn = FALSE;


GameBase::GameBase()
{
	_pReceiver = NULL;
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : GameBase의 포인터
// 받는값 : VOID
// 하는일 : 메시지를 받을 클래스를 등록한다. 하나만 가능하다.
VOID GameBase::EventReceiver(GameBase* pReceiver)
{
	_pReceiver = pReceiver;
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : 메시지, 임의의값1, 임의의값2
// 받는값 : VOID
// 하는일 : 이벤트가 생겼을때, 메시지를 등록된클래스에 보낸다.
VOID GameBase::Event(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (_pReceiver) _pReceiver->OnEvent(this, uMsg, wParam, lParam);
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : 프로그래머가 직접넣지 않는다.
// 받는값 : VOID
// 하는일 : 
// 함수를 재정의 해서, 메시지를 받은후 처리할 함수를 프로그래머가 연결해야한다.
VOID GameBase::OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

}