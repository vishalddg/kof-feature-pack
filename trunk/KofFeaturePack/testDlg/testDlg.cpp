
// testDlg.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "testDlg.h"
#include "testDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestDlgApp

BEGIN_MESSAGE_MAP(CtestDlgApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CtestDlgApp construction

CtestDlgApp::CtestDlgApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CtestDlgApp object

CtestDlgApp theApp;


// CtestDlgApp initialization

BOOL CtestDlgApp::InitInstance()
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

	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
	CKofStyleHelper::GetInstance()->SetStyle(CKofStyleHelper::KOF_CMFCVisualManagerOffice2007);

	AfxInitRichEdit2();
	InitShellManager();

	CtestDlgDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CtestDlgApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
	return KofMessageBox(lpszPrompt, nType);
	//return CWinAppEx::DoMessageBox(lpszPrompt, nType, nIDPrompt);
}
