#pragma once
#include "SkinEditorHelper.h"
#include "DrawCommon.h"

// DrawScrollView ��ͼ
class CDrawScrollView : public CScrollView
{
	DECLARE_DYNCREATE(CDrawScrollView)

protected:
	CDrawScrollView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDrawScrollView();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

//��Ա����
public:
	void InitialUpdate();
	void SetSize(int width,int hight);
	void SetSkinData(SkinData* skin_data) { m_skin_data = skin_data; }
	void SetBackImage(CImage* background_s, CImage* background_l);
	void SetShowItemOutline(bool* show_item_outline) { m_show_item_outline = show_item_outline; }
	void SetFont(CFont* pfont) { m_font = pfont; }

//��Ա����
protected:
	CSize m_size;
	CPoint m_start_point;			//��ͼ����ʼλ��

	SkinData* m_skin_data;
	CImage* m_background_s;
	CImage* m_background_l;
	bool* m_show_item_outline;
	CFont* m_font;

	const COLORREF m_outline_color{ RGB(96,96,96) };

protected:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();     // �����ĵ�һ��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


