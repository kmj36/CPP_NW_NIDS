
// FireBat.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CFireBatApp:
// �� Ŭ������ ������ ���ؼ��� FireBat.cpp�� �����Ͻʽÿ�.
//

class CFireBatApp : public CWinAppEx
{
public:
	CFireBatApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CFireBatApp theApp;