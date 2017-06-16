#include <Windows.h>
#include <d3dx9.h>
#include "ShootingData.h"
#include "GameBase.h"

#include "Character.h"


Character::Character(VOID)
{

}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : Character�� �̹����� �׸���.
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::Draw(VOID)
{
	if (_Image.Visible == TRUE)
	{
		_pSprite->Draw(_Image.Texture, &_Image.Source, &_Image.Center, &_Image.Position, 0xffffffff);
	}

}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �̹����� ������ ��´�.
// �ִ°� : VOID
// �޴°� : Image�� ������
const Image* Character::getImage(VOID)
{
	return &_Image;
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �̹����� ������ �����Ѵ�.
// �ִ°� : Image�� ������
// �޴°� : VOID
VOID Character::setImage(Image* pImage)
{
	_Image = *pImage;
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
		_Image.Visible = FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �������� �̵�
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::moveLeft(VOID)
{
	_Image.Position.x -= _Property.Speed * t;
}

//////////////////////////////////////////////////////////////////////////
// �ϴ��� : ���������� �̵�
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::moveRight(VOID)
{
	_Image.Position.x += _Property.Speed * t;
}

//////////////////////////////////////////////////////////////////////////
// �ϴ��� : ���� �̵�
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::moveUp(VOID)
{
	_Image.Position.y -= _Property.Speed * t;
}

//////////////////////////////////////////////////////////////////////////
// �ϴ��� : �Ʒ��� �̵�
// �ִ°� : VOID
// �޴°� : VOID
VOID Character::moveDown(VOID)
{
	_Image.Position.y += _Property.Speed * t;
}
