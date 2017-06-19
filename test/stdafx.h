
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#define WIN32_LEAN_AND_MEAN			  // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define _CRT_SECURE_NO_WARNINGS		  // �����Լ� �̻���� ����
#define _CRT_NON_CONFORMING_SWPRINTFS // swprintf �����Լ� �̻���� ���� 


// Windows ��� ����:
#include <windows.h>

// C�� ��Ÿ�� ��� �����Դϴ�.
#include <Mmsystem.h>			// timeGetTime


// STL
#define _SECURE_SCL 0	
#define _SECURE_SCL_THROWS 1
#define _HAS_ITERATOR_DEBUGGING 0
#include <vector>
#include <list>


// DX9
#include <d3dx9.h>



// ���� �ؿ� ���ߵ�
// Visual Leak Detector
// #include "vld.h"