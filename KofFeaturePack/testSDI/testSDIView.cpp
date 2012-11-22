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

// testSDIView.cpp : implementation of the CtestSDIView class
//

#include "stdafx.h"
#include "testSDI.h"

#include "testSDIDoc.h"
#include "testSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestSDIView

IMPLEMENT_DYNCREATE(CtestSDIView, CView)

BEGIN_MESSAGE_MAP(CtestSDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CtestSDIView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CtestSDIView construction/destruction

CtestSDIView::CtestSDIView()
{
	// TODO: add construction code here

}

CtestSDIView::~CtestSDIView()
{
}

BOOL CtestSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CtestSDIView drawing

void CtestSDIView::OnDraw(CDC* /*pDC*/)
{
	CtestSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CtestSDIView printing


void CtestSDIView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CtestSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CtestSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CtestSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CtestSDIView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CtestSDIView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CtestSDIView diagnostics

#ifdef _DEBUG
void CtestSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CtestSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestSDIDoc* CtestSDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestSDIDoc)));
	return (CtestSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestSDIView message handlers
