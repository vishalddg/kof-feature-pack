#pragma once
#include "KofPack.h"


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
	BOOL SetStyle(UINT nStyle);

	virtual BOOL OnFillDialog(CDC* pDC, CWnd* pDlg, CRect rect);
	virtual CBrush& GetDlgBackBrush(CWnd* pDlg);
	virtual CSize GetCheckRadioDefaultSize();
	virtual void OnDrawRadioButton(CDC *pDC, CRect rect, BOOL bOn, BOOL bHighlighted, BOOL bPressed, BOOL bEnabled);
	virtual BOOL OnDrawPushButton(CDC* pDC, CRect rect, CMFCButton* pButton, COLORREF& clrText);
	virtual BOOL IsOwnerDrawDlgSeparator(CWnd* /*pCtrl*/);
	virtual void OnDrawDlgSeparator(CDC* pDC, CWnd* pCtrl, CRect rect, BOOL bIsHorz);
	virtual void OnDrawEditBorder(CDC* pDC, CRect rect, BOOL bHighlighted, BOOL bDroppedDowned, BOOL bEnabled);
	virtual void OnDrawRibbonComboDropButton(CDC* pDC, CRect rect, BOOL bDisabled, BOOL bIsDropped, BOOL bIsHighlighted);
	virtual void OnEditContextMenu(CWnd* pWnd, CPoint point);
	virtual BOOL Draw2007RadioButton(CDC *pDC, CRect rect, BOOL bHighlighted, BOOL bChecked, BOOL bEnabled, BOOL bPressed);

private:
	CKofStyleHelper(void);
	~CKofStyleHelper(void);

	UINT m_Style;
	COLORREF m_clrDlgBackground;
	CBrush m_brDlgBackground;
	CMFCControlRenderer m_ctrlRibbonBtnPush;
	CMFCControlRenderer m_ctrlRibbonBtnRadio;
	COLORREF m_clrRibbonEditBorder;
	COLORREF m_clrRibbonEditBorderDisabled;
	COLORREF m_clrRibbonEditBorderHighlighted;
	COLORREF m_clrRibbonEditBorderPressed;
};
