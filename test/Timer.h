#include "stdafx.h"
#include <windows.h>

class CTimer
{
	/**
	* 함수 포인터 타입 선언
	*/
	typedef void(*func)(void);

public:

	/**
	* 생성자, 함수포인터와 카운트다운 시간을 받는다.
	*/
	CTimer(func _f, int _milliSeconds) :f(_f), milliSeconds(_milliSeconds) {}

	/**
	* 소멸자.
	*/
	virtual ~CTimer() {}

	/**
	* run() 쓰레드를 실행한다.
	*/
	void run()
	{
		h = CreateThread(NULL, 0, ThreadFunc, this, 0, 0);
	}
private:
	/**
	* 클래스 멤버함수를 쓰레드로 돌리려면 static이어야 한다.
	* 파라미터 LPVOID p는 CTimer 인스턴스를 받게 된다.
	*/
	static DWORD CALLBACK ThreadFunc(LPVOID p)
	{
		((CTimer*)p)->counting();
		return 0;
	}

	/**
	* counting()은 while loop를 돌면서 1/1000초씩 슬립을 하고 카운트 다운을 하게된다.
	*/
	void counting()
	{
		while (1)
		{
			if (milliSeconds < 0)
				break;
			SleepEx(1, false);
			if (milliSeconds == 0)
			{
				f();
				break;
			}
			milliSeconds -= 1;
		}
	}

	/**
	* 멤버 변수들이다. 쓰레드 핸들, 함수포인터, 카운트다운 시간을 저장하고 있다.
	*/
	HANDLE h;
	func f;
	int milliSeconds;
};