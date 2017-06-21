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
	// �̺�Ʈ
	VOID OnCOL_BulletToEnemy(Character* pBullet, Character* pEnemy);
	VOID OnEnemyExplosion_ani_end(Character* pExplosion);
	VOID OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam);


	VOID OnBarrage(UINT uNum);

	// �ؽ���
	LPDIRECT3DTEXTURE9	_EnemyBullet_texture;	// �� �Ѿ�
	LPDIRECT3DTEXTURE9	_Enemy_texture;		// ��
	LPDIRECT3DTEXTURE9	_EnemyExplosion_texture; // ��������

	Character*			_Bullet;
	LPDIRECT3DTEXTURE9	_Bullet_texture;	// �÷��̾��� �Ѿ�

	Character*			_Player;			// �÷��̾�
	LPDIRECT3DTEXTURE9	_Player_texture[3];	// �÷��̾� �ؽ���

	Character*			_Enemy1;
	Character*			_Enemy2;
	UINT	_uBarrage_Number;
};



///////////////////////////////////////////////////////////////
// Ŭ����  �̸� : GameScene
// ù����  ��¥ : 2009. 9. 3
// ������������ : 2009. 9. 24(��)
//
// Nick : ���ڰ�
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// �ϴ��� : GameScene�ȿ��� �Ͼ�� �ϵ��� �����Ѵ�.