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
// Ŭ����  �̸� : Component
// ù����  ��¥ : 2009. 9. 26(��)
// ������������ : 2009. 9. 26(��)
//
// Nick : ���ڰ�
// home : http://www.masque.kr/
// eMail : masque79@gmail.com
//
// �ϴ��� : Character�� �߰������� �� ������Ʈ�� �⺻�Լ��� �����Ѵ�.
