#include "stdafx.h"
#include "SkinEditorHelper.h"


CSkinEditorHelper::CSkinEditorHelper()
{
}


CSkinEditorHelper::~CSkinEditorHelper()
{
}


SkinData CSkinEditorHelper::LoadSkin()
{
	CIniHelper ini_helper;
	SkinData data;
	if (m_ini_path.empty())
		return data;
	ini_helper.SetPath(m_ini_path);

	//data.text_color = ini_helper.GetInt(L"skin", L"text_color", 0);
	ini_helper.GetIntArray(L"skin", L"text_color", (int*)data.text_colors, MAIN_WND_COLOR_NUM, 0);
	data.specify_each_item_color = ini_helper.GetBool(L"skin", L"specify_each_item_color", false);
	data.skin_author = ini_helper.GetString(L"skin", L"skin_author", L"unknow");
	data.up_string = ini_helper.GetString(L"skin", L"up_string", L"\"�ϴ�: \"");
	data.down_string = ini_helper.GetString(L"skin", L"down_string", L"\"����: \"");
	data.cpu_string = ini_helper.GetString(L"skin", L"cpu_string", L"\"CPU: \"");
	data.memory_string = ini_helper.GetString(L"skin", L"memory_string", L"\"�ڴ�: \"");
	//data.font_name = ini_helper.GetString(L"skin", L"font_name", L"");
	//data.font_size = ini_helper.GetInt(L"skin", L"font_size", 0);
	FontInfo default_font{};
	ini_helper.LoadFontData(L"skin", data.font, default_font);

	data.text_height = ini_helper.GetInt(L"layout", L"text_height", 20);
	data.no_text = ini_helper.GetBool(L"layout", L"no_text", false);
	data.preview_width = ini_helper.GetInt(L"layout", L"preview_width", 238);
	data.preview_height = ini_helper.GetInt(L"layout", L"preview_height", 116);

	data.width_l = ini_helper.GetInt(L"layout", L"width_l", 220);
	data.height_l = ini_helper.GetInt(L"layout", L"height_l", 43);
	data.up_x_l = ini_helper.GetInt(L"layout", L"up_x_l", 6);
	data.up_y_l = ini_helper.GetInt(L"layout", L"up_y_l", 2);
	data.up_width_l = ini_helper.GetInt(L"layout", L"up_width_l", 108);
	data.up_align_l = static_cast<Alignment>(ini_helper.GetInt(L"layout", L"up_align_l", 0));
	data.down_x_l = ini_helper.GetInt(L"layout", L"down_x_l", 114);
	data.down_y_l = ini_helper.GetInt(L"layout", L"down_y_l", 2);
	data.down_width_l = ini_helper.GetInt(L"layout", L"down_width_l", 110);
	data.down_align_l = static_cast<Alignment>(ini_helper.GetInt(L"layout", L"down_align_l", 0));
	data.cpu_x_l = ini_helper.GetInt(L"layout", L"cpu_x_l", 6);
	data.cpu_y_l = ini_helper.GetInt(L"layout", L"cpu_y_l", 22);
	data.cpu_width_l = ini_helper.GetInt(L"layout", L"cpu_width_l", 108);
	data.cpu_align_l = static_cast<Alignment>(ini_helper.GetInt(L"layout", L"cpu_align_l", 0));
	data.memory_x_l = ini_helper.GetInt(L"layout", L"memory_x_l", 114);
	data.memory_y_l = ini_helper.GetInt(L"layout", L"memory_y_l", 22);
	data.memory_width_l = ini_helper.GetInt(L"layout", L"memory_width_l", 110);
	data.memory_align_l = static_cast<Alignment>(ini_helper.GetInt(L"layout", L"memory_align_l", 0));
	data.show_up_l = ini_helper.GetBool(L"layout", L"show_up_l", true);
	data.show_down_l = ini_helper.GetBool(L"layout", L"show_down_l", true);
	data.show_cpu_l = ini_helper.GetBool(L"layout", L"show_cpu_l", true);
	data.show_memory_l = ini_helper.GetBool(L"layout", L"show_memory_l", true);
	data.preview_x_l = ini_helper.GetInt(L"layout", L"preview_x_l", 0);
	data.preview_y_l = ini_helper.GetInt(L"layout", L"preview_y_l", 47);

	data.width_s = ini_helper.GetInt(L"layout", L"width_s", 220);
	data.height_s = ini_helper.GetInt(L"layout", L"height_s", 28);
	data.up_x_s = ini_helper.GetInt(L"layout", L"up_x_s", 6);
	data.up_y_s = ini_helper.GetInt(L"layout", L"up_y_s", 4);
	data.up_width_s = ini_helper.GetInt(L"layout", L"up_width_s", 108);
	data.up_align_s = static_cast<Alignment>(ini_helper.GetInt(L"layout", L"up_align_s", 0));
	data.down_x_s = ini_helper.GetInt(L"layout", L"down_x_s", 114);
	data.down_y_s = ini_helper.GetInt(L"layout", L"down_y_s", 4);
	data.down_width_s = ini_helper.GetInt(L"layout", L"down_width_s", 110);
	data.down_align_s = static_cast<Alignment>(ini_helper.GetInt(L"layout", L"down_align_s", 0));
	data.cpu_x_s = ini_helper.GetInt(L"layout", L"cpu_x_s", 0);
	data.cpu_y_s = ini_helper.GetInt(L"layout", L"cpu_y_s", 0);
	data.cpu_width_s = ini_helper.GetInt(L"layout", L"cpu_width_s", 0);
	data.cpu_align_s = static_cast<Alignment>(ini_helper.GetInt(L"layout", L"cpu_align_s", 0));
	data.memory_x_s = ini_helper.GetInt(L"layout", L"memory_x_s", 0);
	data.memory_y_s = ini_helper.GetInt(L"layout", L"memory_y_s", 0);
	data.memory_width_s = ini_helper.GetInt(L"layout", L"memory_width_s", 0);
	data.memory_align_s = static_cast<Alignment>(ini_helper.GetInt(L"layout", L"memory_align_s", 0));
	data.show_up_s = ini_helper.GetBool(L"layout", L"show_up_s", true);
	data.show_down_s = ini_helper.GetBool(L"layout", L"show_down_s", true);
	data.show_cpu_s = ini_helper.GetBool(L"layout", L"show_cpu_s", false);
	data.show_memory_s = ini_helper.GetBool(L"layout", L"show_memory_s", false);
	data.preview_x_s = ini_helper.GetInt(L"layout", L"preview_x_s", 0);
	data.preview_y_s = ini_helper.GetInt(L"layout", L"preview_y_s", 0);

	return data;
}

bool CSkinEditorHelper::SaveSkin(const SkinData& data, bool asign_item_text, bool assign_font)
{
	CIniHelper ini_helper;
	if (m_ini_path.empty())
		return false;
	ini_helper.SetPath(m_ini_path);
	bool success{ true };
	DeleteFileW(m_ini_path.c_str());		//����ǰ��ɾ��ini�ļ�
	//success = (success && ini_helper.WriteInt(L"skin", L"text_color", data.text_color));
	success = (success && ini_helper.WriteIntArray(L"skin", L"text_color", (int*)data.text_colors, MAIN_WND_COLOR_NUM));
	success = (success && ini_helper.WriteBool(L"skin", L"specify_each_item_color", data.specify_each_item_color));
	success = (success && ini_helper.WriteString(L"skin", L"skin_author", data.skin_author));
	if (asign_item_text)
	{
		success = (success && ini_helper.WriteString(L"skin", L"up_string", data.up_string));
		success = (success && ini_helper.WriteString(L"skin", L"down_string", data.down_string));
		success = (success && ini_helper.WriteString(L"skin", L"cpu_string", data.cpu_string));
		success = (success && ini_helper.WriteString(L"skin", L"memory_string", data.memory_string));
	}
	if (assign_font)
	{
		//success = (success && ini_helper.WriteString(L"skin", L"font_name", data.font_name));
		//success = (success && ini_helper.WriteInt(L"skin", L"font_size", data.font_size));
		success = (success && ini_helper.SaveFontData(L"skin", data.font));
	}

	success = (success && ini_helper.WriteInt(L"layout", L"text_height", data.text_height));
	success = (success && ini_helper.WriteBool(L"layout", L"no_text", data.no_text));
	success = (success && ini_helper.WriteInt(L"layout", L"preview_width", data.preview_width));
	success = (success && ini_helper.WriteInt(L"layout", L"preview_height", data.preview_height));

	success = (success && ini_helper.WriteInt(L"layout", L"width_l", data.width_l));
	success = (success && ini_helper.WriteInt(L"layout", L"height_l", data.height_l));
	success = (success && ini_helper.WriteInt(L"layout", L"up_x_l", data.up_x_l));
	success = (success && ini_helper.WriteInt(L"layout", L"up_y_l", data.up_y_l));
	success = (success && ini_helper.WriteInt(L"layout", L"up_width_l", data.up_width_l));
	success = (success && ini_helper.WriteInt(L"layout", L"up_align_l", static_cast<int>(data.up_align_l)));
	success = (success && ini_helper.WriteInt(L"layout", L"down_x_l", data.down_x_l));
	success = (success && ini_helper.WriteInt(L"layout", L"down_y_l", data.down_y_l));
	success = (success && ini_helper.WriteInt(L"layout", L"down_width_l", data.down_width_l));
	success = (success && ini_helper.WriteInt(L"layout", L"down_align_l", static_cast<int>(data.down_align_l)));
	success = (success && ini_helper.WriteInt(L"layout", L"cpu_x_l", data.cpu_x_l));
	success = (success && ini_helper.WriteInt(L"layout", L"cpu_y_l", data.cpu_y_l));
	success = (success && ini_helper.WriteInt(L"layout", L"cpu_width_l", data.cpu_width_l));
	success = (success && ini_helper.WriteInt(L"layout", L"cpu_align_l", static_cast<int>(data.cpu_align_l)));
	success = (success && ini_helper.WriteInt(L"layout", L"memory_x_l", data.memory_x_l));
	success = (success && ini_helper.WriteInt(L"layout", L"memory_y_l", data.memory_y_l));
	success = (success && ini_helper.WriteInt(L"layout", L"memory_width_l", data.memory_width_l));
	success = (success && ini_helper.WriteInt(L"layout", L"memory_align_l", static_cast<int>(data.memory_align_l)));
	success = (success && ini_helper.WriteBool(L"layout", L"show_up_l", data.show_up_l));
	success = (success && ini_helper.WriteBool(L"layout", L"show_down_l", data.show_down_l));
	success = (success && ini_helper.WriteBool(L"layout", L"show_cpu_l", data.show_cpu_l));
	success = (success && ini_helper.WriteBool(L"layout", L"show_memory_l", data.show_memory_l));
	success = (success && ini_helper.WriteInt(L"layout", L"preview_x_l", data.preview_x_l));
	success = (success && ini_helper.WriteInt(L"layout", L"preview_y_l", data.preview_y_l));

	success = (success && ini_helper.WriteInt(L"layout", L"width_s", data.width_s));
	success = (success && ini_helper.WriteInt(L"layout", L"height_s", data.height_s));
	success = (success && ini_helper.WriteInt(L"layout", L"up_x_s", data.up_x_s));
	success = (success && ini_helper.WriteInt(L"layout", L"up_y_s", data.up_y_s));
	success = (success && ini_helper.WriteInt(L"layout", L"up_width_s", data.up_width_s));
	success = (success && ini_helper.WriteInt(L"layout", L"up_align_s", static_cast<int>(data.up_align_s)));
	success = (success && ini_helper.WriteInt(L"layout", L"down_x_s", data.down_x_s));
	success = (success && ini_helper.WriteInt(L"layout", L"down_y_s", data.down_y_s));
	success = (success && ini_helper.WriteInt(L"layout", L"down_width_s", data.down_width_s));
	success = (success && ini_helper.WriteInt(L"layout", L"down_align_s", static_cast<int>(data.down_align_s)));
	success = (success && ini_helper.WriteInt(L"layout", L"cpu_x_s", data.cpu_x_s));
	success = (success && ini_helper.WriteInt(L"layout", L"cpu_y_s", data.cpu_y_s));
	success = (success && ini_helper.WriteInt(L"layout", L"cpu_width_s", data.cpu_width_s));
	success = (success && ini_helper.WriteInt(L"layout", L"cpu_align_s", static_cast<int>(data.cpu_align_s)));
	success = (success && ini_helper.WriteInt(L"layout", L"memory_x_s", data.memory_x_s));
	success = (success && ini_helper.WriteInt(L"layout", L"memory_y_s", data.memory_y_s));
	success = (success && ini_helper.WriteInt(L"layout", L"memory_width_s", data.memory_width_s));
	success = (success && ini_helper.WriteInt(L"layout", L"memory_align_s", static_cast<int>(data.memory_align_s)));
	success = (success && ini_helper.WriteBool(L"layout", L"show_up_s", data.show_up_s));
	success = (success && ini_helper.WriteBool(L"layout", L"show_down_s", data.show_down_s));
	success = (success && ini_helper.WriteBool(L"layout", L"show_cpu_s", data.show_cpu_s));
	success = (success && ini_helper.WriteBool(L"layout", L"show_memory_s", data.show_memory_s));
	success = (success && ini_helper.WriteInt(L"layout", L"preview_x_s", data.preview_x_s));
	success = (success && ini_helper.WriteInt(L"layout", L"preview_y_s", data.preview_y_s));
	return success;
}

void CSkinEditorHelper::SetSkinPath(const wstring & skin_path)
{
	m_ini_path = skin_path;
	if (skin_path.size() > 1 && skin_path.back() != L'\\' && skin_path.back() != L'/')
		m_ini_path.push_back(L'\\');
	m_ini_path += L"skin.ini";
}

