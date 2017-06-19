#pragma once

class GameBase
{
public:
	GameBase();
	VOID	EventReceiver(GameBase* pReceiver);		// �̺�Ʈ�� ���� Ŭ������ ����

protected:
	VOID	Event(UINT uMsg, WPARAM wParam = NULL, LPARAM lParam = NULL);				// �̺�Ʈ�� ������
	virtual VOID OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �̺�Ʈ�� ������

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
// Ŭ����  �̸� : GameBase
// ù����  ��¥ : 2009. 7. 5
// ������������ : 2009. 9. 24(��)
//
// Nick : ���ڰ�
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// �ϴ��� : Ŭ������ ������ �־���� �⺻�Լ��� ������ ������ �ִ�.