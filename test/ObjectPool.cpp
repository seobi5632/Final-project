#include "stdafx.h"			// 미리컴파일된헤더
#include "ShootingData.h"

#include "Character.h"
#include "ObjectPool.h"




// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 모든 리소스를 초기화한다.
ObjectPool::~ObjectPool()
{
	// 씬의 오브젝트 리스트에서 삭제되므로 Clear를 사용하지 않는다.
	// 하지만 현재는 없으므로 삭제
	// Clear();
}






// 넣는값 : 오브젝트의 번호
// 받는값 : 오브젝트의 포인터
// 하는일 : 
// 여분의 인스턴스를 리턴한다.
// 만약, 여분이 부족하면 여분을 2배로 만든다.
Character* ObjectPool::New(UINT uObject)
{
	// 여분이 없으면 2배로 한다.
	if (_vSpare[uObject].empty() == TRUE)
	{
		UINT uSize = _vUse[uObject].size();

		for (UINT i = 0; i<uSize; ++i)
			_vSpare[uObject].push_back(m_vOriginal[uObject]->Copy());

	}



	// 넘겨준다. 
	Character* pObject = NULL;
	pObject = *_vSpare[uObject].begin();
	_vSpare[uObject].pop_front();
	_vUse[uObject].push_back(pObject);





	// 풀로 생성되었을때 초기화 함수호출??
	// 초기화 함수호출
	return pObject;
}




// 넣는값 : 삭제할 오브젝트의 포인터
// 받는값 : VOID
// 하는일 : 
// 오브젝트를 받아서 여분에 넣는다.
// 만약 삭제락이 걸려있으면, 삭제할 리스트에 넣는다.
VOID ObjectPool::Delete(Character* pObject)
{
	// 풀로 삭제시 초기화 함수호출??


	UINT uObject = pObject->getObjectPool_number();


	 //삭제 락이 있을때
	if (_vlockDelete[uObject] == TRUE)
	{
		_vDelete[uObject].push_back(pObject);
		return;
	}



	// 여분에 넣는다.
	CharacterList::iterator it;
	for (it = _vUse[uObject].begin(); it != _vUse[uObject].end(); ++it)
	{
		if (pObject == *it)
		{
			_vSpare[uObject].push_back(pObject);
			_vUse[uObject].erase(it);
			break;
		}
	}

}


// 넣는값 : 모두 삭제할 오브젝트의 번호
// 받는값 : VOID
// 하는일 : 
// 모든 오브젝트를 삭제(여분으로 이동)한다.
// 필요시 락을거는것도 검토한다.
VOID ObjectPool::DeleteAll(UINT uObject)
{

	CharacterList::iterator it;
	for (it = _vUse[uObject].begin(); it != _vUse[uObject].end(); ++it)
		_vSpare[uObject].push_back(*it);

	_vUse[uObject].clear();

}




// 넣는값 : 오브젝트의 번호
// 받는값 : VOID
// 하는일 : 
// 바로 삭제하지 못하도록 락을 건다.
VOID ObjectPool::lockDelete(UINT uObject)
{
	_vlockDelete[uObject] = TRUE;
}



// 넣는값 : 오브젝트의 번호
// 받는값 : VOID
// 하는일 : 
// 락을 푼다.
// 삭제할 리스트에 오브젝트가 있으면 삭제한다(여분에 넣는다.)
VOID ObjectPool::unlockDelete(UINT uObject)
{
	// 락을 해제
	_vlockDelete[uObject] = FALSE;


	if (_vDelete.empty() == TRUE)
		return;


	// 삭제 대기목록에 있던것을 삭제(여분에넣는다.) 한다.
	CharacterList::iterator it;
	for (it = _vDelete[uObject].begin(); it != _vDelete[uObject].end(); ++it)
		Delete(*it);


	_vDelete[uObject].clear();
}



// 넣는값 : 오브젝트의 번호
// 받는값 : 풀의 원본
// 하는일 : 오브젝트풀의 원본을 받는다.
Character* ObjectPool::getOriginal(UINT uObject)
{
	return m_vOriginal[uObject];
}



// 넣는값 : 오브젝트의 번호
// 받는값 : CharacterList*
// 하는일 : New로 생성된(사용하고 있는) 오브젝트의 리스트를 넘겨준다.
CharacterList* ObjectPool::getUseList(UINT uObject)
{
	return &_vUse[uObject];

}


// 넣는값 : 오브젝트의 번호
// 받는값 : CharacterList*
// 하는일 : 여분의 오브젝트의 리스트를 넘긴다.
CharacterList* ObjectPool::getSpareList(UINT uObject)
{
	return &_vSpare[uObject];
}





// 넣는값 : 오브젝트 포인터
// 받는값 : VOID
// 하는일 : 
// 새로운 오브젝트원본을 넣어서 Pool을 만든다.
// 벡터를 하나씩 추가한다
VOID ObjectPool::pushPool(Character* pObject, UINT uSize)
{
	// 오브젝트의 번호를 세팅한다.
	m_vOriginal.push_back(pObject);
	UINT uObject = m_vOriginal.size() - 1;
	m_vOriginal[uObject]->setObjectPool_number(uObject);


	// 각 벡터마다 들어갈수있는 리스트공간을 만든다.
	CharacterList listTemp;
	_vUse.push_back(listTemp);
	_vDelete.push_back(listTemp);
	_vSpare.push_back(listTemp);

	BOOL bTemp = FALSE;
	_vlockDelete.push_back(bTemp);



	// 오브젝트 여분을 만든다.
	Character* pNodeTemp = NULL;
	for (UINT i = 0; i<uSize; ++i)
	{
		pNodeTemp = m_vOriginal[uObject]->Copy();
		_vSpare[uObject].push_back(pNodeTemp);
	}
}



// 넣는값 : 오브젝트의 포인터
// 받는값 : VOID
// 하는일 : 오브젝트 Pool을 삭제한다. 당장안써서 미구현
VOID ObjectPool::popPool(Character* pObject)
{
	// 미구현, 쓸일이 없을거 같아...서.
}



// 넣는값 : Pool벡터의 공간크기를 넣는다.
// 받는값 : VOID
// 하는일 : Pool벡터공간 예약
VOID ObjectPool::reservePool(UINT uPoolsize)
{
	m_vOriginal.reserve(uPoolsize);

	_vUse.reserve(uPoolsize);
	_vDelete.reserve(uPoolsize);
	_vSpare.reserve(uPoolsize);

	_vlockDelete.reserve(uPoolsize);
}



// 당장쓸일이없어서 주석화, 필요하면 푼다.
// 넣는값 : Pool번호, Pool의 오브젝트개수
// 받는값 : VOID
// 하는일 : 
// 오브젝트의 개수를 설정한다.
// 개수를 키울수만 있다.
//VOID ObjectPool::resizeObject(UINT uPool, UINT uObject_size)
//{
//	if ( uObject_size <= _vUse[uPool].size() + _vSpare[uPool].size() )
//		return;
//
//
//	// 더 넣기
//	UINT uSize = uObject_size - _vUse[uPool].size() + _vSpare[uPool].size();
//	for ( UINT i=0; i<uSize; ++i )
//		_vSpare[uPool].push_back( m_vOriginal[uPool]->Copy() );
//
//}



// 넣는값 : VOID
// 받는값 : VOID
// 하는일 : 
// 모든 Pool과 그안에 들은 오브젝트를 삭제한다.
// 당분간 씬의 오브젝트리스트에서 자동삭제되므로 이건 사용하지 않는다.
VOID ObjectPool::Clear(VOID)
{
	UINT uSize = 0;

	// 원본데이터 삭제
	uSize = m_vOriginal.size();
	for (UINT i = 0; i<uSize; ++i)
	{
		m_vOriginal[i]->Release();
		delete m_vOriginal[i];
	}

	m_vOriginal.clear();




	// Pool데이터 삭제
	CharacterList::iterator it;


	// Use삭제
	uSize = _vUse.size();
	for (UINT i = 0; i<uSize; ++i)
	{
		for (it = _vUse[i].begin(); it != _vUse[i].end(); ++it)
		{
			(*it)->Release();
			delete *it;
		}

	}
	_vUse.clear();


	// Delete삭제
	_vDelete.clear();


	// Spare삭제
	uSize = _vSpare.size();
	for (UINT i = 0; i<uSize; ++i)
	{
		for (it = _vSpare[i].begin(); it != _vSpare[i].end(); ++it)
		{
			(*it)->Release();
			delete *it;
		}

	}
	_vSpare.clear();




	// Lock정보 삭제
	_vlockDelete.clear();
}




