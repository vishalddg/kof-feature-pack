
// testDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testDlg.h"
#include "testDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CtestDlgDlg dialog




CtestDlgDlg::CtestDlgDlg(CWnd* pParent /*=NULL*/)
	: CKofDialogEx(CtestDlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CKofDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO3, m_ComboFont);
	DDX_Control(pDX, IDC_BUTTON3, m_BtnColor);
	DDX_Control(pDX, IDC_BUTTON2, m_BtnMenu);
	DDX_Control(pDX, IDC_BUTTON4, m_BtnLink);
}

BEGIN_MESSAGE_MAP(CtestDlgDlg, CKofDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_ABOUTBOX, OnAbout)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO2, &CtestDlgDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestDlgDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CtestDlgDlg message handlers

BOOL CtestDlgDlg::OnInitDialog()
{
	CKofDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))->SetPos(35);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(5);
	((CKofMFCEdit*)GetDlgItem(IDC_EDIT2))->EnableFileBrowseButton();
	((CKofMFCEdit*)GetDlgItem(IDC_EDIT3))->EnableFolderBrowseButton();
	m_menu.LoadMenu(IDR_MENU1);
	m_BtnMenu.m_hMenu = m_menu.GetSubMenu(0)->GetSafeHmenu();
	m_BtnMenu.SizeToContent();
	m_BtnMenu.m_bOSMenu = FALSE;

	// TODO: Add extra initialization here
	//((CMFCSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetBuddy(GetDlgItem(IDC_EDIT1));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtestDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CKofDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtestDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CKofDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtestDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtestDlgDlg::OnAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CtestDlgDlg::OnCbnSelchangeCombo2()
{
	int nSel = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
	switch (nSel)
	{
	case 0:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;
	case 1:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;
	case 2:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;
	case 3:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		break;
	case 4:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		break;
	case 5:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;
	case 6:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;
	case 7:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;
	case 8:
		CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		break;
	}
	CKofStyleHelper::GetInstance()->AutoSetStyle();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
}

void CtestDlgDlg::OnBnClickedButton2()
{
	CString strItem;
	switch (m_BtnMenu.m_nMenuResult)
	{
	case ID_32771:strItem = _T("点击了第一项");
		break;
	case ID_32772:strItem = _T("点击了第二项");
		break;
	}
	AfxMessageBox(strItem, MB_OK | MB_ICONINFORMATION);
}
