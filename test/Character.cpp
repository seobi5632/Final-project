#include "stdafx.h"			// �̸������ϵ����
#include "ShootingData.h"
#include "GameBase.h"

#include "Character.h"


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : ������ �ʱ�ȭ �Ѵ�.
// �ִ°� : VOID
// �޴°� : VOID
Character::Character(VOID)
{
	_bVisible = TRUE;
	_uAni_num = 0;

	_bFistplay = TRUE;
	_bAniplay = TRUE;
	_fAnisec = .0f;
	_uImage_num = 0;

	ZeroMemory(&_Property, sizeof(_Property));
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : 
// �̹����� �����ؼ� ����Ѵ�.
// �̹����� ����ð��� ������ �������� �ѱ��.
// ���������� ����ϸ�, ó���� ����Ѵ�.
// ����ð��� �̸����� =>  0 < sec
// ����ù��° ����̸�, t�� ������ �ʴ´�.
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::Update(VOID)
{
	if (_bAniplay == FALSE
		|| _vImages[_uAni_num].size() <= 1)
		return;


	if (_bFistplay == TRUE)
	{
		_bFistplay = FALSE;
		return;
	}


	_fAnisec += t;

	while (_fAnisec > _vImages[_uAni_num][_uImage_num]->Sec)
	{
		_fAnisec -= _vImages[_uAni_num][_uImage_num]->Sec;
		_uImage_num++;


		if (_uImage_num >= _vImages[_uAni_num].size())
		{
			_uImage_num = 0;
		}
	}

}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : Character�� �̹����� �׸���.
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::Draw(VOID)
{
	if (_bVisible == FALSE
		|| _vImages.empty() == TRUE)
		return;



	_pSprite->Draw(_vImages[_uAni_num][_uImage_num]->Texture,
		&_vImages[_uAni_num][_uImage_num]->Source,
		&_vImages[_uAni_num][_uImage_num]->Center,
		&_vImages[_uAni_num][_uImage_num]->Position,
		0xffffffff);
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : Character�� ���̱� ���θ� �����Ѵ�.
// �ִ°� : BOOL
// �޴°� : VOID
VOID Character::setVisible(BOOL bVisible)
{
	_bVisible = bVisible;
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : Character�� ���̱� ���θ� ��´�.
// �ִ°� : VOID
// �޴°� : BOOL
BOOL Character::getVisible(VOID)
{
	return _bVisible;
}


////////////////////////////////////////////////////////////////////////////
// �ϴ��� : �̹����� ������ ��´�.
// �ִ°� : VOID
// �޴°� : Image�� ������
const Image* Character::getImage(VOID)
{
	return _vImages[_uAni_num][_uImage_num];
}


////////////////////////////////////////////////////////////////////////////
// �ϴ��� : Character�� ����̹�����ġ�� �����Ѵ�.
// �ִ°� : Image�� ��ġ
// �޴°� : VOID
VOID Character::setPosition(D3DXVECTOR3* vPos)
{
	INT iAniSize = _vImages.size();
	INT iImage_size = 0;

	for (INT i = 0; i<iAniSize; ++i)
	{
		iImage_size = _vImages[i].size();
		for (INT k = 0; k<iImage_size; ++k)
		{
			_vImages[i][k]->Position = *vPos;
		}
	}



	//for (INT i=0; i<iAniSize; ++i)
	//{
	//	_vImages[i]->Position = *vPos;
	//}
}


////////////////////////////////////////////////////////////////////////////
//// �ϴ��� : �̹����� ������ �����Ѵ�.
//// �ִ°� : Image�� ������
//// �޴°� : VOID
//VOID Character::setImage(Image* pImage)
//{
//	_Image = *pImage;
//}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� :
// �̹����� ������, ���޸𸮿��� �����Ͽ� �����Ѵ�.
// �ִ°� : Image�� ������
// �޴°� : VOID
//VOID Character::addImage(Image* pImage)
//{
//	Image* pTemp = new Image;
//	*pTemp = *pImage;
//	_vImages.push_back(pTemp);
//}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �ִϸ��̼��� �ִ´�.
// �ִ°� : 2���� �̹��� ������ ������
// �޴°� : VOID
VOID Character::setAnimation(ImageVec2* vImage)
{
	_vImages = *vImage;
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : 
// �ִϸ��̼��� �����Ѵ�.
// �ִϸ� �����ϸ�, �ִ���������� �ʱ�ȭ �ȴ�.
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::selAnimation(UINT iNum)
{
	if (iNum == _uAni_num
		|| iNum >= _vImages.size())
		return;


	_uAni_num = iNum;

	_bFistplay = TRUE;
	_fAnisec = .0f;
	_uImage_num = 0;
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �̹����� ����Ѵ�.
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::playAni(VOID)
{
	_bFistplay = TRUE;
	_bAniplay = TRUE;
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �̹��� ����� �����.
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::stopAni(VOID)
{
	_bAniplay = FALSE;
}

//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �ɷ�ġ�� ��´�.
// �ִ°� : VOID
// �޴°� : Property�� ������
const Property* Character::getProperty(VOID)
{
	return &_Property;
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �ɷ�ġ�� �����Ѵ�.
// �ִ°� : Property�� ������
// �޴°� : VOID
VOID Character::setProperty(Property* pProperty)
{
	_Property = *pProperty;

	if (_Property.HP <= .0f)
	{
		_bVisible = FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �������� �̵�
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::moveLeft(VOID)
{
	INT iAniSize = _vImages.size();
	INT iImage_size = 0;

	for (INT i = 0; i<iAniSize; ++i)
	{
		iImage_size = _vImages[i].size();
		for (INT k = 0; k<iImage_size; ++k)
		{
			_vImages[i][k]->Position.x -= _Property.Speed * t;
		}
	}




	//INT iSize = _vImages.size();

	//for (INT i=0; i<iSize; ++i)
	//{
	//	_vImages[i]->Position.x -= _Property.Speed * t;
	//}


}

//////////////////////////////////////////////////////////////////////////
// �ϴ��� : ���������� �̵�
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::moveRight(VOID)
{
	INT iAniSize = _vImages.size();
	INT iImage_size = 0;

	for (INT i = 0; i<iAniSize; ++i)
	{
		iImage_size = _vImages[i].size();
		for (INT k = 0; k<iImage_size; ++k)
		{
			_vImages[i][k]->Position.x += _Property.Speed * t;
		}
	}




	//INT iSize = _vImages.size();

	//for (INT i=0; i<iSize; ++i)
	//{
	//	_vImages[i]->Position.x += _Property.Speed * t;
	//}


}

//////////////////////////////////////////////////////////////////////////
// �ϴ��� : ���� �̵�
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::moveUp(VOID)
{
	INT iAniSize = _vImages.size();
	INT iImage_size = 0;

	for (INT i = 0; i<iAniSize; ++i)
	{
		iImage_size = _vImages[i].size();
		for (INT k = 0; k<iImage_size; ++k)
		{
			_vImages[i][k]->Position.y -= _Property.Speed * t;
		}
	}



	//INT iSize = _vImages.size();

	//for (INT i=0; i<iSize; ++i)
	//{
	//	_vImages[i]->Position.y -= _Property.Speed * t;
	//}



}

//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �Ʒ��� �̵�
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::moveDown(VOID)
{
	INT iAniSize = _vImages.size();
	INT iImage_size = 0;

	for (INT i = 0; i<iAniSize; ++i)
	{
		iImage_size = _vImages[i].size();
		for (INT k = 0; k<iImage_size; ++k)
		{
			_vImages[i][k]->Position.y += _Property.Speed * t;
		}
	}



	//INT iSize = _vImages.size();

	//for (INT i=0; i<iSize; ++i)
	//{
	//	_vImages[i]->Position.y += _Property.Speed * t;
	//}


}
