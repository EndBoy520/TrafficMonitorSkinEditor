#pragma once

class CCommon
{
public:
	CCommon();
	~CCommon();

	static bool FileExist(const wstring& file);	//�ж��ļ��Ƿ����
	static bool FolderExist(const wstring& file);	//�ж��ļ����Ƿ����
};

