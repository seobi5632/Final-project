#include "stdafx.h"
#include "ShootingData.h"



//////////////////////////////////////////////////////////////////////////]
// �ϴ��� : MS�� �޸� Ǯ�� ����Ѵ�
// �ִ°� : VOID
// �޴°� : LFH ��뿩���� BOOL
// ���� 

// Low-Fragmentation Heap�� ���
// ���α׷��� �����Ҷ� �ѹ�ȣ�����ش�.
// ����Ű� ����Ǹ�(F5) ����� ���� ����ϹǷ� CTRL+F5�� ������ 
// Low-Fragmentation Heap�� ���ǰ�, TRUE�� ���ϵǴ°��� �˼��ִ�.

// Low-Fragmentation Heap�� ����
// Ư���� ���α׷��Ӵ� �Ű澲�� �ʾƵ�, �޸�Ǯ�� ���,
// ���α׷��� ���� ���ϼ��ִ�.
// �޸� ����ȭ�� �����Ҽ��ְ�, ���޸𸮻���, ������ ȿ���� ��������.
// Ư��, ��Ƽ�ھ� �ý��ۿ��� ���� ��������� �ִ�.

// Low-Fragmentation Heap���� ����
// �� �Լ��� ȣ����� �ʾƵ�, ���ڵ尡 ������ Win2000Pro Sp4�̻��� 
// OS������ �����ϹǷ�, Win98�� �����Ϸ��� �Ѵٸ�, �ּ�ȭ���Ѿ� �Ѵ�.

// ��Ÿ�� ���Լ��� ȣ������ �ʾƵ� �⺻�����Ѵ�.
// �� �Լ��� �ϳ��� ���μ����� �޸�Ǯ�� ��������� ��Ƽ���μ����� �����Ϸ���, �������ʿ��ϴ�.
// 16K���� ���� �޸𸮸� �Ҵ��ϸ�, LFH�� �޸𸮰� �Ҵ�, ���̻��� ���������� �Ҵ�ȴ�.
BOOL CheckLFH(VOID)
{
	// �ϳ��� ���μ��������� ����
	ULONG  HeapFragValue = 2;

	if (HeapSetInformation(GetProcessHeap(),
		HeapCompatibilityInformation,
		&HeapFragValue,
		sizeof(HeapFragValue))
		)
	{
		return TRUE;
	}
	return FALSE;


	// �ټ��� ���μ������� ����
	//HANDLE hHeap[1025];
	//UINT uEA = GetProcessHeaps(1024, hHeap);

	//for (UINT i=0; i<uEA; ++i)
	//{
	//	ULONG  HeapFragValue = 2;

	//	HeapSetInformation(hHeap[i],
	//		HeapCompatibilityInformation,
	//		&HeapFragValue,
	//		sizeof(HeapFragValue) );
	//}

}
