// Sheet.cpp : implementation file
//

#include "stdafx.h"
#include "testSDI.h"
#include "Sheet.h"


// CSheet

IMPLEMENT_DYNAMIC(CSheet, CKofMFCPropertySheet)

CSheet::CSheet()
{
	SetLook (CMFCPropertySheet::PropSheetLook_List);
	AddPage(&m_Page1);
	AddPage(&m_Page2);
}

CSheet::~CSheet()
{
}


BEGIN_MESSAGE_MAP(CSheet, CKofMFCPropertySheet)
END_MESSAGE_MAP()



// CSheet message handlers


