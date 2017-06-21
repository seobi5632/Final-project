#pragma once
class GameScene : public GameBase
{
public:
	GameScene();
	VOID Initialize(VOID);
	VOID Update(VOID);
	VOID Draw(VOID);
	VOID Release(VOID);


	VOID initBullet(VOID);
	VOID initEnemyBullet(VOID);
	VOID initEnemy(VOID);
	VOID initEnemy_Explosion(VOID);
	VOID initPlayer(VOID);

	VOID updateKey(VOID);
	VOID updateBullet(VOID);
	VOID UpdateBarrage(VOID);
	VOID updateCharacter(VOID);
	VOID updateCollision(VOID);
	VOID Collision(UINT uMsg, Character* Bullet, Character* Target);

protected:
	// 이벤트
	VOID OnCOL_BulletToEnemy(Character* pBullet, Character* pEnemy);
	VOID OnEnemyExplosion_ani_end(Character* pExplosion);
	VOID OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam);


	VOID OnBarrage(UINT uNum);

	// 텍스쳐
	LPDIRECT3DTEXTURE9	_EnemyBullet_texture;	// 적 총알
	LPDIRECT3DTEXTURE9	_Enemy_texture;		// 적
	LPDIRECT3DTEXTURE9	_EnemyExplosion_texture; // 적의폭팔

	Character*			_Bullet;
	LPDIRECT3DTEXTURE9	_Bullet_texture;	// 플레이어의 총알

	Character*			_Player;			// 플레이어
	LPDIRECT3DTEXTURE9	_Player_texture[3];	// 플레이어 텍스쳐

	Character*			_Enemy1;
	Character*			_Enemy2;
	UINT	_uBarrage_Number;
};



///////////////////////////////////////////////////////////////
// 클래스  이름 : GameScene
// 첫만든  날짜 : 2009. 9. 3
// 마지막갱신일 : 2009. 9. 24(목)
//
// Nick : 날자고도
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// 하는일 : GameScene안에서 일어나는 일들을 관리한다.