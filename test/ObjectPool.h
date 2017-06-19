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

	//VOID resizeObject(UINT uPool, UINT uObject_size);// Pool�� ������Ʈ����, Ű����� �ִ�.	// �ߵǸ����
	CharacterVec m_vOriginal;

	PoolVec		 _vUse;
	PoolVec		 _vDelete;
	PoolVec		 _vSpare;

	BOOLVec		 _vlockDelete;
};


///////////////////////////////////////////////////////////////
// ù����  ��¥ : 2009. 9. 24
// ������������ : 2009. 9. 26(��)
// Ŭ����  �̸� : ObjectPool
// �ϴ��� : ������Ʈ���� Ǯ�� ���� �޸𸮸� �����Ѵ�.

// ObjectPool���� ��� ������Ʈ Ǯ�� ����
// Pool�� ��������
// �Է½� Ǯ�� ����� ������Ʈ ������ �Է¹޴´�.
// ���� �������� �� ���� ��û�� ���� ������ 2��� �ø���.
// Pool������, ������Ʈ�� ����Ʈ���
// define�� ������Ʈ��ȣ������ ����
// �Ŭ���������� ObjectPoolŬ������ �����Ҽ��ִ�.
// ������Ʈ�� ��ȣ�� �˰�, �׼������ �־�� �Ѵ�.
// ���� ������ ������ �θ� �����Ǵ°� ��� �ڽ����� ����Ѵ�.
// or Ǯ�� ������ �ٸ�������� ���� ������Ʈ����Ʈ�� ����Ѵ�.
// delete�� �Ҷ��� ������ �ʰ� �ϰ�, Ǯ�� Delete�� ȣ���Ѵ�.
// �����޸𸮿��� �����ÿ��� Ǯ���� ���������ʰ�, ���� ������Ʈ����Ʈ���� �����ȴ�.

// Ǯ�� ������ ������ �ʱ�ȭ �Լ�? OnNew, OnDelete
// popPool�̱���


