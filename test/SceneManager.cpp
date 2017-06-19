#include "stdafx.h"			// 미리컴파일된헤더
#include "ShootingData.h"

#include "Character.h"
#include "ObjectPool.h"
#include "GameScene.h"
#include "SceneManager.h"



SceneManager::SceneManager()
{
	_pGameScene = NULL;
}

VOID SceneManager::Initialize(VOID)
{
	_pPool = new ObjectPool;

	_pGameScene = new GameScene;
	_pGameScene->Initialize();
}

VOID SceneManager::Update(VOID)
{
	_pGameScene->Update();
}

VOID SceneManager::Draw(VOID)
{
	_pGameScene->Draw();
}

VOID SceneManager::Release(VOID)
{
	_pGameScene->Release();
	delete _pGameScene;

	delete _pPool;
}

