﻿
// TrafficMonitorSkinEditor.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "../CommonTools/Common.h"
#include "../CommonTools/CommonData.h"

// CTrafficMonitorSkinEditorApp:
// 有关此类的实现，请参阅 TrafficMonitorSkinEditor.cpp
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

private:
    ULONG_PTR m_gdiplusToken{};

    // 重写
public:
    virtual BOOL InitInstance();

    // 实现

    DECLARE_MESSAGE_MAP()
    afx_msg void OnHelp();
};

extern CTrafficMonitorSkinEditorApp theApp;
