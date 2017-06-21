#include "stdafx.h"			// �̸������ϵ����
#include "ShootingData.h"

#include "Character.h"
#include "ObjectPool.h"
#include "Component.h"
#include "Barrage.h"
#include "GameScene.h"
#include "d3dx9math.h"



GameScene::GameScene()
{
	_Bullet_texture = NULL;
	_Enemy_texture = NULL;
	ZeroMemory(_Player_texture, sizeof(_Player_texture));

	_Enemy2 = NULL;
	_uBarrage_Number = 0;
}



////////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ��縮�ҽ��� �ʱ�ȭ�Ѵ�.
VOID GameScene::Initialize(VOID)
{
	EventReceiver(this);

	_pPool->reservePool(POOL_Max);
	initEnemyBullet();
	initEnemy();
	initEnemy_Explosion();
	initBullet();
	initPlayer();

}



////////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ĳ������ ������ ������Ʈ �Ѵ�.
VOID GameScene::Update(VOID)
{
	updateKey();		// Ű�Է�
	updateCollision();	// �Ѿ� �浹üũ
	updateBullet();		// �Ѿ��̵�

	UpdateBarrage();


	// ��� ������Ʈ
	// �ִϳ����� ���� ���� �ɰͿ� ���ؼ� ���� �Ǵ�.
	_pPool->lockDelete(POOL_EnemyBullet);
	_pPool->lockDelete(POOL_EnemyExplosion);
	updateCharacter();
	_pPool->unlockDelete(POOL_EnemyBullet);
	_pPool->unlockDelete(POOL_EnemyExplosion);
}



////////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ĳ���͵��� �׸���.
VOID GameScene::Draw(VOID)
{
	CharacterList::iterator it;
	CharacterList *pList = NULL;
	for (UINT i = 0; i<POOL_Max; ++i)
	{
		pList = _pPool->getUseList(i);
		for (it = pList->begin(); it != pList->end(); ++it)
			(*it)->Draw();

	}
}



////////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ���ҽ��� �����Ѵ�.
VOID GameScene::Release(VOID)
{
	// ������Ʈ ��� ����

	_pPool->Clear();

	if (_EnemyBullet_texture)
		_EnemyBullet_texture->Release();

	if (_Enemy_texture)
		_Enemy_texture->Release();

	if (_EnemyExplosion_texture)
		_EnemyExplosion_texture->Release();

	// �÷��̾� ����
	if (_Player_texture[0])
	{
		_Player_texture[0]->Release();
		_Player_texture[1]->Release();
		_Player_texture[2]->Release();
	}

	// �÷��̾� �Ѿ�����
	if (_Bullet_texture)
		_Bullet_texture->Release();

}




////////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : �Ѿ��� ���ҽ��� �о���δ�.
VOID GameScene::initBullet(VOID)
{
	// �Ѿ� �ʱ�ȭ
	Character* pBullet = NULL;
	pBullet = new Character;

	ImageVec2 vBulletImage;
	vBulletImage.resize(1);

	Image* pBulletImage = new Image;
	ZeroMemory(pBulletImage, sizeof(Image_data));
	pBulletImage->Source.left = 0;
	pBulletImage->Source.top = 80;
	pBulletImage->Source.right = 40;
	pBulletImage->Source.bottom = 120;
	pBulletImage->Time = 1.0f;

	pBulletImage->Position.x = -6.5f;
	pBulletImage->Position.y = -13.0f;


	Property BulletProperty;
	ZeroMemory(&BulletProperty, sizeof(Property));
	BulletProperty.Speed = 250.0f;
	BulletProperty.AttackDamage = 1.0f;
	BulletProperty.ALive = TRUE;


	// �̹��� �θ���
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"PlayerBullet.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &pBulletImage->Texture);
	_Bullet_texture = pBulletImage->Texture;





	// ������ ����
	vBulletImage[0].push_back(pBulletImage);
	pBullet->setAnimation(&vBulletImage);
	pBullet->setProperty(&BulletProperty);



	// �浹 ������ �ֱ�
	BoundBoxVec vBound;
	BoundingBox* pBox = new BoundingBox;
	pBox->LT.x = -6.5f;
	pBox->LT.y = -13.0f;
	pBox->RB.x = 6.5f;
	pBox->RB.y = 13.0f;
	vBound.push_back(pBox);

	pBullet->setBoundingBox(&vBound);


	_pPool->pushPool(pBullet, 300);

}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ���� �Ѿ˸��ҽ��� �о���δ�.
VOID GameScene::initEnemyBullet(VOID)
{
	// ù��° ���ֱ�
	Character* pChar = NULL;
	pChar = new Character;

	ImageVec2 vEnemyImage;
	vEnemyImage.resize(1);

	Image* EnemyImage = new Image;
	ZeroMemory(EnemyImage, sizeof(Image_data));
	EnemyImage->Source.left = 0;
	EnemyImage->Source.top = 0;
	EnemyImage->Source.right = 14;
	EnemyImage->Source.bottom = 16;
	EnemyImage->Time = 1.0f;


	EnemyImage->Position.x = -7.0f;
	EnemyImage->Position.y = -8.0f;



	Property EnemyProperty;
	ZeroMemory(&EnemyProperty, sizeof(Property));
	EnemyProperty.HealthPoint = 200.0f;
	EnemyProperty.ALive = TRUE;


	// �̹��� �θ���
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"EnemyBullet.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &EnemyImage->Texture);
	_EnemyBullet_texture = EnemyImage->Texture;

	// ������ ����
	vEnemyImage[0].push_back(EnemyImage);
	pChar->setAnimation(&vEnemyImage);
	pChar->setProperty(&EnemyProperty);

	// �浹 ������ �ֱ�
	BoundBoxVec vBound;
	BoundingBox* pBox = new BoundingBox;
	pBox->LT.x = -6.5f;
	pBox->LT.y = -13.0f;
	pBox->RB.x = 6.5f;
	pBox->RB.y = 13.0f;
	vBound.push_back(pBox);

	pChar->setBoundingBox(&vBound);

	_pPool->pushPool(pChar, 1000);

}




//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ���Ǹ��ҽ��� �о���δ�.
VOID GameScene::initEnemy(VOID)
{
	// ù��° ���ֱ�
	Character* pEnemy = NULL;
	pEnemy = new Character;

	ImageVec2 vEnemyImage;
	vEnemyImage.resize(1);

	Image* EnemyImage = new Image;
	ZeroMemory(EnemyImage, sizeof(Image_data));
	EnemyImage->Source.left = 0;
	EnemyImage->Source.top = 0;
	EnemyImage->Source.right = 179;
	EnemyImage->Source.bottom = 238;
	EnemyImage->Time = 1.0f;


	EnemyImage->Position.x = -90.50f;
	EnemyImage->Position.y = -119.0f;



	Property EnemyProperty;
	ZeroMemory(&EnemyProperty, sizeof(Property));
	EnemyProperty.HealthPoint = 200.0f;
	EnemyProperty.ALive = TRUE;


	// �̹��� �θ���
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"cirno.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &EnemyImage->Texture);
	_Enemy_texture = EnemyImage->Texture;

	// ������ ����
	vEnemyImage[0].push_back(EnemyImage);
	pEnemy->setAnimation(&vEnemyImage);
	pEnemy->setProperty(&EnemyProperty);




	// ��� ������ �ֱ�
	MotionVec vMotion;
	Motion* pMotion = NULL;

	pMotion = new Motion;
	pMotion->Position.x = 234.0f;
	pMotion->Position.y = 64.0f;
	pMotion->Time = .0f;
	vMotion.push_back(pMotion);


	pMotion = new Motion;
	pMotion->Position.x = 96.0f;
	pMotion->Position.y = 289.0f;
	pMotion->Time = 2.0f;
	vMotion.push_back(pMotion);


	pMotion = new Motion;
	pMotion->Position.x = 451.0f;
	pMotion->Position.y = 267.0f;
	pMotion->Time = 4.0f;
	vMotion.push_back(pMotion);


	pMotion = new Motion;
	pMotion->Position.x = 234.0f;
	pMotion->Position.y = 145.0f;
	pMotion->Time = 6.0f;
	vMotion.push_back(pMotion);

	pEnemy->setMotion(&vMotion);


	// �浹 ������ �ֱ�
	BoundBoxVec vBound;
	BoundingBox* pBox = NULL;

	pBox = new BoundingBox;
	pBox->LT.x = -54.0f;
	pBox->LT.y = -90.0f;
	pBox->LT.z = .0f;
	pBox->RB.x = 43.0f;
	pBox->RB.y = 104.0f;
	vBound.push_back(pBox);
	pEnemy->setBoundingBox(&vBound);

	pEnemy->setPosition(&D3DXVECTOR3(234.0f, 64.0f, .0f));



	_pPool->pushPool(pEnemy, 2);



	//// 1��° ���ֱ�
	//Character* pEnemy1 = NULL;
	//pEnemy1 = _pPool->New(POOL_Enemy);
	//pEnemy1->playMotion();
	//pEnemy1->setPosition(&D3DXVECTOR3(234.0f, 64.0f, .0f));



	// 2��° ���ֱ�
	Character* pEnemy2 = NULL;
	pEnemy2 = _pPool->New(POOL_Enemy);
	pEnemy2->playMotion();
	pEnemy2->setPosition(&D3DXVECTOR3(434.0f, 64.0f, .0f));

	_Enemy2 = pEnemy2;
	OnBarrage(1);


}




//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ���� ���Ⱦִϸ��ҽ��� �о���δ�.
VOID GameScene::initEnemy_Explosion(VOID)
{

	// �̹��� �θ���
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"Enemy_Explosion.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &_EnemyExplosion_texture);





	// �̹��� ��ǥ�ֱ�
	ImageVec2 vEnemyImage;
	vEnemyImage.resize(1);


	Image* EnemyImage = NULL;

	for (UINT i = 0; i<12; ++i)
	{
		EnemyImage = new Image;
		ZeroMemory(EnemyImage, sizeof(Image_data));
		EnemyImage->Source.left = 0 + i * 80;
		EnemyImage->Source.top = 0;
		EnemyImage->Source.right = 80 + i * 80;
		EnemyImage->Source.bottom = 80;
		EnemyImage->Time = .20f;
		EnemyImage->Texture = _EnemyExplosion_texture;

		EnemyImage->Position.x = -40.0f;
		EnemyImage->Position.y = -40.0f;

		vEnemyImage[0].push_back(EnemyImage);
	}





	// ĳ������ �Ӽ����ֱ�
	Property EnemyProperty;
	ZeroMemory(&EnemyProperty, sizeof(Property));
	EnemyProperty.ALive = TRUE;


	// POOL�����ֱ�
	Character* pEnemyExplosion = NULL;
	pEnemyExplosion = new Character;
	pEnemyExplosion->setAnimation(&vEnemyImage);
	pEnemyExplosion->setProperty(&EnemyProperty);
	_pPool->pushPool(pEnemyExplosion, 50);	// ������ ������ 50���� ����
}




//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : Player���ҽ��� �о���δ�.
VOID GameScene::initPlayer(VOID)
{
	ImageVec2 vPlayerImage;
	//vPlayerImage.resize(1);
	vPlayerImage.resize(3);

	Image PlayerImage;
	Image* pPlayerImage = NULL;
	ZeroMemory(&PlayerImage, sizeof(Image_data));

	PlayerImage.Source.left = 0;
	PlayerImage.Source.top = 0;
	PlayerImage.Source.right = 28;
	PlayerImage.Source.bottom = 49;
	PlayerImage.Time = .20f;

	PlayerImage.Position.x = -14.0f;
	PlayerImage.Position.y = -24.5f;






	// �̹��� �θ���
	//D3DXCreateTextureFromFileExW( _pd3dDevice, L"nemo80_160.png", 
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"player_left.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &PlayerImage.Texture);
	_Player_texture[0] = PlayerImage.Texture;

	// ����
	for (UINT i = 0; i<8; ++i)
	{
		pPlayerImage = new Image;
		*pPlayerImage = PlayerImage;
		pPlayerImage->Source.left = 0 + i * 28;
		pPlayerImage->Source.right = 28 + i * 28;
		vPlayerImage[0].push_back(pPlayerImage);
	}




	// �̹��� �θ���
	//D3DXCreateTextureFromFileExW( _pd3dDevice, L"nemo80_160.png", 
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"player_center.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &PlayerImage.Texture);
	_Player_texture[1] = PlayerImage.Texture;


	// �߰�
	for (UINT i = 0; i<8; ++i)
	{
		pPlayerImage = new Image;
		*pPlayerImage = PlayerImage;
		pPlayerImage->Source.left = 0 + i * 28;
		pPlayerImage->Source.right = 28 + i * 28;
		vPlayerImage[1].push_back(pPlayerImage);
	}






	// �̹��� �θ���
	//D3DXCreateTextureFromFileExW( _pd3dDevice, L"nemo80_160.png", 
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"player_right.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &PlayerImage.Texture);
	_Player_texture[2] = PlayerImage.Texture;


	// �߰�
	for (UINT i = 0; i<8; ++i)
	{
		pPlayerImage = new Image;
		*pPlayerImage = PlayerImage;
		pPlayerImage->Source.left = 0 + i * 28;
		pPlayerImage->Source.right = 28 + i * 28;
		vPlayerImage[2].push_back(pPlayerImage);
	}





	Property PlayerProperty;
	ZeroMemory(&PlayerProperty, sizeof(Property));
	PlayerProperty.Speed = 500.0f;
	PlayerProperty.HealthPoint = 1000.0f;
	PlayerProperty.ALive = TRUE;



	// ������ ����
	Character* pPlayer = NULL;
	pPlayer = new Character;
	pPlayer->setAnimation(&vPlayerImage);
	pPlayer->selAnimation(0);
	pPlayer->setProperty(&PlayerProperty);

	

	BoundBoxVec vBound;
	BoundingBox* pBox = NULL;

	pBox = new BoundingBox;
	pBox->LT.x = -9.0f;
	pBox->LT.y = -20.0f;
	pBox->LT.z = .0f;
	pBox->RB.x = 9.0f;
	pBox->RB.y = 20.0f;
	vBound.push_back(pBox);
	pPlayer->setBoundingBox(&vBound);
	
	pPlayer->setPosition(&D3DXVECTOR3(300.0f, 650.0f, .0f));

	
	_pPool->pushPool(pPlayer, 1);
	_Player = _pPool->New(POOL_Player);
	_Player->playAni();
}



VOID GameScene::updateKey(VOID)
{

	if (GetAsyncKeyState(VK_LEFT))
	{
		_Player->moveLeft();
		_Player->selAnimation(PLAYER_Left);
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		_Player->moveRight();
		_Player->selAnimation(PLAYER_Right);
	}

	if (GetAsyncKeyState(VK_UP))
	{
		_Player->moveUp();
		_Player->selAnimation(PLAYER_Center);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		_Player->moveDown();
		_Player->selAnimation(PLAYER_Center);
	}


	// �Ѿ˹߻�
	if (GetAsyncKeyState(0x5a))
	{
		Character* pBullet = _pPool->New(POOL_PlayerBullet);
		pBullet->setPosition(_Player->getPosition());
	}
}



VOID GameScene::updateBullet(VOID)
{
	// �Ѿ� �̵�
	_pPool->lockDelete(POOL_PlayerBullet);

	CharacterList::iterator it;
	CharacterList* pList = NULL;
	pList = _pPool->getUseList(POOL_PlayerBullet);
	for (it = pList->begin(); it != pList->end(); ++it)
	{
		(*it)->moveUp();

		if ((*it)->getPosition()->y < -40.0f)
			_pPool->Delete(*it);

	}

	_pPool->unlockDelete(POOL_PlayerBullet);

}



VOID GameScene::UpdateBarrage(VOID)
{
	if (_bPgUp)
	{
		if (_uBarrage_Number < 4)
		{
			_uBarrage_Number++;
			OnBarrage(_uBarrage_Number);
		}


		_bPgUp = FALSE;
	}

	if (_bPgDn)
	{
		if (_uBarrage_Number > 0)
		{
			_uBarrage_Number--;
			OnBarrage(_uBarrage_Number);
		}


		_bPgDn = FALSE;
	}
}





//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : Character�� ������Ʈ�� �Ѵ�.
VOID GameScene::updateCharacter(VOID)
{
	CharacterList::iterator it;
	CharacterList *pList = NULL;
	for (UINT i = 0; i<POOL_Max; ++i)
	{
		pList = _pPool->getUseList(i);
		for (it = pList->begin(); it != pList->end(); ++it)
			(*it)->Update();

	}

}




//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : �浹üũ�� �ϰ�, �޽����� ������.
VOID GameScene::updateCollision(VOID)
{

	// �浹�׽�Ʈ�� �Ѵ�. 
	// �Ѿ��� ���̴� �����̰�, ���� ����ִ� �����̸� �浹�׽�Ʈ�� �Ѵ�.
	_pPool->lockDelete(POOL_Enemy);
	_pPool->lockDelete(POOL_PlayerBullet);

	CharacterList::iterator itE;
	CharacterList* plsitEnemy = NULL;
	plsitEnemy = _pPool->getUseList(POOL_Enemy);

	CharacterList::iterator itB;
	CharacterList* plistBullet = NULL;
	plistBullet = _pPool->getUseList(POOL_PlayerBullet);

	for (itE = plsitEnemy->begin(); itE != plsitEnemy->end(); ++itE)
	{
		for (itB = plistBullet->begin(); itB != plistBullet->end(); ++itB)
		{
			Collision(COL_BulletToEnemy, *itB, *itE);
		}
	}


	_pPool->unlockDelete(POOL_PlayerBullet);
	_pPool->unlockDelete(POOL_Enemy);
}






//////////////////////////////////////////////////////////////////////////
// �ִ°� : �浹�� �߻��Ǿ����� ���� �޽��� uMSg, �浹üũ�� ������Ʈ1, 2
// �޴°� : VOID
// �ϴ��� : �浹�� üũ�ϰ�, �߻��� �޽����� ������.
VOID GameScene::Collision(UINT uMsg, Character* pBullet, Character* pTarget)
{
	const BoundBoxVec& vBullet = pBullet->getBoundingBox();
	const BoundBoxVec& vTarget = pTarget->getBoundingBox();


	for (UINT i = 0; i<vBullet.size(); ++i)
	{
		for (UINT k = 0; k<vTarget.size(); ++k)
		{
			if (vTarget[k]->LT.x < vBullet[i]->RB.x
				&&vBullet[i]->LT.x < vTarget[k]->RB.x
				&&vTarget[k]->LT.y < vBullet[i]->RB.y
				&&vBullet[i]->LT.y < vTarget[k]->RB.y)
			{

				// �浹�޽��� �߻�
				Event(uMsg, (WPARAM)pBullet, (LPARAM)pTarget);
				return;
			}
		}
	}
}




//////////////////////////////////////////////////////////////////////////
// �ִ°� : �Ѿ��� ������, ���� ������
// �޴°� : VOID
// �ϴ��� :
// ���� �Ѿ��� �浹������ ó���� �ִ´�.
// �Ѿ��� �Ⱥ��̰� �ϰ�, ���� ������ ����
// ���Ⱦִϸ� �����ؼ� �����ش�.
VOID GameScene::OnCOL_BulletToEnemy(Character* pBullet, Character* pEnemy)
{
	// ���Ⱥ��̰�
	_pPool->Delete(pBullet);


	Character* pEnemyExplosion = NULL;
	pEnemyExplosion = _pPool->New(POOL_EnemyExplosion);
	pEnemyExplosion->setPosition(pBullet->getPosition());
	pEnemyExplosion->playAni();
	pEnemyExplosion->EventReceiver(this);



	// ������ ������
	Property proEnemy = *pEnemy->getProperty();
	proEnemy.HealthPoint -= pBullet->getProperty()->AttackDamage;


	// HP�� ������, ����
	if (proEnemy.HealthPoint <= .0f)
	{
		_pPool->Delete(pEnemy);
	}

	// ���� �ɷ� �缳��
	pEnemy->setProperty(&proEnemy);
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ���� �ִϰ� ��������, �޸𸮿��� ���� �Ѵ�.
VOID GameScene::OnEnemyExplosion_ani_end(Character* pExplosion)
{
	_pPool->Delete(pExplosion);
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// �̺�Ʈ�� �߻������� ó���� �Լ��� �������� �ִ´�.
// �ǵ����̸�, ���⼭ ����ó���ϱ� ���ٴ� �Լ��� ���� ���� ó���� �ϴ°��� ����.
VOID GameScene::OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case COL_BulletToEnemy:
		OnCOL_BulletToEnemy((Character*)wParam, (Character*)lParam);
		break;
	case ANI_End:
		OnEnemyExplosion_ani_end((Character*)pObj);
		break;
	}
}




VOID GameScene::OnBarrage(UINT uNum)
{
	Barrage_data Bar_data;
	Barrage* pBarrage = NULL;


	_pPool->DeleteAll(POOL_EnemyBullet);
	_Enemy2->clearComponent();


	switch (uNum)
	{
	case 0:
		pBarrage = new Barrage;
		Bar_data.BulletSpeed = 400.0f;
		Bar_data.FireSpeed = .1f;
		Bar_data.FireAngle = D3DXToRadian(180.0f);
		Bar_data.FireAngle_rotate = .0f;
		pBarrage->setData(&Bar_data);
		_Enemy2->addComponent(pBarrage);
		break;
	case 1:
		pBarrage = new Barrage;
		Bar_data.BulletSpeed = 100.0f;
		Bar_data.FireSpeed = .05f;
		Bar_data.FireAngle = .0f;
		Bar_data.FireAngle_rotate = D3DXToRadian(270.0f);
		pBarrage->setData(&Bar_data);
		_Enemy2->addComponent(pBarrage);
		break;
	case 2:
		for (UINT i = 0; i<4; ++i)
		{
			pBarrage = new Barrage;
			Bar_data.BulletSpeed = 100.0f;
			Bar_data.FireSpeed = .05f;
			Bar_data.FireAngle = D3DXToRadian(90.0f * i);
			Bar_data.FireAngle_rotate = D3DXToRadian(270.0f);
			pBarrage->setData(&Bar_data);
			_Enemy2->addComponent(pBarrage);
		}
		break;
	case 3:
		for (UINT i = 0; i<100; ++i)
		{
			pBarrage = new Barrage;
			Bar_data.BulletSpeed = 100.0f;
			Bar_data.FireSpeed = 1.0f;
			Bar_data.FireAngle = D3DXToRadian(3.60f * i);
			Bar_data.FireAngle_rotate = D3DXToRadian(.0f);
			pBarrage->setData(&Bar_data);
			_Enemy2->addComponent(pBarrage);
		}
		break;
	case 4:
		pBarrage = new Barrage;
		Bar_data.BulletSpeed = 600.0f;
		Bar_data.FireSpeed = .05f;
		Bar_data.FireAngle = D3DXToRadian(90.0f);
		Bar_data.FireAngle_rotate = D3DXToRadian(.0f);
		pBarrage->setData(&Bar_data);
		_Enemy2->addComponent(pBarrage);

		pBarrage = new Barrage;
		Bar_data.BulletSpeed = 600.0f;
		Bar_data.FireSpeed = .05f;
		Bar_data.FireAngle = D3DXToRadian(110.0f);
		Bar_data.FireAngle_rotate = D3DXToRadian(.0f);
		pBarrage->setData(&Bar_data);
		_Enemy2->addComponent(pBarrage);

		pBarrage = new Barrage;
		Bar_data.BulletSpeed = 600.0f;
		Bar_data.FireSpeed = .05f;
		Bar_data.FireAngle = D3DXToRadian(130.0f);
		Bar_data.FireAngle_rotate = D3DXToRadian(.0f);
		pBarrage->setData(&Bar_data);
		_Enemy2->addComponent(pBarrage);
		break;
	}
}



