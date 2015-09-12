// mainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "mainDlg.h"
#include "FPA.h"
#include "process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#pragma comment(lib, "Debug\\FP.lib")

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON5);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMainDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMainDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMainDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDCANCEL, &CMainDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON7, &CMainDlg::OnBnClickedButton7)
	ON_EN_CHANGE(IDC_EDIT1, &CMainDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMainDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON9, &CMainDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMainDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMainDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CMainDlg::OnBnClickedButton12)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon

	SetIcon(m_hIcon, FALSE);		// Set small icon

	HICON hicon;

	hicon =::AfxGetApp ()->LoadIcon (IDI_ICON5);

	ASSERT(hicon);

	AfxGetMainWnd() ->SendMessage(WM_SETICON,TRUE,(LPARAM)hicon);

	// TODO: Add extra initialization here
	SetIcon(m_hIcon, FALSE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint() 
{

	CRect rect;
	GetClientRect(&rect);
	
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icons



	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMainDlg::OnOK() 
{	
	

	//CDialog::OnOK();
}

void CMainDlg::OnBnClickedOk()
{
		m_Dib1=new DIB();
		HBITMAP Bitmap1;
		CStatic *Cstatic1;
		CString FilePathName;
		CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
        NULL,
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("JPG Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"),
        NULL);
	  
	  if(dlg.DoModal()==IDOK)
	  {
			FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
			Bitmap1=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),FilePathName,
			IMAGE_BITMAP,0,0,    
			LR_CREATEDIBSECTION   
			|   LR_DEFAULTSIZE   
			|   LR_LOADFROMFILE   
			|   LR_DEFAULTCOLOR); 

		  Cstatic1=(CStatic *)GetDlgItem(IDC_STATIC1);

		  //Cstatic1->ModifyStyle(NULL,SS_BITMAP|SS_CENTERIMAGE,0);

		  Cstatic1->SetBitmap(Bitmap1);

		  m_Dib1->LoadFile(FilePathName);

		  this->m_lpdata=(uchar *)malloc(m_Dib1->GetSize());

		  this->lptemp=(uchar *)malloc(m_Dib1->GetSize());

		  m_height=m_Dib1->GetHeight();

		  m_width=m_Dib1->GetWidth();

		  m_size=m_Dib1->GetSize();

		  fpnow=m_Dib1->GetData();

		  memcpy(m_lpdata,m_Dib1->GetData(),m_Dib1->GetSize());

		  memcpy(lptemp,m_lpdata,m_Dib1->GetSize());
		  
	  }
			
	  

}

void CMainDlg::OnBnClickedButton1()
{
		CString FilePathName;
	// TODO: 在此添加控件通知处理程序代码
		CFileDialog dlg(FALSE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
        NULL,
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("TXT Files (*.txt)|*.txt|All Files (*.*)|*.*||"),
        NULL);
		if(dlg.DoModal()==IDOK)
	  {
		  
			FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里

			m_Dib1->saveastxt(FilePathName);
	  }
		
}

void CMainDlg::OnBnClickedButton2()
{
	Binary(m_Dib1);

	CStatic *m_static1;
	m_static1=new CStatic();
	HBITMAP m_bitmap;
	uchar *smoo;
	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(300,20,100,400), AfxGetMainWnd(),NULL);



	smooth(m_Dib1->GetData(), smoo, m_Dib1->GetWidth(), m_Dib1->GetHeight(), 2, 2);

	m_Dib1->saveFile("binary.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"binary.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);


	m_static1->SetBitmap(m_bitmap);
	// TODO: 在此添加控件通知处理程序代码
}

void CMainDlg::OnBnClickedButton3()
{	
	CStatic *m_static1;
	m_static1=new CStatic();
	HBITMAP m_bitmap;
	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(300,20,100,400), AfxGetMainWnd(),NULL);
	
	

	smooth(m_Dib1->GetData(),lptemp,m_width,m_height,2,2);

	memcpy(fpnow,lptemp,m_size);

	m_Dib1->saveFile("smooth.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"smooth.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);

}

void CMainDlg::OnBnClickedButton4()
{
	UINT IMGH,IMGW;
	CStatic *m_static1;

	HBITMAP m_bitmap;
  
	unsigned char *zoom;
	
	zoom=(unsigned char *)malloc(m_Dib1->GetSize());
	m_gray=(unsigned char *)malloc(m_Dib1->GetSize());


	IMGW=m_Dib1->GetWidth();
	IMGH=m_Dib1->GetHeight();

	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(300,20,100,400), AfxGetMainWnd(),NULL);
	
	zoomout(m_lpdata,zoom,IMGW,IMGH);
	
	FPA_Grads(zoom,m_gray,m_Dib1->GetWidth(),m_Dib1->GetHeight(),6);

	memcpy(m_Dib1->GetData(),m_gray,m_Dib1->GetSize());

	m_Dib1->saveFile("gray.bmp");
	
	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"gray.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);

	// TODO: 在此添加控件通知处理程序代码
}

void CMainDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	HBITMAP m_bitmap;
	CStatic *m_static;
	uchar *zoom;
	m_ori=(uchar *)malloc(m_size);


	m_static=new CStatic();

	zoom=(uchar *)malloc(m_Dib1->GetSize());

	m_static->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(300,20,100,400), AfxGetMainWnd(),NULL);
	
	zoomout(m_lpdata,zoom,m_Dib1->GetWidth(),m_Dib1->GetHeight());


	getOrientMap(zoom,m_ori,m_Dib1->GetWidth(),m_Dib1->GetHeight(),6);

	memcpy(m_Dib1->GetData(),m_ori,m_Dib1->GetSize());

	m_Dib1->saveFile("orient.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"orient.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);
	
	m_static->SetBitmap(m_bitmap);
	
}

void CMainDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CMainDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CMainDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
 
void CMainDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码

	UINT IMGH,IMGW;
	CStatic *m_static1;

	HBITMAP m_bitmap;

	unsigned char *zoom;
	unsigned char *v_segment;

	zoom=(unsigned char *)malloc(m_Dib1->GetSize());

	m_seg=(unsigned char *)malloc(m_Dib1->GetSize());

	IMGW=m_Dib1->GetWidth();

	IMGH=m_Dib1->GetHeight();

	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(300,20,100,400), AfxGetMainWnd(),NULL);

	FPA_Segment(m_gray,m_seg,6,80,m_width,m_height);

	segment_clearEdge(m_lpdata,m_ori,m_seg,m_width,m_height);

	memcpy(fpnow,m_lpdata,m_size);

	m_Dib1->saveFile("segment.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"segment.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);
	
}

void CMainDlg::OnBnClickedButton9()
{
	CStatic *m_static1;

	HBITMAP m_bitmap;
	
	uchar *equalize2;
	
	equalize2=(uchar *)malloc(m_size);

	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(300,20,100,400), AfxGetMainWnd(),NULL);
	
	equalize(m_Dib1->GetData(),equalize2,m_width,m_height);
	
	memcpy(m_Dib1->GetData(),equalize2,m_Dib1->GetSize());


	m_Dib1->saveFile("equalize2.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"equalize2.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);

}

void CMainDlg::OnBnClickedButton10()
{
	CStatic *m_static1;
	uchar *cover;
	HBITMAP m_bitmap;
	cover=(uchar *)malloc(m_size);
	m_static1=new CStatic();
	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(300,20,100,400), AfxGetMainWnd(),NULL);

	// TODO: 在此添加控件通知处理程序代码
	GaussSmooth(m_lpdata,cover,m_width,m_height,0.4);

	memcpy(m_Dib1->GetData(),cover,m_Dib1->GetSize());

	m_Dib1->saveFile("cover.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"cover.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);


	
	
}

void CMainDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic *m_static1;
	
	uchar *smooth2;

	HBITMAP m_bitmap;
	smooth2=(uchar *)malloc(m_size);
	m_static1=new CStatic();
	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(300,20,100,400), AfxGetMainWnd(),NULL);

	// TODO: 在此添加控件通知处理程序代码
	smooth(m_Dib1->GetData(),smooth2,m_width,m_height,1,1);

	memcpy(m_Dib1->GetData(),smooth2,m_Dib1->GetSize());

	m_Dib1->saveFile("smooth2.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"smooth2.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);

}

void CMainDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic *m_static1;

	uchar *enhance;

	HBITMAP m_bitmap;

	enhance=(uchar *)malloc(m_size);

	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(300,20,100,400), AfxGetMainWnd(),NULL);

	// TODO: 在此添加控件通知处理程序代码

	memcpy(enhance,m_lpdata,m_size);

	orientEnhance(m_ori,enhance,m_width,m_height);



	memcpy(m_Dib1->GetData(),enhance,m_Dib1->GetSize());

	m_Dib1->saveFile("enhance.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"enhance.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);



}
