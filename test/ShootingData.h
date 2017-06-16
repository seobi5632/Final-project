#pragma once


// 클래스선언들
class GameBase;






// 구조체들


// 이미지정보
struct Image
{
	BOOL Visible;
	LPDIRECT3DTEXTURE9 Texture;
	RECT Source;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Center;
};


// 능력치 정보
struct Property
{
	FLOAT Speed;
	FLOAT HP;
	FLOAT AttackDamage;
};