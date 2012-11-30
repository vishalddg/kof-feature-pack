// Sheet.cpp : implementation file
//

#include "stdafx.h"
#include "testSDI.h"
#include "Sheet.h"


// CSheet

IMPLEMENT_DYNAMIC(CSheet, CKofMFCPropertySheet)

CSheet::CSheet()
{
	//SetLook (CMFCPropertySheet::PropSheetLook_Tabs);
	//SetLook (CMFCPropertySheet::PropSheetLook_List);
	//SetLook (CMFCPropertySheet::PropSheetLook_Tree);
	//SetLook (CMFCPropertySheet::PropSheetLook_OutlookBar);
	SetLook(CMFCPropertySheet::PropSheetLook_OneNoteTabs);
	SetIconsList(IDB_BITMAP1, 16);
	AddPage(&m_Page1);
	AddPage(&m_Page2);
}

CSheet::~CSheet()
{
}


BEGIN_MESSAGE_MAP(CSheet, CKofMFCPropertySheet)
END_MESSAGE_MAP()



// CSheet message handlers


