
// linkus.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// ClinkusApp: 
// �йش����ʵ�֣������ linkus.cpp
//

class ClinkusApp : public CWinApp
{
public:
	ClinkusApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern ClinkusApp theApp;
