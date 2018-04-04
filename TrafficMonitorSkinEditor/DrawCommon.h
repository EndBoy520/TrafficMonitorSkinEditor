//��װ�Ļ�ͼ��
#pragma once
#include "Common.h"
class CDrawCommon
{
public:

	//����ģʽ
	enum class StretchMode
	{
		STRETCH,		//���죬��ı����
		FILL,			//��䣬���ı��������ü�����
		FIT			//��Ӧ������ı���������ü�
	};

	CDrawCommon();
	~CDrawCommon();

	void Create(CDC* pDC, CWnd* pMainWnd);
	void SetFont(CFont* pfont);		//���û����ı�������
	void SetDC(CDC* pDC);		//���û�ͼ��DC
	CDC* GetDC() { return m_pDC; }

	void DrawWindowText(CRect rect, LPCTSTR lpszString, COLORREF color, Alignment align = Alignment::LEFT);	//��ָ���ľ��������ڻ����ı�
	void DrawRectOutLine(CRect rect, COLORREF color, bool dot_line = false);	//���ƾ��α߿����dot_lineΪtrue����Ϊ����

	void SetDrawRect(CRect rect);

	void DrawBitmap(CBitmap& bitmap, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);
	void DrawBitmap(UINT bitmap_id, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);
	void DrawBitmap(HBITMAP hbitmap, CPoint start_point, CSize size, StretchMode stretch_mode = StretchMode::STRETCH);

	void FillRect(CRect rect, COLORREF color);

private:
	CDC* m_pDC{};		//���ڻ�ͼ��CDC���ָ��
	CWnd* m_pMainWnd{};	//��ͼ���ڵľ��
	CFont* m_pfont{};
};

