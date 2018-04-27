
// TrafficMonitorSkinEditorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Common.h"
#include "SkinEditorHelper.h"
#include "ColorStatic.h"
#include "DrawScrollView.h"
#include "SpinEdit.h"
#include "MainWndColorDlg.h"

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

	SkinData m_skin_data;
	wstring m_path;
	bool m_edit_small_window{ false };
	bool m_asign_item_text{ false };
	bool m_asing_font{ false };
	bool m_show_item_outline{ true };
	CImage m_background_s;
	CImage m_background_l;
	CFont m_font;

	bool m_modified{ false };
	bool m_spin_clicked{ false };

	//�ؼ�����
	CColorStatic m_text_color_static;
	CEdit m_skin_author_edit;
	CButton m_assign_text_chk;
	CEdit m_up_string_edit;
	CEdit m_down_string_edit;
	CEdit m_cpu_string_edit;
	CEdit m_memory_string_edit;
	CButton m_assign_font_chk;
	CButton m_specify_each_item_color_chk;
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
	CComboBox m_up_align_combo;
	CComboBox m_down_align_combo;
	CComboBox m_cpu_align_combo;
	CComboBox m_memory_align_combo;

	CSpinEdit m_preview_width_edit;
	CSpinEdit m_preview_height_edit;
	CSpinEdit m_preview_x_s_edit;
	CSpinEdit m_preview_y_s_edit;
	CSpinEdit m_preview_x_l_edit;
	CSpinEdit m_preview_y_l_edit;

	void DrawPreview();
	void LayoutDataToUI(bool small_window);
	void AllToUI();
	void LoadBackImage(const wstring& path, bool small_image);		//���뱳��ͼ��pathΪƤ������·����small_imageָ������С����ͼ���Ǵ󱳾�ͼ
	void LoadSkin(const wstring& path);		//����Ƥ����pathΪƤ������·��
	void SetTitle();
	void Modified();	//�иĶ�ʱ�Ĵ���
	void IniAlignComboBox(CComboBox& combo);	//Ϊ�����뷽ʽ�������б�ؼ�����ַ���
	void SetFontText();		//��������༭���е��ı�
	void SetViewFont();		//����Ԥ��ͼ�е�����
	void SetTextColorPreview();		//�����ı���ɫ�ؼ��е�Ԥ����ɫ

	//���ÿؼ������úͽ���
	void EnableTextControl(bool enable);
	void EnableFontControl(bool enable);
	void EnableUpControl(bool enable);
	void EnableDownControl(bool enable);
	void EnableCpuControl(bool enable);
	void EnableMemoryControl(bool enable);
	void SetItemControlEnable();

	bool SaveSkin(const wstring& path);
	bool _OnFileSave();
	bool _OnFileSaveAs();
	bool SaveInquiry();		//ѯ���û��Ƿ񱣴棬���ѡ���ˡ��ǡ��򷵻�true
	void _OnImportBackImage(bool small_image);		//���뱳��ͼ

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
	//afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeSkinAuthorEdit();
	afx_msg void OnBnClickedLargeWindowRadio();
	afx_msg void OnBnClickedSmallWindowRadio();
	afx_msg void OnBnClickedAssignTextCheck();
	afx_msg void OnEnChangeUploadEdit();
	afx_msg void OnEnChangeDownloadEdit();
	afx_msg void OnEnChangeCpuEdit();
	afx_msg void OnEnChangeMemoryEdit();
	afx_msg void OnEnChangePreviewWidthEdit();
	afx_msg void OnEnChangePreviewHeightEdit();
	afx_msg void OnEnChangePreviewXSEdit();
	afx_msg void OnEnChangePreviewYSEdit();
	afx_msg void OnEnChangePreviewXLEdit();
	afx_msg void OnEnChangePreviewYLEdit();
	afx_msg void OnEnChangeTextHeightEdit();
	afx_msg void OnBnClickedNoItemTextCheck();
	afx_msg void OnEnChangeWndWidthEdit();
	afx_msg void OnEnChangeWndHeightEdit();
	afx_msg void OnEnChangeUpXEdit();
	afx_msg void OnEnChangeUpYEdit();
	afx_msg void OnEnChangeUpWidthEdit();
	afx_msg void OnEnChangeDownXEdit();
	afx_msg void OnEnChangeDownYEdit();
	afx_msg void OnEnChangeDownWidthEdit();
	afx_msg void OnEnChangeCpuXEdit();
	afx_msg void OnEnChangeCpuYEdit();
	afx_msg void OnEnChangeCpuWidthEdit();
	afx_msg void OnEnChangeMemoryXEdit();
	afx_msg void OnEnChangeMemoryYEdit();
	afx_msg void OnEnChangeMemoryWidthEdit();
	afx_msg void OnBnClickedNoUploadCheck();
	afx_msg void OnBnClickedCnoDownloadHeck();
	afx_msg void OnBnClickedNoCpuCheck();
	afx_msg void OnBnClickedNoMemoryCheck();
	afx_msg void OnDeltaposSpin(NMHDR *pNMHDR, LRESULT *pResult); afx_msg void OnFileNew();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnClose();
	afx_msg void OnImportLargeBackImage();
	afx_msg void OnImportSmallBackImage();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedShowItemOutlineCheck();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedAssignFontCheck();
	afx_msg void OnBnClickedSetFontButton();
	afx_msg void OnBnClickedSpecifyEachItemColorCheck();
	afx_msg void OnLanguageFollowingSystem();
	afx_msg void OnLanguageEnglish();
	afx_msg void OnLanguageSimplifiedChinese();
	afx_msg void OnInitMenu(CMenu* pMenu);
};
