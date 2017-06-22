#pragma once

//////////////////////////////////////////////////////////////////////////
// Ŭ���������
class GameBase;
class Component;
class Application;
//{
class SceneManager;
//	{
class GameScene;
//		{
class Character;
//			{
class Barrage;
//			} // Character
//		} //  Game
class ObjectPool;
//	} // Scene
//}	// App







//////////////////////////////////////////////////////////////////////////
// ����ü��


struct BoundingBox
{
	D3DXVECTOR3 LT;
	D3DXVECTOR3 RB;
};
typedef std::vector <BoundingBox*> BoundBoxVec;


// �̹�������
struct Image_data
{
	LPDIRECT3DTEXTURE9	Texture;	// �ؽ���
	RECT				Source;		// �ؽ��ĳ� �̹����� ��ǥ
	D3DXVECTOR3			Position;	// �̹����� ȭ�鿡 �׷��� ��ǥ
	D3DXVECTOR3			Center;		// �̹����� ����
	FLOAT				Time;		// ����ð�, ���ð�
};

// �浹�ڽ��� �߰��� ����
// ���͸� ZeroMemory�� �ʱ�ȭ �Ҽ���� �Ҽ���� ����
struct Image : public Image_data
{
	BoundBoxVec			BoundBox;	// �浹�ڽ�
};




// �ɷ�ġ ����
struct Property
{
	FLOAT Speed;			// �̵��ӵ�
	FLOAT HealthPoint;		// �����
	FLOAT AttackDamage;		// ���ݷ�

	BOOL ALive;				// ����ִ� ����
};


// �̵� ����
struct Motion
{
	FLOAT		Time;		// ����ð�, 0, 3, 5, 10, .. �̷������� Ű�ð��� ��
	D3DXVECTOR3	Position;
};



// ź������
// 3�ð� 0��, �ð�������� ���� ����
struct Barrage_data
{
	FLOAT BulletSpeed;			// �Ѿ��� �ʴ��̵��ϴ� �ȼ���
	FLOAT FireSpeed;			// �ʴ� �߻�ӵ�
	FLOAT FireAngle;			// �߻簢, ����
	FLOAT FireAngle_rotate;		// �߻簢 ȸ���ӵ�, ����
};







//////////////////////////////////////////////////////////////////////////
// typedef
typedef std::vector <Image*> ImageVec;
typedef std::vector <ImageVec> ImageVec2;
typedef std::vector <Motion*> MotionVec;


typedef std::vector <GameBase*> BaseVec;
typedef std::list <GameBase*> BaseList;

typedef std::vector <Character*> CharacterVec;
typedef std::list <Character*> CharacterList;
typedef std::vector <CharacterList> PoolVec;

typedef std::list <Component*> ComponentList;


typedef std::list <UINT> UINTList;

typedef std::vector <INT> INTvec;
typedef std::vector <UINT> UINTvec;
typedef std::vector <BOOL> BOOLVec;






//////////////////////////////////////////////////////////////////////////
// �Լ���


// Low-Fragmentation Heap
BOOL CheckLFH(VOID);







//////////////////////////////////////////////////////////////////////////
// define
enum PLAYER_move
{
	PLAYER_Left = 0,
	PLAYER_Center,
	PLAYER_Right,
};



// �޽��� ���
enum GameMessageID
{
	GameMessage = 0,

	ANI_End,
	MOT_End,


	COL_BulletToEnemy,
	COL_BulletToPlayer,

};


// ������Ʈ Ǯ�� ����� ���
enum POOL_Number
{
	//	POOL_EnemyBullet = 0,
	POOL_EnemyBullet = 0,
	POOL_Enemy,
	POOL_EnemyExplosion,

	POOL_PlayerBullet,
	POOL_Player,


	POOL_Max,
};





//////////////////////////////////////////////////////////////////////////
// BaseClass
#include "GameBase.h"