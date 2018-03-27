
// TrafficMonitorSkinEditorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitorSkinEditor.h"
#include "TrafficMonitorSkinEditorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTrafficMonitorSkinEditorDlg �Ի���



CTrafficMonitorSkinEditorDlg::CTrafficMonitorSkinEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrafficMonitorSkinEditorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrafficMonitorSkinEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_COLOR_STATIC, m_text_color_static);
	DDX_Control(pDX, IDC_SKIN_AUTHOR_EDIT, m_skin_author_edit);
	DDX_Control(pDX, IDC_ASSIGN_TEXT_CHECK, m_assign_text_chk);
	DDX_Control(pDX, IDC_UPLOAD_EDIT, m_up_string_edit);
	DDX_Control(pDX, IDC_DOWNLOAD_EDIT, m_down_string_edit);
	DDX_Control(pDX, IDC_CPU_EDIT, m_cpu_string_edit);
	DDX_Control(pDX, IDC_MEMORY_EDIT, m_memory_string_edit);
	DDX_Control(pDX, IDC_NO_ITEM_TEXT_CHECK, m_no_item_text_chk);
	DDX_Control(pDX, IDC_TEXT_HEIGHT_EDIT, m_text_height_edit);
	DDX_Control(pDX, IDC_WND_WIDTH_EDIT, m_window_width_edit);
	DDX_Control(pDX, IDC_WND_HEIGHT_EDIT, m_window_heitht_edit);
	DDX_Control(pDX, IDC_UP_X_EDIT, m_up_x_edit);
	DDX_Control(pDX, IDC_UP_Y_EDIT, m_up_y_edit);
	DDX_Control(pDX, IDC_UP_WIDTH_EDIT, m_up_width_edit);
	DDX_Control(pDX, IDC_NO_UPLOAD_CHECK, m_no_upload_chk);
	DDX_Control(pDX, IDC_DOWN_X_EDIT, m_down_x_edit);
	DDX_Control(pDX, IDC_DOWN_Y_EDIT, m_down_y_edit);
	DDX_Control(pDX, IDC_DOWN_WIDTH_EDIT, m_down_width_edit);
	DDX_Control(pDX, IDC_CNO_DOWNLOAD_HECK, m_no_download_chk);
	DDX_Control(pDX, IDC_CPU_X_EDIT, m_cpu_x_edit);
	DDX_Control(pDX, IDC_CPU_Y_EDIT, m_cpu_y_edit);
	DDX_Control(pDX, IDC_CPU_WIDTH_EDIT, m_cpu_width_edit);
	DDX_Control(pDX, IDC_NO_CPU_CHECK, m_no_cpu_chk);
	DDX_Control(pDX, IDC_MEMORY_X_EDIT, m_memory_x_edit);
	DDX_Control(pDX, IDC_MEMORY_Y_EDIT, m_memory_y_edit);
	DDX_Control(pDX, IDC_MEMORY_WIDTH_EDIT, m_memory_width_edit);
	DDX_Control(pDX, IDC_NO_MEMORY_CHECK, m_no_memory_chk);
	DDX_Control(pDX, IDC_PREVIEW_WIDTH_EDIT, m_preview_width_edit);
	DDX_Control(pDX, IDC_PREVIEW_HEIGHT_EDIT, m_preview_height_edit);
	DDX_Control(pDX, IDC_PREVIEW_X_S_EDIT, m_preview_x_s_edit);
	DDX_Control(pDX, IDC_PREVIEW_Y_S_EDIT, m_preview_y_s_edit);
	DDX_Control(pDX, IDC_PREVIEW_X_L_EDIT, m_preview_x_l_edit);
	DDX_Control(pDX, IDC_PREVIEW_Y_L_EDIT, m_preview_y_l_edit);
}

BEGIN_MESSAGE_MAP(CTrafficMonitorSkinEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_STATIC_CLICKED, &CTrafficMonitorSkinEditorDlg::OnStaticClicked)
	ON_COMMAND(ID_APP_ABOUT, &CTrafficMonitorSkinEditorDlg::OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, &CTrafficMonitorSkinEditorDlg::OnFileOpen)
	//ON_BN_CLICKED(IDC_BUTTON1, &CTrafficMonitorSkinEditorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_LARGE_WINDOW_RADIO, &CTrafficMonitorSkinEditorDlg::OnBnClickedLargeWindowRadio)
	ON_BN_CLICKED(IDC_SMALL_WINDOW_RADIO, &CTrafficMonitorSkinEditorDlg::OnBnClickedSmallWindowRadio)
	ON_BN_CLICKED(IDC_ASSIGN_TEXT_CHECK, &CTrafficMonitorSkinEditorDlg::OnBnClickedAssignTextCheck)
END_MESSAGE_MAP()


// CTrafficMonitorSkinEditorDlg ��Ϣ�������

void CTrafficMonitorSkinEditorDlg::DrawPreview()
{
	m_view->SetSize(m_skin_data.preview_width, m_skin_data.preview_height);
	m_view->Invalidate();
}

void CTrafficMonitorSkinEditorDlg::LayoutDataToUI(bool small_window)
{
	m_text_height_edit.SetValue(m_skin_data.text_height);
	m_no_item_text_chk.SetCheck(m_skin_data.no_text);
	if (small_window)
	{
		m_window_width_edit.SetValue(m_skin_data.width_s);
		m_window_heitht_edit.SetValue(m_skin_data.height_s);

		m_up_x_edit.SetValue(m_skin_data.up_x_s);
		m_up_y_edit.SetValue(m_skin_data.up_y_s);
		m_up_width_edit.SetValue(m_skin_data.up_width_s);
		m_no_upload_chk.SetCheck(!m_skin_data.show_up_s);
		m_down_x_edit.SetValue(m_skin_data.down_x_s);
		m_down_y_edit.SetValue(m_skin_data.down_y_s);
		m_down_width_edit.SetValue(m_skin_data.down_width_s);
		m_no_download_chk.SetCheck(!m_skin_data.show_down_s);
		m_cpu_x_edit.SetValue(m_skin_data.cpu_x_s);
		m_cpu_y_edit.SetValue(m_skin_data.cpu_y_s);
		m_cpu_width_edit.SetValue(m_skin_data.cpu_width_s);
		m_no_cpu_chk.SetCheck(!m_skin_data.show_cpu_s);
		m_memory_x_edit.SetValue(m_skin_data.memory_x_s);
		m_memory_y_edit.SetValue(m_skin_data.memory_y_s);
		m_memory_width_edit.SetValue(m_skin_data.memory_width_s);
		m_no_memory_chk.SetCheck(!m_skin_data.show_memory_s);
	}
	else
	{
		m_window_width_edit.SetValue(m_skin_data.width_l);
		m_window_heitht_edit.SetValue(m_skin_data.height_l);

		m_up_x_edit.SetValue(m_skin_data.up_x_l);
		m_up_y_edit.SetValue(m_skin_data.up_y_l);
		m_up_width_edit.SetValue(m_skin_data.up_width_l);
		m_no_upload_chk.SetCheck(!m_skin_data.show_up_l);
		m_down_x_edit.SetValue(m_skin_data.down_x_l);
		m_down_y_edit.SetValue(m_skin_data.down_y_l);
		m_down_width_edit.SetValue(m_skin_data.down_width_l);
		m_no_download_chk.SetCheck(!m_skin_data.show_down_l);
		m_cpu_x_edit.SetValue(m_skin_data.cpu_x_l);
		m_cpu_y_edit.SetValue(m_skin_data.cpu_y_l);
		m_cpu_width_edit.SetValue(m_skin_data.cpu_width_l);
		m_no_cpu_chk.SetCheck(!m_skin_data.show_cpu_l);
		m_memory_x_edit.SetValue(m_skin_data.memory_x_l);
		m_memory_y_edit.SetValue(m_skin_data.memory_y_l);
		m_memory_width_edit.SetValue(m_skin_data.memory_width_l);
		m_no_memory_chk.SetCheck(!m_skin_data.show_memory_l);
	}
}

void CTrafficMonitorSkinEditorDlg::AllToUI()
{
	m_text_color_static.SetFillColor(m_skin_data.text_color);
	m_skin_author_edit.SetWindowTextW(m_skin_data.skin_author.c_str());
	m_assign_text_chk.SetCheck(m_asign_item_text);

	m_up_string_edit.SetWindowTextW(m_skin_data.up_string.c_str());
	m_down_string_edit.SetWindowTextW(m_skin_data.down_string.c_str());
	m_cpu_string_edit.SetWindowTextW(m_skin_data.cpu_string.c_str());
	m_memory_string_edit.SetWindowTextW(m_skin_data.memory_string.c_str());

	m_up_string_edit.EnableWindow(m_asign_item_text);
	m_down_string_edit.EnableWindow(m_asign_item_text);
	m_cpu_string_edit.EnableWindow(m_asign_item_text);
	m_memory_string_edit.EnableWindow(m_asign_item_text);

	LayoutDataToUI(m_edit_small_window);
}

BOOL CTrafficMonitorSkinEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	theApp.GetDPI(this);

	//m_text_color_static.SetFillColor(RGB(255, 192, 0));
	m_text_color_static.SetLinkCursor(true);

	//��ʼ��Ԥ����ͼ
	m_view = (CDrawScrollView*)RUNTIME_CLASS(CDrawScrollView)->CreateObject();
	CRect rect;
	GetDlgItem(IDC_PREVIEW_GROUP_STATIC)->GetWindowRect(rect);		//��ȡ��Ԥ���� group box ��λ��
	ScreenToClient(&rect);
	m_start_point.x = rect.left + theApp.DPI(12);
	m_start_point.y = rect.top + theApp.DPI(110);
	CRect scroll_view_rect{ rect };
	scroll_view_rect.DeflateRect(theApp.DPI(12), theApp.DPI(12));
	scroll_view_rect.top = m_start_point.y;
	m_view->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, scroll_view_rect, this, 3000);
	m_view->InitialUpdate();
	m_view->SetSkinData(&m_skin_data);
	m_view->ShowWindow(SW_SHOW);

	//
	((CButton*)GetDlgItem(IDC_LARGE_WINDOW_RADIO))->SetCheck(TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTrafficMonitorSkinEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTrafficMonitorSkinEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTrafficMonitorSkinEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



afx_msg LRESULT CTrafficMonitorSkinEditorDlg::OnStaticClicked(WPARAM wParam, LPARAM lParam)
{
	CWnd* pWnd = (CWnd*)wParam;
	if (pWnd == &m_text_color_static)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK)
		{
			m_skin_data.text_color = dlg.GetColor();
			m_text_color_static.SetFillColor(m_skin_data.text_color);
		}
	}
	return 0;
}


void CTrafficMonitorSkinEditorDlg::OnAppAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CTrafficMonitorSkinEditorDlg::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFolderPickerDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_path = dlg.GetPathName();
		//����Ƥ������
		CSkinEditorHelper skin_editor;
		skin_editor.SetSkinPath(m_path);
		m_skin_data = skin_editor.LoadSkin();
		AllToUI();
	}
}


//void CTrafficMonitorSkinEditorDlg::OnBnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	int v = m_text_height_edit.GetValue();
//}


void CTrafficMonitorSkinEditorDlg::OnBnClickedLargeWindowRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit_small_window = false;
	LayoutDataToUI(m_edit_small_window);
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedSmallWindowRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit_small_window = true;
	LayoutDataToUI(m_edit_small_window);
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedAssignTextCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_asign_item_text = (m_assign_text_chk.GetCheck() != 0);

	m_up_string_edit.EnableWindow(m_asign_item_text);
	m_down_string_edit.EnableWindow(m_asign_item_text);
	m_cpu_string_edit.EnableWindow(m_asign_item_text);
	m_memory_string_edit.EnableWindow(m_asign_item_text);
}
