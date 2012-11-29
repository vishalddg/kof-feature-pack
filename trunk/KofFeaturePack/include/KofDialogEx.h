#pragma once
#include "KofDlgImpl.h"
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofDialogEx

class KOFPACKDLLEXPORT CKofDialogEx : public CDialogEx
{
	DECLARE_DYNAMIC(CKofDialogEx)

public:
	CKofDialogEx();
	CKofDialogEx(UINT nIDTemplate, CWnd *pParent = NULL);
	CKofDialogEx(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);
	virtual ~CKofDialogEx();

	void EnableVisualManagerStyle(BOOL bEnable = TRUE, BOOL bNCArea = FALSE, const CList<UINT,UINT>* plstNonSubclassedItems = NULL);

protected:
	CKofDlgImpl m_KImpl;

protected:
	afx_msg void OnNcPaint();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnSetText(WPARAM, LPARAM);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnChangeVisualManager(WPARAM, LPARAM);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};


