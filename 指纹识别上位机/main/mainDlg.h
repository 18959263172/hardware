// mainDlg.h : header file
//

#include "afxwin.h"
#include "mscomm1.h"
#include "serial.h"
#include "sigslot.h"

#include"feature.h"
#if !defined(AFX_MAINDLG_H__14F0DA4B_A7A6_4CBE_8D50_1B9267EA47C7__INCLUDED_)
#define AFX_MAINDLG_H__14F0DA4B_A7A6_4CBE_8D50_1B9267EA47C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CDialog,public sigslot::has_slots<>
{
// Construction
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor;
// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_MAIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CString m_strRXData;
	HICON m_hIcon;
	DIB *m_Dib1;
	uchar *m_lpdata;  //
	uchar *lptemp;
	uchar *fpnow;
	uchar *m_ori,*m_gray,*m_seg,*m_thin;   //分别为方向场，梯度场，和分割场,预处理后的指纹图片
	int m_height,m_width;
	int m_size;
	FEATURE *  m_feature;
	CListCtrl *m_CListpattern,*m_CListnow;
	CString COM;
	COMM m_comm;
	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void OnData(char *pData,int count);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedThin();
	afx_msg void OnBnClickedButton15();
	CComboBox m_combox;
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton8();
	CEdit m_edsend;
	CEdit m_edrcv;
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnNMClickListnow(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__14F0DA4B_A7A6_4CBE_8D50_1B9267EA47C7__INCLUDED_)
