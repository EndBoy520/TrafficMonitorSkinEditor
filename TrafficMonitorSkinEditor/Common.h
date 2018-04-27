#pragma once

enum class Alignment
{
	LEFT,
	RIGHT,
	CENTER
};

//����
struct FontInfo
{
	CString name;	//��������
	int size;		//�����С
	bool bold;			//����
	bool italic;		//б��
	bool underline;		//�»���
	bool strike_out;	//ɾ����
};

//���ֺ�ת�ɳ�LOGFONT�ṹ�е�lfHeight
#define FONTSIZE_TO_LFHEIGHT(font_size) (-MulDiv(font_size, GetDeviceCaps(::GetDC(HWND_DESKTOP), LOGPIXELSY), 72))

//����
enum class Language
{
	FOLLOWING_SYSTEM,		//����ϵͳ
	ENGLISH,				//Ӣ��
	SIMPLIFIED_CHINESE		//��������
};

class CCommon
{
public:
	CCommon();
	~CCommon();

	static bool FileExist(const wstring& file);	//�ж��ļ��Ƿ����
	static bool FolderExist(const wstring& file);	//�ж��ļ����Ƿ����
	static wstring GetModulePath();

	//ɾ���������ƺ����Bold��Light���ַ�������������Щ�ַ������������ϸ
	static void NormalizeFont(LOGFONT& font);

	//��ȫ���ַ������ƺ���
	static void WStringCopy(wchar_t* str_dest, int dest_size, const wchar_t* str_source, int source_size = INT_MAX);

	//����Դ�ļ������ַ��������У�front_str��back_strΪ�����ַ���ʱ��Ҫ��ǰ��������ӵ��ַ���
	static CString LoadText(UINT id, LPCTSTR back_str = nullptr);
	static CString LoadText(LPCTSTR front_str, UINT id, LPCTSTR back_str = nullptr);

};

