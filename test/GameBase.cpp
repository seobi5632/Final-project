#include "stdafx.h"			// �̸������ϵ����
#include "ShootingData.h"



FLOAT GameBase::t = .0f;
LPDIRECT3DDEVICE9  GameBase::_pd3dDevice = NULL;
LPD3DXSPRITE GameBase::_pSprite = NULL;

BOOL GameBase::_bBound_visible = FALSE;
LPDIRECT3DTEXTURE9 GameBase::_pWhite_texture = NULL;
ObjectPool* GameBase::_pPool = NULL;

BOOL GameBase::_bPgUp = FALSE;
BOOL GameBase::_bPgDn = FALSE;


GameBase::GameBase()
{
	_pReceiver = NULL;
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : GameBase�� ������
// �޴°� : VOID
// �ϴ��� : �޽����� ���� Ŭ������ ����Ѵ�. �ϳ��� �����ϴ�.
VOID GameBase::EventReceiver(GameBase* pReceiver)
{
	_pReceiver = pReceiver;
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : �޽���, �����ǰ�1, �����ǰ�2
// �޴°� : VOID
// �ϴ��� : �̺�Ʈ�� ��������, �޽����� ��ϵ�Ŭ������ ������.
VOID GameBase::Event(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (_pReceiver) _pReceiver->OnEvent(this, uMsg, wParam, lParam);
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : ���α׷��Ӱ� �������� �ʴ´�.
// �޴°� : VOID
// �ϴ��� : 
// �Լ��� ������ �ؼ�, �޽����� ������ ó���� �Լ��� ���α׷��Ӱ� �����ؾ��Ѵ�.
VOID GameBase::OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

}