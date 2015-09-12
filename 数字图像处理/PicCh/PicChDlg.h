// PicChDlg.h : header file
//

#if !defined(AFX_PICCHDLG_H__D1EEEDD3_71CB_4361_894B_6E7CD0DBAEBB__INCLUDED_)
#define AFX_PICCHDLG_H__D1EEEDD3_71CB_4361_894B_6E7CD0DBAEBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPicChDlg dialog

class CPicChDlg : public CDialog
{
// Construction
public:
	CPoint m_ptOrigin;

	CPicChDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPicChDlg)
	enum { IDD = IDD_PICCH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicChDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	//{{AFX_MSG(CPicChDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CButton m_btn;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICCHDLG_H__D1EEEDD3_71CB_4361_894B_6E7CD0DBAEBB__INCLUDED_)
