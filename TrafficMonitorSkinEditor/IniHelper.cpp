#include "stdafx.h"
#include "IniHelper.h"


CIniHelper::CIniHelper()
{
}


CIniHelper::~CIniHelper()
{
}

void CIniHelper::SetPath(const wstring & path)
{
	m_path = path;
}

bool CIniHelper::WriteString(const wchar_t * AppName, const wchar_t * KeyName, wstring str)
{
	str = DEF_CH + str + DEF_CH;
	return (::WritePrivateProfileStringW(AppName, KeyName, str.c_str(), m_path.c_str()) != FALSE);
}

wstring CIniHelper::GetString(const wchar_t * AppName, const wchar_t * KeyName, const wchar_t * default_str)
{
	wstring rtn;
	wchar_t buff[256];
	::GetPrivateProfileStringW(AppName, KeyName, default_str, buff, 256, m_path.c_str());
	rtn = buff;
	//�����ȡ���ַ���ǰ����ָ�����ַ�����ɾ����
	if (!rtn.empty() && (rtn.front() == L'$' || rtn.front() == DEF_CH))
		rtn = rtn.substr(1);
	if (!rtn.empty() && (rtn.back() == L'$' || rtn.back() == DEF_CH))
		rtn.pop_back();
	return rtn;
}

bool CIniHelper::WriteInt(const wchar_t * AppName, const wchar_t * KeyName, int value)
{
	wchar_t buff[11]{};
	_itow_s(value, buff, 10);
	return (::WritePrivateProfileStringW(AppName, KeyName, buff, m_path.c_str()) != FALSE);
}

int CIniHelper::GetInt(const wchar_t * AppName, const wchar_t * KeyName, int default_value)
{
	return GetPrivateProfileIntW(AppName, KeyName, default_value, m_path.c_str());
}

bool CIniHelper::WriteBool(const wchar_t * AppName, const wchar_t * KeyName, bool value)
{
	if(value)
		return (::WritePrivateProfileStringW(AppName, KeyName, L"1", m_path.c_str()) != FALSE);
	else
		return (::WritePrivateProfileStringW(AppName, KeyName, L"0", m_path.c_str()) != FALSE);
}

bool CIniHelper::GetBool(const wchar_t * AppName, const wchar_t * KeyName, bool default_value)
{
	return (GetPrivateProfileIntW(AppName, KeyName, default_value, m_path.c_str()) != 0);
}

bool CIniHelper::WriteIntArray(const wchar_t * AppName, const wchar_t * KeyName, const int * values, int size)
{
	CString str, tmp;
	for (int i{}; i < size; i++)
	{
		tmp.Format(_T("%d,"), values[i]);
		str += tmp;
	}
	return (::WritePrivateProfileStringW(AppName, KeyName, str, m_path.c_str()) != FALSE);
}

bool CIniHelper::GetIntArray(const wchar_t * AppName, const wchar_t * KeyName, int * values, int size, int default_value)
{
	wchar_t buff[256];
	bool result;
	CString default_str;
	default_str.Format(_T("%d"), default_value);
	result = ::GetPrivateProfileStringW(AppName, KeyName, default_str, buff, 256, m_path.c_str());
	wstring str{ buff };
	size_t index{}, index0{};
	for (int i{}; i < size; i++)
	{
		index0 = index;
		if (index0 < 256 && str[index0] == L',')
			index0++;
		index = str.find(L',', index + 1);
		if (index0 == index)
		{
			values[i] = default_value;
		}
		else
		{
			wstring tmp = str.substr(index0, index - index0);
			values[i] = _wtoi(tmp.c_str());
		}
	}
	return result;
}

bool CIniHelper::WriteBoolArray(const wchar_t * AppName, const wchar_t * KeyName, const bool * values, int size)
{
	int value{};
	for (int i{}; i < size; i++)
	{
		if (values[i])
			value |= (1 << i);
	}
	return WriteInt(AppName, KeyName, value);
}

void CIniHelper::GetBoolArray(const wchar_t * AppName, const wchar_t * KeyName, bool * values, int size, bool default_value)
{
	int value = GetInt(AppName, KeyName, 0);
	for (int i{}; i < size; i++)
	{
		values[i] = ((value >> i) % 2 != 0);
	}
}

bool CIniHelper::SaveFontData(const wchar_t * AppName, const FontInfo & font)
{
	bool success{ true };
	success = (success && WriteString(AppName, L"font_name", wstring(font.name)));
	success = (success && WriteInt(AppName, L"font_size", font.size));
	bool style[4];
	style[0] = font.bold;
	style[1] = font.italic;
	style[2] = font.underline;
	style[3] = font.strike_out;
	success = (success && WriteBoolArray(AppName, L"font_style", style, 4));
	return success;
}

void CIniHelper::LoadFontData(const wchar_t * AppName, FontInfo & font, const FontInfo& default_font)
{
	font.name = GetString(AppName, L"font_name", default_font.name).c_str();
	font.size = GetInt(AppName, L"font_size", default_font.size);
	bool style[4];
	GetBoolArray(AppName, L"font_style", style, 4);
	font.bold = style[0];
	font.italic = style[1];
	font.underline = style[2];
	font.strike_out = style[3];
}
