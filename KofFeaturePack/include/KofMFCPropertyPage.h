#pragma once
#include "KofPack.h"
#include "KofDlgImpl.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCPropertyPage

class KOFPACKDLLEXPORT CKofMFCPropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(CKofMFCPropertyPage)

public:
	CKofMFCPropertyPage();
	CKofMFCPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0);
	CKofMFCPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0);
	virtual ~CKofMFCPropertyPage();

	void EnableVisualManagerStyle(BOOL bEnable = TRUE, const CList<UINT,UINT>* plstNonSubclassedItems = NULL);

protected:
	CKofDlgImpl m_KImpl;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnNcPaint();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};


