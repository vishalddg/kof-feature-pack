#pragma once
#include "KofPack.h"
#include "KofDlgImpl.h"

//////////////////////////////////////////////////////////////////////////
// CKofFormView form view

class KOFPACKDLLEXPORT CKofFormView : public CFormView
{
	DECLARE_DYNAMIC(CKofFormView)

protected:
	CKofFormView(LPCTSTR lpszTemplateName);
	CKofFormView(UINT nIDTemplate);
	virtual ~CKofFormView();

public:
	void EnableVisualManagerStyle(BOOL bEnable = TRUE, const CList<UINT,UINT>* plstNonSubclassedItems = NULL);
	virtual void OnInitialUpdate();

protected:
	CKofDlgImpl m_KImpl;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};


