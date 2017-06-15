#pragma once

//////////////////////////////////////////////////////////////////////////
// Ŭ���������
class GameBase;





//////////////////////////////////////////////////////////////////////////
// ����ü��


// �̹�������
struct Image
{
	LPDIRECT3DTEXTURE9	Texture;	// �ؽ���
	RECT				Source;		// �ؽ��ĳ� �̹����� ��ǥ
	D3DXVECTOR3			Position;	// �̹����� ȭ�鿡 �׷��� ��ǥ
	D3DXVECTOR3			Center;		// �̹����� ����
	FLOAT				Sec;		// ����ð�
};


// �ɷ�ġ ����
struct Property
{
	FLOAT Speed;
	FLOAT HP;
	FLOAT AttackDamage;
};




//////////////////////////////////////////////////////////////////////////
// typedef
typedef std::vector <Image*> ImageVec;
typedef std::vector <ImageVec> ImageVec2;






// define
enum PLAYER_move
{
	PLAYER_Left = 0,
	PLAYER_Center,
	PLAYER_Right,
};

