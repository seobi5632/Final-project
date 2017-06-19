#pragma once

class ObjectPool
{
public:
	~ObjectPool();

	Character* New(UINT uObject);
	VOID Delete(Character* pObject);
	VOID DeleteAll(UINT uObject);
	VOID lockDelete(UINT uObject);
	VOID unlockDelete(UINT uObject);

	Character* getOriginal(UINT uObject);
	CharacterList* getUseList(UINT uObject);
	CharacterList* getSpareList(UINT uObject);
	VOID pushPool(Character* pObject, UINT uSize);
	VOID popPool(Character* pObject);

	VOID reservePool(UINT uPool);
	VOID Clear(VOID);
protected:

	//VOID resizeObject(UINT uPool, UINT uObject_size);// Pool의 오브젝트개수, 키울수만 있다.	// 잘되면삭제
	CharacterVec m_vOriginal;

	PoolVec		 _vUse;
	PoolVec		 _vDelete;
	PoolVec		 _vSpare;

	BOOLVec		 _vlockDelete;
};


///////////////////////////////////////////////////////////////
// 첫만든  날짜 : 2009. 9. 24
// 마지막갱신일 : 2009. 9. 26(토)
// 클래스  이름 : ObjectPool
// 하는일 : 오브젝트들의 풀을 만들어서 메모리를 관리한다.

// ObjectPool에서 모든 오브젝트 풀을 관리
// Pool의 개수선택
// 입력시 풀로 사용할 오브젝트 개수를 입력받는다.
// 현재 사용수보다 더 많은 요청이 오면 개수를 2배로 늘린다.
// Pool은벡터, 오브젝트는 리스트사용
// define의 오브젝트번호값으로 접근
// 어떤클래스에서나 ObjectPool클래스를 참조할수있다.
// 오브젝트의 번호를 알고, 그순서대로 넣어야 한다.
// 출을 생성시 원본의 부모에 생성되는것 모두 자식으로 등록한다.
// or 풀을 생성시 다른방법으로 씬의 오브젝트리스트에 등록한다.
// delete를 할때는 보이지 않게 하고, 풀의 Delete를 호출한다.
// 최종메모리에서 삭제시에는 풀에서 삭제하지않고, 씬의 오브젝트리스트에서 삭제된다.

// 풀로 생성과 삭제시 초기화 함수? OnNew, OnDelete
// popPool미구현


