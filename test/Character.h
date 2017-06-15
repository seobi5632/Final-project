#pragma once

class Character : public GameBase
{
public:
	Character();
	VOID Update(VOID);
	VOID Draw(VOID);
	BOOL getVisible(VOID);
	VOID setVisible(BOOL bVisible);


	const Image* getImage(VOID);
	VOID setPosition(D3DXVECTOR3* vPos);
	//VOID setImage(Image* pImage);
	//VOID addImage(Image* pImage);
	VOID setAnimation(ImageVec2* vImage);
	VOID selAnimation(UINT uNum);
	VOID playAni(VOID);
	VOID stopAni(VOID);

	const Property* getProperty(VOID);
	VOID setProperty(Property* pProperty);

	VOID moveLeft(VOID);
	VOID moveRight(VOID);
	VOID moveUp(VOID);
	VOID moveDown(VOID);


protected:
	//	Image		_Image;
	BOOL		_bVisible;

	ImageVec2	_vImages;
	UINT		_uAni_num;

	BOOL		_bFistplay;
	BOOL		_bAniplay;
	FLOAT		_fAnisec;
	UINT		_uImage_num;

	Property	_Property;
};


///////////////////////////////////////////////////////////////
// 클래스  이름 : Character
// 하는일 : 이미지, 능력치등, 캐릭터의 정보를 관리한다.
// 첫만든  날짜 : 2009. 7. 5
// 마지막갱신일 : 2009. 7. 7
//
// Nick : 날자고도, Vita500
// blog : http://masque.textcube.com/
// eMail : masque79@gmail.com

