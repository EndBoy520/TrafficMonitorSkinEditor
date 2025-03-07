﻿#pragma once
// 这是一个带微调按钮的Edit控件，在CEdit右侧附加一个微调按钮，请预留空间
// CSpinEdit

#define WM_SPIN_EDIT_POS_CHANGED (WM_USER + 101)

class CSpinEdit : public CEdit
{
    DECLARE_DYNAMIC(CSpinEdit)

public:
    CSpinEdit();
    virtual ~CSpinEdit();

    void SetRange(short lower, short upper, short step = 1);        // 设置文本框中的数值范围
    void SetValue(int value);                       //设置文本框中的数值
    int GetValue();                                 //获取文本框中的数值

protected:
    CSpinButtonCtrl m_spin;                         //微调按钮控件
    int m_step{ 1 };
    int m_spin_width{};

    DECLARE_MESSAGE_MAP()
    virtual void PreSubclassWindow();
protected:
    afx_msg LRESULT OnTabletQuerysystemgesturestatus(WPARAM wParam, LPARAM lParam);
public:
    void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnEnable(BOOL bEnable);
    afx_msg void OnSize(UINT nType, int cx, int cy);
};


