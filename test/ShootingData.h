#pragma once

//////////////////////////////////////////////////////////////////////////
// 클래스선언들
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
// 구조체들


struct BoundingBox
{
	D3DXVECTOR3 LT;
	D3DXVECTOR3 RB;
};
typedef std::vector <BoundingBox*> BoundBoxVec;


// 이미지정보
struct Image_data
{
	LPDIRECT3DTEXTURE9	Texture;	// 텍스쳐
	RECT				Source;		// 텍스쳐내 이미지의 좌표
	D3DXVECTOR3			Position;	// 이미지가 화면에 그려질 좌표
	D3DXVECTOR3			Center;		// 이미지의 센터
	FLOAT				Time;		// 재생시간, 상대시간
};

// 충돌박스를 추가한 정보
// 벡터를 ZeroMemory로 초기화 할수없어서 할수없어서 나눔
struct Image : public Image_data
{
	BoundBoxVec			BoundBox;	// 충돌박스
};




// 능력치 정보
struct Property
{
	FLOAT Speed;			// 이동속도
	FLOAT HealthPoint;		// 생명력
	FLOAT AttackDamage;		// 공격력

	BOOL ALive;				// 살아있는 상태
};


// 이동 정보
struct Motion
{
	FLOAT		Time;		// 절대시간, 0, 3, 5, 10, .. 이런식으로 키시간이 들어감
	D3DXVECTOR3	Position;
};



// 탄막정보
// 3시가 0도, 시계방향으로 각이 증가
struct Barrage_data
{
	FLOAT BulletSpeed;			// 총알이 초당이동하는 픽셀값
	FLOAT FireSpeed;			// 초당 발사속도
	FLOAT FireAngle;			// 발사각, 라디안
	FLOAT FireAngle_rotate;		// 발사각 회전속도, 라디안
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
// 함수들


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



// 메시지 목록
enum GameMessageID
{
	GameMessage = 0,

	ANI_End,
	MOT_End,


	COL_BulletToEnemy,
	COL_BulletToPlayer,

};


// 오브젝트 풀을 사용할 목록
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