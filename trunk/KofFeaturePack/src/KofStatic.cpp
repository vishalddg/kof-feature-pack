// ..\src\KofStatic.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofStatic.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofStatic

IMPLEMENT_DYNAMIC(CKofStatic, CStatic)

CKofStatic::CKofStatic()
{
	m_clrText = (COLORREF)-1;
	m_hFont	= NULL;
}

CKofStatic::~CKofStatic()
{
}

BEGIN_MESSAGE_MAP(CKofStatic, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_ENABLE()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
END_MESSAGE_MAP()

BOOL CKofStatic::OnEraseBkgnd(CDC* pDC)
{
	return CStatic::OnEraseBkgnd(pDC);
}

void CKofStatic::OnNcPaint()
{
	const DWORD dwStyle = GetStyle ();
	BOOL bIsSeparator = (dwStyle & SS_ETCHEDHORZ) == SS_ETCHEDHORZ || (dwStyle & SS_ETCHEDVERT) == SS_ETCHEDVERT;

	if (!bIsSeparator || !CKofStyleHelper::GetInstance()->IsOwnerDrawDlgSeparator(this))
	{
		Default();
		return;
	}

	CWindowDC dc(this);

	CRect rect;
	GetWindowRect (rect);

	rect.bottom -= rect.top;
	rect.right -= rect.left;
	rect.left = rect.top = 0;

	CKofStyleHelper::GetInstance()->OnDrawDlgSeparator(&dc, this, rect, (dwStyle & SS_ETCHEDVERT) != SS_ETCHEDVERT);
}

void CKofStatic::OnPaint()
{
	if (!TRUE && !FALSE)
	{
		Default ();
		return;
	}

	const DWORD dwStyle = GetStyle ();

	if ((dwStyle & SS_ICON) == SS_ICON ||
		(dwStyle & SS_BLACKRECT) == SS_BLACKRECT ||
		(dwStyle & SS_GRAYRECT) == SS_GRAYRECT ||
		(dwStyle & SS_WHITERECT) == SS_WHITERECT ||
		(dwStyle & SS_BLACKFRAME) == SS_BLACKFRAME ||
		(dwStyle & SS_GRAYFRAME) == SS_GRAYFRAME ||
		(dwStyle & SS_WHITEFRAME) == SS_WHITEFRAME ||
		(dwStyle & SS_USERITEM) == SS_USERITEM ||
		(dwStyle & SS_ETCHEDHORZ) == SS_ETCHEDHORZ ||
		(dwStyle & SS_ETCHEDVERT) == SS_ETCHEDVERT)
	{
		Default ();
		return;
	}

	CPaintDC dc(this); // device context for painting

	CMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();

	CRect rectText;
	GetClientRect(rectText);

	afxGlobalData.DrawParentBackground(this, pDC);

	if (m_hFont != NULL && ::GetObjectType (m_hFont) != OBJ_FONT)
	{
		m_hFont = NULL;
	}

	CFont* pOldFont = m_hFont == NULL ?
		(CFont*) pDC->SelectStockObject (DEFAULT_GUI_FONT) :
	pDC->SelectObject (CFont::FromHandle (m_hFont));
	ASSERT(pOldFont != NULL);

	UINT uiDTFlags = DT_WORDBREAK;

	if (dwStyle & SS_CENTER)
	{
		uiDTFlags |= DT_CENTER;
	}
	else if (dwStyle & SS_RIGHT)
	{
		uiDTFlags |= DT_RIGHT;
	}

	if (dwStyle & SS_NOPREFIX)
	{
		uiDTFlags |= DT_NOPREFIX;
	}

	if ((dwStyle & SS_CENTERIMAGE) == SS_CENTERIMAGE)
	{
		uiDTFlags |= DT_SINGLELINE | DT_VCENTER;
	}

	COLORREF clrText = m_clrText == (COLORREF)-1 ? (FALSE ? RGB(0, 0, 0) : afxGlobalData.clrBarText) : m_clrText;
	if (!IsWindowEnabled ())
	{
		clrText = CMFCVisualManager::GetInstance()->GetToolbarDisabledTextColor();
	}

	CString strText;
	GetWindowText(strText);

	if (strText.Find(_T('\t')) >= 0)
	{
		uiDTFlags |= (DT_TABSTOP | 0x40);
	}

	if (!FALSE)
	{
		COLORREF clrTextOld = pDC->SetTextColor(clrText);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strText, rectText, uiDTFlags);
		pDC->SetTextColor(clrTextOld);
	}
	else
	{
	}

	pDC->SelectObject(pOldFont);
}

void CKofStatic::OnEnable(BOOL bEnable)
{
	CStatic::OnEnable(bEnable);

	if (GetParent() != NULL)
	{
		CRect rect;
		GetWindowRect(rect);

		GetParent()->ScreenToClient(&rect);
		GetParent()->RedrawWindow(rect);
	}
}

LRESULT CKofStatic::OnSetText( WPARAM, LPARAM lp )
{
	LRESULT lr = Default();

	if (GetParent () != NULL)
	{
		CRect rect;
		GetWindowRect(rect);

		GetParent()->ScreenToClient(&rect);
		GetParent()->RedrawWindow(rect);
	}

	return lr;
}

LRESULT CKofStatic::OnSetFont( WPARAM wParam, LPARAM lp )
{
	m_hFont = (HFONT) wParam;
	return Default();
}
