#pragma once



// CMyForm form view

class CMyForm : public CKofFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // protected constructor used by dynamic creation
	virtual ~CMyForm();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};


