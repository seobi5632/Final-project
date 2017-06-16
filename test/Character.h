#pragma once

class Character : public GameBase
{
public:
	Character();
	VOID Draw(VOID);
	const Image* getImage(VOID);
	VOID setImage(Image* pImage);
	const Property* getProperty(VOID);
	VOID setProperty(Property* pProperty);

	VOID moveLeft(VOID);
	VOID moveRight(VOID);
	VOID moveUp(VOID);
	VOID moveDown(VOID);


protected:
	Image		_Image;
	Property	_Property;
};


///////////////////////////////////////////////////////////////
// Ŭ����  �̸� : Character
// ù����  ��¥ : 2009. 7. 5
// ������������ : 2009. 7. 5
// �ۼ��� : Naver : ���ڰ�, DC : Vita500
// �ϴ��� : �̹���, �ɷ�ġ��, ĳ������ ������ �����Ѵ�.
