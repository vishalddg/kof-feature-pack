#pragma once


// CPage1 dialog

class CPage1 : public CKofMFCPropertyPage
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1();
	virtual ~CPage1();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
#pragma once


// CPage2 dialog

class CPage2 : public CKofMFCPropertyPage
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2();
	virtual ~CPage2();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
