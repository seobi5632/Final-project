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
// 클래스  이름 : Character
// 첫만든  날짜 : 2009. 7. 5
// 마지막갱신일 : 2009. 7. 5
// 작성자 : Naver : 날자고도, DC : Vita500
// 하는일 : 이미지, 능력치등, 캐릭터의 정보를 관리한다.
