// ..\src\KofMessageBox.cpp : implementation file

#include "stdafx.h"
#include "..\include\KofMessageBox.h"

CSize GetWindowTextExtent (CWnd* pControl, const CString& strText, CFont* pFont = NULL)
{
	if (pFont == NULL && pControl != NULL)
	{
		ASSERT (pControl != NULL);
		pFont = pControl->GetFont ();
	}

	CWindowDC dc (pControl);

	CFont* pOldFont = NULL;
	if (pFont != NULL)
	{
		dc.SelectObject (pFont);
	}

	CSize szText = dc.GetTextExtent (strText);

	if (pFont != NULL)
	{
		dc.SelectObject (pOldFont);
	}
	return szText;
}

static void AdjustControls (CWnd** pControlsArray, UINT nControlsCount, const RECT& rcBounds, DWORD dwAdjustment)
{
	if (nControlsCount == 0 || pControlsArray == NULL)
	{
		return;
	}

	RECT rect;
	pControlsArray[0]->GetWindowRect(&rect);
	int nLeft = rect.left;
	pControlsArray[nControlsCount - 1]->GetWindowRect(&rect);
	int nRight = rect.right;

	int xOffset = 0;

	const DWORD TA_HorzMask = TA_LEFT | TA_CENTER | TA_RIGHT;

	switch (dwAdjustment & TA_HorzMask)
	{
	case TA_LEFT:
		xOffset = rcBounds.left - nLeft;
		break;
	case TA_CENTER:
		xOffset = ((rcBounds.right + rcBounds.left) - (nRight + nLeft)) / 2;
		break;
	case TA_RIGHT:
		xOffset = rcBounds.right - nRight;
		break;
	}

	for (UINT i = 0; i < nControlsCount; ++i)
	{
		pControlsArray[i]->GetWindowRect (&rect);

		int y = (rcBounds.top == rcBounds.bottom) ? rcBounds.top : rect.top;
		pControlsArray[i]->MoveWindow (rect.left + xOffset, y, rect.right - rect.left, rect.bottom - rect.top, TRUE);
	}
}

//////////////////////////////////////////////////////////////////////////
// CKofMessageBox

IMPLEMENT_DYNAMIC(CKofMessageBox, CKofDialogEx)

CKofMessageBox::CKofMessageBox( const MSGBOXPARAMS* pParams )
{
	CopyMemory(&m_Params, pParams, sizeof(MSGBOXPARAMS));
	Initialize();
}

CKofMessageBox::CKofMessageBox( const KOF_MSGBOXPARAMS* pParams )
{
	CopyMemory(&m_Params, pParams, sizeof(KOF_MSGBOXPARAMS));
	Initialize();
}

CKofMessageBox::~CKofMessageBox()
{
	for (int i = 0; i < (int)m_arrButtons.GetSize (); ++i)
	{
		delete m_arrButtons[i];
	}

	if (m_pTemplate != NULL)
	{
		::GlobalFree (m_pTemplate);
	}
}

BEGIN_MESSAGE_MAP(CKofMessageBox, CKofDialogEx)
	ON_WM_PAINT()
	ON_MESSAGE(WM_HELP, OnHelp)
	ON_COMMAND_RANGE(1, 0xFFFF, OnButton)
END_MESSAGE_MAP()

void CKofMessageBox::Initialize()
{
	CWnd* pParent = CWnd::FromHandle (m_Params.hwndOwner);

	if (pParent == NULL)
	{
		pParent = CWnd::GetActiveWindow();

		if (pParent != NULL)
		{
			CWnd* pPopup = pParent->GetLastActivePopup();

			if (pPopup != NULL)
			{
				pParent = pPopup;
			}
		}
	}

	// Loading an icon

	LPTSTR iconID = NULL;

	switch (m_Params.dwStyle & MB_ICONMASK)
	{
	case MB_ICONASTERISK:
		iconID = IDI_ASTERISK;
		break;
	case MB_ICONEXCLAMATION:
		iconID = IDI_EXCLAMATION;
		break;
	case MB_ICONHAND:
		iconID = IDI_HAND;
		break;
	case MB_ICONQUESTION:
		iconID = IDI_QUESTION;
		break;
	}

	m_hMessageIcon = NULL;
	if (iconID)
	{
		m_hMessageIcon = ::LoadIcon (NULL, MAKEINTRESOURCE(iconID));
	}

	if (m_Params.dwStyle & MB_USERICON)
	{
		m_hMessageIcon = ::LoadIcon (m_Params.hInstance, m_Params.lpszIcon);
	}

	m_rectIcon.SetRectEmpty ();
	if (m_hMessageIcon != NULL)
	{
		m_rectIcon.right = ::GetSystemMetrics(SM_CXICON);
		m_rectIcon.bottom = ::GetSystemMetrics(SM_CYICON);
	}

	m_strMessageCaption = m_Params.lpszCaption, _T("Error");
	m_strMessageText = m_Params.lpszText;
	m_strCheckBox = m_Params.lpszCheckBoxText;

	switch (m_Params.dwStyle & MB_DEFMASK)
	{
	case MB_DEFBUTTON1:
		m_nDefaultButtonIndex = 0;
		break;
	case MB_DEFBUTTON2:
		m_nDefaultButtonIndex = 1;
		break;
	case MB_DEFBUTTON3:
		m_nDefaultButtonIndex = 2;
		break;
	case MB_DEFBUTTON4:
		m_nDefaultButtonIndex = 3;
		break;
	default:
		m_nDefaultButtonIndex = -1;
		break;
	}

	// Creating dialog template

	m_pTemplate = (DLGTEMPLATE*)::GlobalAlloc (GPTR, 1024);

	m_pTemplate->x = 0;
	m_pTemplate->y = 0;
	m_pTemplate->cx = 62;
	m_pTemplate->cy = 40;
	m_pTemplate->cdit = 0;

	m_pTemplate->style = WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_POPUP | DS_MODALFRAME | DS_CENTER;

	m_pTemplate->dwExtendedStyle = 0;

	m_bRightAlignment = (m_Params.dwStyle & MB_RIGHT) != 0;

	if (m_Params.dwStyle & MB_RTLREADING)
	{
		//// Uncomment to enable RTL
		//m_pTemplate->dwExtendedStyle |= WS_EX_LAYOUTRTL;
		//m_bRightAlignment = !m_bRightAlignment;
	}

	if (m_Params.dwStyle & MB_SYSTEMMODAL)
	{
		m_pTemplate->style |= DS_SYSMODAL;
	}

	WORD* pEnd = (WORD*)(m_pTemplate + 1);
	*pEnd = 0;

	InitModalIndirect (m_pTemplate, pParent);

	// Calculating margins, sizes and spacings
	m_rectClientMargins.SetRect (7, 7, 5, 7);
	m_szButton.cx = 52;
	m_szButton.cy = 14;
	m_cxIconSpacing = 12; // spacing between an icon and message text
	m_cyCheckBoxHeight = 10;
	m_cxButtonSpacing = 4; // gap between buttons
	m_cyVerticalSpacing = 11; // vertical spacing between text, optional check box and buttons
}

#ifndef IDTRYAGAIN
#define IDTRYAGAIN  10
#endif

#ifndef IDCONTINUE
#define IDCONTINUE  11
#endif

#ifndef MB_CANCELTRYCONTINUE
#define MB_CANCELTRYCONTINUE    6
#endif

struct STD_BUTTON_TEXT 
{
	UINT    id;
	UINT    resId;
	LPCTSTR pszText;
};

static STD_BUTTON_TEXT s_Buttons [] =
{
	{ IDOK,       800,  _T("确定")			},
	{ IDCANCEL,   801,  _T("取消")			},
	{ IDABORT,    802,  _T("终止(&A)")		},
	{ IDRETRY,    803,  _T("重试(&R)")		},
	{ IDIGNORE,   804,  _T("忽略(&I)")		},
	{ IDYES,      805,  _T("是(&Y)")		},
	{ IDNO,       806,  _T("否(&N)")		},
	{ IDTRYAGAIN, 809,  _T("重试(&T)")		},
	{ IDCONTINUE, 810,  _T("继续(&C)")		}
};

void CKofMessageBox::AddButton( UINT id, HINSTANCE hInst, LPCTSTR lpszCaption /*= NULL*/ )
{
	CString strText = lpszCaption;

	if (strText.IsEmpty ())
	{
		const STD_BUTTON_TEXT* sbt = NULL;

		for (int i = 0; i < sizeof(s_Buttons) / sizeof(*s_Buttons); ++i)
		{
			if (s_Buttons[i].id == id)
			{
				sbt = &s_Buttons[i];
				break;
			}
		}

		if (sbt != NULL)
		{			

			if (strText.IsEmpty ())
			{
				strText = sbt->pszText;
			}
		}
	}

	DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_TABSTOP;

	int nButtonIndex = (int)m_arrButtons.GetSize ();

	if (nButtonIndex == m_nDefaultButtonIndex)
	{
		dwStyle |= BS_DEFPUSHBUTTON;
	}
	else
	{
		dwStyle |= BS_PUSHBUTTON;
	}

	int nButtonWidth = m_szButton.cx;
	CRect rectButton (m_ptNextButtonPos.x, 0, m_ptNextButtonPos.x + nButtonWidth, m_szButton.cy);

	CKofMFCButton* pBtn = new CKofMFCButton ();
	pBtn->Create (strText, dwStyle, rectButton, this, id);

	if (pBtn->GetSafeHwnd () != NULL)
	{
		CSize szButtonText = GetWindowTextExtent (pBtn, strText);
		const int cxButtonMargins = 5; // Minimal space between button text and button's left and right borders.
		if (szButtonText.cx > m_szButton.cx - cxButtonMargins * 2)
		{
			// Resize button to show whole text
			szButtonText.cx = min (szButtonText.cx, 512); // Preserve from too long button text
			nButtonWidth = szButtonText.cx + cxButtonMargins * 2;
			pBtn->SetWindowPos (NULL, 0, 0, nButtonWidth, m_szButton.cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
		}

		m_ptNextButtonPos.x += nButtonWidth + m_cxButtonSpacing;

		m_arrButtons.Add (pBtn);
		if (id == IDCANCEL)
		{
			m_bHasCancelButton = true; // enable close button
		}
	}
}

BOOL CKofMessageBox::OnInitDialog()
{
	CKofDialogEx::OnInitDialog();

	SetWindowText (m_strMessageCaption);
	CenterWindow ();

	::MessageBeep (m_Params.dwStyle & MB_ICONMASK);

	if (m_nDefaultButtonIndex >= 0 && m_nDefaultButtonIndex < (int)m_arrButtons.GetSize ())
	{
		m_arrButtons[m_nDefaultButtonIndex]->SetFocus ();
		return FALSE; // Focus changed
	}

	return TRUE;
}

void CKofMessageBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.DrawIcon(m_rectIcon.left, m_rectIcon.top, m_hMessageIcon);
	DrawText(&dc);

	if (m_Params.bShowCheckBox && m_Params.bShowSeparator)
	{
		CRect rectClient;
		GetClientRect (&rectClient);
		rectClient.DeflateRect (m_rectClientMargins);
		rectClient.top  = m_cySeparatorLine - 1;
		rectClient.bottom = m_cySeparatorLine + 1;

		dc.Draw3dRect (rectClient, afxGlobalData.clrBarDkShadow, afxGlobalData.clrBarHilite);
	}
}

BOOL CKofMessageBox::PreTranslateMessage( MSG* pMsg )
{
#ifdef _UNICODE
#define _TCF_TEXT	CF_UNICODETEXT
#else
#define _TCF_TEXT	CF_TEXT
#endif

	if (pMsg->message == WM_KEYDOWN)
	{
		UINT nChar = (UINT) pMsg->wParam;
		BOOL bIsCtrl = (::GetAsyncKeyState (VK_CONTROL) & 0x8000);

		if (bIsCtrl && (nChar == _T('C') || nChar == VK_INSERT))
		{
			if (OpenClipboard ())
			{
				::EmptyClipboard ();

				LPCTSTR szDelimiter = _T("---------------------------\r\n");
				LPCTSTR szEOL = _T("\r\n");
				CString strText;
				strText = szDelimiter;
				strText += m_strMessageCaption + szEOL;
				strText += szDelimiter;
				strText += m_strMessageText + szEOL;
				strText += szDelimiter;
				if (m_Params.bShowCheckBox)
				{
					strText += m_strCheckBox + szEOL;
					strText += szDelimiter;
				}

				for (int i = 0; i < (int)m_arrButtons.GetSize (); i++)
				{
					CString strButton;
					m_arrButtons[i]->GetWindowText (strButton);
					strButton.Replace (_T("&&"), _T("\v"));
					strButton.Remove (_T('&'));
					strButton.Replace (_T('\v'), _T('&'));
					strButton += _T(' ');
					strText += strButton;
				}

				strText += szEOL;
				strText += szDelimiter;

				HGLOBAL hClipbuffer = ::GlobalAlloc (GMEM_DDESHARE, (strText.GetLength () + 1) * sizeof (TCHAR));
				LPTSTR lpszBuffer = (LPTSTR)::GlobalLock (hClipbuffer);

				lstrcpy (lpszBuffer, (LPCTSTR) strText);

				::GlobalUnlock (hClipbuffer);
				::SetClipboardData (_TCF_TEXT, hClipbuffer);

				::CloseClipboard();
			}
		}
	}

	return CKofDialogEx::PreTranslateMessage(pMsg);
}

void CKofMessageBox::DrawText( CDC* pDC )
{
	CFont* pOldFont = pDC->SelectObject (&m_fntText);
	pDC->SetTextColor (TRUE ? afxGlobalData.clrBarText : afxGlobalData.clrWindowText);
	pDC->SetBkMode (TRANSPARENT);
	CRect rectTemp = m_rectText;
	pDC->DrawText (m_strMessageText, &rectTemp, m_dwDrawTextFlags | DT_NOCLIP);
	pDC->SelectObject (pOldFont);
}

void CKofMessageBox::PreInitDialog()
{
	CKofDialogEx::PreInitDialog();
	// Setting font

	NONCLIENTMETRICS ncm;
	ZeroMemory (&ncm, sizeof (ncm));
	ncm.cbSize = sizeof (ncm);
	::SystemParametersInfo (SPI_GETNONCLIENTMETRICS, 0, (LPVOID)&ncm, 0);
	m_fntText.CreateFontIndirect (&ncm.lfMessageFont);

	// Calculating gaps, spaces and margins

	{
		MapDialogRect (&m_rectClientMargins);

		CRect rectTemp (m_cxIconSpacing, m_cyVerticalSpacing, m_cxButtonSpacing, m_cyCheckBoxHeight);
		MapDialogRect (&rectTemp);
		m_cxIconSpacing = rectTemp.left;
		m_cyVerticalSpacing = rectTemp.top;
		m_cxButtonSpacing = rectTemp.right;
		m_cyCheckBoxHeight = rectTemp.bottom;

		rectTemp.TopLeft () = m_szButton;
		MapDialogRect (&rectTemp);
		m_szButton = rectTemp.TopLeft ();
	}

	// Creating buttons

	m_bHasCancelButton = false;
	m_ptNextButtonPos.x = 0;
	m_ptNextButtonPos.y = 0;

	HINSTANCE hInst = NULL;//::LoadLibrary (_T("user32.dll"));

	if (!m_Params.bIgnoreStandardButtons)
	{
		switch (m_Params.dwStyle & MB_TYPEMASK)
		{
		case MB_OK:
			AddButton (IDOK, hInst);
			break;
		case MB_OKCANCEL:
			AddButton (IDOK, hInst);
			AddButton (IDCANCEL, hInst);
			break;
		case MB_ABORTRETRYIGNORE:
			AddButton (IDABORT, hInst);
			AddButton (IDRETRY, hInst);
			AddButton (IDIGNORE, hInst);
			break;
		case MB_YESNO:
			AddButton (IDYES, hInst);
			AddButton (IDNO, hInst);
			break;
		case MB_YESNOCANCEL:
			AddButton (IDYES, hInst);
			AddButton (IDNO, hInst);
			AddButton (IDCANCEL, hInst);
			break;
		case MB_RETRYCANCEL:
			AddButton (IDRETRY, hInst);
			AddButton (IDCANCEL, hInst);
			break;

		case MB_CANCELTRYCONTINUE:
			AddButton (IDCANCEL, hInst);
			AddButton (IDTRYAGAIN, hInst);
			AddButton (IDCONTINUE, hInst);
			break;
		}
	}

	for (int iBtn = 0; iBtn < KOF_MSGBOXPARAMS::UserButtonsCount; ++iBtn)
	{
		if (m_Params.uiUserButtonID [iBtn] != 0)
		{
			LPCTSTR pszCaption = m_Params.lpszUserButtonText[iBtn];
			AddButton (m_Params.uiUserButtonID [iBtn], pszCaption == NULL ? hInst : m_Params.hInstance, pszCaption);
		}
	}

	if (hInst != NULL)
	{
		::FreeLibrary (hInst);
	}

	int nBtnCount = (int)m_arrButtons.GetSize ();
	ASSERT (nBtnCount != 0);

	if (nBtnCount == 1 && (m_Params.dwStyle & MB_TYPEMASK) == MB_OK)
	{
		m_bHasCancelButton = true;
	}

	// Calculate window size

	int nMinClientWidth = m_ptNextButtonPos.x;

	CRect rectScreen;
	::SystemParametersInfo (SPI_GETWORKAREA, 0, (LPVOID)&rectScreen, 0);

	int nMaxMessageBoxWidth = (rectScreen.Width () / 2) + 80;

	m_rectText.SetRect (0, 0, nMaxMessageBoxWidth, rectScreen.Height() - m_szButton.cy - m_cxButtonSpacing);
	if (!m_rectIcon.IsRectEmpty ())
	{
		m_rectText.right -= (m_rectIcon.Width () + m_cxIconSpacing);
	}


	HDC hdcScreen = ::GetDC (NULL); // Screen DC
	HFONT hOldFont =  (HFONT)::SelectObject (hdcScreen, m_fntText);

	m_dwDrawTextFlags = DT_NOPREFIX | DT_WORDBREAK | DT_EXPANDTABS;

	::DrawText (hdcScreen, m_strMessageText, -1, &m_rectText, m_dwDrawTextFlags | DT_CALCRECT);

	m_dwDrawTextFlags |= (m_bRightAlignment ? DT_RIGHT : DT_LEFT);

	// Calculate minimal width for message box window

	if (m_Params.bShowCheckBox)
	{
		SIZE szCheckBox;
		::GetTextExtentPoint32 (hdcScreen, m_strCheckBox, m_strCheckBox.GetLength (), &szCheckBox);
		szCheckBox.cx += 2 * m_cyCheckBoxHeight;
		if (m_hMessageIcon != NULL)
		{
			szCheckBox.cx += m_rectIcon.Width ();
		}
		nMinClientWidth = max (nMinClientWidth, szCheckBox.cx);
	}

	::SelectObject (hdcScreen, hOldFont);
	::ReleaseDC (NULL, hdcScreen);

	CSize szTotal (m_rectText.Width (), m_rectText.Height ());
	if (m_hMessageIcon != NULL)
	{
		CSize szTextOffset (m_rectIcon.Width () + m_cxIconSpacing, 0);

		if (m_rectIcon.Height () > m_rectText.Height ())
		{
			// Center text vertically against icon
			szTextOffset.cy = (m_rectIcon.Height () - m_rectText.Height()) / 2;
		}

		m_rectText.OffsetRect (szTextOffset);

		szTotal.cx += m_rectIcon.Width () + m_cxIconSpacing;
		szTotal.cy = max (szTotal.cy, m_rectIcon.Height ());
	}

	if (szTotal.cx < nMinClientWidth)
	{
		szTotal.cx = nMinClientWidth;
	}
	szTotal.cy += m_cyVerticalSpacing;

	if (m_bRightAlignment)
	{
		m_rectText.OffsetRect (szTotal.cx - m_rectText.right, 0);
	}

	// Adjusting buttons

	int yButtons = szTotal.cy + m_rectClientMargins.top;

	// Add check box if necessary

	m_cySeparatorLine = -1;

	if (m_Params.bShowCheckBox)
	{
		int xCheckBox = m_rectClientMargins.left;
		if (m_hMessageIcon != NULL)
		{
			xCheckBox += m_rectIcon.Width () + m_cxIconSpacing;
		}

		CRect rectCheckBox (xCheckBox, yButtons, m_rectClientMargins.left + szTotal.cx, yButtons + m_cyCheckBoxHeight);
		int yOffset = rectCheckBox.Height() + m_cyVerticalSpacing;

		if (m_Params.bShowSeparator)
		{
			m_cySeparatorLine = rectCheckBox.top;
			rectCheckBox.OffsetRect(0, m_cyVerticalSpacing);
			yOffset += m_cyVerticalSpacing;
		}

		m_wndDontAskCheckBox.Create(m_strCheckBox,
			WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTOCHECKBOX,
			rectCheckBox, this, 0);

		if (m_Params.bIsChecked)
		{
			m_wndDontAskCheckBox.SetCheck(TRUE);
		}

		yButtons += yOffset;
		szTotal.cy += yOffset;
	}

	m_rectIcon.OffsetRect(m_rectClientMargins.left, m_rectClientMargins.top);
	m_rectText.OffsetRect(m_rectClientMargins.left, m_rectClientMargins.top);

	CRect rectButtons (m_rectClientMargins.left, yButtons, m_rectClientMargins.right + szTotal.cx, yButtons);
	AdjustControls(&m_arrButtons[0], (UINT)m_arrButtons.GetSize(), rectButtons, TA_CENTER);

	szTotal.cy += m_szButton.cy; // place for buttons

	CRect rectClient (0, 0, szTotal.cx, szTotal.cy);
	rectClient.InflateRect(m_rectClientMargins);

	AdjustWindowRectEx(&rectClient, 
		::GetWindowLong(GetSafeHwnd (), GWL_STYLE) | WS_CAPTION | WS_BORDER,
		false,
		::GetWindowLong(GetSafeHwnd (), GWL_EXSTYLE)
		);

	SetWindowPos(NULL, 0, 0, rectClient.Width(), rectClient.Height(),
		SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOSENDCHANGING);

	if (!m_bHasCancelButton)
	{
		GetSystemMenu (FALSE)->EnableMenuItem(SC_CLOSE, MF_GRAYED);
		UpdateCaptionButtons();
	}
}

void CKofMessageBox::OnButton( UINT nID )
{
	if (nID == IDCANCEL && !m_bHasCancelButton)
	{
		return;
	}

	if (m_Params.puiAutoRespond != NULL)
	{
		*m_Params.puiAutoRespond = m_wndDontAskCheckBox.IsChecked () ? nID : 0;
	}

	if ((m_Params.dwStyle & MB_TYPEMASK) == MB_OK && m_arrButtons.GetSize () == 1)
	{
		// If 'OK' is the only button force modal result to IDOK
		nID = IDOK;
	}

	EndDialog (nID);
}

LRESULT CKofMessageBox::OnHelp( WPARAM /*wp*/, LPARAM lParam )
{
	HELPINFO hinfo;

	memcpy (&hinfo, (void*)lParam, sizeof(hinfo));
	hinfo.dwContextId = GetWindowContextHelpId();

	if (m_Params.lpfnMsgBoxCallback)
	{
		m_Params.lpfnMsgBoxCallback (&hinfo);
	}
	else
	{
		::SendMessage(m_Params.hwndOwner, WM_HELP, 0, (LPARAM)&hinfo);
	}

	return TRUE;
}

void CKofMessageBox::SetLocalizedString( UINT uID, LPCTSTR lpszText )
{
	for (int i = 0; i < sizeof(s_Buttons) / sizeof(*s_Buttons); ++i)
	{
		if (s_Buttons[i].id == uID)
		{
			s_Buttons[i].pszText = lpszText;
			break;
		}
	}
}

int KofMessageBox( HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType )
{
	MSGBOXPARAMS params;
	ZeroMemory(&params, sizeof(params));

	params.cbSize = sizeof(params);
	params.hwndOwner = hWnd;
	params.hInstance = NULL;
	params.lpszText = lpText;
	params.lpszCaption = lpCaption;
	params.dwStyle = uType;
	params.lpszIcon = NULL;
	params.dwContextHelpId = 0;
	params.lpfnMsgBoxCallback = NULL;
	params.dwLanguageId = LANG_NEUTRAL;

	return KofMessageBoxIndirect(&params);
}

int KofMessageBox( LPCTSTR lpszText, UINT nType /*= MB_OK*/ )
{
	return KofMessageBox(::GetActiveWindow(), lpszText, AfxGetAppName(), nType);
}

int KofMessageBox( UINT nIDPrompt, UINT nType /*= MB_OK*/ )
{
	return KofMessageBox(::GetActiveWindow(), MAKEINTRESOURCE(nIDPrompt), AfxGetAppName(), nType);
}

int KofMessageBoxIndirect( const MSGBOXPARAMS* pMsgBoxParams )
{
	CKofMessageBox mb(pMsgBoxParams);
	return (int)mb.DoModal();
}

int KofMessageBoxIndirect( const KOF_MSGBOXPARAMS* pMsgBoxParams )
{
	CKofMessageBox mb(pMsgBoxParams);
	return (int)mb.DoModal();
}

