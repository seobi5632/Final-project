#include "stdafx.h"			// 미리컴파일된헤더
#include "ShootingData.h"

#include "Component.h"





Component::Component()
{
	_pCharacter = NULL;
}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 함수재정의를 위해서 존재한다.
VOID Component::Update()
{

}



//////////////////////////////////////////////////////////////////////////
// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 부모가 되는 Character의 포인터를 받는다.
VOID Component::setCharacter(Character* pObj)
{
	_pCharacter = pObj;
}