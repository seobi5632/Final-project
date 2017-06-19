#pragma once

class Character : public GameBase
{
public:
	Character();
	Character(const Character* Obj);
	UINT getObjectPool_number();
	VOID setObjectPool_number(UINT uNumber);
	Character* Copy(VOID);
	VOID Update(VOID);
	VOID Draw(VOID);
	VOID Release(VOID);
	BOOL getVisible(VOID);
	VOID setVisible(BOOL bVisible);

	const Image* getImage(VOID);
	VOID setAnimation(const ImageVec2* vImage);
	VOID selAnimation(UINT uNum);
	VOID playAni(VOID);
	VOID stopAni(VOID);
	VOID setBoundingBox(const BoundBoxVec* vBox);
	BoundBoxVec& getBoundingBox(VOID);

	VOID moveLeft(VOID);
	VOID moveRight(VOID);
	VOID moveUp(VOID);
	VOID moveDown(VOID);
	VOID movePosition(const D3DXVECTOR3* vPos);
	VOID setPosition(const D3DXVECTOR3* vPos);
	const D3DXVECTOR3* getPosition(VOID);

	VOID setMotion(const MotionVec* vMotion);
	VOID beginMotion(VOID);
	VOID playMotion(VOID);
	VOID stopMotion(VOID);
	VOID clearMotion(VOID);
	VOID addMotionTime(FLOAT fTime);

	const Property* getProperty(VOID);
	VOID setProperty(Property* pProperty);

	VOID addComponent(Component* pObj);
	VOID clearComponent(VOID);
protected:
	VOID operator=(const Character& Obj);		// =에는 가상이 의미가 없다.

	VOID updateAnimation(VOID);
	VOID updateMotion(VOID);



	// Character의 기본정보
	BOOL		_bVisible;
	UINT		_uPool_number;	// 오브젝트Pool의 번호
	D3DXVECTOR3 _vPosition;
	BoundBoxVec	_vBoundBox;
	ComponentList _listComponent;

	// 애니메이션 관련
	ImageVec2	_vImages;
	UINT		_uAni;
	BOOL		_bAni_play;
	BOOL		_bAni_first_play;

	UINT		_uImg;
	Image*		_pAni_Key;		// 현프레임의 이미지를 받아와서, 짧은변수명으로 사용한다.
	FLOAT		_fAni_cnt;


	// 모션관련
	MotionVec	_vMotion;
	BOOL		_bMot_play;
	BOOL		_bMot_first_play;

	UINT		_uMot_num;
	FLOAT		_fMot_time;		// 모션과 모션의 시간간격
	FLOAT		_fMot_cnt;		// 모션시간을 카운트


								// 능력치
	Property	_Property;
};


///////////////////////////////////////////////////////////////
// 클래스  이름 : Character
// 첫만든  날짜 : 2009. 7. 5
// 마지막갱신일 : 2009. 10. 17
//
// Nick : 날자고도
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// 하는일 : 이미지, 능력치등, 캐릭터의 정보를 관리한다.

// 현재 필요없는 기능
// Visible
// Alive

// 모션도 컴포넌트로 빼야할듯..