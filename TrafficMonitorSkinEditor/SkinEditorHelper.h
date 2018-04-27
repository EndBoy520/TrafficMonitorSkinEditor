#pragma once
#include "IniHelper.h"
#include "Common.h"

//���ڲ�������
struct SkinData
{
	//Ƥ������
	COLORREF text_colors[MAIN_WND_COLOR_NUM]{};		//������ɫ���ֱ�Ϊ���ϴ����������ء�����CPU�������ڴ桱����ɫ��
	bool specify_each_item_color;		//�Ƿ�ָ��ÿ����Ŀ����ɫ
	wstring skin_author;
	wstring up_string;
	wstring down_string;
	wstring cpu_string;
	wstring memory_string;
	FontInfo font;		//����

	//��������
	int text_height;	//�ı�����ĸ߶�
	bool no_text;		//����ʾ��ֵǰ�ġ��ϴ����������ء����ı�
	int preview_width;		//Ԥ�����������
	int preview_height;		//Ԥ���������߶�

	//�󴰿�ģʽ����ѡ����ʾ������Ϣ��ʱ�Ĳ��֣�
	int width_l;	//���ڵĿ��
	int height_l;	//���ڵĸ߶�
	int up_x_l;		//���ϴ�����x����
	int up_y_l;		//���ϴ�����y����
	int up_width_l;		//���ϴ����Ŀ��
	Alignment up_align_l;	//���ϴ����Ķ��뷽ʽ
	bool show_up_l;			//�Ƿ���ʾ���ϴ���
	int down_x_l;			//�����ء���x����
	int down_y_l;			//�����ء���y����
	int down_width_l;		//�����ء��Ŀ��
	Alignment down_align_l;	//�����ء��Ķ��뷽ʽ
	bool show_down_l;		//�Ƿ���ʾ�����ء�
	int cpu_x_l;			//��CPU����x����
	int cpu_y_l;			//��CPU����y����
	int cpu_width_l;		//��CPU���Ŀ��
	Alignment cpu_align_l;	//��CPU���Ķ��뷽ʽ
	bool show_cpu_l;		//�Ƿ���ʾ��CPU��
	int memory_x_l;			//���ڴ桱��x����
	int memory_y_l;			//���ڴ桱��y����
	int memory_width_l;		//���ڴ桱�Ŀ��
	Alignment memory_align_l;	//���ڴ桱�Ķ��뷽ʽ
	bool show_memory_l;		//�Ƿ���ʾ���ڴ桱
	int preview_x_l;		//�ڡ�ѡ��Ƥ����������Ԥ��ͼ��x����
	int preview_y_l;		//�ڡ�ѡ��Ƥ����������Ԥ��ͼ��y����

	//С����ģʽ������ѡ����ʾ������Ϣ��ʱ�Ĳ��֣�
	int width_s;	//���ڵĿ��
	int height_s;	//���ڵĸ߶�
	int up_x_s;		//���ϴ�����x����
	int up_y_s;		//���ϴ�����y����
	int up_width_s;		//���ϴ����Ŀ��
	Alignment up_align_s;	//���ϴ����Ķ��뷽ʽ
	bool show_up_s;			//�Ƿ���ʾ���ϴ���
	int down_x_s;			//�����ء���x����
	int down_y_s;			//�����ء���y����
	int down_width_s;		//�����ء��Ŀ��
	Alignment down_align_s;	//�����ء��Ķ��뷽ʽ
	bool show_down_s;		//�Ƿ���ʾ�����ء�
	int cpu_x_s;			//��CPU����x����
	int cpu_y_s;			//��CPU����y����
	int cpu_width_s;		//��CPU���Ŀ��
	Alignment cpu_align_s;	//��CPU���Ķ��뷽ʽ
	bool show_cpu_s;		//�Ƿ���ʾ��CPU��
	int memory_x_s;			//���ڴ桱��x����
	int memory_y_s;			//���ڴ桱��y����
	int memory_width_s;		//���ڴ桱�Ŀ��
	Alignment memory_align_s;	//���ڴ桱�Ķ��뷽ʽ
	bool show_memory_s;		//�Ƿ���ʾ���ڴ桱
	int preview_x_s;	//�ڡ�ѡ��Ƥ����������Ԥ��ͼ��x����
	int preview_y_s;	//�ڡ�ѡ��Ƥ����������Ԥ��ͼ��y����
};

class CSkinEditorHelper
{
public:
	CSkinEditorHelper();
	~CSkinEditorHelper();

	//����ͱ���Ƥ��������ΪƤ���ļ��е�·��
	SkinData LoadSkin();
	bool SaveSkin(const SkinData& data, bool asign_item_text = false, bool assign_font = false);

	void SetSkinPath(const wstring& skin_path);

protected:
	wstring m_ini_path;
};

