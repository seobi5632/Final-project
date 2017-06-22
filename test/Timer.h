#include "stdafx.h"
#include <windows.h>

class CTimer
{
	/**
	* �Լ� ������ Ÿ�� ����
	*/
	typedef void(*func)(void);

public:

	/**
	* ������, �Լ������Ϳ� ī��Ʈ�ٿ� �ð��� �޴´�.
	*/
	CTimer(func _f, int _milliSeconds) :f(_f), milliSeconds(_milliSeconds) {}

	/**
	* �Ҹ���.
	*/
	virtual ~CTimer() {}

	/**
	* run() �����带 �����Ѵ�.
	*/
	void run()
	{
		h = CreateThread(NULL, 0, ThreadFunc, this, 0, 0);
	}
private:
	/**
	* Ŭ���� ����Լ��� ������� �������� static�̾�� �Ѵ�.
	* �Ķ���� LPVOID p�� CTimer �ν��Ͻ��� �ް� �ȴ�.
	*/
	static DWORD CALLBACK ThreadFunc(LPVOID p)
	{
		((CTimer*)p)->counting();
		return 0;
	}

	/**
	* counting()�� while loop�� ���鼭 1/1000�ʾ� ������ �ϰ� ī��Ʈ �ٿ��� �ϰԵȴ�.
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
	* ��� �������̴�. ������ �ڵ�, �Լ�������, ī��Ʈ�ٿ� �ð��� �����ϰ� �ִ�.
	*/
	HANDLE h;
	func f;
	int milliSeconds;
};