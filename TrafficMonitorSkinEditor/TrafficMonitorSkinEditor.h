
// TrafficMonitorSkinEditor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTrafficMonitorSkinEditorApp: 
// �йش����ʵ�֣������ TrafficMonitorSkinEditor.cpp
//

class CTrafficMonitorSkinEditorApp : public CWinApp
{
public:
	CTrafficMonitorSkinEditorApp();

	int DPI(int pixel);
	void GetDPI(CWnd* pWnd);

protected:
	int m_dpi{ 96 };


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTrafficMonitorSkinEditorApp theApp;