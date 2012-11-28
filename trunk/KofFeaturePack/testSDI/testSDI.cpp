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

// testSDI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "testSDI.h"
#include "MainFrm.h"

#include "testSDIDoc.h"
#include "testSDIView.h"
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#include "afxcmn.h"
#include "afxcolorbutton.h"
#include "afxtagmanager.h"
#include "kofmfcbutton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestSDIApp

BEGIN_MESSAGE_MAP(CtestSDIApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CtestSDIApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CtestSDIApp construction

CtestSDIApp::CtestSDIApp()
{

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CtestSDIApp object

CtestSDIApp theApp;


// CtestSDIApp initialization

BOOL CtestSDIApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(0);  // Load standard INI file options

	InitContextMenuManager();
	AfxInitRichEdit2();
	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CtestSDIDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CtestSDIView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CKofDialogEx
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
public:
	CKofMFCButton m_BtnOne;
	CKofMFCEdit m_EditCtrl;
	virtual BOOL OnInitDialog();
	CKofComboBox m_Com2;
	CKofComboBox m_Com3;
	CKofStatic m_StcText;
	CKofStatic m_StcColorText;
	CKofProgressCtrl m_PgcOne;
	CKofMFCColorButton m_ColorPicker;
	CKofMFCSpinButtonCtrl m_SpnOne;
	CKofMFCEdit m_EditTwo;
	CKofRichEditCtrl m_RichOne;
	CKofMFCEdit m_edtTwo;
	CMFCListCtrl m_ListOne;
	CKofMFCFontComboBox m_comFont;
	CKofMFCMaskedEdit m_EdtMask;
	CKofMFCButton m_BtnChk1;
	CKofMFCButton m_BtnRad1;
	CKofMFCButton m_BtnChk2;
	CKofMFCButton m_BtnRad2;
	CKofMFCButton m_BtnOK;
};

CAboutDlg::CAboutDlg() : CKofDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CKofDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_BtnOne);
	DDX_Control(pDX, IDC_EDIT1, m_EditCtrl);
	DDX_Control(pDX, IDC_COMBO2, m_Com2);
	DDX_Control(pDX, IDC_COMBO3, m_Com3);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_StcText);
	DDX_Control(pDX, IDC_STATIC_CORTEXT, m_StcColorText);
	DDX_Control(pDX, IDC_PROGRESS1, m_PgcOne);
	DDX_Control(pDX, IDC_BUTTON2, m_ColorPicker);
	DDX_Control(pDX, IDC_SPIN1, m_SpnOne);
	DDX_Control(pDX, IDC_EDIT2, m_EditTwo);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichOne);
	DDX_Control(pDX, IDC_EDIT3, m_edtTwo);
	DDX_Control(pDX, IDC_LIST1, m_ListOne);
	DDX_Control(pDX, IDC_COMBO1, m_comFont);
	DDX_Control(pDX, IDC_EDIT4, m_EdtMask);
	DDX_Control(pDX, IDC_CHECK1, m_BtnChk1);
	DDX_Control(pDX, IDC_RADIO1, m_BtnRad1);
	DDX_Control(pDX, IDC_CHECK2, m_BtnChk2);
	DDX_Control(pDX, IDOK, m_BtnOK);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CKofDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CtestSDIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CtestSDIApp customization load/save methods

void CtestSDIApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CtestSDIApp::LoadCustomState()
{
}

void CtestSDIApp::SaveCustomState()
{
}

// CtestSDIApp message handlers




BOOL CAboutDlg::OnInitDialog()
{
	CKofDialogEx::OnInitDialog();

	m_EditCtrl.EnableFileBrowseButton();
	m_StcColorText.SetTextColor(RGB(255, 0, 0));
	m_PgcOne.SetPos(20);
	m_ColorPicker.EnableAutomaticButton(_T("默认值"), RGB(0, 0, 0)); 
	m_ColorPicker.EnableOtherButton(_T("其余颜色")); 
	m_ColorPicker.SetColor((COLORREF)-1); 
	m_ColorPicker.SetColumnsNumber(10); 

	m_ListOne.InsertColumn(0, _T("列一"), LVCFMT_LEFT, 40);
	m_ListOne.InsertColumn(1, _T("列二"), LVCFMT_LEFT, 30);
	m_ListOne.InsertItem(0, _T("dfdf"));
	m_ListOne.InsertItem(1, _T("dfdfdfdf"));

	m_comFont.SelectFont(_T("Arial"));
	m_EdtMask.EnableMask(_T(" ddd  ddd dddd"), // The mask string
		_T("(___) ___-____"), // Literal, "_" char = character entry
		_T(' ')); // Default char
	m_EdtMask.SetValidChars(NULL); // Valid string characters
	m_EdtMask.SetWindowText(_T("(123) 123-1212"));

	m_BtnRad2.SubclassDlgItem(IDC_RADIO2, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
