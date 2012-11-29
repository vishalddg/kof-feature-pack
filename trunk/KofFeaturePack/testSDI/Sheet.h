#pragma once
#include "Page.h"

// CSheet

class CSheet : public CKofMFCPropertySheet
{
	DECLARE_DYNAMIC(CSheet)

public:
	CSheet();
	virtual ~CSheet();

	CPage1 m_Page1;
	CPage2 m_Page2;
protected:
	DECLARE_MESSAGE_MAP()
};


