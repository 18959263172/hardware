// main.h : main header file for the MAIN application
//

#if !defined(AFX_MAIN_H__90B99FAE_64A9_4909_87CE_15E960D90C76__INCLUDED_)
#define AFX_MAIN_H__90B99FAE_64A9_4909_87CE_15E960D90C76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include"DIB.H"
#include "process.h"
/////////////////////////////////////////////////////////////////////////////
// CMainApp:
// See main.cpp for the implementation of this class
//
;
class CMainApp : public CWinApp
{
public:
	CMainApp();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMainApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAIN_H__90B99FAE_64A9_4909_87CE_15E960D90C76__INCLUDED_)
