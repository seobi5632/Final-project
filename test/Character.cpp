#include <Windows.h>
#include <d3dx9.h>
#include "ShootingData.h"
#include "GameBase.h"

#include "Character.h"


Character::Character(VOID)
{

}


//////////////////////////////////////////////////////////////////////////
// 하는일 : Character의 이미지를 그린다.
// 넣는값 : VOID
// 받는값 : VOID
VOID Character::Draw(VOID)
{
	if (_Image.Visible == TRUE)
	{
		_pSprite->Draw(_Image.Texture, &_Image.Source, &_Image.Center, &_Image.Position, 0xffffffff);
	}

}


//////////////////////////////////////////////////////////////////////////
// 하는일 : 이미지의 정보를 얻는다.
// 넣는값 : VOID
// 받는값 : Image의 포인터
const Image* Character::getImage(VOID)
{
	return &_Image;
}


//////////////////////////////////////////////////////////////////////////
// 하는일 : 이미지의 정보를 수정한다.
// 넣는값 : Image의 포인터
// 받는값 : VOID
VOID Character::setImage(Image* pImage)
{
	_Image = *pImage;
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
		_Image.Visible = FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
// 하는일 : 왼쪽으로 이동
// 넣는값 : VOID
// 받는값 : VOID
VOID Character::moveLeft(VOID)
{
	_Image.Position.x -= _Property.Speed * t;
}

//////////////////////////////////////////////////////////////////////////
// 하는일 : 오른쪽으로 이동
// 넣는값 : VOID
// 받는값 : VOID
VOID Character::moveRight(VOID)
{
	_Image.Position.x += _Property.Speed * t;
}

//////////////////////////////////////////////////////////////////////////
// 하는일 : 위로 이동
// 넣는값 : VOID
// 받는값 : VOID
VOID Character::moveUp(VOID)
{
	_Image.Position.y -= _Property.Speed * t;
}

//////////////////////////////////////////////////////////////////////////
// 하는일 : 아래로 이동
// 넣는값 : VOID
// 받는값 : VOID
VOID Character::moveDown(VOID)
{
	_Image.Position.y += _Property.Speed * t;
}
