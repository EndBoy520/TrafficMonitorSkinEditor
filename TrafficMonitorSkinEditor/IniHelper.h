#pragma once
#define NONE_CH L'$'		//д��Ͷ�ȡini�ļ��ַ���ʱ�����ַ���ǰ����ӵ��ַ�

class CIniHelper
{
public:
	CIniHelper();
	~CIniHelper();

	void SetPath(const wstring& path);

	bool WriteString(const wchar_t* AppName, const wchar_t* KeyName, wstring str);
	wstring GetString(const wchar_t* AppName, const wchar_t* KeyName, const wchar_t* default_str);
	bool WriteInt(const wchar_t * AppName, const wchar_t * KeyName, int value);
	int GetInt(const wchar_t * AppName, const wchar_t * KeyName, int default_value);
	bool WriteBool(const wchar_t * AppName, const wchar_t * KeyName, bool value);
	bool GetBool(const wchar_t * AppName, const wchar_t * KeyName, bool default_value);

protected:
	wstring m_path;
};

