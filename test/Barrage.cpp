#include "stdafx.h"			// 미리컴파일된헤더
#include "ShootingData.h"

#include "Character.h"
#include "ObjectPool.h"
#include "Component.h"
#include "Barrage.h"
#include "d3dx9math.h"


Barrage::Barrage()
{
	_bFirstPlay = TRUE;
	_fSec_count = .0f;

	_Data.BulletSpeed = 500.0f;
	_Data.FireSpeed = .50f;
	_Data.FireAngle = D3DXToRadian(90.0f);
	_Data.FireAngle_rotate = .0f;
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// 일정시간마다 총알을 생성한다.
// 총알을 가져와서 적의 위치에 설정하고, 좌표를 넣어 이동시킨다.
// 정확한 이동을 위해, 각과 이동한거리를 보정한다.
VOID Barrage::Update(VOID)
{
	if (_bFirstPlay == TRUE)
		_bFirstPlay = FALSE;
	else
	{
		_fSec_count += t;
		_Data.FireAngle += _Data.FireAngle_rotate * t;

		if (_Data.FireAngle >= 6.283185308f)
			_Data.FireAngle -= 6.283185308f;

	}


	while (_fSec_count >= _Data.FireSpeed)
	{
		// 카운터 정산
		_fSec_count -= _Data.FireSpeed;



		// 총알을 얻어오기
		Character* pChar = NULL;
		pChar = _pPool->New(POOL_EnemyBullet);
		pChar->EventReceiver(this);


		// Enemy의 위치를 얻어온다.
		const D3DXVECTOR3* pPos = _pCharacter->getPosition();


		// 모션 데이터 넣기
		MotionVec vMotion;
		Motion* pMotion = NULL;


		pMotion = new Motion;
		pMotion->Position.x = pPos->x;
		pMotion->Position.y = pPos->y;
		pMotion->Time = .0f;
		vMotion.push_back(pMotion);


		// 지나간 시간(FireAngle_rotate * _fSec_count) 정확한 각을 구하여 이동을 시작하게 한다.
		pMotion = new Motion;
		pMotion->Position.x = pPos->x
			+ cos(_Data.FireAngle - _Data.FireAngle_rotate * _fSec_count) * 1000.0f;
		pMotion->Position.y = pPos->y
			+ sin(_Data.FireAngle - _Data.FireAngle_rotate * _fSec_count) * 1000.0f;
		pMotion->Time = 1000.0f / _Data.BulletSpeed;
		vMotion.push_back(pMotion);


		pChar->setPosition(pPos);			// 임시로 넣음, 나중에 필요없으면 빼도됨
		pChar->setMotion(&vMotion);
		pChar->beginMotion();
		pChar->addMotionTime(_fSec_count);	// 지나간 시간만큼 이동한거리를 보정한다.
	}



}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : 탄막설정값
// 받는값 : VOID
// 하는일 : 탄막패턴 데이터를 설정한다.
VOID Barrage::setData(Barrage_data* pData)
{
	memcpy(&_Data, pData, sizeof(Barrage_data));
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 다이동된 총알을 삭제한다.
VOID Barrage::OnEnemyBullet_mot_end(Character* pChar)
{
	_pPool->Delete(pChar);
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 메시지를 받고, 해당 함수를 연결한다.
VOID Barrage::OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case MOT_End:
		OnEnemyBullet_mot_end((Character*)pObj);
		break;
	}
}