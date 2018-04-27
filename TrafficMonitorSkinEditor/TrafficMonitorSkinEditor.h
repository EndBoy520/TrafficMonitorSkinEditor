
// TrafficMonitorSkinEditor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Common.h"

// CTrafficMonitorSkinEditorApp: 
// �йش����ʵ�֣������ TrafficMonitorSkinEditor.cpp
//

class CTrafficMonitorSkinEditorApp : public CWinApp
{
public:
	CTrafficMonitorSkinEditorApp();

	int DPI(int pixel);
	void DPI(CRect& rect);
	void GetDPI(CWnd* pWnd);

	void SaveConfig();

private:
	void LoadConfig();

public:
	Language m_language;
	wstring m_config_path;

protected:
	int m_dpi{ 96 };


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnHelp();
};

extern CTrafficMonitorSkinEditorApp theApp;