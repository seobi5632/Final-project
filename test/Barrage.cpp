#include "stdafx.h"			// �̸������ϵ����
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
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// �����ð����� �Ѿ��� �����Ѵ�.
// �Ѿ��� �����ͼ� ���� ��ġ�� �����ϰ�, ��ǥ�� �־� �̵���Ų��.
// ��Ȯ�� �̵��� ����, ���� �̵��ѰŸ��� �����Ѵ�.
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
		// ī���� ����
		_fSec_count -= _Data.FireSpeed;



		// �Ѿ��� ������
		Character* pChar = NULL;
		pChar = _pPool->New(POOL_EnemyBullet);
		pChar->EventReceiver(this);


		// Enemy�� ��ġ�� ���´�.
		const D3DXVECTOR3* pPos = _pCharacter->getPosition();


		// ��� ������ �ֱ�
		MotionVec vMotion;
		Motion* pMotion = NULL;


		pMotion = new Motion;
		pMotion->Position.x = pPos->x;
		pMotion->Position.y = pPos->y;
		pMotion->Time = .0f;
		vMotion.push_back(pMotion);


		// ������ �ð�(FireAngle_rotate * _fSec_count) ��Ȯ�� ���� ���Ͽ� �̵��� �����ϰ� �Ѵ�.
		pMotion = new Motion;
		pMotion->Position.x = pPos->x
			+ cos(_Data.FireAngle - _Data.FireAngle_rotate * _fSec_count) * 1000.0f;
		pMotion->Position.y = pPos->y
			+ sin(_Data.FireAngle - _Data.FireAngle_rotate * _fSec_count) * 1000.0f;
		pMotion->Time = 1000.0f / _Data.BulletSpeed;
		vMotion.push_back(pMotion);


		pChar->setPosition(pPos);			// �ӽ÷� ����, ���߿� �ʿ������ ������
		pChar->setMotion(&vMotion);
		pChar->beginMotion();
		pChar->addMotionTime(_fSec_count);	// ������ �ð���ŭ �̵��ѰŸ��� �����Ѵ�.
	}



}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : ź��������
// �޴°� : VOID
// �ϴ��� : ź������ �����͸� �����Ѵ�.
VOID Barrage::setData(Barrage_data* pData)
{
	memcpy(&_Data, pData, sizeof(Barrage_data));
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ���̵��� �Ѿ��� �����Ѵ�.
VOID Barrage::OnEnemyBullet_mot_end(Character* pChar)
{
	_pPool->Delete(pChar);
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : �޽����� �ް�, �ش� �Լ��� �����Ѵ�.
VOID Barrage::OnEvent(GameBase* pObj, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case MOT_End:
		OnEnemyBullet_mot_end((Character*)pObj);
		break;
	}
}