// ..\src\KofFormView.cpp : implementation file

#include "stdafx.h"
#include "..\include\KofFormView.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofFormView

IMPLEMENT_DYNAMIC(CKofFormView, CFormView)

CKofFormView::CKofFormView( LPCTSTR lpszTemplateName )
:CFormView(lpszTemplateName),
m_KImpl(*this)
{

}

CKofFormView::CKofFormView( UINT nIDTemplate )
:CFormView(nIDTemplate),
m_KImpl(*this)
{

}

CKofFormView::~CKofFormView()
{

}

BEGIN_MESSAGE_MAP(CKofFormView, CFormView)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

#ifdef _DEBUG
void CKofFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CKofFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

HBRUSH CKofFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (TRUE)
	{
		HBRUSH hbr = m_KImpl.OnCtlColor(pDC, pWnd, nCtlColor);
		if (hbr != NULL)
		{
			return hbr;
		}
	}	
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

BOOL CKofFormView::OnEraseBkgnd(CDC* pDC)
{
	CRect rectClient;
	GetClientRect (rectClient);

	if (TRUE &&	CKofStyleHelper::GetInstance()->OnFillDialog(pDC, this, rectClient))
	{
		return TRUE;
	}
	return CFormView::OnEraseBkgnd(pDC);
}

void CKofFormView::OnDestroy()
{
	m_KImpl.OnDestroy();
	CFormView::OnDestroy();
}

void CKofFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	if (TRUE)
	{
		m_KImpl.EnableVisualManagerStyle(TRUE);
	}
}

void CKofFormView::EnableVisualManagerStyle( BOOL bEnable /*= TRUE*/, const CList<UINT,UINT>* plstNonSubclassedItems /*= NULL*/ )
{
	m_KImpl.EnableVisualManagerStyle (bEnable, FALSE, plstNonSubclassedItems);
}
