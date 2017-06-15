#include "stdafx.h"			// 미리컴파일된헤더
#include "ShootingData.h"
#include "GameBase.h"

#include "Character.h"


//////////////////////////////////////////////////////////////////////////
// 하는일 : 변수를 초기화 한다.
// 넣는값 : VOID
// 받는값 : VOID
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
// 하는일 : 
// 이미지를 연속해서 재생한다.
// 이미지의 재생시간이 끝나면 다음으로 넘긴다.
// 마지막까지 재생하면, 처음을 재생한다.
// 재생시간은 미만까지 =>  0 < sec
// 만약첫번째 재생이면, t를 더하지 않는다.
// 넣는값 : VOID
// 받는값 : VOID
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
// 하는일 : Character의 이미지를 그린다.
// 넣는값 : VOID
// 받는값 : VOID
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
// 하는일 : Character의 보이기 여부를 결정한다.
// 넣는값 : BOOL
// 받는값 : VOID
VOID Character::setVisible(BOOL bVisible)
{
	_bVisible = bVisible;
}


//////////////////////////////////////////////////////////////////////////
// 하는일 : Character의 보이기 여부를 얻는다.
// 넣는값 : VOID
// 받는값 : BOOL
BOOL Character::getVisible(VOID)
{
	return _bVisible;
}


////////////////////////////////////////////////////////////////////////////
// 하는일 : 이미지의 정보를 얻는다.
// 넣는값 : VOID
// 받는값 : Image의 포인터
const Image* Character::getImage(VOID)
{
	return _vImages[_uAni_num][_uImage_num];
}


////////////////////////////////////////////////////////////////////////////
// 하는일 : Character의 모든이미지위치를 수정한다.
// 넣는값 : Image의 위치
// 받는값 : VOID
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
//// 하는일 : 이미지의 정보를 수정한다.
//// 넣는값 : Image의 포인터
//// 받는값 : VOID
//VOID Character::setImage(Image* pImage)
//{
//	_Image = *pImage;
//}


//////////////////////////////////////////////////////////////////////////
// 하는일 :
// 이미지를 넣으면, 힙메모리에서 생성하여 복사한다.
// 넣는값 : Image의 포인터
// 받는값 : VOID
//VOID Character::addImage(Image* pImage)
//{
//	Image* pTemp = new Image;
//	*pTemp = *pImage;
//	_vImages.push_back(pTemp);
//}


//////////////////////////////////////////////////////////////////////////
// 하는일 : 애니메이션을 넣는다.
// 넣는값 : 2차원 이미지 벡터의 포인터
// 받는값 : VOID
VOID Character::setAnimation(ImageVec2* vImage)
{
	_vImages = *vImage;
}


//////////////////////////////////////////////////////////////////////////
// 하는일 : 
// 애니메이션을 선택한다.
// 애니를 선택하면, 애니재생값들이 초기화 된다.
// 넣는값 : VOID
// 받는값 : VOID
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
// 하는일 : 이미지를 재생한다.
// 넣는값 : VOID
// 받는값 : VOID
VOID Character::playAni(VOID)
{
	_bFistplay = TRUE;
	_bAniplay = TRUE;
}


//////////////////////////////////////////////////////////////////////////
// 하는일 : 이미지 재생을 멈춘다.
// 넣는값 : VOID
// 받는값 : VOID
VOID Character::stopAni(VOID)
{
	_bAniplay = FALSE;
}

//////////////////////////////////////////////////////////////////////////
// 하는일 : 능력치를 얻는다.
// 넣는값 : VOID
// 받는값 : Property의 포인터
const Property* Character::getProperty(VOID)
{
	return &_Property;
}


//////////////////////////////////////////////////////////////////////////
// 하는일 : 능력치를 설정한다.
// 넣는값 : Property의 포인터
// 받는값 : VOID
VOID Character::setProperty(Property* pProperty)
{
	_Property = *pProperty;

	if (_Property.HP <= .0f)
	{
		_bVisible = FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
// 하는일 : 왼쪽으로 이동
// 넣는값 : VOID
// 받는값 : VOID
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
// 하는일 : 오른쪽으로 이동
// 넣는값 : VOID
// 받는값 : VOID
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
// 하는일 : 위로 이동
// 넣는값 : VOID
// 받는값 : VOID
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
// 하는일 : 아래로 이동
// 넣는값 : VOID
// 받는값 : VOID
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
