
// TrafficMonitorSkinEditorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Common.h"
#include "SkinEditorHelper.h"
#include "ColorStatic.h"
#include "DrawScrollView.h"
#include "SpinEdit.h"

// CTrafficMonitorSkinEditorDlg �Ի���
class CTrafficMonitorSkinEditorDlg : public CDialog
{
// ����
public:
	CTrafficMonitorSkinEditorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TRAFFICMONITORSKINEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CDrawScrollView* m_view;	//Ԥ������ͼ��
	CPoint m_start_point;		//Ԥ��������ʼλ��

	SkinData m_skin_data;
	wstring m_path;

	//�ؼ�����
	CColorStatic m_text_color_static;
	CEdit m_skin_author_edit;
	CButton m_assign_text_chk;
	CEdit m_up_string_edit;
	CEdit m_down_string_edit;
	CEdit m_cpu_string_edit;
	CEdit m_memory_string_edit;
	CButton m_no_item_text_chk;
	CSpinEdit m_text_height_edit;
	CSpinEdit m_window_width_edit;
	CSpinEdit m_window_heitht_edit;
	CSpinEdit m_up_x_edit;
	CSpinEdit m_up_y_edit;
	CSpinEdit m_up_width_edit;
	CButton m_no_upload_chk;
	CSpinEdit m_down_x_edit;
	CSpinEdit m_down_y_edit;
	CSpinEdit m_down_width_edit;
	CButton m_no_download_chk;
	CSpinEdit m_cpu_x_edit;
	CSpinEdit m_cpu_y_edit;
	CSpinEdit m_cpu_width_edit;
	CButton m_no_cpu_chk;
	CSpinEdit m_memory_x_edit;
	CSpinEdit m_memory_y_edit;
	CSpinEdit m_memory_width_edit;
	CButton m_no_memory_chk;

	void DrawPreview();
	void LayoutDataToUI(bool small_window);

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnStaticClicked(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnBnClickedButton1();
};
