#include "stdafx.h"			// �̸������ϵ����
#include "ShootingData.h"

#include "Component.h"





Component::Component()
{
	_pCharacter = NULL;
}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : �Լ������Ǹ� ���ؼ� �����Ѵ�.
VOID Component::Update()
{

}



//////////////////////////////////////////////////////////////////////////
// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : �θ� �Ǵ� Character�� �����͸� �޴´�.
VOID Component::setCharacter(Character* pObj)
{
	_pCharacter = pObj;
}