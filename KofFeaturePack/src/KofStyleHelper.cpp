#include "StdAfx.h"
#include "..\include\KofStyleHelper.h"
#include "..\include\KofResource.h"
#include "..\include\KofDialogEx.h"
#include "..\include\KofMFCPropertySheet.h"
#include "afxtagmanager.h"

extern HINSTANCE theInstance;

class CKofMFCVisualManager : public CMFCVisualManager
{
	friend class CKofStyleHelper;
};
class CKofMFCVisualManagerOfficeXP : public CMFCVisualManagerOfficeXP
{
	friend class CKofStyleHelper;
};
class CKofMFCVisualManagerOffice2003 : public CMFCVisualManagerOffice2003
{
	friend class CKofStyleHelper;
};
class CKofMFCVisualManagerOffice2007 : public CMFCVisualManagerOffice2007
{
	friend class CKofStyleHelper;
};
class CKofMFCVisualManagerVS2005 : public CMFCVisualManagerVS2005
{
	friend class CKofStyleHelper;
};
class CKofMFCVisualManagerWindows : public CMFCVisualManagerWindows
{
	friend class CKofStyleHelper;
};

class CKofMFCToolBarComboBoxButton : public CMFCToolBarComboBoxButton
{
	friend class CKofStyleHelper;
};

//////////////////////////////////////////////////////////////////////////
// CKofStyleHelper

CKofStyleHelper::CKofStyleHelper(void)
:m_Style(KOF_MAXCOUNT)
{
	m_clrDlgBackground = (COLORREF)-1;
	m_clrRibbonEditBorder = (COLORREF)-1;
	m_clrRibbonEditBorderDisabled = (COLORREF)-1;
	m_clrRibbonEditBorderHighlighted = (COLORREF)-1;
	m_clrRibbonEditBorderPressed = (COLORREF)-1;
	m_bDlgCaptionCenter = FALSE;
}

CKofStyleHelper::~CKofStyleHelper(void)
{
	m_clrDlgBackground = (COLORREF)-1;
	m_brDlgBackground.DeleteObject();
	m_ctrlRibbonBtnPush.CleanUp();
	m_ctrlRibbonBtnRadio.CleanUp();
}

BOOL CKofStyleHelper::SetStyle( UINT nStyle )
{
	if (nStyle >= KOF_MAXCOUNT)
	{
		return FALSE;
	}

	m_Style = nStyle;
	UINT style2007 = 4;
	if (KOF_CMFCVisualManagerOffice2007 == m_Style)
	{
		style2007 = CMFCVisualManagerOffice2007::GetStyle();
	}

	switch (m_Style)
	{
	case KOF_CMFCVisualManagerOffice2007:
		{
			//HINSTANCE saveInstance = AfxGetResourceHandle();
			//AfxSetResourceHandle(theInstance);			

			m_clrDlgBackground = afxGlobalData.clrBarLight;
			UINT nIDPush = 0, nIDRadio = 0, nIDGroup = 0;
			CString strPushItem = _T("<SIZE>102, 22</SIZE><CORNERS>3, 4, 3, 3</CORNERS>"),
					strRadioItem = _T("<SIZE>13, 13</SIZE>"),
					strGroupItem = _T("<SIZE>7, 7</SIZE><CORNERS>3, 3, 3, 3</CORNERS><SIDES>2, 2, 2, 2</SIDES>");
			switch (style2007)
			{
			case CMFCVisualManagerOffice2007::Office2007_LunaBlue:	
				m_clrDlgBackground = RGB(213, 228, 242);
				nIDPush = BLUE_IDB_OFFICE2007_RIBBON_BUTTONS_PUSH;
				nIDRadio = BLUE_IDB_OFFICE2007_RIBBON_BUTTONS_RADIO;
				nIDGroup = BLUE_IDB_OFFICE2007_RIBBON_BUTTONS_GROUP;
				break;
			case CMFCVisualManagerOffice2007::Office2007_ObsidianBlack:				
				nIDPush = BLACK_IDB_OFFICE2007_RIBBON_BUTTONS_PUSH;
				nIDRadio = BLACK_IDB_OFFICE2007_RIBBON_BUTTONS_RADIO;
				nIDGroup = BLACK_IDB_OFFICE2007_RIBBON_BUTTONS_GROUP;
				break;
			case CMFCVisualManagerOffice2007::Office2007_Aqua:			
				nIDPush = AQUA_IDB_OFFICE2007_RIBBON_BUTTONS_PUSH;
				nIDRadio = AQUA_IDB_OFFICE2007_RIBBON_BUTTONS_RADIO;
				nIDGroup = AQUA_IDB_OFFICE2007_RIBBON_BUTTONS_GROUP;
				strPushItem = _T("<SIZE>22, 22</SIZE><CORNERS>2, 2, 2, 2</CORNERS>");
				break;
			case CMFCVisualManagerOffice2007::Office2007_Silver:				
				nIDPush = SILVER_IDB_OFFICE2007_RIBBON_BUTTONS_PUSH;
				nIDRadio = SILVER_IDB_OFFICE2007_RIBBON_BUTTONS_RADIO;
				nIDGroup = SILVER_IDB_OFFICE2007_RIBBON_BUTTONS_GROUP;
				break;
			}
			CKofMFCVisualManagerOffice2007 *pVisualManager = (CKofMFCVisualManagerOffice2007 *)CMFCVisualManager::GetInstance();
			if (pVisualManager)
			{
				m_clrRibbonEditBorder = pVisualManager->m_clrRibbonEditBorder;
				m_clrRibbonEditBorderDisabled = pVisualManager->m_clrRibbonEditBorderDisabled;
				m_clrRibbonEditBorderHighlighted = pVisualManager->m_clrRibbonEditBorderHighlighted;
				m_clrRibbonEditBorderPressed = pVisualManager->m_clrRibbonEditBorderPressed;
			}			
			m_ctrlRibbonBtnPush.CleanUp();
			CMFCControlRendererInfo params(MAKEINTRESOURCE(nIDPush), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0));
			if (CTagManager::ParseControlRendererInfo(strPushItem, params))
			{
				m_ctrlRibbonBtnPush.Create(params);
			}

			m_ctrlRibbonBtnRadio.CleanUp();
			CMFCControlRendererInfo params2(MAKEINTRESOURCE(nIDRadio), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0));
			if (CTagManager::ParseControlRendererInfo(strRadioItem, params2))
			{
				m_ctrlRibbonBtnRadio.Create(params2);
			}

			m_ctrlRibbonBtnGroup.CleanUp();
			CMFCControlRendererInfo params3(MAKEINTRESOURCE(nIDGroup), CRect(0, 0, 0, 0), CRect(0, 0, 0, 0));
			if (CTagManager::ParseControlRendererInfo(strGroupItem, params3))
			{
				m_ctrlRibbonBtnGroup.Create(params3);
			}

			//AfxSetResourceHandle(saveInstance);
		}
		break;
	default:
		{
			m_clrDlgBackground = afxGlobalData.clrBarFace;
			m_clrRibbonEditBorder = afxGlobalData.clrBarShadow;
			m_clrRibbonEditBorderDisabled = m_clrRibbonEditBorder;
			m_clrRibbonEditBorderHighlighted = m_clrRibbonEditBorder;
			m_clrRibbonEditBorderPressed = m_clrRibbonEditBorder;
		}
	}
	m_brDlgBackground.DeleteObject();
	m_brDlgBackground.CreateSolidBrush(m_clrDlgBackground);
	return TRUE;
}

BOOL CKofStyleHelper::OnFillDialog( CDC* pDC, CWnd* pDlg, CRect rect )
{
	ASSERT_VALID (pDC);
	pDC->FillRect (rect, &GetDlgBackBrush(pDlg));

	return TRUE;
}

CBrush& CKofStyleHelper::GetDlgBackBrush( CWnd* pDlg )
{
	pDlg;
	return m_brDlgBackground;
}

CSize CKofStyleHelper::GetCheckRadioDefaultSize()
{
	// 这边简化了
	if (KOF_CMFCVisualManagerOffice2007 == m_Style)
	{
		return CSize (15, 15);
	}

	return CSize (::GetSystemMetrics (SM_CXMENUCHECK) + 1, ::GetSystemMetrics (SM_CYMENUCHECK) + 1);
}

void CKofStyleHelper::OnDrawRadioButton( CDC *pDC, CRect rect, BOOL bOn, BOOL bHighlighted, BOOL bPressed, BOOL bEnabled )
{
	switch (m_Style)
	{
	case KOF_CMFCVisualManagerWindows:
	case KOF_CMFCVisualManagerOffice2003:
	case KOF_CMFCVisualManagerVS2005:
		if (CMFCVisualManager::GetInstance()->DrawRadioButton(pDC, rect, bHighlighted, bOn, bEnabled, bPressed))
		{
			return;
		}
		break;
	case KOF_CMFCVisualManagerOffice2007:
		if (Draw2007RadioButton(pDC, rect, bHighlighted, bOn, bEnabled, bPressed))
		{
			return;
		}
		break;
	}
	CDrawingManager dm (*pDC);

	rect.DeflateRect (1, 1);

	dm.DrawEllipse (rect,
		bEnabled ? afxGlobalData.clrBarHilite : afxGlobalData.clrBarFace,
		bHighlighted && bEnabled ? afxGlobalData.clrBarDkShadow : afxGlobalData.clrBarShadow);

	if (bOn)
	{
		rect.DeflateRect (rect.Width () / 3, rect.Width () / 3);

		dm.DrawEllipse (rect,
			bHighlighted && bEnabled ? afxGlobalData.clrBarDkShadow : afxGlobalData.clrBarShadow,
			(COLORREF)-1);
	}
}

BOOL CKofStyleHelper::OnDrawPushButton( CDC* pDC, CRect rect, CKofMFCButton* pButton, COLORREF& clrText )
{
	switch (m_Style)
	{
	case KOF_CMFCVisualManagerWindows:
	case KOF_CMFCVisualManagerOffice2003:
	case KOF_CMFCVisualManagerVS2005:
		{
			CKofMFCVisualManagerOfficeXP *pVisualManager = (CKofMFCVisualManagerOfficeXP *)CMFCVisualManager::GetInstance();
			if (!pVisualManager)
			{
				break;
			}
			ASSERT_VALID (pDC);
			ASSERT_VALID (pButton);

			CDrawingManager dm (*pDC);

			COLORREF clrFace = afxGlobalData.clrBarFace;

			if (!pButton->IsWindowEnabled ())
			{
				if (FALSE)
				{
					dm.DrawRect (rect, clrFace, afxGlobalData.clrBarShadow);
				}
				else
				{
					pDC->FillRect (rect, &afxGlobalData.brBarFace);
					pDC->Draw3dRect (rect, afxGlobalData.clrBarShadow, afxGlobalData.clrBarShadow);
				}
			}
			else if (pButton->IsPressed () || pButton->GetCheck ())
			{
				pVisualManager->OnFillHighlightedArea (pDC, rect, &pVisualManager->m_brHighlightDn, NULL);

				if (FALSE)
				{
					dm.DrawRect (rect, (COLORREF)-1, pVisualManager->m_clrMenuItemBorder);
				}
				else
				{
					pDC->Draw3dRect (rect, pVisualManager->m_clrMenuItemBorder, pVisualManager->m_clrMenuItemBorder);
				}

				clrFace = pVisualManager->m_clrHighlightDn;
			}
			else if (pButton->IsHighlighted () || CWnd::GetFocus () == pButton)
			{
				pVisualManager->OnFillHighlightedArea (pDC, rect, &pVisualManager->m_brHighlight, NULL);

				if (FALSE)
				{
					dm.DrawRect (rect, (COLORREF)-1, pVisualManager->m_clrMenuItemBorder);
				}
				else
				{
					pDC->Draw3dRect (rect, pVisualManager->m_clrMenuItemBorder, pVisualManager->m_clrMenuItemBorder);
				}

				clrFace = pVisualManager->m_clrHighlight;
			}
			else
			{
				if (FALSE)
				{
					dm.DrawRect (rect, clrFace, afxGlobalData.clrBarDkShadow);
				}
				else
				{
					pDC->FillRect (rect, &afxGlobalData.brBarFace);
					pDC->Draw3dRect (rect, afxGlobalData.clrBarDkShadow, afxGlobalData.clrBarDkShadow);
				}
			}

			if (GetRValue (clrFace) <= 128 ||
				GetGValue (clrFace) <= 128 ||
				GetBValue (clrFace) <= 128)
			{
				clrText = RGB (255, 255, 255);
			}

			return TRUE;
		}
		break;
	case KOF_CMFCVisualManagerOffice2007:
		{
			ASSERT_VALID (pDC);
			ASSERT_VALID (pButton);

			int index = 0;

			BOOL bDisabled    = !pButton->IsWindowEnabled ();
			BOOL bFocused     = pButton->GetSafeHwnd () == ::GetFocus ();
			BOOL bDefault     = pButton->IsDefaultButton ();
			BOOL bPressed     = pButton->IsPressed ();
			BOOL bChecked     = pButton->IsChecked ();
			BOOL bHighlighted = pButton->IsHighlighted ();

			bHighlighted |= bFocused;

			if (bDisabled)
			{
				index = 6;
			}
			else
			{
				if (bChecked)
				{
					index = 3;
				}
				else
				{
					if (bDefault && !bHighlighted)
					{
						index = 5;
					}
				}

				if (bPressed)
				{
					if (bHighlighted)
					{
						index = 2;
					}
				}
				else if (bHighlighted)
				{
					index++;
				}
			}

			afxGlobalData.DrawParentBackground (pButton, pDC);
			m_ctrlRibbonBtnPush.Draw (pDC, rect, index);

			CKofMFCVisualManagerOffice2007 *pVisualManager = (CKofMFCVisualManagerOffice2007 *)CMFCVisualManager::GetInstance();
			if (!pVisualManager)
			{
				return TRUE;
			}
			if (bDisabled)
			{
				clrText = pVisualManager->m_clrToolBarBtnTextDisabled;
			}
			else if (bHighlighted)
			{
				clrText = pVisualManager->m_clrToolBarBtnTextHighlighted;
			}

			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CKofStyleHelper::IsOwnerDrawDlgSeparator( CWnd* /*pCtrl*/ )
{
	if (KOF_CMFCVisualManagerOffice2007 == m_Style)
	{
		return TRUE;
	}
	return FALSE;
}

void CKofStyleHelper::OnDrawDlgSeparator( CDC* pDC, CWnd* pCtrl, CRect rect, BOOL bIsHorz )
{
	if (KOF_CMFCVisualManagerOffice2007 != m_Style)
	{
		return;
	}
	CPen pen1(PS_SOLID, 0, afxGlobalData.clrBarShadow);
	CPen pen2(PS_SOLID, 0, afxGlobalData.clrBarLight);

	CRect rect1(rect);
	CRect rect2;

	if (bIsHorz)
	{
		rect1.top += rect.Height() / 2 - 1;
		rect1.bottom = rect1.top;
		rect2 = rect1;
		rect2.OffsetRect(0, 1);
	}
	else
	{
		rect1.left += rect.Width() / 2 - 1;
		rect1.right = rect1.left;
		rect2 = rect1;
		rect2.OffsetRect(1, 0);
	}

	if (CMFCToolBarImages::m_bIsDrawOnGlass)
	{
		CDrawingManager dm(*pDC);

		LOGPEN logpen;

		pen1.GetLogPen(&logpen);
		dm.DrawLine(rect1.left, rect1.top, rect1.right, rect1.bottom, logpen.lopnColor);

		pen2.GetLogPen(&logpen);
		dm.DrawLine(rect2.left, rect2.top, rect2.right, rect2.bottom, logpen.lopnColor);
	}
	else
	{
		CPen* pOldPen = pDC->SelectObject(&pen1);
		pDC->MoveTo(rect1.TopLeft());
		pDC->LineTo(rect1.BottomRight());

		pDC->SelectObject(&pen2);
		pDC->MoveTo(rect2.TopLeft());
		pDC->LineTo(rect2.BottomRight());

		pDC->SelectObject(pOldPen);
	}
}

void CKofStyleHelper::OnDrawEditBorder( CDC* pDC, CRect rect, BOOL bHighlighted, BOOL bDroppedDowned, BOOL bEnabled )
{
	COLORREF colorBorder = m_clrRibbonEditBorder;

	if (!bEnabled)
	{
		colorBorder = m_clrRibbonEditBorderDisabled;
	}
	else if (bHighlighted || bDroppedDowned)
	{
		colorBorder = bDroppedDowned ? m_clrRibbonEditBorderPressed : m_clrRibbonEditBorderHighlighted;
	}

	pDC->Draw3dRect(rect, colorBorder, colorBorder);
}

void CKofStyleHelper::OnDrawRibbonComboDropButton( CDC* pDC, CRect rect, BOOL bDisabled, BOOL bIsDropped, BOOL bIsHighlighted )
{
	CKofMFCToolBarComboBoxButton buttonDummy;
	buttonDummy.m_bIsRibbon = TRUE;
	CMFCVisualManager::GetInstance ()->OnDrawComboDropButton (
		pDC, rect, bDisabled, bIsDropped,
		bIsHighlighted,
		&buttonDummy);
}

void CKofStyleHelper::OnEditContextMenu( CWnd* pWnd, CPoint point )
{
	pWnd->SetFocus();

	CEdit *pEdit = DYNAMIC_DOWNCAST(CEdit, pWnd);
	CRichEditCtrl *pRichEdit = DYNAMIC_DOWNCAST(CRichEditCtrl, pWnd);
	if (NULL == pEdit && NULL == pRichEdit)
	{
		return;
	}

	const UINT idCut		= (UINT) -10002;
	const UINT idCopy		= (UINT) -10003;
	const UINT idPaste		= (UINT) -10004;
	const UINT idSelectAll	= (UINT) -10005;

	CString strItem;
	TCHAR szFullText [256];

	CMenu menu;
	menu.CreatePopupMenu ();

	AfxLoadString (ID_EDIT_CUT, szFullText);	
	AfxExtractSubString (strItem, szFullText, 1, '\n');
	menu.AppendMenu (MF_STRING, idCut, strItem.IsEmpty() ? _T("剪切") : strItem);

	AfxLoadString (ID_EDIT_COPY, szFullText);
	AfxExtractSubString (strItem, szFullText, 1, '\n');
	menu.AppendMenu (MF_STRING, idCopy, strItem.IsEmpty() ? _T("复制") : strItem);

	AfxLoadString (ID_EDIT_PASTE, szFullText);
	AfxExtractSubString (strItem, szFullText, 1, '\n');
	menu.AppendMenu (MF_STRING, idPaste, strItem.IsEmpty() ? _T("粘贴") : strItem);

	menu.AppendMenu (MF_SEPARATOR);

	AfxLoadString (ID_EDIT_SELECT_ALL, szFullText);
	AfxExtractSubString (strItem, szFullText, 1, '\n');
	menu.AppendMenu (MF_STRING, idSelectAll, strItem.IsEmpty() ? _T("全选") : strItem);

#ifdef _UNICODE
	#define _TCF_TEXT	CF_UNICODETEXT
#else
	#define _TCF_TEXT	CF_TEXT
#endif

	if (!::IsClipboardFormatAvailable (_TCF_TEXT))
	{
		menu.EnableMenuItem (idPaste, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	long nStart, nEnd;
	if (pEdit)
	{
		int niStart, niEnd;
		pEdit->GetSel (niStart, niEnd);
		nStart = niStart;
		nEnd = niEnd;
	} 
	else
	{
		pRichEdit->GetSel (nStart, nEnd);
	}

	if (nEnd <= nStart)
	{
		menu.EnableMenuItem (idCopy, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		menu.EnableMenuItem (idCut, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	if (pWnd->GetWindowTextLength () == 0)
	{
		menu.EnableMenuItem (idSelectAll, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
	int nMenuResult = 0;
	if (((CWinAppEx*)AfxGetApp())->GetContextMenuManager() != NULL)
	{
		nMenuResult = ((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->TrackPopupMenu (
			menu, point.x, point.y, pWnd);
	} 
	else
	{
		nMenuResult = menu.TrackPopupMenu(TPM_LEFTBUTTON | TPM_RETURNCMD, point.x, point.y, pWnd);
	}

	if (pEdit)
	{
		switch (nMenuResult)
		{
		case idCut:
			pEdit->Cut ();
			break;

		case idCopy:
			pEdit->Copy ();
			break;

		case idPaste:
			pEdit->Paste ();
			break;

		case idSelectAll:
			pEdit->SetSel (0, -1);
			break;
		}
	} 
	else
	{
		switch (nMenuResult)
		{
		case idCut:
			pRichEdit->Cut ();
			break;

		case idCopy:
			pRichEdit->Copy ();
			break;

		case idPaste:
			pRichEdit->Paste ();
			break;

		case idSelectAll:
			pRichEdit->SetSel (0, -1);
			break;
		}
	}	
}

BOOL CKofStyleHelper::Draw2007RadioButton( CDC *pDC, CRect rect, BOOL bHighlighted, BOOL bChecked, BOOL bEnabled, BOOL bPressed )
{
	int index = bChecked ? 4 : 0;

	if (!bEnabled)
	{
		index += 3;
	}
	else if (bPressed)
	{
		if (bHighlighted)
		{
			index += 2;
		}
	}
	else if (bHighlighted)
	{
		index += 1;
	}

	if (afxGlobalData.m_bIsRTL)
	{
		m_ctrlRibbonBtnRadio.Mirror ();
	}

	m_ctrlRibbonBtnRadio.FillInterior (pDC, rect, 
		CMFCToolBarImages::ImageAlignHorzCenter, 
		CMFCToolBarImages::ImageAlignVertCenter,
		index);

	if (afxGlobalData.m_bIsRTL)
	{
		m_ctrlRibbonBtnRadio.Mirror ();
	}

	return TRUE;
}

void CKofStyleHelper::OnDrawGroup( CDC* pDC, CKofGroup* pGroup, CRect rect, const CString& strName )
{
	if (KOF_CMFCVisualManagerOffice2007 == m_Style)
	{
		ASSERT_VALID (pDC);
		ASSERT_VALID (pGroup);

		CSize sizeText = pDC->GetTextExtent (strName);

		CRect rectFrame = rect;
		rectFrame.top += sizeText.cy / 2;

		if (sizeText == CSize (0, 0))
		{
			rectFrame.top += pDC->GetTextExtent (_T("A")).cy / 2;
		}

		int xMargin = sizeText.cy / 2;

		CRect rectText = rect;
		rectText.left += xMargin;
		rectText.right = rectText.left + sizeText.cx + xMargin;
		rectText.bottom = rectText.top + sizeText.cy;

		if (!strName.IsEmpty ())
		{
			pDC->ExcludeClipRect (rectText);
		}

		m_ctrlRibbonBtnGroup.DrawFrame (pDC, rectFrame);

		pDC->SelectClipRgn (NULL);

		if (strName.IsEmpty ())
		{
			return;
		}

		DWORD dwTextStyle = DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_NOCLIP;

		if (FALSE)
		{
			//DrawTextOnGlass (pDC, strName, rectText, dwTextStyle, 10, afxGlobalData.clrBarText);
		}
		else
		{
			CString strCaption = strName;
			pDC->DrawText (strCaption, rectText, dwTextStyle);
		}
		return;
	}
	ASSERT_VALID (pDC);
	ASSERT_VALID (pGroup);

	CSize sizeText = pDC->GetTextExtent (strName);

	CRect rectFrame = rect;
	rectFrame.top += sizeText.cy / 2;

	if (sizeText == CSize (0, 0))
	{
		rectFrame.top += pDC->GetTextExtent (_T("A")).cy / 2;
	}

	int xMargin = sizeText.cy / 2;

	CRect rectText = rect;
	rectText.left += xMargin;
	rectText.right = rectText.left + sizeText.cx + xMargin;
	rectText.bottom = rectText.top + sizeText.cy;

	if (!strName.IsEmpty ())
	{
		pDC->ExcludeClipRect (rectText);
	}
	CKofMFCVisualManagerOfficeXP *pVisualManager = (CKofMFCVisualManagerOfficeXP *)CMFCVisualManager::GetInstance();
	if (!pVisualManager)
	{
		return;
	}
	if (pVisualManager->m_pfDrawThemeBackground != NULL && pVisualManager->m_hThemeButton != NULL && !FALSE)
	{
		(*pVisualManager->m_pfDrawThemeBackground) (pVisualManager->m_hThemeButton, pDC->GetSafeHdc(), BP_GROUPBOX, 
			pGroup->IsWindowEnabled () ? GBS_NORMAL : GBS_DISABLED, &rectFrame, 0);
	}
	else
	{
		CDrawingManager dm (*pDC);
		dm.DrawRect (rectFrame, (COLORREF)-1, afxGlobalData.clrBarDkShadow);
	}

	pDC->SelectClipRgn (NULL);

	if (strName.IsEmpty ())
	{
		return;
	}

	DWORD dwTextStyle = DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_NOCLIP;

	if (FALSE)
	{
		//DrawTextOnGlass (pDC, strName, rectText, dwTextStyle, 10, afxGlobalData.clrBarText);
	}
	else
	{
		CString strCaption = strName;
		pDC->DrawText (strCaption, rectText, dwTextStyle);
	}
}

BOOL CKofStyleHelper::OnNcPaint( CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw )
{
	if (KOF_CMFCVisualManagerOffice2007 != m_Style)
	{
		return CMFCVisualManager::GetInstance()->OnNcPaint(pWnd, lstSysButtons, rectRedraw);
	}
	CKofMFCVisualManagerOffice2007 *pVisualManager = (CKofMFCVisualManagerOffice2007 *)CMFCVisualManager::GetInstance();
	if (!pVisualManager)
	{
		return CMFCVisualManager::GetInstance()->OnNcPaint(pWnd, lstSysButtons, rectRedraw);
	}
	ASSERT_VALID(pWnd);

	if (pWnd->GetSafeHwnd() == NULL)
	{
		return FALSE;
	}

	CWindowDC dc(pWnd);

	if (dc.GetSafeHdc() != NULL)
	{
		CRgn rgn;
		if (!rectRedraw.IsRectEmpty())
		{
			rgn.CreateRectRgnIndirect(rectRedraw);
			dc.SelectClipRgn(&rgn);
		}


		CMFCRibbonBar* pBar = pVisualManager->GetRibbonBar(pWnd);
		BOOL bRibbonCaption  = pBar != NULL && pBar->IsWindowVisible() && pBar->IsReplaceFrameCaption();

		CRect rtWindow;
		pWnd->GetWindowRect(rtWindow);
		pWnd->ScreenToClient(rtWindow);

		CRect rtClient;
		pWnd->GetClientRect(rtClient);

		rtClient.OffsetRect(-rtWindow.TopLeft());
		dc.ExcludeClipRect(rtClient);

		rtWindow.OffsetRect(-rtWindow.TopLeft());

		BOOL bActive = pVisualManager->IsWindowActive(pWnd);

		// Modify bActive (if currently TRUE) for owner-drawn MDI child windows: draw child
		// frame active only if window is active MDI child and the MDI frame window is active.
		if (bActive && pVisualManager->IsOwnerDrawCaption() && pWnd->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)))
		{
			CMDIFrameWnd *pParent = ((CMDIChildWnd *)pWnd)->GetMDIFrame();
			if (pParent)
			{
				CMDIChildWnd *pActiveChild = pParent->MDIGetActive(NULL);
				if (pActiveChild)
				{
					bActive = ((pActiveChild->GetSafeHwnd() == pWnd->GetSafeHwnd()) && pVisualManager->IsWindowActive(pParent));
				}
			}
		}

		CRect rectCaption(rtWindow);
		CSize szSysBorder(pVisualManager->GetSystemBorders(bRibbonCaption));

		BOOL bDialog = pWnd->IsKindOf (RUNTIME_CLASS (CKofDialogEx)) || pWnd->IsKindOf (RUNTIME_CLASS (CKofMFCPropertySheet));
		if (bDialog && (pWnd->GetStyle () & WS_THICKFRAME) == 0)
		{
			szSysBorder.cy = ::GetSystemMetrics (SM_CYFIXEDFRAME);
		}

		rectCaption.bottom = rectCaption.top + szSysBorder.cy;

		const DWORD dwStyle = pWnd->GetStyle();
		BOOL bMaximized = (dwStyle & WS_MAXIMIZE) == WS_MAXIMIZE;

		if (!bRibbonCaption)
		{
			const int nSysCaptionHeight = ::GetSystemMetrics(SM_CYCAPTION);
			rectCaption.bottom += nSysCaptionHeight;

			const DWORD dwStyleEx = pWnd->GetExStyle();

			HICON hIcon = pWnd->GetIcon(FALSE);

			if (hIcon == NULL)
			{
				hIcon = pWnd->GetIcon(TRUE);

				if (hIcon != NULL)
				{
					CImageList il;
					il.Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 1);
					il.Add(hIcon);

					if (il.GetImageCount() == 1)
					{
						hIcon = il.ExtractIcon(0);
					}
				}
			}

			if (hIcon == NULL)
			{
				hIcon = (HICON)(LONG_PTR)::GetClassLongPtr(pWnd->GetSafeHwnd(), GCLP_HICONSM);
			}

			if (hIcon == NULL)
			{
				hIcon = (HICON)(LONG_PTR)::GetClassLongPtr(pWnd->GetSafeHwnd(), GCLP_HICON);
			}

			CString strText;
			pWnd->GetWindowText(strText);

			CString strTitle(strText);
			CString strDocument;

			BOOL bPrefix = FALSE;
			if ((dwStyle & FWS_ADDTOTITLE) == FWS_ADDTOTITLE)
			{
				bPrefix = (dwStyle & FWS_PREFIXTITLE) == FWS_PREFIXTITLE;
				CFrameWnd* pFrameWnd = DYNAMIC_DOWNCAST(CFrameWnd, pWnd);

				if (pFrameWnd != NULL)
				{
					strTitle = pFrameWnd->GetTitle();

					if (!strTitle.IsEmpty())
					{
						int pos = strText.Find(strTitle);

						if (pos != -1)
						{
							if (strText.GetLength() > strTitle.GetLength())
							{
								if (pos == 0)
								{
									bPrefix = FALSE; // avoid exception
									strTitle = strText.Left(strTitle.GetLength() + 3);
									strDocument = strText.Right(strText.GetLength() - strTitle.GetLength());
								}
								else
								{
									strTitle = strText.Right(strTitle.GetLength() + 3);
									strDocument = strText.Left(strText.GetLength() - strTitle.GetLength());
								}
							}
						}
					}
					else
					{
						strDocument = strText;
					}
				}
			}

			if (bMaximized)
			{
				rectCaption.InflateRect(szSysBorder.cx, szSysBorder.cy, szSysBorder.cx, 0);
			}

			if (m_bDlgCaptionCenter)
			{
				pVisualManager->DrawNcCaption(&dc, rectCaption, dwStyle, dwStyleEx, strTitle, strDocument, hIcon, bPrefix, bActive, pVisualManager->m_bNcTextCenter, lstSysButtons);
			} 
			else
			{
				pVisualManager->DrawNcCaption(&dc, rectCaption, dwStyle, dwStyleEx, strTitle, strDocument, hIcon, bPrefix, bActive, FALSE, lstSysButtons);
			}

			if (hIcon)
			{
				DestroyIcon(hIcon);
			}
			if (bMaximized)
			{
				return TRUE;
			}
		}

		else
		{
			if (bMaximized)
			{
				return TRUE;
			}

			rectCaption.bottom += pBar->GetCaptionHeight();

			CRect rectBorder(pVisualManager->m_ctrlMainBorderCaption.GetParams().m_rectSides);

			if (pVisualManager->IsBeta())
			{
				COLORREF clr1  = bActive ? pVisualManager->m_clrAppCaptionActiveStart : pVisualManager->m_clrAppCaptionInactiveStart;
				COLORREF clr2  = bActive ? pVisualManager->m_clrAppCaptionActiveFinish : pVisualManager->m_clrAppCaptionInactiveFinish;

				CRect rectCaption2(rectCaption);
				rectCaption2.DeflateRect(rectBorder.left, rectBorder.top, rectBorder.right, rectBorder.bottom);

				{
					CDrawingManager dm(dc);
					dm.Fill4ColorsGradient(rectCaption2, clr1, clr2, clr2, clr1, FALSE);
				}

				pVisualManager->m_ctrlMainBorderCaption.DrawFrame(&dc, rectCaption, bActive ? 0 : 1);
			}
			else
			{
				pVisualManager->m_ctrlMainBorderCaption.Draw(&dc, rectCaption, bActive ? 0 : 1);
			}
		}

		rtWindow.top = rectCaption.bottom;
		dc.ExcludeClipRect(rectCaption);

		if (pWnd->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)) || bDialog)
		{
			if (bDialog)
			{
				CRect rtDialog (rtWindow);
				rtDialog.DeflateRect (1, 0, 1, 1);
				dc.FillRect (rtDialog, &GetDlgBackBrush (pWnd));

				dc.ExcludeClipRect (rtDialog);
			}
			pVisualManager->m_ctrlMDIChildBorder.DrawFrame(&dc, rtWindow, bActive ? 0 : 1);
		}
		else
		{
			pVisualManager->m_ctrlMainBorder.DrawFrame(&dc, rtWindow, bActive ? 0 : 1);
		}
		if (bDialog)
		{
			dc.SelectClipRgn (NULL);
			return TRUE;
		}

		//-------------------------------
		// Find status bar extended area:
		//-------------------------------
		CRect rectExt(0, 0, 0, 0);
		BOOL bExtended    = FALSE;
		BOOL bBottomFrame = FALSE;
		BOOL bIsStatusBar = FALSE;

		CWnd* pStatusBar = pWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR, TRUE);

		if (pStatusBar->GetSafeHwnd() != NULL && pStatusBar->IsWindowVisible())
		{
			CMFCStatusBar* pClassicStatusBar = DYNAMIC_DOWNCAST(CMFCStatusBar, pStatusBar);
			if (pClassicStatusBar != NULL)
			{
				bExtended = pClassicStatusBar->GetExtendedArea(rectExt);
				bIsStatusBar = TRUE;
			}

			else
			{
				CMFCRibbonStatusBar* pRibbonStatusBar = DYNAMIC_DOWNCAST(CMFCRibbonStatusBar, pStatusBar);
				if (pRibbonStatusBar != NULL)
				{
					bExtended    = pRibbonStatusBar->GetExtendedArea(rectExt);
					bBottomFrame = pRibbonStatusBar->IsBottomFrame();
					bIsStatusBar = TRUE;
				}
			}

		}

		if (bIsStatusBar)
		{
			CRect rectStatus;
			pStatusBar->GetClientRect(rectStatus);

			int nHeight = rectStatus.Height();
			rectStatus.bottom = rtWindow.bottom;
			rectStatus.top    = rectStatus.bottom - nHeight -(bBottomFrame ? -1 : szSysBorder.cy);
			rectStatus.left   = rtWindow.left;
			rectStatus.right  = rtWindow.right;

			if (bExtended)
			{
				rectExt.left   = rectStatus.right - rectExt.Width() - szSysBorder.cx;
				rectExt.top    = rectStatus.top;
				rectExt.bottom = rectStatus.bottom;
				rectExt.right  = rtWindow.right;
			}

			pVisualManager->m_ctrlStatusBarBack.Draw(&dc, rectStatus, bActive ? 0 : 1);

			if (bExtended)
			{
				rectExt.left -= pVisualManager->m_ctrlStatusBarBack_Ext.GetParams().m_rectCorners.left;
				pVisualManager->m_ctrlStatusBarBack_Ext.Draw(&dc, rectExt, bActive ? 0 : 1);
			}
		}

		dc.SelectClipRgn(NULL);

		return TRUE;
	}

	return CMFCVisualManager::GetInstance()->OnNcPaint(pWnd, lstSysButtons, rectRedraw);
}

BOOL CKofStyleHelper::OnSetWindowRegion( CWnd* pWnd, CSize sizeWindow )
{
	if (KOF_CMFCVisualManagerOffice2007 != m_Style)
	{
		return CMFCVisualManager::GetInstance()->OnSetWindowRegion(pWnd, sizeWindow);
	}
	CKofMFCVisualManagerOffice2007 *pVisualManager = (CKofMFCVisualManagerOffice2007 *)CMFCVisualManager::GetInstance();
	if (!pVisualManager)
	{
		return CMFCVisualManager::GetInstance()->OnSetWindowRegion(pWnd, sizeWindow);
	}
	ASSERT_VALID(pWnd);

	if (pWnd->GetSafeHwnd() == NULL)
	{
		return FALSE;
	}

	if (!pVisualManager->CanDrawImage())
	{
		return FALSE;
	}

	if (afxGlobalData.DwmIsCompositionEnabled())
	{
		return FALSE;
	}

	CSize sz(0, 0);

	BOOL bMainWnd = FALSE;

	if (DYNAMIC_DOWNCAST(CMFCPopupMenu, pWnd) != NULL)
	{
		sz  = CSize(3, 3);
	}
	else if (DYNAMIC_DOWNCAST(CMFCRibbonBar, pWnd) != NULL)
	{
		return FALSE;
	}
	else
	{
		if ((pWnd->GetStyle() & WS_MAXIMIZE) == WS_MAXIMIZE)
		{
			pWnd->SetWindowRgn(NULL, TRUE);
			return TRUE;
		}

		sz  = CSize(9, 9);
		bMainWnd = TRUE;
	}

	if (sz != CSize(0, 0))
	{
		CRgn rgn;
		BOOL bCreated = FALSE;

		bCreated = rgn.CreateRoundRectRgn(0, 0, sizeWindow.cx + 1, sizeWindow.cy + 1, sz.cx, sz.cy);

		if (bCreated)
		{
			if (pWnd->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)) ||	
				pWnd->IsKindOf (RUNTIME_CLASS (CKofDialogEx)) ||
				pWnd->IsKindOf (RUNTIME_CLASS (CKofMFCPropertySheet)))
			{
				CRgn rgnWinodw;
				rgnWinodw.CreateRectRgn(0, sz.cy, sizeWindow.cx, sizeWindow.cy);

				rgn.CombineRgn(&rgn, &rgnWinodw, RGN_OR);
			}

			pWnd->SetWindowRgn((HRGN)rgn.Detach(), TRUE);
			return TRUE;
		}
	}

	return FALSE;
}

