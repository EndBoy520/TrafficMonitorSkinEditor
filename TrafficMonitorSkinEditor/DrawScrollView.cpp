// DrawScrollView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawScrollView.h"


// DrawScrollView

IMPLEMENT_DYNCREATE(CDrawScrollView, CScrollView)

CDrawScrollView::CDrawScrollView()
{
}

CDrawScrollView::~CDrawScrollView()
{
}


BEGIN_MESSAGE_MAP(CDrawScrollView, CScrollView)
END_MESSAGE_MAP()


// DrawScrollView ��ͼ

void CDrawScrollView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: �������ͼ�ĺϼƴ�С
	m_size.cx = 0;	
	m_size.cy = 0;	
	SetScrollSizes(MM_TEXT, m_size);

}

void CDrawScrollView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���

}


// DrawScrollView ���
#ifdef _DEBUG
void CDrawScrollView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CDrawScrollView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

void CDrawScrollView::InitialUpdate()
{
	OnInitialUpdate();
}

void CDrawScrollView::SetSize(int width,int hight)
{
	m_size =CSize(width,hight);
	SetScrollSizes(MM_TEXT, m_size);
}

