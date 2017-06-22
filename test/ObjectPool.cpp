#include "stdafx.h"			// �̸������ϵ����
#include "ShootingData.h"

#include "Character.h"
#include "ObjectPool.h"




// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : ��� ���ҽ��� �ʱ�ȭ�Ѵ�.
ObjectPool::~ObjectPool()
{
	// ���� ������Ʈ ����Ʈ���� �����ǹǷ� Clear�� ������� �ʴ´�.
	// ������ ����� �����Ƿ� ����
	// Clear();
}






// �ִ°� : ������Ʈ�� ��ȣ
// �޴°� : ������Ʈ�� ������
// �ϴ��� : 
// ������ �ν��Ͻ��� �����Ѵ�.
// ����, ������ �����ϸ� ������ 2��� �����.
Character* ObjectPool::New(UINT uObject)
{
	// ������ ������ 2��� �Ѵ�.
	if (_vSpare[uObject].empty() == TRUE)
	{
		UINT uSize = _vUse[uObject].size();

		for (UINT i = 0; i<uSize; ++i)
			_vSpare[uObject].push_back(m_vOriginal[uObject]->Copy());

	}



	// �Ѱ��ش�. 
	Character* pObject = NULL;
	pObject = *_vSpare[uObject].begin();
	_vSpare[uObject].pop_front();
	_vUse[uObject].push_back(pObject);





	// Ǯ�� �����Ǿ����� �ʱ�ȭ �Լ�ȣ��??
	// �ʱ�ȭ �Լ�ȣ��
	return pObject;
}




// �ִ°� : ������ ������Ʈ�� ������
// �޴°� : VOID
// �ϴ��� : 
// ������Ʈ�� �޾Ƽ� ���п� �ִ´�.
// ���� �������� �ɷ�������, ������ ����Ʈ�� �ִ´�.
VOID ObjectPool::Delete(Character* pObject)
{
	// Ǯ�� ������ �ʱ�ȭ �Լ�ȣ��??


	UINT uObject = pObject->getObjectPool_number();


	 //���� ���� ������
	if (_vlockDelete[uObject] == TRUE)
	{
		_vDelete[uObject].push_back(pObject);
		return;
	}



	// ���п� �ִ´�.
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


// �ִ°� : ��� ������ ������Ʈ�� ��ȣ
// �޴°� : VOID
// �ϴ��� : 
// ��� ������Ʈ�� ����(�������� �̵�)�Ѵ�.
// �ʿ�� �����Ŵ°͵� �����Ѵ�.
VOID ObjectPool::DeleteAll(UINT uObject)
{

	CharacterList::iterator it;
	for (it = _vUse[uObject].begin(); it != _vUse[uObject].end(); ++it)
		_vSpare[uObject].push_back(*it);

	_vUse[uObject].clear();

}




// �ִ°� : ������Ʈ�� ��ȣ
// �޴°� : VOID
// �ϴ��� : 
// �ٷ� �������� ���ϵ��� ���� �Ǵ�.
VOID ObjectPool::lockDelete(UINT uObject)
{
	_vlockDelete[uObject] = TRUE;
}



// �ִ°� : ������Ʈ�� ��ȣ
// �޴°� : VOID
// �ϴ��� : 
// ���� Ǭ��.
// ������ ����Ʈ�� ������Ʈ�� ������ �����Ѵ�(���п� �ִ´�.)
VOID ObjectPool::unlockDelete(UINT uObject)
{
	// ���� ����
	_vlockDelete[uObject] = FALSE;


	if (_vDelete.empty() == TRUE)
		return;


	// ���� ����Ͽ� �ִ����� ����(���п��ִ´�.) �Ѵ�.
	CharacterList::iterator it;
	for (it = _vDelete[uObject].begin(); it != _vDelete[uObject].end(); ++it)
		Delete(*it);


	_vDelete[uObject].clear();
}



// �ִ°� : ������Ʈ�� ��ȣ
// �޴°� : Ǯ�� ����
// �ϴ��� : ������ƮǮ�� ������ �޴´�.
Character* ObjectPool::getOriginal(UINT uObject)
{
	return m_vOriginal[uObject];
}



// �ִ°� : ������Ʈ�� ��ȣ
// �޴°� : CharacterList*
// �ϴ��� : New�� ������(����ϰ� �ִ�) ������Ʈ�� ����Ʈ�� �Ѱ��ش�.
CharacterList* ObjectPool::getUseList(UINT uObject)
{
	return &_vUse[uObject];

}


// �ִ°� : ������Ʈ�� ��ȣ
// �޴°� : CharacterList*
// �ϴ��� : ������ ������Ʈ�� ����Ʈ�� �ѱ��.
CharacterList* ObjectPool::getSpareList(UINT uObject)
{
	return &_vSpare[uObject];
}





// �ִ°� : ������Ʈ ������
// �޴°� : VOID
// �ϴ��� : 
// ���ο� ������Ʈ������ �־ Pool�� �����.
// ���͸� �ϳ��� �߰��Ѵ�
VOID ObjectPool::pushPool(Character* pObject, UINT uSize)
{
	// ������Ʈ�� ��ȣ�� �����Ѵ�.
	m_vOriginal.push_back(pObject);
	UINT uObject = m_vOriginal.size() - 1;
	m_vOriginal[uObject]->setObjectPool_number(uObject);


	// �� ���͸��� �����ִ� ����Ʈ������ �����.
	CharacterList listTemp;
	_vUse.push_back(listTemp);
	_vDelete.push_back(listTemp);
	_vSpare.push_back(listTemp);

	BOOL bTemp = FALSE;
	_vlockDelete.push_back(bTemp);



	// ������Ʈ ������ �����.
	Character* pNodeTemp = NULL;
	for (UINT i = 0; i<uSize; ++i)
	{
		pNodeTemp = m_vOriginal[uObject]->Copy();
		_vSpare[uObject].push_back(pNodeTemp);
	}
}



// �ִ°� : ������Ʈ�� ������
// �޴°� : VOID
// �ϴ��� : ������Ʈ Pool�� �����Ѵ�. ����ȽἭ �̱���
VOID ObjectPool::popPool(Character* pObject)
{
	// �̱���, ������ ������ ����...��.
}



// �ִ°� : Pool������ ����ũ�⸦ �ִ´�.
// �޴°� : VOID
// �ϴ��� : Pool���Ͱ��� ����
VOID ObjectPool::reservePool(UINT uPoolsize)
{
	m_vOriginal.reserve(uPoolsize);

	_vUse.reserve(uPoolsize);
	_vDelete.reserve(uPoolsize);
	_vSpare.reserve(uPoolsize);

	_vlockDelete.reserve(uPoolsize);
}



// ���徵���̾�� �ּ�ȭ, �ʿ��ϸ� Ǭ��.
// �ִ°� : Pool��ȣ, Pool�� ������Ʈ����
// �޴°� : VOID
// �ϴ��� : 
// ������Ʈ�� ������ �����Ѵ�.
// ������ Ű����� �ִ�.
//VOID ObjectPool::resizeObject(UINT uPool, UINT uObject_size)
//{
//	if ( uObject_size <= _vUse[uPool].size() + _vSpare[uPool].size() )
//		return;
//
//
//	// �� �ֱ�
//	UINT uSize = uObject_size - _vUse[uPool].size() + _vSpare[uPool].size();
//	for ( UINT i=0; i<uSize; ++i )
//		_vSpare[uPool].push_back( m_vOriginal[uPool]->Copy() );
//
//}



// �ִ°� : VOID
// �޴°� : VOID
// �ϴ��� : 
// ��� Pool�� �׾ȿ� ���� ������Ʈ�� �����Ѵ�.
// ��а� ���� ������Ʈ����Ʈ���� �ڵ������ǹǷ� �̰� ������� �ʴ´�.
VOID ObjectPool::Clear(VOID)
{
	UINT uSize = 0;

	// ���������� ����
	uSize = m_vOriginal.size();
	for (UINT i = 0; i<uSize; ++i)
	{
		m_vOriginal[i]->Release();
		delete m_vOriginal[i];
	}

	m_vOriginal.clear();




	// Pool������ ����
	CharacterList::iterator it;


	// Use����
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


	// Delete����
	_vDelete.clear();


	// Spare����
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




	// Lock���� ����
	_vlockDelete.clear();
}




