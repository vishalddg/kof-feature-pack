#pragma once
#include "KofPack.h"
#include "KofMFCButton.h"
#include "KofGroup.h"

//////////////////////////////////////////////////////////////////////////
// CKofStyleHelper

class KOFPACKDLLEXPORT CKofStyleHelper
{
public:
	static CKofStyleHelper *GetInstance(){
		static CKofStyleHelper styleHelper;
		return &styleHelper;
	};

	enum{
		KOF_CMFCVisualManager = 0,
		KOF_CMFCVisualManagerOfficeXP,
		KOF_CMFCVisualManagerWindows,
		KOF_CMFCVisualManagerOffice2003,
		KOF_CMFCVisualManagerVS2005,
		KOF_CMFCVisualManagerOffice2007,
		KOF_MAXCOUNT,
	};
	BOOL AutoSetStyle();
	BOOL SetStyle(UINT nStyle);
	void SetDlgCaptionCenter(BOOL bDlgCaptionCenter){m_bDlgCaptionCenter = bDlgCaptionCenter;}

	virtual BOOL OnFillDialog(CDC* pDC, CWnd* pDlg, CRect rect);
	virtual CBrush& GetDlgBackBrush(CWnd* pDlg);
	virtual CSize GetCheckRadioDefaultSize();
	virtual void OnDrawRadioButton(CDC *pDC, CRect rect, BOOL bOn, BOOL bHighlighted, BOOL bPressed, BOOL bEnabled);
	virtual BOOL OnDrawPushButton(CDC* pDC, CRect rect, CKofMFCButton* pButton, COLORREF& clrText);
	virtual BOOL IsOwnerDrawDlgSeparator(CWnd* /*pCtrl*/);
	virtual void OnDrawDlgSeparator(CDC* pDC, CWnd* pCtrl, CRect rect, BOOL bIsHorz);
	virtual void OnDrawEditBorder(CDC* pDC, CRect rect, BOOL bHighlighted, BOOL bDroppedDowned, BOOL bEnabled);
	virtual void OnDrawRibbonComboDropButton(CDC* pDC, CRect rect, BOOL bDisabled, BOOL bIsDropped, BOOL bIsHighlighted);
	virtual void OnEditContextMenu(CWnd* pWnd, CPoint point);
	virtual BOOL Draw2007RadioButton(CDC *pDC, CRect rect, BOOL bHighlighted, BOOL bChecked, BOOL bEnabled, BOOL bPressed);
	virtual void OnDrawGroup(CDC* pDC, CKofGroup* pGroup, CRect rect, const CString& strName);
	virtual BOOL OnNcPaint(CWnd* pWnd, const CObList& lstSysButtons, CRect rectRedraw);
	virtual BOOL OnSetWindowRegion(CWnd* pWnd, CSize sizeWindow);
	virtual void OnDrawSpinButtons(CDC* pDC, CRect rectSpin, int nState, BOOL bOrientation, CMFCSpinButtonCtrl* pSpinCtrl);
	virtual void OnDrawRibbonProgressBar(CDC* pDC, CMFCRibbonProgressBar* pProgress, CRect rectProgress, CRect rectChunk, BOOL bInfiniteMode);

private:
	CKofStyleHelper(void);
	~CKofStyleHelper(void);

	UINT m_Style;
	COLORREF m_clrDlgBackground;
	CBrush m_brDlgBackground;
	CMFCControlRenderer m_ctrlRibbonBtnPush;
	CMFCControlRenderer m_ctrlRibbonBtnRadio;
	CMFCControlRenderer	m_ctrlRibbonBtnGroup;
	COLORREF m_clrRibbonEditBorder;
	COLORREF m_clrRibbonEditBorderDisabled;
	COLORREF m_clrRibbonEditBorderHighlighted;
	COLORREF m_clrRibbonEditBorderPressed;
	BOOL m_bDlgCaptionCenter;
};