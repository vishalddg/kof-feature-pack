// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// testSDIDoc.cpp : implementation of the CtestSDIDoc class
//

#include "stdafx.h"
#include "testSDI.h"

#include "testSDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestSDIDoc

IMPLEMENT_DYNCREATE(CtestSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CtestSDIDoc, CDocument)
END_MESSAGE_MAP()


// CtestSDIDoc construction/destruction

CtestSDIDoc::CtestSDIDoc()
{
	// TODO: add one-time construction code here

}

CtestSDIDoc::~CtestSDIDoc()
{
}

BOOL CtestSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CtestSDIDoc serialization

void CtestSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CtestSDIDoc diagnostics

#ifdef _DEBUG
void CtestSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtestSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CtestSDIDoc commands
