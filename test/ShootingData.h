#pragma once


// Ŭ���������
class GameBase;






// ����ü��


// �̹�������
struct Image
{
	BOOL Visible;
	LPDIRECT3DTEXTURE9 Texture;
	RECT Source;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Center;
};


// �ɷ�ġ ����
struct Property
{
	FLOAT Speed;
	FLOAT HP;
	FLOAT AttackDamage;
};