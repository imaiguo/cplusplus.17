
// PrintCard.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPrintCardApp:
// �йش����ʵ�֣������ PrintCard.cpp
//

class CPrintCardApp : public CWinApp
{
public:
	CPrintCardApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPrintCardApp theApp;