// ..\src\KofMFCTabCtrl.cpp : implementation file

#include "stdafx.h"
#include "..\include\KofMFCTabCtrl.h"
#include "..\include\KofStyleHelper.h"

#define AFX_TABS_FONT         _T("Arial")

//////////////////////////////////////////////////////////////////////////
// CKofMFCTabCtrl

int CMFCBaseTabCtrl::AFX_TAB_TEXT_MARGIN = 4;
int CMFCBaseTabCtrl::AFX_TAB_IMAGE_MARGIN = 4;

IMPLEMENT_DYNCREATE(CKofMFCTabCtrl, CMFCTabCtrl)

CKofMFCTabCtrl::CKofMFCTabCtrl()
{
	m_bIsDlgControl2 = FALSE;
}

CKofMFCTabCtrl::~CKofMFCTabCtrl()
{
}

BEGIN_MESSAGE_MAP(CKofMFCTabCtrl, CMFCTabCtrl)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CKofMFCTabCtrl::PreTranslateMessage( MSG* pMsg )
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		if (m_iActiveTab != -1 && ::GetAsyncKeyState(VK_CONTROL) & 0x8000) // Ctrl is pressed
		{
			switch(pMsg->wParam)
			{
			case VK_NEXT:
				{
					for (int i = m_iActiveTab + 1; i < m_iActiveTab + m_iTabsNum; ++i)
					{
						int iTabIndex = i % m_iTabsNum;
						if (IsTabVisible(iTabIndex))
						{
							m_bUserSelectedTab = TRUE;
							SetActiveTab(iTabIndex);
							GetActiveWnd()->SetFocus();
							FireChangeActiveTab(m_iActiveTab);
							m_bUserSelectedTab = FALSE;
							break;
						}
					}
					return TRUE;
				}
			case VK_PRIOR:
				{
					for (int i = m_iActiveTab - 1 + m_iTabsNum; i > m_iActiveTab; --i)
					{
						int iTabIndex = i % m_iTabsNum;
						if (IsTabVisible(iTabIndex))
						{
							m_bUserSelectedTab = TRUE;
							SetActiveTab(iTabIndex);
							GetActiveWnd()->SetFocus();
							FireChangeActiveTab(m_iActiveTab);
							m_bUserSelectedTab = FALSE;
							break;
						}
					}
					return TRUE;
				}
			}
		}

		// Continue....

	case WM_SYSKEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_NCLBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_NCMBUTTONDOWN:
	case WM_NCLBUTTONUP:
	case WM_NCRBUTTONUP:
	case WM_NCMBUTTONUP:
	case WM_MOUSEMOVE:
		if (m_pToolTipClose->GetSafeHwnd() != NULL)
		{
			m_pToolTipClose->RelayEvent(pMsg);
		}

		if (m_pToolTip->GetSafeHwnd() != NULL)
		{
			m_pToolTip->RelayEvent(pMsg);
		}
		break;
	}

	if (pMsg->message == WM_LBUTTONDBLCLK && pMsg->hwnd == m_btnClose.GetSafeHwnd())
	{
		return TRUE;
	}

	return CMFCBaseTabCtrl::PreTranslateMessage(pMsg);
}

void CKofMFCTabCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CMemDC memDC(dc, this);
	CDC* pDC = &memDC.GetDC();

	dc.GetClipBox(&m_rectCurrClip);

	COLORREF clrDark;
	COLORREF clrBlack;
	COLORREF clrHighlight;
	COLORREF clrFace;
	COLORREF clrDarkShadow;
	COLORREF clrLight;
	CBrush* pbrFace = NULL;
	CBrush* pbrBlack = NULL;

	CMFCVisualManager::GetInstance()->GetTabFrameColors(this, clrDark, clrBlack, clrHighlight, clrFace, clrDarkShadow, clrLight, pbrFace, pbrBlack);

	ASSERT_VALID(pbrFace);
	ASSERT_VALID(pbrBlack);

	CRect rectClient;
	GetClientRect(&rectClient);

	CBrush* pOldBrush = pDC->SelectObject(pbrFace);
	ENSURE(pOldBrush != NULL);

	CPen penDark(PS_SOLID, 1, clrDark);
	CPen penBlack(PS_SOLID, 1, clrBlack);
	CPen penHiLight(PS_SOLID, 1, clrHighlight);

	CPen* pOldPen = (CPen*) pDC->SelectObject(&penDark);
	ENSURE(pOldPen != NULL);

	const int nTabBorderSize = GetTabBorderSize();

	CRect rectTabs = rectClient;

	if (m_location == LOCATION_BOTTOM)
	{
		rectTabs.top = m_rectTabsArea.top;
	}
	else
	{
		rectTabs.bottom = m_rectTabsArea.bottom;
	}

	pDC->ExcludeClipRect(m_rectWndArea);

	BOOL bBackgroundIsReady = CMFCVisualManager::GetInstance()->OnEraseTabsFrame(pDC, rectClient, this);

	if (!m_bDrawFrame && !bBackgroundIsReady)
	{
		pDC->FillRect(rectClient, pbrFace);
	}

	if (m_bIsDlgControl2)
	{
		CKofStyleHelper::GetInstance()->OnFillDialog(pDC, GetParent(), rectTabs);
	}
	else
	{
		CMFCVisualManager::GetInstance()->OnEraseTabsArea(pDC, rectTabs, this);
	}

	CRect rectFrame = rectClient;

	if (nTabBorderSize == 0)
	{
		if (m_location == LOCATION_BOTTOM)
		{
			rectFrame.bottom = m_rectTabsArea.top + 1;
		}
		else
		{
			rectFrame.top = m_rectTabsArea.bottom - 1;
		}

		if (m_bFlat)
		{
			pDC->FrameRect(&rectFrame, pbrBlack);
		}
		else
		{
			pDC->FrameRect(&rectFrame, pbrFace);
		}
	}
	else
	{
		int yLine = m_location == LOCATION_BOTTOM ? m_rectTabsArea.top : m_rectTabsArea.bottom;

		if (!m_bFlat)
		{
			if (m_location == LOCATION_BOTTOM)
			{
				rectFrame.bottom = m_rectTabsArea.top;
			}
			else
			{
				rectFrame.top = m_rectTabsArea.bottom;
			}
		}

		//-----------------------------------------------------
		// Draw wide 3-dimensional frame around the Tabs area:
		//-----------------------------------------------------
		if (m_bFlatFrame)
		{
			CRect rectBorder(rectFrame);

			if (m_bFlat)
			{
				if (m_location == LOCATION_BOTTOM)
				{
					rectBorder.bottom = m_rectTabsArea.top + 1;
				}
				else
				{
					rectBorder.top = m_rectTabsArea.bottom - 1;
				}
			}

			rectFrame.DeflateRect(1, 1);

			if (m_bDrawFrame && !bBackgroundIsReady && rectFrame.Width() > 0 && rectFrame.Height() > 0)
			{
				pDC->PatBlt(rectFrame.left, rectFrame.top, nTabBorderSize, rectFrame.Height(), PATCOPY);
				pDC->PatBlt(rectFrame.left, rectFrame.top, rectFrame.Width(), nTabBorderSize, PATCOPY);
				pDC->PatBlt(rectFrame.right - nTabBorderSize - 1, rectFrame.top, nTabBorderSize + 1, rectFrame.Height(), PATCOPY);
				pDC->PatBlt(rectFrame.left, rectFrame.bottom - nTabBorderSize, rectFrame.Width(), nTabBorderSize, PATCOPY);

				if (m_location == LOCATION_BOTTOM)
				{
					pDC->PatBlt(rectFrame.left, m_rectWndArea.bottom, rectFrame.Width(), rectFrame.bottom - m_rectWndArea.bottom, PATCOPY);
				}
				else
				{
					pDC->PatBlt(rectFrame.left, rectFrame.top, rectFrame.Width(), m_rectWndArea.top - rectFrame.top, PATCOPY);
				}
			}

			if (m_bFlat)
			{
				//---------------------------
				// Draw line below the tabs:
				//---------------------------
				pDC->SelectObject(&penBlack);
				pDC->MoveTo(rectFrame.left + nTabBorderSize, yLine);
				pDC->LineTo(rectFrame.right - nTabBorderSize, yLine);
			}

			pDC->Draw3dRect(&rectBorder, clrFace, clrFace);

			if (GetTabsHeight() == 0)
			{
				pDC->Draw3dRect(&rectBorder, clrFace, clrFace);
			}
			else
			{
				if (m_bDrawFrame)
				{
					pDC->Draw3dRect(&rectBorder, clrDark, clrDark);
				}

				if (!m_bIsOneNoteStyle)
				{
					int xRight = rectBorder.right - 1;

					if (!m_bDrawFrame)
					{
						xRight -= nTabBorderSize;
					}

					if (m_location == LOCATION_BOTTOM)
					{
						pDC->SelectObject(&penBlack);

						pDC->MoveTo(rectBorder.left, rectBorder.bottom - 1);
						pDC->LineTo(xRight, rectBorder.bottom - 1);
					}
					else
					{
						pDC->SelectObject(&penHiLight);

						pDC->MoveTo(rectBorder.left, rectBorder.top);
						pDC->LineTo(xRight, rectBorder.top);
					}
				}
			}
		}
		else
		{
			if (m_bDrawFrame)
			{
				pDC->Draw3dRect(&rectFrame, clrHighlight, clrDarkShadow);

				rectFrame.DeflateRect(1, 1);
				pDC->Draw3dRect(&rectFrame, clrLight, clrDark);

				rectFrame.DeflateRect(1, 1);

				if (!bBackgroundIsReady && rectFrame.Width() > 0 && rectFrame.Height() > 0)
				{
					pDC->PatBlt(rectFrame.left, rectFrame.top, nTabBorderSize, rectFrame.Height(), PATCOPY);
					pDC->PatBlt(rectFrame.left, rectFrame.top, rectFrame.Width(), nTabBorderSize, PATCOPY);
					pDC->PatBlt(rectFrame.right - nTabBorderSize, rectFrame.top, nTabBorderSize, rectFrame.Height(), PATCOPY);
					pDC->PatBlt(rectFrame.left, rectFrame.bottom - nTabBorderSize, rectFrame.Width(), nTabBorderSize, PATCOPY);

					if (m_location == LOCATION_BOTTOM)
					{
						pDC->PatBlt(rectFrame.left, m_rectWndArea.bottom, rectFrame.Width(), rectFrame.bottom - m_rectWndArea.bottom, PATCOPY);
					}
					else
					{
						pDC->PatBlt(rectFrame.left, rectFrame.top, rectFrame.Width(), m_rectWndArea.top - rectFrame.top, PATCOPY);
					}

					if (m_bFlat)
					{
						//---------------------------
						// Draw line below the tabs:
						//---------------------------
						pDC->SelectObject(&penBlack);

						pDC->MoveTo(rectFrame.left + nTabBorderSize, yLine);
						pDC->LineTo(rectFrame.right - nTabBorderSize, yLine);
					}

					if (nTabBorderSize > 2)
					{
						rectFrame.DeflateRect(nTabBorderSize - 2, nTabBorderSize - 2);
					}

					if (rectFrame.Width() > 0 && rectFrame.Height() > 0)
					{
						pDC->Draw3dRect(&rectFrame, clrDarkShadow, clrHighlight);
					}
				}
				else
				{
					rectFrame.DeflateRect(2, 2);
				}
			}
		}
	}

	if (m_bTopEdge && m_location == LOCATION_TOP)
	{
		pDC->SelectObject(&penDark);

		pDC->MoveTo(rectClient.left, m_rectTabsArea.bottom);
		pDC->LineTo(rectClient.left, rectClient.top);
		pDC->LineTo(rectClient.right - 1, rectClient.top);
		pDC->LineTo(rectClient.right - 1, m_rectTabsArea.bottom);
	}

	CFont* pOldFont = pDC->SelectObject(m_bFlat ? &m_fntTabs : &afxGlobalData.fontRegular);
	ENSURE(pOldFont != NULL);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(afxGlobalData.clrBtnText);

	if (m_rectTabsArea.Width() > 5 && m_rectTabsArea.Height() > 5)
	{
		//-----------
		// Draw tabs:
		//-----------
		CRect rectClip = m_rectTabsArea;
		rectClip.InflateRect(1, nTabBorderSize);

		CRgn rgn;
		rgn.CreateRectRgnIndirect(rectClip);

		for (int i = m_iTabsNum - 1; i >= 0; i--)
		{
			CKofMFCTabInfo* pTab = (CKofMFCTabInfo*) m_arTabs [i];
			ASSERT_VALID(pTab);

			if (!pTab->m_bVisible)
				continue;

			m_iCurTab = i;

			if (i != m_iActiveTab) // Draw active tab last
			{
				pDC->SelectClipRgn(&rgn);

				if (m_bFlat)
				{
					pDC->SelectObject(&penBlack);
					DrawFlatTab(pDC, (CMFCTabInfo *)pTab, FALSE);
				}
				else
				{
					Draw3DTab(pDC, (CMFCTabInfo *)pTab, FALSE);
				}
			}
		}

		if (m_iActiveTab >= 0)
		{
			//-----------------
			// Draw active tab:
			//-----------------
			pDC->SetTextColor(afxGlobalData.clrWindowText);

			CKofMFCTabInfo* pTabActive = (CKofMFCTabInfo*) m_arTabs [m_iActiveTab];
			ASSERT_VALID(pTabActive);

			m_iCurTab = m_iActiveTab;

			pDC->SelectClipRgn(&rgn);

			if (m_bFlat)
			{
				pDC->SelectObject(&m_brActiveTab);
				pDC->SelectObject(&m_fntTabsBold);
				pDC->SetTextColor(GetActiveTabTextColor());
				pDC->SelectObject(&penBlack);

				DrawFlatTab(pDC, (CMFCTabInfo *)pTabActive, TRUE);

				//---------------------------------
				// Draw line bellow the active tab:
				//---------------------------------
				const int xLeft = max( m_rectTabsArea.left + 1, pTabActive->m_rect.left + 1);

				if (pTabActive->m_rect.right > m_rectTabsArea.left + 1)
				{
					CPen penLight(PS_SOLID, 1, GetActiveTabColor());
					pDC->SelectObject(&penLight);

					if (m_location == LOCATION_BOTTOM)
					{
						pDC->MoveTo(xLeft, pTabActive->m_rect.top);
						pDC->LineTo(pTabActive->m_rect.right, pTabActive->m_rect.top);
					}
					else
					{
						pDC->MoveTo(xLeft, pTabActive->m_rect.bottom);
						pDC->LineTo(pTabActive->m_rect.right, pTabActive->m_rect.bottom);
					}

					pDC->SelectObject(pOldPen);
				}
			}
			else
			{
				if (m_bIsActiveTabBold)
				{
					if (!IsMDITabGroup() || m_bIsActiveInMDITabGroup)
					{
						pDC->SelectObject(&afxGlobalData.fontBold);
					}
				}

				Draw3DTab(pDC, (CMFCTabInfo *)pTabActive, TRUE);
			}
		}

		pDC->SelectClipRgn(NULL);
	}

	if (!m_rectTabSplitter.IsRectEmpty())
	{
		pDC->FillRect(m_rectTabSplitter, pbrFace);

		CRect rectTabSplitter = m_rectTabSplitter;

		pDC->Draw3dRect(rectTabSplitter, clrDarkShadow, clrDark);
		rectTabSplitter.DeflateRect(1, 1);
		pDC->Draw3dRect(rectTabSplitter, clrHighlight, clrDark);
	}

	if (m_bFlat && m_nTabsHorzOffset > 0)
	{
		pDC->SelectObject(&penDark);

		const int xDivider = m_rectTabsArea.left - 1;

		if (m_location == LOCATION_BOTTOM)
		{
			pDC->MoveTo(xDivider, m_rectTabsArea.top + 1);
			pDC->LineTo(xDivider, m_rectTabsArea.bottom - 2);
		}
		else
		{
			pDC->MoveTo(xDivider, m_rectTabsArea.bottom);
			pDC->LineTo(xDivider, m_rectTabsArea.top + 2);
		}
	}

	if (!m_rectResize.IsRectEmpty())
	{
#if _MSC_VER > 1500
		CMFCVisualManager::GetInstance ()->OnDrawTabResizeBar(pDC, this, m_ResizeMode == RESIZE_VERT, m_rectResize, pbrFace, &penDark);
#else
		pDC->FillRect(m_rectResize, pbrFace);

		pDC->SelectObject(&penDark);

		if (m_ResizeMode == RESIZE_VERT)
		{
			pDC->MoveTo(m_rectResize.left, m_rectResize.top);
			pDC->LineTo(m_rectResize.left, m_rectResize.bottom);
		}
		else
		{
			pDC->MoveTo(m_rectResize.left, m_rectResize.top);
			pDC->LineTo(m_rectResize.right, m_rectResize.top);
		}
#endif		
	}

	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	if (memDC.IsMemDC())
	{
		dc.ExcludeClipRect(m_rectWndArea);
	}
}

void CKofMFCTabCtrl::AdjustTabs()
{
	m_bHiddenDocuments = FALSE;

	m_rectCloseButton.SetRectEmpty();

	int nVisibleTabsNum = GetVisibleTabsNum();
	if (nVisibleTabsNum == 0 || GetTabsHeight() == 0)
	{
		return;
	}

	if (m_bHideSingleTab && nVisibleTabsNum <= 1)
	{
		for (int i = 0; i < m_iTabsNum; i ++)
		{
			CKofMFCTabInfo* pTab = (CKofMFCTabInfo*) m_arTabs [i];
			ASSERT_VALID(pTab);

			pTab->m_rect.SetRectEmpty();
		}

		return;
	}

	if (m_pToolTipClose->GetSafeHwnd() != NULL)
	{
		if (m_pToolTipClose->GetToolCount() == 0)
		{
			m_pToolTipClose->AddTool(this, LPSTR_TEXTCALLBACK, CRect(0, 0, 0, 0), 1);
		}
	}

	CRect rectActiveTabTT(0, 0, 0, 0);

	//-------------------------
	// Define tab's full width:
	//-------------------------
	CClientDC dc(this);

	CFont* pOldFont = dc.SelectObject(m_bFlat ? &m_fntTabsBold : &afxGlobalData.fontRegular);
	ENSURE(pOldFont != NULL);

	m_nTabsTotalWidth = 0;

	//----------------------------------------------
	// First, try set all tabs in its original size:
	//----------------------------------------------
	int x = m_rectTabsArea.left - m_nTabsHorzOffset;
	int i = 0;

	for (i = 0; i < m_iTabsNum; i++)
	{
		CKofMFCTabInfo* pTab = (CKofMFCTabInfo*) m_arTabs [i];
		ASSERT_VALID(pTab);

		CSize sizeImage(0, 0);
		if (pTab->m_hIcon != NULL || pTab->m_uiIcon != (UINT)-1)
		{
			sizeImage = m_sizeImage;
		}

		if (m_bIsActiveTabBold &&(m_bIsOneNoteStyle || m_bIsVS2005Style || i == m_iActiveTab))
		{
			dc.SelectObject(&afxGlobalData.fontBold);
		}

		int nExtraWidth = 0;

		if (pTab->m_bVisible)
		{
			pTab->m_nFullWidth = sizeImage.cx + AFX_TAB_IMAGE_MARGIN + (pTab->m_bIconOnly ? 0 : dc.GetTextExtent(pTab->m_strText).cx) + 2 * AFX_TAB_TEXT_MARGIN;

			if (m_bLeftRightRounded)
			{
				pTab->m_nFullWidth += m_rectTabsArea.Height() / 2;
				nExtraWidth = m_rectTabsArea.Height() / 2;
			}
			else if (m_bIsOneNoteStyle)
			{
				pTab->m_nFullWidth += m_rectTabsArea.Height() + 2 * AFX_TAB_IMAGE_MARGIN;
				nExtraWidth = m_rectTabsArea.Height() - AFX_TAB_IMAGE_MARGIN - 1;
			}
			else if (m_bIsVS2005Style)
			{
				pTab->m_nFullWidth += m_rectTabsArea.Height();
				nExtraWidth = m_rectTabsArea.Height() - AFX_TAB_IMAGE_MARGIN - 1;
			}

			if (m_bActiveTabCloseButton && i == m_iActiveTab)
			{
				pTab->m_nFullWidth += m_rectTabsArea.Height() - 2;
			}
		}
		else
		{
			pTab->m_nFullWidth = 0;
		}

		if (m_bIsActiveTabBold && i == m_iActiveTab)
		{
			dc.SelectObject(&afxGlobalData.fontRegular); // Bold tab is available for 3d tabs only
		}

		int nTabWidth = pTab->m_nFullWidth;

		if (m_bScroll && m_nTabMaxWidth > 0)
		{
			nTabWidth = min(nTabWidth, m_nTabMaxWidth);
		}

		pTab->m_rect = CRect(CPoint(x, m_rectTabsArea.top), CSize(nTabWidth, m_rectTabsArea.Height() - 2));

		if (!pTab->m_bVisible)
		{
			if (m_pToolTip->GetSafeHwnd() != NULL)
			{
				m_pToolTip->SetToolRect(this, pTab->m_iTabID, CRect(0, 0, 0, 0));
			}
			continue;
		}

		if (m_location == LOCATION_TOP)
		{
			pTab->m_rect.OffsetRect(0, 2);
		}

		if (m_bTabDocumentsMenu && pTab->m_rect.right > m_rectTabsArea.right)
		{
			BOOL bHideTab = TRUE;

			if (i == m_iActiveTab && i == 0)
			{
				int nWidth = m_rectTabsArea.right - pTab->m_rect.left;

				if (nWidth >= nExtraWidth + 2 * AFX_TAB_TEXT_MARGIN)
				{
					pTab->m_rect.right = m_rectTabsArea.right;
					bHideTab = FALSE;
				}
			}

			if (bHideTab)
			{
				pTab->m_nFullWidth = 0;
				pTab->m_rect.SetRectEmpty();
				m_bHiddenDocuments = TRUE;
				continue;
			}
		}

		if (m_pToolTip->GetSafeHwnd() != NULL)
		{
			BOOL bShowTooltip = pTab->m_bAlwaysShowToolTip || m_bCustomToolTips;

			if (pTab->m_rect.left < m_rectTabsArea.left ||
				pTab->m_rect.right > m_rectTabsArea.right)
			{
				bShowTooltip = TRUE;
			}

			if (m_bScroll && m_nTabMaxWidth > 0 &&
				pTab->m_rect.Width() < pTab->m_nFullWidth)
			{
				bShowTooltip = TRUE;
			}

			m_pToolTip->SetToolRect(this, pTab->m_iTabID,
				bShowTooltip ? pTab->m_rect : CRect(0, 0, 0, 0));

			if (bShowTooltip && i == m_iActiveTab)
			{
				rectActiveTabTT = pTab->m_rect;
			}
		}

		x += pTab->m_rect.Width() + 1 - nExtraWidth;
		m_nTabsTotalWidth += pTab->m_rect.Width() + 1;

		if (i > 0)
		{
			m_nTabsTotalWidth -= nExtraWidth;
		}

		if (m_bFlat)
		{
			//--------------------------------------------
			// In the flat mode tab is overlapped by next:
			//--------------------------------------------
			pTab->m_rect.right += m_nTabsHeight / 2;
		}
	}

	if (m_bScroll || x < m_rectTabsArea.right)
	{
		m_nTabsTotalWidth += m_nTabsHeight / 2;
	}
	else
	{
		//-----------------------------------------
		// Not enouth space to show the whole text.
		//-----------------------------------------
		int nTabsWidth = m_rectTabsArea.Width();
		int nTabWidth = nTabsWidth / nVisibleTabsNum - 1;

		if (m_bLeftRightRounded)
		{
			nTabWidth = max( m_sizeImage.cx + m_rectTabsArea.Height() / 2, (nTabsWidth - m_rectTabsArea.Height() / 3) / nVisibleTabsNum);
		}

		//------------------------------------
		// May be it's too wide for some tabs?
		//------------------------------------
		int nRest = 0;
		int nCutTabsNum = nVisibleTabsNum;

		for (i = 0; i < m_iTabsNum; i ++)
		{
			CKofMFCTabInfo* pTab = (CKofMFCTabInfo*) m_arTabs [i];
			ASSERT_VALID(pTab);

			if (!pTab->m_bVisible)
			{
				continue;
			}

			if (pTab->m_nFullWidth < nTabWidth)
			{
				nRest += nTabWidth - pTab->m_nFullWidth;
				nCutTabsNum --;
			}
		}

		if (nCutTabsNum > 0)
		{
			nTabWidth += nRest / nCutTabsNum;

			//----------------------------------
			// Last pass: set actual rectangles:
			//----------------------------------
			x = m_rectTabsArea.left;
			for (i = 0; i < m_iTabsNum; i ++)
			{
				CKofMFCTabInfo* pTab = (CKofMFCTabInfo*) m_arTabs [i];
				ASSERT_VALID(pTab);

				if (!pTab->m_bVisible)
				{
					if (m_pToolTip->GetSafeHwnd() != NULL)
					{
						m_pToolTip->SetToolRect(this, pTab->m_iTabID, CRect(0, 0, 0, 0));
					}

					continue;
				}

				CSize sizeImage(0, 0);
				if (pTab->m_hIcon != NULL || pTab->m_uiIcon != (UINT)-1)
				{
					sizeImage = m_sizeImage;
				}

				BOOL bIsTrucncated = pTab->m_nFullWidth > nTabWidth;
				int nCurrTabWidth = (bIsTrucncated) ? nTabWidth : pTab->m_nFullWidth;

				if (nTabWidth < sizeImage.cx + AFX_TAB_IMAGE_MARGIN)
				{
					// Too narrow!
					nCurrTabWidth = (m_rectTabsArea.Width() + m_nTabBorderSize * 2) / nVisibleTabsNum;
				}
				else
				{
					if (pTab->m_strText.IsEmpty() || pTab->m_bIconOnly)
					{
						nCurrTabWidth = sizeImage.cx + 2 * CMFCBaseTabCtrl::AFX_TAB_TEXT_MARGIN;
					}
				}

				if (m_bLeftRightRounded)
				{
					nCurrTabWidth += m_rectTabsArea.Height() / 2 - 1;
				}

				pTab->m_rect = CRect(CPoint(x, m_rectTabsArea.top), CSize(nCurrTabWidth, m_rectTabsArea.Height() - 2));

				if (!m_bFlat)
				{
					if (m_location == LOCATION_TOP)
					{
						pTab->m_rect.OffsetRect(0, 2);
					}

					if (m_pToolTip->GetSafeHwnd() != NULL)
					{
						BOOL bShowTooltip = bIsTrucncated || pTab->m_bAlwaysShowToolTip || m_bCustomToolTips;

						m_pToolTip->SetToolRect(this, pTab->m_iTabID, bShowTooltip ? pTab->m_rect : CRect(0, 0, 0, 0));

						if (bShowTooltip && i == m_iActiveTab)
						{
							rectActiveTabTT = pTab->m_rect;
						}
					}
				}

				x += nCurrTabWidth;
				if (m_bLeftRightRounded)
				{
					x -= m_rectTabsArea.Height() / 2;
				}

				if (nRest > 0)
				{
					x ++;
				}
			}
		}
	}

	dc.SelectObject(pOldFont);

	if (m_bActiveTabCloseButton && m_iActiveTab >= 0)
	{
		GetTabRect(m_iActiveTab, m_rectCloseButton);

		m_rectCloseButton.left = m_rectCloseButton.right - m_rectCloseButton.Height();

		m_rectCloseButton.DeflateRect(2, 2);
		m_rectCloseButton.OffsetRect(-CMFCVisualManager::GetInstance()->GetTabHorzMargin(this), GetLocation() == CMFCBaseTabCtrl::LOCATION_TOP ? 1 : -1);

		if (m_pToolTipClose->GetSafeHwnd() != NULL)
		{
			m_pToolTipClose->SetToolRect(this, 1, m_rectCloseButton);

			CKofMFCTabInfo* pActiveTab = (CKofMFCTabInfo*) m_arTabs [m_iActiveTab];

			if (m_pToolTip->GetSafeHwnd() != NULL && pActiveTab != NULL)
			{
				if (!rectActiveTabTT.IsRectEmpty())
				{
					rectActiveTabTT.right = m_rectCloseButton.left - 1;
					m_pToolTip->SetToolRect(this, pActiveTab->m_iTabID, rectActiveTabTT);
				}
			}
		}
	}
}

int CKofMFCTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CWnd *pWnd = FromHandle(lpCreateStruct->hwndParent);
	if (pWnd && (pWnd->IsKindOf(RUNTIME_CLASS(CDialog)) || 
				 pWnd->IsKindOf(RUNTIME_CLASS(CPropertyPage))))
	{
		m_bIsDlgControl2 = TRUE;
	}

	return 0;
}
