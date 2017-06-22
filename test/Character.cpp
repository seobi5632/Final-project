#include "stdafx.h"			// �̸������ϵ����
#include "ShootingData.h"

#include "Component.h"
#include "Character.h"


//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ������ �ʱ�ȭ �Ѵ�.
Character::Character(VOID)
{
	_bVisible = TRUE;
	_uPool_number = 0;
	ZeroMemory(&_vPosition, sizeof(D3DXVECTOR3));


	// �ִϸ��̼�
	_uAni = 0;
	_bAni_play = FALSE;
	_bAni_first_play = TRUE;

	_uImg = 0;
	_pAni_Key = NULL;
	_fAni_cnt = .0f;



	// ���
	_bMot_play = FALSE;
	_bMot_first_play = TRUE;

	_uMot_num = 0;
	_fMot_time = .0f;
	_fMot_cnt = .0f;
	ZeroMemory(&_Property, sizeof(_Property));
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : Character
// �޴°� : VOID
// �ϴ��� : �����ÿ� �ʱ�ȭ �����ʰ� �����Ѵ�.
Character::Character(const Character* Obj)
{
	*this = *Obj;
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : Pool�� ��ȣ
// �ϴ��� : Pool�� ��ȣ�� �Ѱ��ش�.
UINT Character::getObjectPool_number()
{
	return _uPool_number;
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : Pool�� ��ȣ
// �޴°� : VOID
// �ϴ��� : Pool�� ��ȣ�� �����Ѵ�.
VOID Character::setObjectPool_number(UINT uNumber)
{
	_uPool_number = uNumber;
}




//////////////////////////////////////////////////////////////////////////
// �ִ°� : Character
// �޴°� : VOID
// �ϴ��� : 
// Character�� �浹�ڽ�
// �ִϸ��̼��� �̹�����, �׸��� ���̹����� �浹�ڽ�
// ��ǵ��� �����Ѵ�.
VOID Character::operator=(const Character& Obj)
{
	// ����Character�̿ܿ� Ŭ������ �����, �װ��� _pReceiver�� ����(or����)�ؾ� �Ѵ�.
	_pReceiver = Obj._pReceiver;

	_bVisible = Obj._bVisible;
	_uPool_number = Obj._uPool_number;
	_vPosition = Obj._vPosition;

	UINT uSize = 0;
	uSize = Obj._vBoundBox.size();
	_vBoundBox.resize(uSize);
	for (UINT i = 0; i<uSize; ++i)
		_vBoundBox[i] = new BoundingBox(*Obj._vBoundBox[i]);




	// �ִϸ��̼�
	uSize = Obj._vImages.size();
	_vImages.resize(uSize);
	UINT uImageSize = 0;
	Image* pImage = NULL;
	UINT uBoundSize = 0;


	// �̹��� �׷�
	for (UINT i = 0; i<uSize; ++i)
	{
		uImageSize = Obj._vImages[i].size();
		_vImages[i].resize(uImageSize);

		// �̹���
		for (UINT k = 0; k<uImageSize; ++k)
		{
			pImage = new Image;
			memcpy(pImage, Obj._vImages[i][k], sizeof(Image_data));
			_vImages[i][k] = pImage;

			uBoundSize = Obj._vImages[i][k]->BoundBox.size();
			_vImages[i][k]->BoundBox.resize(uBoundSize);

			// �̹��� ���� ����ִ� �浹�ڽ�
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





	// ���
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
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// Character�� ��ɵ��� ������Ʈ�Ѵ�.
// �̵��Ұ��� ��� �ϰ� �ִϸ��̼��� ������Ʈ�ؾ��Ѵ�.
// �׸���, ������Ʈ���� ������Ʈ �Ѵ�.
VOID Character::Update(VOID)
{
	updateMotion();
	updateAnimation();


	// Component������Ʈ
	ComponentList::iterator it;
	for (it = _listComponent.begin(); it != _listComponent.end(); ++it)
		(*it)->Update();
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// �̹����� �����ؼ� ����Ѵ�.
// �̹����� ����ð��� ������ �������� �ѱ��.
// ���������� ����ϸ�, ó���� ����Ѵ�.
// ����ð��� �̸����� =>  0 < sec
// ����ù��° ����̸�, t�� ������ �ʴ´�.
// �ִϸ��̼��� ���¿� ���� �޽����� ������.
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


		// �ִϸ��̼��� ������ ���������, �޽����� ������, ó����������Ѵ�.
		if (_uImg >= _vImages[_uAni].size())
		{
			Event(ANI_End);
			_uImg = 0;
		}

		_pAni_Key = _vImages[_uAni][_uImg];
	}

}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// ù����� �����ϸ�, ��ġ�� �����ϰ�, ���������Ӻ��� �ð��� ���� �����Ѵ�.
//
// ����� ������ġ�� ������ġ�� �ð��������� ����ؼ�, ������ġ�� �����.
// D3DXVec3Lerp( &vOut, &v1, &v2, 1.0f);
// ������ġ, ������ġ, ������ġ, �ð������� 100%���������� ��
// �ð��� ��� ��������, ���帶���� (���-1)���� �����.
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
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// Character�� �̹����� �׸���.
// _bBound_visible���� TRUE�̸�, �浹������ �׸���.
// �ִϸ��̼� Ű�������� ������ ��������, ���⿡ ª�� ���������� Ȱ���Ѵ�.
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
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// Character�� ��� ���ҽ� �ڿ��� �������ش�.
// �������� ���Ž����� Character���������� �ƴ϶�, ���Ҷ� �Ҽ��ִ�.
VOID Character::Release(VOID)
{
	// �̹��� ����
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



	// �������
	clearMotion();




	// �浹�ڽ�����
	INT iBound_size = _vBoundBox.size();

	for (INT i = 0; i<iBound_size; ++i)
	{
		delete _vBoundBox[i];
	}
	_vBoundBox.clear();



	// Component����
	clearComponent();
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : BOOL
// �޴°� : VOID
// �ϴ��� : Character�� ���̱� ���θ� �����Ѵ�.
VOID Character::setVisible(BOOL bVisible)
{
	_bVisible = bVisible;
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : BOOL
// �ϴ��� : Character�� ���̱� ���θ� ��´�.
BOOL Character::getVisible(VOID)
{
	return _bVisible;
}


////////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : Image�� ������
// �ϴ��� : �̹����� ������ ��´�.
const Image* Character::getImage(VOID)
{
	return _vImages[_uAni][_uImg];
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : 2���� �̹��� ������ ������
// �޴°� : VOID
// �ϴ��� : 
// �ִϸ��̼��� �ִ´�.
// Ű�������� �̶� �ٽù޴´�.
VOID Character::setAnimation(const ImageVec2* vImage)
{
	_vImages = *vImage;

	_pAni_Key = _vImages[0][0];
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// �ִϸ��̼��� �����Ѵ�.
// �ִϸ� �����ϸ�, �ִ���������� �ʱ�ȭ �ȴ�.
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
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// �̹����� ����Ѵ�.
// �ִϸ��̼��� �ϳ��� ���ų�
// �ִϸ��̼��� �̹����� 1������ ������� ����� ���� �ʴ´�.
// ó�� ���� ����� �Ѵ�.
VOID Character::playAni(VOID)
{
	if (_vImages.empty() == TRUE)
		return;

	if (_vImages[_uAni].size() <= 1
		|| _bAni_play == TRUE)
		return;


	_bAni_play = TRUE;
	_bAni_first_play = TRUE;

	// �ִϸ��̼� �ʱ�ȭ
	_uImg = 0;
	_pAni_Key = _vImages[_uAni][_uImg];
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : �̹��� ����� �����.
VOID Character::stopAni(VOID)
{
	_bAni_play = FALSE;
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : const BoundBoxVec*
// �޴°� : VOID
// �ϴ��� : �浹�ڽ��� ���������ͷ� �ִ´�.
VOID Character::setBoundingBox(const BoundBoxVec* vBox)
{
	_vBoundBox = *vBox;
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : BoundBoxVec&
// �ϴ��� : 
// �̹����κ��� �浹�ڽ����͸� ��´�.
// ���� Character�� �浹�ڽ��� ������, �װ��� �Ѱ�����.
// ����, �̹����� �ϳ��� ���µ�, ���Լ��� ȣ���ϸ�, ���α׷��� ��������.
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
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : �������� �̵�
VOID Character::moveLeft(VOID)
{
	movePosition(&D3DXVECTOR3(-_Property.Speed * t, .0f, .0f));
}

//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ���������� �̵�
VOID Character::moveRight(VOID)
{
	movePosition(&D3DXVECTOR3(_Property.Speed * t, .0f, .0f));
}

//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ���� �̵�
VOID Character::moveUp(VOID)
{
	movePosition(&D3DXVECTOR3(.0f, -_Property.Speed * t, .0f));
}

//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : �Ʒ��� �̵�
VOID Character::moveDown(VOID)
{
	movePosition(&D3DXVECTOR3(.0f, _Property.Speed * t, .0f));

}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// ��ġ�� �̵��Ѵ�.
// �̹����� ��� ��ǥ�� ����ġ��ŭ�̵���Ų��.
// �浹�ڽ��� �����ǥ�� ����ġ��ŭ �̵���Ų��.
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
// �ִ°� : D3DXVECTOR3*
// �޴°� : VOID
// �ϴ��� : 
// ��ġ�� �����Ѵ�.
// ���� ��ġ���� �󸶸�ŭ �̵��ߴ����� ���ؼ� �̵���Ų��.
VOID Character::setPosition(const D3DXVECTOR3* vPos)
{
	D3DXVECTOR3 vMove;
	vMove = *vPos - _vPosition;

	movePosition(&vMove);
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : const D3DXVECTOR3
// �ϴ��� : ��ġ�� �����ش�.
const D3DXVECTOR3* Character::getPosition(VOID)
{
	return &_vPosition;
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : 1���� ��Ǻ����� ������
// �޴°� : VOID
// �ϴ��� : 
// ������ �ִ� ����� ���� �ϰ�, ����� �ٽ� �ִ´�.
// �׸��� ����� ������Ű�� ���� �ʱ�ȭ �Ѵ�.
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
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� :
// �������� �����Ѵ�.
// ����� ������ 1������ ������� ����� ���� �ʴ´�.
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
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ������ ����� �̾ ����Ѵ�.
VOID Character::playMotion(VOID)
{
	_bMot_play = TRUE;
	_bMot_first_play = TRUE;
}




//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ����� ����� �����Ѵ�.
VOID Character::stopMotion(VOID)
{
	_bMot_play = FALSE;
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ��ǵ����͸� ��� Ŭ�����Ѵ�.
VOID Character::clearMotion(VOID)
{
	// �������
	INT iMot_size = _vMotion.size();

	for (INT i = 0; i<iMot_size; ++i)
		delete _vMotion[i];


	_vMotion.clear();

}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : �ð��� �����ϱ����� �귯���ð��� �ִ´�.
// �����������Ƿ� tick�� ���ϱ� ���� _bMot_first_play�� FALSE�� �ִ´�.
// �ִϸ��̼��� �ð��� ���ؾ� �ϳ�, �ϴܱ������� �ʴ´�.
VOID Character::addMotionTime(FLOAT fTime)
{
	_fMot_cnt += fTime;
	_bMot_first_play = FALSE;
}




//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : Property�� ������
// �ϴ��� : �ɷ�ġ�� ��´�.
const Property* Character::getProperty(VOID)
{
	return &_Property;
}


//////////////////////////////////////////////////////////////////////////
// �ִ°� : Property�� ������
// �޴°� : VOID
// �ϴ��� : �ɷ�ġ�� �����Ѵ�.
VOID Character::setProperty(Property* pProperty)
{
	_Property = *pProperty;
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : Property�� ������
// �޴°� : VOID
// �ϴ��� : Component�� �߰� �Ѵ�.
VOID Character::addComponent(Component* pObj)
{
	pObj->setCharacter(this);
	_listComponent.push_back(pObj);
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : Component�� ��� �����Ѵ�.
VOID Character::clearComponent(VOID)
{
	ComponentList::iterator it;
	for (it = _listComponent.begin(); it != _listComponent.end(); ++it)
		delete *it;

	_listComponent.clear();
}


