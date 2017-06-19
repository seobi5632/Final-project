#pragma once
class Component : public GameBase
{
public:
	Component();
	virtual VOID Update(VOID);

	VOID setCharacter(Character* pObj);
protected:
	Character* _pCharacter;
};


///////////////////////////////////////////////////////////////
// 클래스  이름 : Component
// 첫만든  날짜 : 2009. 9. 26(토)
// 마지막갱신일 : 2009. 9. 26(토)
//
// Nick : 날자고도
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// 하는일 : Character에 추가적으로 들어갈 콤포넌트의 기본함수를 선언한다.
