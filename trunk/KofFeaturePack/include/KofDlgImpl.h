#pragma once
#include "KofPack.h"

class KOFPACKDLLEXPORT CKofDlgImpl
{
	friend class CKofDialogEx;
	friend class CKofMFCPropertySheet;
	friend class CKofMFCPropertyPage;

public:
	CKofDlgImpl(CWnd& dlg);
	~CKofDlgImpl(void);

protected:
	BOOL IsOwnerDrawCaption ()
	{
		return m_bVisualManagerNCArea && CMFCVisualManager::GetInstance()->IsOwnerDrawCaption();
	}
	BOOL OnNcPaint();
	void RedrawCaptionButton(CMFCCaptionButtonEx* pBtn);
	void OnLButtonDown(CPoint point);
	CMFCCaptionButtonEx* GetSysButton(UINT nHit);
	void UpdateCaption();
	CRect GetCaptionRect();
	int GetCaptionHeight();
	void OnChangeVisualManager();
	void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	void UpdateCaptionButtons();
	void EnableVisualManagerStyle(BOOL bEnable, BOOL bNCArea = FALSE, const CList<UINT,UINT>* plstNonSubclassedItems = NULL);
	void OnNcActivate (BOOL& bActive);
	void OnActivate(UINT nState, CWnd* pWndOther);
	void OnNcMouseMove(UINT nHitTest, CPoint point);
	void OnTrackCaptionButtons(CPoint point);
	UINT OnNcHitTest(CPoint point);
	void OnLButtonUp(CPoint point);
	void StopCaptionButtonsTracking();
	void OnMouseMove(CPoint point);
	void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	int OnCreate();
	BOOL OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL PreTranslateMessage(MSG* pMsg);
	void OnDestroy();

	CWnd& m_Dlg;
	CObList m_lstCaptionSysButtons;
	CRect m_rectRedraw;
	UINT m_nHotSysButton;
	UINT m_nHitSysButton;
	BOOL m_bWindowPosChanging;
	BOOL m_bIsWindowRgn;
	BOOL m_bHasBorder;
	CRect m_rectResizeBox;
	BOOL m_bVisualManagerNCArea;
	CArray<CWnd*, CWnd*>	m_arSubclassedCtrls;
};
