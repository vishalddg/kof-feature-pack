// ..\src\KofMFCPropertyPage.cpp : implementation file

#include "stdafx.h"
#include "..\include\KofMFCPropertyPage.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCPropertyPage

IMPLEMENT_DYNCREATE(CKofMFCPropertyPage, CMFCPropertyPage)

CKofMFCPropertyPage::CKofMFCPropertyPage()
:m_KImpl(*this)
{

}

CKofMFCPropertyPage::CKofMFCPropertyPage( UINT nIDTemplate, UINT nIDCaption /*= 0*/ )
:CMFCPropertyPage(nIDTemplate, nIDCaption),
m_KImpl(*this)
{

}

CKofMFCPropertyPage::CKofMFCPropertyPage( LPCTSTR lpszTemplateName, UINT nIDCaption /*= 0*/ )
:CMFCPropertyPage(lpszTemplateName, nIDCaption),
m_KImpl(*this)
{

}

CKofMFCPropertyPage::~CKofMFCPropertyPage()
{
}

BEGIN_MESSAGE_MAP(CKofMFCPropertyPage, CMFCPropertyPage)
	ON_WM_ACTIVATE()
	ON_WM_NCACTIVATE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()

void CKofMFCPropertyPage::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CMFCPropertyPage::OnActivate(nState, pWndOther, bMinimized);
	m_KImpl.OnActivate(nState, pWndOther);
}

BOOL CKofMFCPropertyPage::OnNcActivate(BOOL bActive)
{
	m_KImpl.OnNcActivate(bActive);
	return (BOOL) DefWindowProc (WM_NCACTIVATE, bActive, 0L);
}

BOOL CKofMFCPropertyPage::OnEraseBkgnd(CDC* pDC)
{
	BOOL bRes = TRUE;

	CRect rectClient;
	GetClientRect (rectClient);

	if (TRUE)
	{
		if (!CKofStyleHelper::GetInstance()->OnFillDialog(pDC, this, rectClient))
		{
			bRes = CPropertyPage::OnEraseBkgnd (pDC);
		}
	}	
	else
	{
		bRes = CPropertyPage::OnEraseBkgnd(pDC);
	}

	CMFCPropertySheet* pParent = DYNAMIC_DOWNCAST(CMFCPropertySheet, GetParent());
	if (pParent != NULL && pParent->GetHeaderHeight() > 0)
	{
		CRect rectClient;
		GetClientRect(rectClient);

		CRect rectHeader = rectClient;
		rectHeader.bottom = rectHeader.top + pParent->GetHeaderHeight();

		if (pParent->GetLook() == CMFCPropertySheet::PropSheetLook_OutlookBar ||
			pParent->GetLook() == CMFCPropertySheet::PropSheetLook_Tree || pParent->GetLook() == CMFCPropertySheet::PropSheetLook_List)
		{
			CRect rectParent;
			pParent->GetWindowRect(rectParent);

			ScreenToClient(rectParent);

			rectHeader.right = rectParent.right - ::GetSystemMetrics(SM_CXDLGFRAME);
		}

		pParent->OnDrawPageHeader(pDC, pParent->GetPageIndex(this), rectHeader);
	}

	return bRes;
}

HBRUSH CKofMFCPropertyPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (TRUE)
	{
		HBRUSH hbr = m_KImpl.OnCtlColor(pDC, pWnd, nCtlColor);
		if (hbr != NULL)
		{
			return hbr;
		}
	}	
	HBRUSH hbr = CMFCPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

void CKofMFCPropertyPage::OnDestroy()
{
	m_KImpl.OnDestroy();
	CMFCPropertyPage::OnDestroy();
}

void CKofMFCPropertyPage::OnNcPaint()
{
	if (FALSE)
	{
		Default();
	}
}

BOOL CKofMFCPropertyPage::OnInitDialog()
{
	BOOL bRes = CMFCPropertyPage::OnInitDialog();

	EnableVisualManagerStyle(TRUE);
	return bRes; 
}

void CKofMFCPropertyPage::EnableVisualManagerStyle( BOOL bEnable /*= TRUE*/, const CList<UINT,UINT>* plstNonSubclassedItems /*= NULL*/ )
{
	m_KImpl.EnableVisualManagerStyle(bEnable, FALSE, plstNonSubclassedItems);
}
