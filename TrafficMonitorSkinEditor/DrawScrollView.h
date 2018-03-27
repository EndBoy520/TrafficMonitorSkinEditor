#pragma once
#include "SkinEditorHelper.h"

// DrawScrollView ��ͼ
#define WM_VIEW_MOUSE_CLICK (WM_USER + 1)		//����Scroll View������굥����Ϣ
#define WM_VIEW_MOUSE_DBCLICK (WM_USER + 2)		//����Scroll View�������˫����Ϣ

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

//��Ա����
protected:
	CSize m_size;
	CPoint m_start_point;			//��ͼ����ʼλ��

	SkinData* m_skin_data;

protected:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();     // �����ĵ�һ��

	DECLARE_MESSAGE_MAP()
};


