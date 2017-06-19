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
	VOID operator=(const Character& Obj);		// =���� ������ �ǹ̰� ����.

	VOID updateAnimation(VOID);
	VOID updateMotion(VOID);



	// Character�� �⺻����
	BOOL		_bVisible;
	UINT		_uPool_number;	// ������ƮPool�� ��ȣ
	D3DXVECTOR3 _vPosition;
	BoundBoxVec	_vBoundBox;
	ComponentList _listComponent;

	// �ִϸ��̼� ����
	ImageVec2	_vImages;
	UINT		_uAni;
	BOOL		_bAni_play;
	BOOL		_bAni_first_play;

	UINT		_uImg;
	Image*		_pAni_Key;		// ���������� �̹����� �޾ƿͼ�, ª������������ ����Ѵ�.
	FLOAT		_fAni_cnt;


	// ��ǰ���
	MotionVec	_vMotion;
	BOOL		_bMot_play;
	BOOL		_bMot_first_play;

	UINT		_uMot_num;
	FLOAT		_fMot_time;		// ��ǰ� ����� �ð�����
	FLOAT		_fMot_cnt;		// ��ǽð��� ī��Ʈ


								// �ɷ�ġ
	Property	_Property;
};


///////////////////////////////////////////////////////////////
// Ŭ����  �̸� : Character
// ù����  ��¥ : 2009. 7. 5
// ������������ : 2009. 10. 17
//
// Nick : ���ڰ�
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// �ϴ��� : �̹���, �ɷ�ġ��, ĳ������ ������ �����Ѵ�.

// ���� �ʿ���� ���
// Visible
// Alive

// ��ǵ� ������Ʈ�� �����ҵ�..