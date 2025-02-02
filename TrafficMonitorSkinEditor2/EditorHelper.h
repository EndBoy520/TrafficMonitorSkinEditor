#pragma once
#include <string>
#include "ScintillaEditView.h"

//�����Զ���ɵĹؼ���
constexpr char* SKIN_KEY_WORDS = "root skin plugin_map layout preview "
    "text_color specify_each_item_color skin_author font display_text "
    "layout_l layout_s "
    "up down total_speed today_traffic cpu memory gpu cpu_temperature gpu_temperature "
    "hdd_temperature main_board_temperature hdd cpu_freq "
    "text_height no_label width height align show"
    ;

class CEditorHelper
{
public:
    CEditorHelper(CScintillaEditView* view);

    //HTML����Զ����
    //  character_input: ���������ַ�
    void HtmlMarkAutoComp(char character_input);

    //���ƥ���HTML��ǩ
    void MarkMatchedHtmlMarks();

    //�Զ���ʾ��������б�
    void AutoShowCompList();

private:
    std::string GetMatchedCompList(const std::string& str);

private:
    CScintillaEditView* m_view{};

};

