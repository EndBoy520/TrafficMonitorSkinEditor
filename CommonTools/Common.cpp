﻿#include "pch.h"
#include "Common.h"
#include <corecrt_io.h>
#include <afxinet.h>


CCommon::CCommon()
{
}


CCommon::~CCommon()
{
}

wstring CCommon::StrToUnicode(const char* str, bool utf8)
{
    wstring result;
    int size;
    size = MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, NULL, 0);
    if (size <= 0) return wstring();
    wchar_t* str_unicode = new wchar_t[size + 1];
    MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, str_unicode, size);
    result.assign(str_unicode);
    delete[] str_unicode;
    return result;
}

string CCommon::UnicodeToStr(const wchar_t* wstr, bool utf8)
{
    string result;
    int size{ 0 };
    size = WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, NULL, 0, NULL, NULL);
    if (size <= 0) return string();
    char* str = new char[size + 1];
    WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, str, size, NULL, NULL);
    result.assign(str);
    delete[] str;
    return result;
}

wstring CCommon::StrToUnicode(const string& str, CodeType code_type, UINT code_page)
{
    if (str.empty()) return wstring();
    wstring result;
    int size;
    if (code_type == CodeType::ANSI)
    {
        size = MultiByteToWideChar(code_page, 0, str.c_str(), str.size(), NULL, 0);
        if (size <= 0) return wstring();
        wchar_t* str_unicode = new wchar_t[size + 1];
        MultiByteToWideChar(code_page, 0, str.c_str(), str.size(), str_unicode, size);
        result.assign(str_unicode, size);
        delete[] str_unicode;
    }
    else if (code_type == CodeType::UTF8 || code_type == CodeType::UTF8_NO_BOM)
    {
        string temp;
        //如果前面有BOM，则去掉BOM
        if (str.size() >= 3 && str[0] == -17 && str[1] == -69 && str[2] == -65)
            temp = str.substr(3);
        else
            temp = str;
        size = MultiByteToWideChar(CP_UTF8, 0, temp.c_str(), temp.size(), NULL, 0);
        if (size <= 0) return wstring();
        wchar_t* str_unicode = new wchar_t[size + 1];
        MultiByteToWideChar(CP_UTF8, 0, temp.c_str(), temp.size(), str_unicode, size);
        result.assign(str_unicode, size);
        delete[] str_unicode;
    }
    else if (code_type == CodeType::UTF16)
    {
        string temp;
        //如果前面有BOM，则去掉BOM
        if (str.size() >= 2 && str[0] == -1 && str[1] == -2)
            temp = str.substr(2);
        else
            temp = str;
        if (temp.size() % 2 == 1)
            temp.pop_back();
        temp.push_back('\0');
        result.assign((const wchar_t*)temp.c_str(), temp.size() / sizeof(wchar_t));
    }
    return result;
}

string CCommon::UnicodeToStr(const wstring& wstr, bool& char_cannot_convert, CodeType code_type, UINT code_page)
{
    if (wstr.empty()) return string();
    char_cannot_convert = false;
    BOOL UsedDefaultChar{ FALSE };
    string result;
    int size{ 0 };
    if (code_type == CodeType::ANSI)
    {
        size = WideCharToMultiByte(code_page, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
        if (size <= 0) return string();
        char* str = new char[size + 1];
        WideCharToMultiByte(code_page, 0, wstr.c_str(), wstr.size(), str, size, NULL, &UsedDefaultChar);
        result.assign(str, size);
        delete[] str;
    }
    else if (code_type == CodeType::UTF8 || code_type == CodeType::UTF8_NO_BOM)
    {
        result.clear();
        if (code_type == CodeType::UTF8)
        {
            result.push_back(-17);
            result.push_back(-69);
            result.push_back(-65);
        }
        size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
        if (size <= 0) return string();
        char* str = new char[size + 1];
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), str, size, NULL, NULL);
        result.append(str, size);
        delete[] str;
    }
    else if (code_type == CodeType::UTF16)
    {
        result.clear();
        result.push_back(-1);   //在前面加上UTF16的BOM
        result.push_back(-2);
        result.append((const char*)wstr.c_str(), (const char*)wstr.c_str() + wstr.size() * 2);
        result.push_back('\0');
    }
    char_cannot_convert = (UsedDefaultChar != FALSE);
    return result;
}

bool CCommon::GetFileContent(const wchar_t* file_path, string& contents_buff, bool binary /*= true*/)
{
    std::ifstream file{ file_path, (binary ? std::ios::binary : std::ios::in) };
    if (file.fail())
        return false;
    //获取文件长度
    file.seekg(0, file.end);
    size_t length = file.tellg();
    file.seekg(0, file.beg);

    char* buff = new char[length];
    file.read(buff, length);
    file.close();

    contents_buff.assign(buff, length);
    delete[] buff;

    return true;
}

const char* CCommon::GetFileContent(const wchar_t* file_path, size_t& length, bool binary /*= true*/)
{
    std::ifstream file{ file_path, (binary ? std::ios::binary : std::ios::in) };
    length = 0;
    if (file.fail())
        return nullptr;
    //获取文件长度
    file.seekg(0, file.end);
    length = file.tellg();
    file.seekg(0, file.beg);

    char* buff = new char[length];
    file.read(buff, length);
    file.close();

    return buff;
}

CString CCommon::DataSizeToString(unsigned long long size, bool with_space)
{
    CString str;
    if (size < 1024 * 10)                   //10KB以下以KB为单位，保留2位小数
        str.Format(_T("%.2f KB"), size / 1024.0);
    else if (size < 1024 * 1024)            //1MB以下以KB为单位，保留1位小数
        str.Format(_T("%.1f KB"), size / 1024.0);
    else if (size < 1024 * 1024 * 1024)     //1GB以下以MB为单位，保留2位小数
        str.Format(_T("%.2f MB"), size / 1024.0 / 1024.0);
    else if (size < 1024ll * 1024 * 1024 * 1024)
        str.Format(_T("%.2f GB"), size / 1024.0 / 1024.0 / 1024.0);
    else
        str.Format(_T("%.2f TB"), size / 1024.0 / 1024.0 / 1024.0 / 1024.0);
    if (!with_space)
        str.Remove(_T(' '));
    return str;
}


CString CCommon::KBytesToString(unsigned __int64 kb_size)
{
    CString k_bytes_str;
    if (kb_size < 1024)
        k_bytes_str.Format(_T("%d KB"), kb_size);
    else if (kb_size < 1024 * 1024)
        k_bytes_str.Format(_T("%.2f MB"), kb_size / 1024.0);
    else if (kb_size < 1024 * 1024 * 1024)
        k_bytes_str.Format(_T("%.2f GB"), kb_size / 1024.0 / 1024.0);
    else
        k_bytes_str.Format(_T("%.2f TB"), kb_size / 1024.0 / 1024.0 / 1024.0);
    return k_bytes_str;
}

__int64 CCommon::CompareFileTime2(FILETIME time1, FILETIME time2)
{
    __int64 a = static_cast<__int64>(time1.dwHighDateTime) << 32 | time1.dwLowDateTime;
    __int64 b = static_cast<__int64>(time2.dwHighDateTime) << 32 | time2.dwLowDateTime;
    return b - a;
}

void CCommon::WriteLog(const char* str_text, LPCTSTR file_path)
{
    SYSTEMTIME cur_time;
    GetLocalTime(&cur_time);
    char buff[32];
    sprintf_s(buff, "%d/%.2d/%.2d %.2d:%.2d:%.2d.%.3d: ", cur_time.wYear, cur_time.wMonth, cur_time.wDay,
        cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);
    ofstream file{ file_path, std::ios::app };  //以追加的方式打开日志文件
    file << buff;
    file << str_text << std::endl;
}

void CCommon::WriteLog(const wchar_t* str_text, LPCTSTR file_path)
{
    SYSTEMTIME cur_time;
    GetLocalTime(&cur_time);
    char buff[32];
    sprintf_s(buff, "%d/%.2d/%.2d %.2d:%.2d:%.2d.%.3d: ", cur_time.wYear, cur_time.wMonth, cur_time.wDay,
        cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);
    ofstream file{ file_path, std::ios::app };  //以追加的方式打开日志文件
    file << buff;
    file << UnicodeToStr(str_text).c_str() << std::endl;
}

BOOL CCommon::CreateFileShortcut(LPCTSTR lpszLnkFileDir, LPCTSTR lpszFileName, LPCTSTR lpszLnkFileName, LPCTSTR lpszWorkDir, WORD wHotkey, LPCTSTR lpszDescription, int iShowCmd)
{
    if (lpszLnkFileDir == NULL)
        return FALSE;

    HRESULT hr;
    IShellLink* pLink;  //IShellLink对象指针
    IPersistFile* ppf; //IPersisFil对象指针

                         //创建IShellLink对象
    hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
    if (FAILED(hr))
        return FALSE;

    //从IShellLink对象中获取IPersistFile接口
    hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
    if (FAILED(hr))
    {
        pLink->Release();
        return FALSE;
    }

    TCHAR file_path[MAX_PATH];
    GetModuleFileName(NULL, file_path, MAX_PATH);

    //目标
    if (lpszFileName == NULL)
        pLink->SetPath(file_path);
    else
        pLink->SetPath(lpszFileName);

    //工作目录
    if (lpszWorkDir != NULL)
    {
        pLink->SetWorkingDirectory(lpszWorkDir);
    }
    else
    {
        //设置工作目录为快捷方式目标所在位置
        TCHAR workDirBuf[MAX_PATH]{};
        if (lpszFileName == NULL)
            //wcscpy_s(workDirBuf, file_path);
            WStringCopy(workDirBuf, 260, file_path, 260);
        else
            //wcscpy_s(workDirBuf, lpszFileName);
            WStringCopy(workDirBuf, 260, lpszFileName);
        LPTSTR pstr = wcsrchr(workDirBuf, _T('\\'));
        *pstr = _T('\0');
        pLink->SetWorkingDirectory(workDirBuf);
    }

    //快捷键
    if (wHotkey != 0)
        pLink->SetHotkey(wHotkey);

    //备注
    if (lpszDescription != NULL)
        pLink->SetDescription(lpszDescription);

    //显示方式
    pLink->SetShowCmd(iShowCmd);


    //快捷方式的路径 + 名称
    wchar_t szBuffer[MAX_PATH];
    if (lpszLnkFileName != NULL) //指定了快捷方式的名称
        swprintf_s(szBuffer, L"%s\\%s", lpszLnkFileDir, lpszLnkFileName);
    else
    {
        //没有指定名称，就从取指定文件的文件名作为快捷方式名称。
        const wchar_t* pstr;
        if (lpszFileName != NULL)
            pstr = wcsrchr(lpszFileName, L'\\');
        else
            pstr = wcsrchr(file_path, L'\\');

        if (pstr == NULL)
        {
            ppf->Release();
            pLink->Release();
            return FALSE;
        }
        //注意后缀名要从.exe改为.lnk
        swprintf_s(szBuffer, L"%s\\%s", lpszLnkFileDir, pstr);
        int nLen = wcslen(szBuffer);
        szBuffer[nLen - 3] = L'l';
        szBuffer[nLen - 2] = L'n';
        szBuffer[nLen - 1] = L'k';
    }
    //保存快捷方式到指定目录下
    //WCHAR  wsz[MAX_PATH];  //定义Unicode字符串
    //MultiByteToWideChar(CP_ACP, 0, szBuffer, -1, wsz, MAX_PATH);

    hr = ppf->Save(szBuffer, TRUE);

    ppf->Release();
    pLink->Release();
    return SUCCEEDED(hr);
}

wstring CCommon::GetStartUpPath()
{
    LPITEMIDLIST ppidl;
    TCHAR pszStartUpPath[MAX_PATH]{};
    if (SHGetSpecialFolderLocation(NULL, CSIDL_STARTUP, &ppidl) == S_OK)
    {
        SHGetPathFromIDList(ppidl, pszStartUpPath);
        CoTaskMemFree(ppidl);
    }
    return wstring(pszStartUpPath);
}

void CCommon::GetFiles(const wchar_t* path, vector<wstring>& files)
{
    //文件句柄
    intptr_t hFile = 0;
    //文件信息（用Unicode保存使用_wfinddata_t，多字节字符集使用_finddata_t）
    _wfinddata_t fileinfo;
    wstring file_name;
    if ((hFile = _wfindfirst(wstring(path).append(L"\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            file_name.assign(fileinfo.name);
            if (file_name != L"." && file_name != L"..")
                //files.push_back(wstring(path) + L"\\" + file_name);  //将文件名保存(忽略"."和"..")
                files.push_back(L"\\" + file_name);  //将文件名保存(忽略"."和"..")
        } while (_wfindnext(hFile, &fileinfo) == 0);
    }
    _findclose(hFile);
}

bool CCommon::FileExist(LPCTSTR file_name)
{
    return (PathFileExists(file_name) != 0);
}

bool CCommon::FolderExist(LPCTSTR folder_path)
{
    DWORD dwAttrib = GetFileAttributes(folder_path);
    return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

bool CCommon::MoveAFile(LPCTSTR exist_file, LPCTSTR new_file)
{
    if (!FileExist(exist_file))
        return false;
    //if (FileExist(new_file))      //如果目标文件已经存在，则先删除它
    //  DeleteFile(new_file);
    return (MoveFile(exist_file, new_file) != 0);
}

SYSTEMTIME CCommon::CompareSystemTime(SYSTEMTIME a, SYSTEMTIME b)
{
    SYSTEMTIME result{};
    short hour = a.wHour - b.wHour;
    short minute = a.wMinute - b.wMinute;
    short second = a.wSecond - b.wSecond;

    if (second < 0)
    {
        second += 60;
        minute--;
    }

    if (minute < 0)
    {
        minute += 60;
        hour--;
    }

    if (hour < 0)
    {
        hour += 24;
    }
    result.wHour = hour;
    result.wMinute = minute;
    result.wSecond = second;
    return result;
}

wstring CCommon::GetModuleDir()
{
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);
    size_t index;
    wstring current_path{ path };
    index = current_path.find_last_of(L'\\');
    current_path = current_path.substr(0, index + 1);
    return current_path;
}

wstring CCommon::GetSystemDir()
{
    wchar_t buff[MAX_PATH];
    GetSystemDirectory(buff, MAX_PATH);
    return wstring(buff);
}

wstring CCommon::GetTemplateDir()
{
    wstring result;
    wchar_t buff[MAX_PATH];
    GetTempPath(MAX_PATH, buff);        //获取临时文件夹的路径
    result = buff;
    if (result.back() != L'\\' && result.back() != L'/')        //确保路径后面有斜杠
        result.push_back(L'\\');
    return result;
}

wstring CCommon::GetAppDataConfigDir()
{
    LPITEMIDLIST ppidl;
    TCHAR pszAppDataPath[MAX_PATH];
    if (SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &ppidl) == S_OK)
    {
        SHGetPathFromIDList(ppidl, pszAppDataPath);
        CoTaskMemFree(ppidl);
    }
    wstring app_data_path{ pszAppDataPath };        //获取到C:/User/用户名/AppData/Roaming路径
    CreateDirectory(app_data_path.c_str(), NULL);       //如果Roaming不存在，则创建它
    app_data_path += L"\\TrafficMonitor\\";
    CreateDirectory(app_data_path.c_str(), NULL);       //如果C:/User/用户名/AppData/Roaming/TrafficMonitor不存在，则创建它

    return app_data_path;
}

void CCommon::DrawWindowText(CDC* pDC, CRect rect, LPCTSTR lpszString, COLORREF color, COLORREF back_color)
{
    pDC->SetTextColor(color);
    //m_pDC->SetBkMode(TRANSPARENT);
    //用背景色填充矩形区域
    pDC->FillSolidRect(rect, back_color);
    pDC->DrawText(lpszString, rect, DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);

}

//void CCommon::SetDrawArea(CDC * pDC, CRect rect)
//{
//  CRgn rgn;
//  rgn.CreateRectRgnIndirect(rect);
//  pDC->SelectClipRgn(&rgn);
//}


bool CCommon::IsForegroundFullscreen()
{
    bool bFullscreen{ false };      //用于指示前台窗口是否是全屏
    HWND hWnd;
    RECT rcApp;
    RECT rcDesk;
    hWnd = GetForegroundWindow();   //获取当前正在与用户交互的前台窗口句柄
    TCHAR buff[256];
    GetClassName(hWnd, buff, 256);      //获取前台窗口的类名
    CString class_name{ buff };
    if (hWnd != GetDesktopWindow() && class_name != _T("WorkerW") && hWnd != GetShellWindow())//如果前台窗口不是桌面窗口，也不是控制台窗口
    {
        GetWindowRect(hWnd, &rcApp);    //获取前台窗口的坐标
        GetWindowRect(GetDesktopWindow(), &rcDesk); //根据桌面窗口句柄，获取整个屏幕的坐标
        if (rcApp.left <= rcDesk.left && //如果前台窗口的坐标完全覆盖住桌面窗口，就表示前台窗口是全屏的
            rcApp.top <= rcDesk.top &&
            rcApp.right >= rcDesk.right &&
            rcApp.bottom >= rcDesk.bottom)
        {
            bFullscreen = true;
        }
    }//如果前台窗口是桌面窗口，或者是控制台窗口，就直接返回不是全屏
    return bFullscreen;
}

bool CCommon::CopyStringToClipboard(const wstring& str)
{
    if (OpenClipboard(NULL))
    {
        HGLOBAL clipbuffer;
        EmptyClipboard();
        size_t size = (str.size() + 1) * 2;
        clipbuffer = GlobalAlloc(GMEM_DDESHARE, size);
        memcpy_s(GlobalLock(clipbuffer), size, str.c_str(), size);
        GlobalUnlock(clipbuffer);
        if (SetClipboardData(CF_UNICODETEXT, clipbuffer) == NULL)
            return false;
        CloseClipboard();
        return true;
    }
    else return false;
}


wstring CCommon::GetJsonValueSimple(const wstring& json_str, const wstring& name)
{
    wstring str_name{ L"\"" };
    str_name += name;
    str_name += L'\"';
    size_t index = json_str.find(str_name);
    if (index == wstring::npos)
        return wstring();
    index = json_str.find(L':', index + 1);
    if (index == wstring::npos)
        return wstring();
    index = json_str.find_first_not_of(L"\" ", index + 1);
    size_t index_end = json_str.find_first_of(L"\",]}\r\n", index);
    wstring result = json_str.substr(index, index_end - index);
    return result;
}

bool CCommon::GetURL(const wstring& url, wstring& result, bool utf8, const wstring& user_agent)
{
    bool succeed{ false };
    CInternetSession* pSession{};
    CHttpFile* pfile{};
    try
    {
        pSession = new CInternetSession(user_agent.c_str());
        pfile = (CHttpFile*)pSession->OpenURL(url.c_str());
        DWORD dwStatusCode;
        pfile->QueryInfoStatusCode(dwStatusCode);
        if (dwStatusCode == HTTP_STATUS_OK)
        {
            CString content;
            CString data;
            while (pfile->ReadString(data))
            {
                content += data;
            }
            result = StrToUnicode((const char*)content.GetString(), utf8);
            succeed = true;
        }
        pfile->Close();
        delete pfile;
        pSession->Close();
    }
    catch (CInternetException* e)
    {
        ////写入错误日志
        //CString info = CCommon::LoadTextFormat(IDS_GET_URL_ERROR_LOG_INFO, { url, static_cast<size_t>(e->m_dwError) });
        //CCommon::WriteLog(info, theApp.m_log_path.c_str());
        if (pfile != nullptr)
        {
            pfile->Close();
            delete pfile;
        }
        if (pSession != nullptr)
            pSession->Close();
        succeed = false;
        e->Delete();        //没有这句会造成内存泄露
        SAFE_DELETE(pSession);
    }
    SAFE_DELETE(pSession);
    return succeed;
}


void CCommon::SetRect(CRect& rect, int x, int y, int width, int height)
{
    rect.left = x;
    rect.top = y;
    rect.right = x + width;
    rect.bottom = y + height;
}

CString CCommon::LoadText(UINT id, LPCTSTR back_str)
{
    CString str;
    str.LoadString(id);
    if (back_str != nullptr)
        str += back_str;
    return str;
}

CString CCommon::LoadText(LPCTSTR front_str, UINT id, LPCTSTR back_str)
{
    CString str;
    str.LoadString(id);
    if (back_str != nullptr)
        str += back_str;
    if (front_str != nullptr)
        str = front_str + str;
    return str;
}

CString CCommon::StringFormat(LPCTSTR format_str, const std::initializer_list<CVariant>& paras)
{
    CString str_rtn = format_str;
    int index = 1;
    for (const auto& para : paras)
    {
        CString para_str = para.ToString();
        CString format_para;
        format_para.Format(_T("<%%%d%%>"), index);
        str_rtn.Replace(format_para, para_str);

        index++;
    }
    return str_rtn;
}

CString CCommon::LoadTextFormat(UINT id, const std::initializer_list<CVariant>& paras)
{
    CString str;
    str.LoadString(id);
    return StringFormat(str.GetString(), paras);
}

CString CCommon::IntToString(__int64 n, bool thousand_separation, bool is_unsigned)
{
    wstring str = std::to_wstring(is_unsigned ? static_cast<unsigned __int64>(n) : n);
    int count{};
    if (thousand_separation)
    {
        int length{ static_cast<int>(str.size()) };
        for (int i{ length - 1 }; i > 0; i--)
        {
            count++;
            if (count % 3 == 0)
                str.insert(i, L",");
        }
    }
    return str.c_str();
}

void CCommon::NormalizeFont(LOGFONT& font)
{
    wstring name;
    wstring style;
    name = font.lfFaceName;
    if (name.empty())
        return;
    if (name.back() == L' ')
        name.pop_back();
    size_t index = name.rfind(L' ');
    if (index == wstring::npos)
        return;
    style = name.substr(index + 1);
    bool style_acquired = false;
    if (style == L"Light")
    {
        font.lfWeight = FW_LIGHT;
        style_acquired = true;
    }
    else if (style == L"Semilight")
    {
        font.lfWeight = 350;
        style_acquired = true;
    }
    else if (style == L"Semibold")
    {
        font.lfWeight = FW_SEMIBOLD;
        style_acquired = true;
    }
    else if (style == L"Bold")
    {
        font.lfWeight = FW_BOLD;
        style_acquired = true;
    }
    else if (style == L"Black")
    {
        font.lfWeight = FW_BLACK;
        style_acquired = true;
    }

    if (style_acquired)
    {
        name = name.substr(0, index);
    }
    //wcsncpy_s(font.lfFaceName, name.c_str(), 32);
    WStringCopy(font.lfFaceName, 32, name.c_str(), name.size());
}

void CCommon::WStringCopy(wchar_t* str_dest, int dest_size, const wchar_t* str_source, int source_size)
{
    if (dest_size <= 0)
        return;
    if (source_size <= 0 || str_source == nullptr)
    {
        str_dest[0] = L'\0';
        return;
    }
    int i;
    for (i = 0; i < dest_size && i < source_size && str_source[i] != L'\0'; i++)
        str_dest[i] = str_source[i];
    //确保目标字符串末尾有一个\0
    int copy_cnt = i;
    if (copy_cnt < dest_size)
        str_dest[copy_cnt] = L'\0';
    else
        str_dest[dest_size - 1] = L'\0';
}

void CCommon::SetThreadLanguage(Language language)
{
    switch (language)
    {
    case Language::ENGLISH: SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)); break;
    case Language::SIMPLIFIED_CHINESE: SetThreadUILanguage(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)); break;
        //case Language::TRADITIONAL_CHINESE: SetThreadUILanguage(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)); break;
    default: break;
    }
}

void CCommon::TransparentColorConvert(COLORREF& transparent_color)
{
    if (transparent_color == 0)
        return;
    BYTE r = GetRValue(transparent_color);
    BYTE g = GetGValue(transparent_color);
    BYTE b = GetBValue(transparent_color);
    if (r == b)
    {
        if (b >= 255)
            b--;
        else
            b++;
        transparent_color = RGB(r, g, b);
    }
}

void CCommon::SetDialogFont(CWnd* pDlg, CFont* pFont)
{
    if (pDlg->GetSafeHwnd() != NULL)
    {
        CWnd* pWndChild;
        pWndChild = pDlg->GetWindow(GW_CHILD);
        while (pWndChild)
        {
            pWndChild->SetFont(pFont);
            pWndChild = pWndChild->GetWindow(GW_HWNDNEXT);
        }
    }
}

CString CCommon::GetTextResource(UINT id, int code_type)
{
    CString res_str;
    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(id), _T("TEXT"));
    if (hRes != NULL)
    {
        HGLOBAL hglobal = LoadResource(NULL, hRes);
        if (hglobal != NULL)
        {
            if (code_type == 2)
            {
                res_str = (const wchar_t*)hglobal;
            }
            else
            {
                res_str = CCommon::StrToUnicode((const char*)hglobal, (code_type != 0)).c_str();
            }
        }
    }
    return res_str;
}

// CString CCommon::GetLastCompileTime()
// {
//     CString str_compile_time = GetTextResource(IDR_COMPILE_TIME, 0);
//     str_compile_time.Replace(_T("\r\n"), _T(""));
//     str_compile_time.Delete(str_compile_time.GetLength() - 1, 1);
//     return str_compile_time;
// }

HICON CCommon::LoadIconResource(UINT id, int size)
{
    return (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(id), IMAGE_ICON, size, size, 0);
}

int CCommon::GetMenuItemPosition(CMenu* pMenu, UINT id)
{
    int pos = -1;
    int item_count = pMenu->GetMenuItemCount();
    for (int i = 0; i < item_count; i++)
    {
        if (pMenu->GetMenuItemID(i) == id)
        {
            pos = i;
            break;
        }
    }
    return pos;
}

bool CCommon::IsColorSimilar(COLORREF color1, COLORREF color2)
{
    const int DIFF{ 24 };
    return (std::abs(GetRValue(color1) - GetRValue(color2)) < DIFF
        && std::abs(GetGValue(color1) - GetGValue(color2)) < DIFF
        && std::abs(GetBValue(color1) - GetBValue(color2)) < DIFF);
}

int CCommon::CountOneBits(unsigned int value)
{
    int count = 0;
    while (value != 0)
    {
        if (value % 2 == 1)
        {
            count++;
        }
        value = value >> 1;
    }
    return count;
}

void CCommon::SetNumberBit(unsigned int& num, int bit, bool value)
{
    if (value)
    {
        num |= (1 << bit);
    }
    else
    {
        num &= ~(1 << bit);
    }
}

bool CCommon::GetNumberBit(unsigned int num, int bit)
{
    return (num & (1 << bit)) != 0;
}
