#pragma once

//////////////////////////////////////////////////////////////////////////
// 클래스선언들
class GameBase;





//////////////////////////////////////////////////////////////////////////
// 구조체들


// 이미지정보
struct Image
{
	LPDIRECT3DTEXTURE9	Texture;	// 텍스쳐
	RECT				Source;		// 텍스쳐내 이미지의 좌표
	D3DXVECTOR3			Position;	// 이미지가 화면에 그려질 좌표
	D3DXVECTOR3			Center;		// 이미지의 센터
	FLOAT				Sec;		// 재생시간
};


// 능력치 정보
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

