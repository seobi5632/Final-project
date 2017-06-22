#include "stdafx.h"			// 미리컴파일된헤더
#include "ShootingData.h"

#include "Component.h"
#include "Character.h"


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 변수를 초기화 한다.
Character::Character(VOID)
{
	_bVisible = TRUE;
	_uPool_number = 0;
	ZeroMemory(&_vPosition, sizeof(D3DXVECTOR3));


	// 애니메이션
	_uAni = 0;
	_bAni_play = FALSE;
	_bAni_first_play = TRUE;

	_uImg = 0;
	_pAni_Key = NULL;
	_fAni_cnt = .0f;



	// 모션
	_bMot_play = FALSE;
	_bMot_first_play = TRUE;

	_uMot_num = 0;
	_fMot_time = .0f;
	_fMot_cnt = .0f;
	ZeroMemory(&_Property, sizeof(_Property));
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : Character
// 받는값 : VOID
// 하는일 : 생성시에 초기화 하지않고 복사한다.
Character::Character(const Character* Obj)
{
	*this = *Obj;
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : Pool의 번호
// 하는일 : Pool의 번호를 넘겨준다.
UINT Character::getObjectPool_number()
{
	return _uPool_number;
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : Pool의 번호
// 받는값 : VOID
// 하는일 : Pool의 번호를 설정한다.
VOID Character::setObjectPool_number(UINT uNumber)
{
	_uPool_number = uNumber;
}




//////////////////////////////////////////////////////////////////////////
// 넣는값 : Character
// 받는값 : VOID
// 하는일 : 
// Character의 충돌박스
// 애니메이션의 이미지들, 그리고 그이미지의 충돌박스
// 모션들을 복사한다.
VOID Character::operator=(const Character& Obj)
{
	// 만약Character이외에 클래스를 만들면, 그것의 _pReceiver도 복사(or수정)해야 한다.
	_pReceiver = Obj._pReceiver;

	_bVisible = Obj._bVisible;
	_uPool_number = Obj._uPool_number;
	_vPosition = Obj._vPosition;

	UINT uSize = 0;
	uSize = Obj._vBoundBox.size();
	_vBoundBox.resize(uSize);
	for (UINT i = 0; i<uSize; ++i)
		_vBoundBox[i] = new BoundingBox(*Obj._vBoundBox[i]);




	// 애니메이션
	uSize = Obj._vImages.size();
	_vImages.resize(uSize);
	UINT uImageSize = 0;
	Image* pImage = NULL;
	UINT uBoundSize = 0;


	// 이미지 그룹
	for (UINT i = 0; i<uSize; ++i)
	{
		uImageSize = Obj._vImages[i].size();
		_vImages[i].resize(uImageSize);

		// 이미지
		for (UINT k = 0; k<uImageSize; ++k)
		{
			pImage = new Image;
			memcpy(pImage, Obj._vImages[i][k], sizeof(Image_data));
			_vImages[i][k] = pImage;

			uBoundSize = Obj._vImages[i][k]->BoundBox.size();
			_vImages[i][k]->BoundBox.resize(uBoundSize);

			// 이미지 마다 들어있는 충돌박스
			for (UINT o = 0; o<uBoundSize; o++)
				_vImages[i][k]->BoundBox[o] = new BoundingBox(*Obj._vImages[i][k]->BoundBox[o]);


		}

	}

	_uAni = Obj._uAni;
	_bAni_play = Obj._bAni_play;
	_bAni_first_play = Obj._bAni_first_play;

	_uImg = Obj._uImg;
	_pAni_Key = _vImages[_uAni][_uImg];
	_fAni_cnt = Obj._fAni_cnt;





	// 모션
	uSize = Obj._vMotion.size();
	_vMotion.resize(uSize);
	for (UINT i = 0; i<uSize; ++i)
		_vMotion[i] = new Motion(*Obj._vMotion[i]);

	_bMot_play = Obj._bMot_play;
	_bMot_first_play = Obj._bMot_first_play;

	_uMot_num = Obj._uMot_num;
	_fMot_time = Obj._fMot_time;
	_fMot_cnt = Obj._fMot_cnt;
	_Property = Obj._Property;

}



Character* Character::Copy(VOID)
{
	return new Character(this);
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// Character의 기능들을 업데이트한다.
// 이동할것을 모두 하고 애니메이션을 업데이트해야한다.
// 그리고, 컴포넌트들을 업데이트 한다.
VOID Character::Update(VOID)
{
	updateMotion();
	updateAnimation();


	// Component업데이트
	ComponentList::iterator it;
	for (it = _listComponent.begin(); it != _listComponent.end(); ++it)
		(*it)->Update();
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// 이미지를 연속해서 재생한다.
// 이미지의 재생시간이 끝나면 다음으로 넘긴다.
// 마지막까지 재생하면, 처음을 재생한다.
// 재생시간은 미만까지 =>  0 < sec
// 만약첫번째 재생이면, t를 더하지 않는다.
// 애니메이션의 상태에 따라 메시지를 보낸다.
VOID Character::updateAnimation(VOID)
{
	if (_bAni_play == FALSE)
		return;

	if (_bAni_first_play == TRUE)
	{
		_bAni_first_play = FALSE;
		return;
	}



	_fAni_cnt += t;

	while (_fAni_cnt > _pAni_Key->Time)
	{
		_fAni_cnt -= _pAni_Key->Time;
		_uImg++;


		// 애니메이션을 끝까지 재생했을때, 메시지를 보내고, 처음부터재생한다.
		if (_uImg >= _vImages[_uAni].size())
		{
			Event(ANI_End);
			_uImg = 0;
		}

		_pAni_Key = _vImages[_uAni][_uImg];
	}

}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// 첫재생이 시작하면, 위치를 세팅하고, 다음프레임부터 시간에 따라 적용한다.
//
// 모션의 현재위치와 다음위치를 시간간격으로 계산해서, 현재위치를 만든다.
// D3DXVec3Lerp( &vOut, &v1, &v2, 1.0f);
// 현재위치, 이전위치, 다음위치, 시간간격을 100%놓았을때의 값
// 시간이 모두 지나가면, 가장마지막 (모션-1)에서 멈춘다.
VOID Character::updateMotion(VOID)
{
	if (_bMot_play == FALSE)
		return;


	if (_bMot_first_play == TRUE)
	{
		_bMot_first_play = FALSE;
		setPosition(&_vMotion[_uMot_num]->Position);
		return;
	}



	D3DXVECTOR3 vOut;

	_fMot_cnt += t;
	while (_fMot_cnt > _fMot_time)
	{
		_fMot_cnt -= _fMot_time;
		_uMot_num++;

		if (_uMot_num + 1 >= _vMotion.size())
		{
			_uMot_num--;
			Event(MOT_End);
			_fMot_cnt = _fMot_time;
			_bMot_play = FALSE;
		}
		else
			_fMot_time = _vMotion[_uMot_num + 1]->Time - _vMotion[_uMot_num]->Time;

	}


	D3DXVec3Lerp(&vOut,
		&_vMotion[_uMot_num]->Position,
		&_vMotion[_uMot_num + 1]->Position,
		_fMot_cnt / _fMot_time);

	setPosition(&vOut);
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// Character의 이미지를 그린다.
// _bBound_visible값이 TRUE이면, 충돌영역도 그린다.
// 애니메이션 키프레임의 포인터 받은것을, 여기에 짧은 변수명으로 활용한다.
VOID Character::Draw(VOID)
{
	if (_bVisible == FALSE
		|| _vImages.empty() == TRUE)
		return;




	_pSprite->Draw(_pAni_Key->Texture,
		&_pAni_Key->Source,
		&_pAni_Key->Center,
		&_pAni_Key->Position,
		0xffffffff);




	if (!_bBound_visible)
		return;



	static RECT rcSource = { 0, };
	static D3DXVECTOR3 vCenter(.0f, .0f, .0f);
	static UINT uSize = 0;


	if (!_vBoundBox.empty())
	{
		uSize = _vBoundBox.size();

		for (UINT i = 0; i<uSize; ++i)
		{
			rcSource.right = LONG(_vBoundBox[i]->RB.x - _vBoundBox[i]->LT.x);
			rcSource.bottom = LONG(_vBoundBox[i]->RB.y - _vBoundBox[i]->LT.y);
			_pSprite->Draw(_pWhite_texture, &rcSource, &vCenter, &_vBoundBox[i]->LT, 0x50E74280);
		}
	}
	else
	{
		uSize = _pAni_Key->BoundBox.size();

		for (UINT i = 0; i<uSize; ++i)
		{
			rcSource.right = LONG(_pAni_Key->BoundBox[i]->RB.x
				- _pAni_Key->BoundBox[i]->LT.x);
			rcSource.bottom = LONG(_pAni_Key->BoundBox[i]->RB.y
				- _pAni_Key->BoundBox[i]->LT.y);

			_pSprite->Draw(_pWhite_texture, &rcSource, &vCenter,
				&_pAni_Key->BoundBox[i]->LT, 0x50E74280);


		}

	}


}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// Character의 모든 리소스 자원을 해제해준다.
// 데이터의 제거시점을 Character삭제시점이 아니라도, 원할때 할수있다.
VOID Character::Release(VOID)
{
	// 이미지 제거
	INT iAni_size = _vImages.size();
	INT iImage_size = 0;

	for (INT i = 0; i<iAni_size; ++i)
	{
		iImage_size = _vImages[i].size();
		for (INT k = 0; k<iImage_size; ++k)
		{
			delete _vImages[i][k];
		}
		_vImages[i].clear();
	}
	_vImages.clear();



	// 모션제거
	clearMotion();




	// 충돌박스제거
	INT iBound_size = _vBoundBox.size();

	for (INT i = 0; i<iBound_size; ++i)
	{
		delete _vBoundBox[i];
	}
	_vBoundBox.clear();



	// Component제거
	clearComponent();
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : BOOL
// 받는값 : VOID
// 하는일 : Character의 보이기 여부를 결정한다.
VOID Character::setVisible(BOOL bVisible)
{
	_bVisible = bVisible;
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : BOOL
// 하는일 : Character의 보이기 여부를 얻는다.
BOOL Character::getVisible(VOID)
{
	return _bVisible;
}


////////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : Image의 포인터
// 하는일 : 이미지의 정보를 얻는다.
const Image* Character::getImage(VOID)
{
	return _vImages[_uAni][_uImg];
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : 2차원 이미지 벡터의 포인터
// 받는값 : VOID
// 하는일 : 
// 애니메이션을 넣는다.
// 키프레임을 이때 다시받는다.
VOID Character::setAnimation(const ImageVec2* vImage)
{
	_vImages = *vImage;

	_pAni_Key = _vImages[0][0];
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// 애니메이션을 선택한다.
// 애니를 선택하면, 애니재생값들이 초기화 된다.
VOID Character::selAnimation(UINT iNum)
{
	if (iNum == _uAni
		|| iNum >= _vImages.size())
		return;


	_bAni_first_play = TRUE;
	_uAni = iNum;
	_uImg = 0;
	_fAni_cnt = .0f;

	_pAni_Key = _vImages[_uAni][_uImg];
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// 이미지를 재생한다.
// 애니메이션이 하나도 없거나
// 애니메이션의 이미지가 1개보다 작을경우 재생이 되지 않는다.
// 처음 부터 재생을 한다.
VOID Character::playAni(VOID)
{
	if (_vImages.empty() == TRUE)
		return;

	if (_vImages[_uAni].size() <= 1
		|| _bAni_play == TRUE)
		return;


	_bAni_play = TRUE;
	_bAni_first_play = TRUE;

	// 애니메이션 초기화
	_uImg = 0;
	_pAni_Key = _vImages[_uAni][_uImg];
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 이미지 재생을 멈춘다.
VOID Character::stopAni(VOID)
{
	_bAni_play = FALSE;
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : const BoundBoxVec*
// 받는값 : VOID
// 하는일 : 충돌박스를 벡터포인터로 넣는다.
VOID Character::setBoundingBox(const BoundBoxVec* vBox)
{
	_vBoundBox = *vBox;
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : BoundBoxVec&
// 하는일 : 
// 이미지로부터 충돌박스벡터를 얻는다.
// 만약 Character에 충돌박스가 있으면, 그값이 넘겨진다.
// 만약, 이미지가 하나도 없는데, 이함수를 호출하면, 프로그램이 에러난다.
BoundBoxVec& Character::getBoundingBox(VOID)
{
	if (_vBoundBox.empty() == FALSE)
	{
		return _vBoundBox;
	}
	else
	{
		return _vImages[_uAni][_uImg]->BoundBox;
	}
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 왼쪽으로 이동
VOID Character::moveLeft(VOID)
{
	movePosition(&D3DXVECTOR3(-_Property.Speed * t, .0f, .0f));
}

//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 오른쪽으로 이동
VOID Character::moveRight(VOID)
{
	movePosition(&D3DXVECTOR3(_Property.Speed * t, .0f, .0f));
}

//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 위로 이동
VOID Character::moveUp(VOID)
{
	movePosition(&D3DXVECTOR3(.0f, -_Property.Speed * t, .0f));
}

//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 아래로 이동
VOID Character::moveDown(VOID)
{
	movePosition(&D3DXVECTOR3(.0f, _Property.Speed * t, .0f));

}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// 위치를 이동한다.
// 이미지의 모든 좌표를 일정치만큼이동시킨다.
// 충돌박스의 모든좌표를 일정치만큼 이동시킨다.
VOID Character::movePosition(const D3DXVECTOR3* vPos)
{
	_vPosition += *vPos;

	INT iAniSize = 0;
	iAniSize = _vImages.size();
	INT iImage_size = 0;
	INT iBound_size = 0;

	for (INT i = 0; i<iAniSize; ++i)
	{
		iImage_size = _vImages[i].size();
		for (INT k = 0; k<iImage_size; ++k)
		{
			_vImages[i][k]->Position.x += vPos->x;
			_vImages[i][k]->Position.y += vPos->y;

			iBound_size = _vImages[i][k]->BoundBox.size();
			for (INT c = 0; c<iBound_size; ++c)
			{
				_vImages[i][k]->BoundBox[c]->LT.x += vPos->x;
				_vImages[i][k]->BoundBox[c]->LT.y += vPos->y;
				_vImages[i][k]->BoundBox[c]->RB.x += vPos->x;
				_vImages[i][k]->BoundBox[c]->RB.y += vPos->y;
			}
		}
	}


	iBound_size = _vBoundBox.size();
	for (INT c = 0; c<iBound_size; ++c)
	{
		_vBoundBox[c]->LT.x += vPos->x;
		_vBoundBox[c]->LT.y += vPos->y;
		_vBoundBox[c]->RB.x += vPos->x;
		_vBoundBox[c]->RB.y += vPos->y;
	}

}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : D3DXVECTOR3*
// 받는값 : VOID
// 하는일 : 
// 위치를 설정한다.
// 원래 위치에서 얼마만큼 이동했는지를 구해서 이동시킨다.
VOID Character::setPosition(const D3DXVECTOR3* vPos)
{
	D3DXVECTOR3 vMove;
	vMove = *vPos - _vPosition;

	movePosition(&vMove);
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : const D3DXVECTOR3
// 하는일 : 위치를 돌려준다.
const D3DXVECTOR3* Character::getPosition(VOID)
{
	return &_vPosition;
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : 1차원 모션벡터의 포인터
// 받는값 : VOID
// 하는일 : 
// 기존에 있던 모션을 제거 하고, 모션을 다시 넣는다.
// 그리고 모션을 정지시키고 값을 초기화 한다.
VOID Character::setMotion(const MotionVec* vMotion)
{
	clearMotion();
	_vMotion = *vMotion;
	_bMot_play = FALSE;
	_uMot_num = 0;
	_fMot_cnt = .0f;


	if (_vMotion.size() >= 2)
		_fMot_time = _vMotion[_uMot_num + 1]->Time - _vMotion[_uMot_num]->Time;
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 :
// 모션재생을 시작한다.
// 모션의 개수가 1개보다 작을경우 재생이 되지 않는다.
VOID Character::beginMotion(VOID)
{
	if (_vMotion.size() <= 1)
		return;


	_bMot_play = TRUE;
	_bMot_first_play = TRUE;
	_uMot_num = 0;
	_fMot_cnt = .0f;

	_fMot_time = _vMotion[_uMot_num + 1]->Time - _vMotion[_uMot_num]->Time;
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 정지된 모션을 이어서 재생한다.
VOID Character::playMotion(VOID)
{
	_bMot_play = TRUE;
	_bMot_first_play = TRUE;
}




//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 모션을 재생을 정지한다.
VOID Character::stopMotion(VOID)
{
	_bMot_play = FALSE;
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 모션데이터를 모두 클리어한다.
VOID Character::clearMotion(VOID)
{
	// 모션제거
	INT iMot_size = _vMotion.size();

	for (INT i = 0; i<iMot_size; ++i)
		delete _vMotion[i];


	_vMotion.clear();

}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 시간을 보정하기위해 흘러간시간을 넣는다.
// 보정을했으므로 tick을 더하기 위해 _bMot_first_play를 FALSE로 넣는다.
// 애니메이션의 시간도 더해야 하나, 일단구현하지 않는다.
VOID Character::addMotionTime(FLOAT fTime)
{
	_fMot_cnt += fTime;
	_bMot_first_play = FALSE;
}




//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : Property의 포인터
// 하는일 : 능력치를 얻는다.
const Property* Character::getProperty(VOID)
{
	return &_Property;
}


//////////////////////////////////////////////////////////////////////////
// 넣는값 : Property의 포인터
// 받는값 : VOID
// 하는일 : 능력치를 설정한다.
VOID Character::setProperty(Property* pProperty)
{
	_Property = *pProperty;
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : Property의 포인터
// 받는값 : VOID
// 하는일 : Component를 추가 한다.
VOID Character::addComponent(Component* pObj)
{
	pObj->setCharacter(this);
	_listComponent.push_back(pObj);
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : Component를 모두 삭제한다.
VOID Character::clearComponent(VOID)
{
	ComponentList::iterator it;
	for (it = _listComponent.begin(); it != _listComponent.end(); ++it)
		delete *it;

	_listComponent.clear();
}


