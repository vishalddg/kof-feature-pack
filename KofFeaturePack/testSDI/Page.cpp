// Page.cpp : implementation file
//

#include "stdafx.h"
#include "testSDI.h"
#include "Page.h"


// CPage1 dialog

IMPLEMENT_DYNAMIC(CPage1, CKofMFCPropertyPage)

CPage1::CPage1()
	: CKofMFCPropertyPage(CPage1::IDD)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CKofMFCPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage1, CKofMFCPropertyPage)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
// CPage2 dialog

IMPLEMENT_DYNAMIC(CPage2, CKofMFCPropertyPage)

CPage2::CPage2()
	: CKofMFCPropertyPage(CPage2::IDD)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CKofMFCPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage2, CKofMFCPropertyPage)
END_MESSAGE_MAP()


// CPage2 message handlers
