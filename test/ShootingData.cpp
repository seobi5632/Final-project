#include "stdafx.h"
#include "ShootingData.h"



//////////////////////////////////////////////////////////////////////////]
// 하는일 : MS의 메모리 풀을 사용한다
// 넣는값 : VOID
// 받는값 : LFH 사용여부의 BOOL
// 참고 

// Low-Fragmentation Heap의 사용
// 프로그램이 시작할때 한번호출해준다.
// 디버거가 연결되면(F5) 디버그 힙을 사용하므로 CTRL+F5를 눌러야 
// Low-Fragmentation Heap이 사용되고, TRUE가 리턴되는것을 알수있다.

// Low-Fragmentation Heap의 장점
// 특별히 프로그래머는 신경쓰지 않아도, 메모리풀을 사용,
// 프로그램의 질을 높일수있다.
// 메모리 단편화를 예방할수있고, 힙메모리생성, 삭제시 효율이 높아진다.
// 특히, 멀티코어 시스템에서 높은 성능향상이 있다.

// Low-Fragmentation Heap사용시 참고
// 이 함수가 호출되지 않아도, 이코드가 있으면 Win2000Pro Sp4이상의 
// OS에서만 동작하므로, Win98을 지원하려고 한다면, 주석화시켜야 한다.

// 비스타는 이함수를 호출하지 않아도 기본동작한다.
// 이 함수는 하나의 프로세스에 메모리풀을 사용함으로 멀티프로세스로 동작하려면, 수정이필요하다.
// 16K보다 작은 메모리를 할당하면, LFH에 메모리가 할당, 그이상은 기존힙에서 할당된다.
BOOL CheckLFH(VOID)
{
	// 하나의 프로세스에서만 사용시
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


	// 다수의 프로세스에서 사용시
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
