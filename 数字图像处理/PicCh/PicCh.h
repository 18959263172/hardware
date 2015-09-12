// PicCh.h : main header file for the PICCH application
//

#if !defined(AFX_PICCH_H__FF8ABD91_A572_4EB8_B329_C16B45E1B7C7__INCLUDED_)
#define AFX_PICCH_H__FF8ABD91_A572_4EB8_B329_C16B45E1B7C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPicChApp:
// See PicCh.cpp for the implementation of this class
//

class CPicChApp : public CWinApp
{
public:
	CPicChApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicChApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPicChApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICCH_H__FF8ABD91_A572_4EB8_B329_C16B45E1B7C7__INCLUDED_)
