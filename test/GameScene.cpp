#include "stdafx.h"			// 미리컴파일된헤더
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
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 모든리소스를 초기화한다.
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
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 캐릭터의 정보를 업데이트 한다.
VOID GameScene::Update(VOID)
{
	updateKey();		// 키입력
	updateCollision();	// 총알 충돌체크
	updateBullet();		// 총알이동

	UpdateBarrage();


	// 모든 오브젝트
	// 애니끝나고 나서 삭제 될것에 대해서 락을 건다.
	_pPool->lockDelete(POOL_EnemyBullet);
	_pPool->lockDelete(POOL_EnemyExplosion);
	updateCharacter();
	_pPool->unlockDelete(POOL_EnemyBullet);
	_pPool->unlockDelete(POOL_EnemyExplosion);
}



////////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 캐릭터들을 그린다.
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
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 리소스를 해제한다.
VOID GameScene::Release(VOID)
{
	// 오브젝트 모두 해제

	_pPool->Clear();

	if (_EnemyBullet_texture)
		_EnemyBullet_texture->Release();

	if (_Enemy_texture)
		_Enemy_texture->Release();

	if (_EnemyExplosion_texture)
		_EnemyExplosion_texture->Release();

	// 플레이어 해제
	if (_Player_texture[0])
	{
		_Player_texture[0]->Release();
		_Player_texture[1]->Release();
		_Player_texture[2]->Release();
	}

	// 플레이어 총알해제
	if (_Bullet_texture)
		_Bullet_texture->Release();

}




////////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 총알의 리소스를 읽어들인다.
VOID GameScene::initBullet(VOID)
{
	// 총알 초기화
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


	// 이미지 부르기
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"PlayerBullet.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &pBulletImage->Texture);
	_Bullet_texture = pBulletImage->Texture;





	// 데이터 적용
	vBulletImage[0].push_back(pBulletImage);
	pBullet->setAnimation(&vBulletImage);
	pBullet->setProperty(&BulletProperty);



	// 충돌 데이터 넣기
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
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 적의 총알리소스를 읽어들인다.
VOID GameScene::initEnemyBullet(VOID)
{
	// 첫번째 적넣기
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


	// 이미지 부르기
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"EnemyBullet.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &EnemyImage->Texture);
	_EnemyBullet_texture = EnemyImage->Texture;

	// 데이터 적용
	vEnemyImage[0].push_back(EnemyImage);
	pChar->setAnimation(&vEnemyImage);
	pChar->setProperty(&EnemyProperty);

	// 충돌 데이터 넣기
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
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 적의리소스를 읽어들인다.
VOID GameScene::initEnemy(VOID)
{
	// 첫번째 적넣기
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


	// 이미지 부르기
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"cirno.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &EnemyImage->Texture);
	_Enemy_texture = EnemyImage->Texture;

	// 데이터 적용
	vEnemyImage[0].push_back(EnemyImage);
	pEnemy->setAnimation(&vEnemyImage);
	pEnemy->setProperty(&EnemyProperty);




	// 모션 데이터 넣기
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


	// 충돌 데이터 넣기
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



	//// 1번째 적넣기
	//Character* pEnemy1 = NULL;
	//pEnemy1 = _pPool->New(POOL_Enemy);
	//pEnemy1->playMotion();
	//pEnemy1->setPosition(&D3DXVECTOR3(234.0f, 64.0f, .0f));



	// 2번째 적넣기
	Character* pEnemy2 = NULL;
	pEnemy2 = _pPool->New(POOL_Enemy);
	pEnemy2->playMotion();
	pEnemy2->setPosition(&D3DXVECTOR3(434.0f, 64.0f, .0f));

	_Enemy2 = pEnemy2;
	OnBarrage(1);


}




//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 적의 폭팔애니리소스를 읽어들인다.
VOID GameScene::initEnemy_Explosion(VOID)
{

	// 이미지 부르기
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"Enemy_Explosion.png",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &_EnemyExplosion_texture);





	// 이미지 좌표넣기
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





	// 캐릭터의 속성값넣기
	Property EnemyProperty;
	ZeroMemory(&EnemyProperty, sizeof(Property));
	EnemyProperty.ALive = TRUE;


	// POOL원본넣기
	Character* pEnemyExplosion = NULL;
	pEnemyExplosion = new Character;
	pEnemyExplosion->setAnimation(&vEnemyImage);
	pEnemyExplosion->setProperty(&EnemyProperty);
	_pPool->pushPool(pEnemyExplosion, 50);	// 여분의 개수를 50개로 잡음
}




//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : Player리소스를 읽어들인다.
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






	// 이미지 부르기
	//D3DXCreateTextureFromFileExW( _pd3dDevice, L"nemo80_160.png", 
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"player_left.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &PlayerImage.Texture);
	_Player_texture[0] = PlayerImage.Texture;

	// 왼쪽
	for (UINT i = 0; i<8; ++i)
	{
		pPlayerImage = new Image;
		*pPlayerImage = PlayerImage;
		pPlayerImage->Source.left = 0 + i * 28;
		pPlayerImage->Source.right = 28 + i * 28;
		vPlayerImage[0].push_back(pPlayerImage);
	}




	// 이미지 부르기
	//D3DXCreateTextureFromFileExW( _pd3dDevice, L"nemo80_160.png", 
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"player_center.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &PlayerImage.Texture);
	_Player_texture[1] = PlayerImage.Texture;


	// 중간
	for (UINT i = 0; i<8; ++i)
	{
		pPlayerImage = new Image;
		*pPlayerImage = PlayerImage;
		pPlayerImage->Source.left = 0 + i * 28;
		pPlayerImage->Source.right = 28 + i * 28;
		vPlayerImage[1].push_back(pPlayerImage);
	}






	// 이미지 부르기
	//D3DXCreateTextureFromFileExW( _pd3dDevice, L"nemo80_160.png", 
	D3DXCreateTextureFromFileExW(_pd3dDevice, L"player_right.tga",
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &PlayerImage.Texture);
	_Player_texture[2] = PlayerImage.Texture;


	// 중간
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



	// 데이터 적용
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


	// 총알발사
	if (GetAsyncKeyState(0x5a))
	{
		Character* pBullet = _pPool->New(POOL_PlayerBullet);
		pBullet->setPosition(_Player->getPosition());
	}
}



VOID GameScene::updateBullet(VOID)
{
	// 총알 이동
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
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : Character의 업데이트를 한다.
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
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 충돌체크를 하고, 메시지를 보낸다.
VOID GameScene::updateCollision(VOID)
{

	// 충돌테스트를 한다. 
	// 총알이 보이는 상태이고, 적이 살아있는 상태이면 충돌테스트를 한다.
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
// 넣는값 : 충돌이 발생되었을때 생길 메시지 uMSg, 충돌체크할 오브젝트1, 2
// 받는값 : VOID
// 하는일 : 충돌을 체크하고, 발생시 메시지를 보낸다.
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

				// 충돌메시지 발생
				Event(uMsg, (WPARAM)pBullet, (LPARAM)pTarget);
				return;
			}
		}
	}
}




//////////////////////////////////////////////////////////////////////////
// 넣는값 : 총알의 포인터, 적의 포인터
// 받는값 : VOID
// 하는일 :
// 적과 총알이 충돌했을때 처리를 넣는다.
// 총알은 안보이게 하고, 적의 게이지 감소
// 폭팔애니를 생성해서 보여준다.
VOID GameScene::OnCOL_BulletToEnemy(Character* pBullet, Character* pEnemy)
{
	// 적안보이게
	_pPool->Delete(pBullet);


	Character* pEnemyExplosion = NULL;
	pEnemyExplosion = _pPool->New(POOL_EnemyExplosion);
	pEnemyExplosion->setPosition(pBullet->getPosition());
	pEnemyExplosion->playAni();
	pEnemyExplosion->EventReceiver(this);



	// 적에게 데미지
	Property proEnemy = *pEnemy->getProperty();
	proEnemy.HealthPoint -= pBullet->getProperty()->AttackDamage;


	// HP가 없으면, 삭제
	if (proEnemy.HealthPoint <= .0f)
	{
		_pPool->Delete(pEnemy);
	}

	// 적의 능력 재설정
	pEnemy->setProperty(&proEnemy);
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 폭팔 애니가 끝났을때, 메모리에서 제거 한다.
VOID GameScene::OnEnemyExplosion_ani_end(Character* pExplosion)
{
	_pPool->Delete(pExplosion);
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// 이벤트가 발생했을때 처리할 함수를 수동으로 넣는다.
// 되도록이면, 여기서 직접처리하기 보다는 함수를 따로 만들어서 처리를 하는것이 좋다.
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



