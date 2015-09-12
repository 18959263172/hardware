// mainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "mainDlg.h"
#include "FPA.h"
#include "process.h"

#include "feature.h"
#include "dymatic.h"
#include "serial.h"

#include"patternMatch.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//#pragma comment(lib, "Debug\\FP.lib")

unsigned char FLag=0;
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
	COM="COM";
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO2, m_combox);
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
	ON_BN_CLICKED(IDC_BUTTON13, &CMainDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CMainDlg::OnBnClickedThin)
	ON_BN_CLICKED(IDC_BUTTON15, &CMainDlg::OnBnClickedButton15)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMainDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON8, &CMainDlg::OnBnClickedButton8)
	
	ON_BN_CLICKED(IDC_BUTTON17, &CMainDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON16, &CMainDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON21, &CMainDlg::OnBnClickedButton21)

	ON_NOTIFY(NM_CLICK, IDC_LISTNOW, &CMainDlg::OnNMClickListnow)
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

	this->m_CListpattern=(CListCtrl *)GetDlgItem(IDC_LISTPATTERN);  
	m_CListpattern->InsertColumn(0,"特征点序号",LVCFMT_CENTER,60);  
	m_CListpattern->InsertColumn(1,"特征点类型",LVCFMT_CENTER,90);
	m_CListpattern->InsertColumn(2,"特征点坐标",LVCFMT_CENTER,90);

	this->m_CListnow=(CListCtrl *)GetDlgItem(IDC_LISTNOW);  
	m_CListnow->InsertColumn(0,"特征点序号",LVCFMT_CENTER,60);  
	m_CListnow->InsertColumn(1,"特征点类型",LVCFMT_CENTER,90);
	m_CListnow->InsertColumn(2,"特征点坐标",LVCFMT_CENTER,90);

	for (unsigned char x=0;x<10;x++)
	{
		CString Z((char)(x+48));
		m_combox.AddString(COM+Z);
	}



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

void CMainDlg::OnBnClickedOk()   //打开指纹图片
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

		  memcpy(m_lpdata,m_Dib1->GetData(),m_Dib1->GetSize());  //m_lpdata为第一次缓存

		  memcpy(lptemp,m_lpdata,m_Dib1->GetSize());   
		  
	  }
			
	  

}

void CMainDlg::OnBnClickedButton1()    //指纹图片加载
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

	smoo=(uchar *)malloc(m_size);

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);



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
	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);
	
	

	smooth(m_Dib1->GetData(),lptemp,m_Dib1->GetWidth(),m_Dib1->GetHeight(),2,2);

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

void CMainDlg::OnBnClickedButton4()   // 求梯度  
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

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);
	
	zoomout(m_Dib1->GetData(),zoom,m_Dib1->GetWidth(),m_Dib1->GetHeight());   //缩小图片
	
	getGrads(zoom,m_gray,m_Dib1->GetWidth(),m_Dib1->GetHeight(),2);   //计算梯度 

	memcpy(m_Dib1->GetData(),m_gray,m_Dib1->GetSize());

	m_Dib1->saveFile("s_gray.bmp");
	
	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"s_gray.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);

	// TODO: 在此添加控件通知处理程序代码
}

void CMainDlg::OnBnClickedButton5()        //获取方向场
{
	// TODO: 在此添加控件通知处理程序代码
	HBITMAP m_bitmap;
	CStatic *m_static;
	uchar *zoom;
	m_ori=(uchar *)malloc(m_size);
	m_static=new CStatic();
	zoom=(uchar *)malloc(m_Dib1->GetSize());


	m_static->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);
	
	zoomout(m_lpdata,zoom,m_Dib1->GetWidth(),m_Dib1->GetHeight());


	getOrientMap(zoom,m_ori,m_Dib1->GetWidth(),m_Dib1->GetHeight(),1);

	memcpy(m_Dib1->GetData(),m_ori,m_Dib1->GetSize());

	m_Dib1->saveFile("s+orient.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"s+orient.bmp",
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
	static unsigned char flag=1;
	if(flag)
	{
		if(m_comm.Serial_init("COM2")) 
		{
			flag=0;

			m_comm.OnData.connect(this,&CMainDlg::OnData);
		}
	}

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
 
void CMainDlg::OnBnClickedButton6() //前景背景分割
{
	// TODO: 在此添加控件通知处理程序代码

	UINT IMGH,IMGW;
	CStatic *m_static1;

	HBITMAP m_bitmap;

	unsigned char *zoom;

	zoom=(unsigned char *)malloc(m_Dib1->GetSize());

	m_seg=(unsigned char *)malloc(m_Dib1->GetSize());

	IMGW=m_Dib1->GetWidth();

	IMGH=m_Dib1->GetHeight();

	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);

	segment(m_gray,m_seg,80,m_Dib1->GetWidth(),m_Dib1->GetHeight());

	segment_clearEdge(m_lpdata,m_ori,m_seg,m_Dib1->GetWidth(),m_Dib1->GetHeight());
	
	memcpy(fpnow,m_lpdata,m_size);

	m_Dib1->saveFile("m_segment.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"m_segment.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);

	
}

void CMainDlg::OnBnClickedButton9()   //直方图均衡
{
	CStatic *m_static1;

	HBITMAP m_bitmap;
	
	uchar *equalize2;
	
	equalize2=(uchar *)malloc(m_size);

	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);
	
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

void CMainDlg::OnBnClickedButton10()  //收敛
{
	CStatic *m_static1;
	uchar *cover;
	HBITMAP m_bitmap;
	cover=(uchar *)malloc(m_size);
	m_static1=new CStatic();
	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);

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

;
	
	
}

void CMainDlg::OnBnClickedButton11()  //平滑
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic *m_static1;
	
	uchar *smooth2;

	HBITMAP m_bitmap;
	smooth2=(uchar *)malloc(m_size);
	m_static1=new CStatic();
	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);

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

void CMainDlg::OnBnClickedButton12()  //增强
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic *m_static1;

	uchar *enhance;

	HBITMAP m_bitmap;

	enhance=(uchar *)malloc(m_size);

	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);

	// TODO: 在此添加控件通知处理程序代码

	memcpy(enhance,m_lpdata,m_size);

	orientEnhance(m_ori,enhance,m_width,m_height);

	memcpy(m_Dib1->GetData(),enhance,m_Dib1->GetSize());

	m_Dib1->saveFile("msenhance.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"msenhance.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);


}

void CMainDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic *m_static1;
	HBITMAP m_bitmap;

	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);

	Binary(m_Dib1);

	m_Dib1->saveFile("enhance_binary.bmp");

	m_bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"enhance_binary.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);

	m_static1->SetBitmap(m_bitmap);

}



void CMainDlg::OnBnClickedThin()
{
	CStatic *m_static1;

	m_static1=new CStatic();
	
	HBITMAP m_bitmap1;
	
	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,536,760), AfxGetMainWnd(),NULL);

	m_thin=(uchar *)malloc(m_Dib1->GetSize());

	// TODO: 在此添加控件通知处理程序代码
	imageThin(m_Dib1->GetData(),m_thin,m_width,m_height);
	//imageThinembed(m_Dib1->GetData(),m_thin,256,360);
	memcpy(m_Dib1->GetData(),m_thin,m_size);

	m_Dib1->saveFile("thin.bmp");

	m_bitmap1=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"thin.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR
		);


	m_static1->SetBitmap(m_bitmap1);


}

void CMainDlg::OnBnClickedButton15()          //指纹获取特征码
{
	char *C_Num;

	CFile m_fp(TEXT("d://feature.dat"),CFile::modeCreate|CFile::modeWrite);

	CDC *dc1;

	HBITMAP m_bitmap1;

	CString strText;

	m_feature=(FEATURE *)malloc(sizeof(FEATURE));

	CRect rc;

	CStatic *m_static1;

	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,200,400), AfxGetMainWnd(),NULL);

	m_bitmap1=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),"thin.bmp",
		IMAGE_BITMAP,0,0,    
		LR_CREATEDIBSECTION   
		|   LR_DEFAULTSIZE   
		|   LR_LOADFROMFILE   
		|   LR_DEFAULTCOLOR  
		);
	m_static1->ModifyStyle(0,BS_OWNERDRAW); 

	//m_static1->SetBitmap(m_bitmap1);

	m_static1->GetClientRect(&rc);

	//getMinutia((char *)m_lpdata,(char *)m_ori,f,m_width,m_height);
	FPA_GetMinutia(m_thin, m_ori, m_feature, m_width, m_height);           //获得特征点

	dc1=m_static1->GetDC();

	C_Num=(char *)malloc(sizeof(int));

	getSingularMinutia(m_ori, m_width, m_height,1, (FEATURE *)m_feature);     //获取奇异点

	m_fp.Write(&(m_feature->MinutiaNum),4);           //写入个数

	m_fp.Write(m_feature->MinutiaArr,(m_feature->MinutiaNum)*sizeof(MINUTIA));         //写入特征点数组

	if (m_feature->MinutiaNum>0)   //绘制特征点
	{
		for (int z=0;z<m_feature->MinutiaNum;z++)
		{
			dc1->DrawEdge(CRect((m_feature->MinutiaArr[z].x)-5,360-(m_feature->MinutiaArr[z].y)-5,(m_feature->MinutiaArr[z].x)+5,
				360-(m_feature->MinutiaArr[z].y)+5),EDGE_BUMP ,BF_TOPLEFT|BF_TOPRIGHT  );
		}
	}


	for(int count=0;count<m_feature->MinutiaNum;count++)
	{
		this->m_CListnow->InsertItem(LVIF_TEXT | LVIF_STATE, 0, strText,   
			(0% 2) == 0 ? LVIS_SELECTED : 0, LVIS_SELECTED, 0, 0);  

		strText.Format("%d",m_feature->MinutiaNum-count);
		m_CListnow->SetItemText(0, 0, strText);  

		switch(m_feature->MinutiaArr[count].Type)
		{
		case 1:
			strText="END";
			break;
		case 2:
			strText="FORK";
			break;
		case 3:
			strText="DELTA";
			break;
		case 4:
			strText="CORE";
			break;
		}

		
		m_CListnow->SetItemText(0, 1, strText);  
		strText.Format(TEXT("(%d,%d)"),m_feature->MinutiaArr[count].x,m_feature->MinutiaArr[count].y);
		m_CListnow->SetItemText(0, 2, strText);  
	}
	
	
	m_fp.Close();
	// TODO: 在此添加控件通知处理程序代码
}
void CMainDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码

}
void CMainDlg::OnBnClickedButton8()
{
	char x[26624];
	memset(x,26624,1);
	FLag=0;
	if(m_comm.Serial_write((char* )m_lpdata,32768)==0)
	{
		AfxMessageBox(TEXT("发送1错误") ,0,0) ;
	}
	else FLag=1;
	Sleep(3000);
	if (FLag==2)
	{
		if(m_comm.Serial_write((char* )(m_lpdata+32768),32768)==0)
		{
				AfxMessageBox(TEXT("发送2错误") ,0,0);
				FLag=3;
		}
		else FLag=4;
	}
	Sleep(3000);
	if(FLag==5)
	{
		if(m_comm.Serial_write((char* )(m_lpdata+65536),26624)==0) AfxMessageBox(TEXT("发送3错误") ,0,0) ;
	}
	// TODO: 在此添加控件通知处理程序代码
}

void CMainDlg::OnBnClickedButton17()   //源文件发送
{
	// TODO: 在此添加控件通知处理程序代码	

}
void CMainDlg::OnData( char *pData,int count )
{
	int i=0;
	if(!strcmp(pData,"02r")) FLag=2;
	if(!strcmp(pData,"2r")) FLag=2;		
	if(!strcmp(pData,"03r")) FLag=5;
	if(!strcmp(pData,"3r")) FLag=5;		
}
void CMainDlg::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	m_comm.Serialclose();
}

void CMainDlg::OnBnClickedButton21()           //图像的扫描
{
	FEATURE *f;

	int errno;

	MATCHRESULT* lpMatchResult;

	lpMatchResult=(MATCHRESULT *)malloc(sizeof(MATCHRESULT));

	f=(FEATURE *)malloc(sizeof(FEATURE));

	CFile m_fp("d://feature.dat",CFile::modeReadWrite);

	errno=GetLastError();

	m_fp.Read(&(f->MinutiaNum),4);           //读入个数

	m_fp.Read(f->MinutiaArr,(f->MinutiaNum)*sizeof(MINUTIA));         //读入特征点数组


	patternMatch(m_feature,f, lpMatchResult, 2 );


	// TODO: 在此添加控件通知处理程序代码

	if(lpMatchResult->Similarity>100)
	{
		::MessageBox(NULL,TEXT("MACH!"),0,MB_OK);
	}
}




void CMainDlg::OnNMClickListnow(NMHDR *pNMHDR, LRESULT *pResult)
{
	CStatic *m_static1;

	CPen pen(0, 1, RGB(255,0,0));



	m_static1=new CStatic();

	m_static1->Create(_TEXT("tmp"),WS_CHILD|WS_VISIBLE|SS_BITMAP, CRect(280,13,200,400), AfxGetMainWnd(),NULL);

	CRect rc; 

	CDC *dc1;

	m_static1->ModifyStyle(0,BS_OWNERDRAW); 

	//m_static1->SetBitmap(m_bitmap1);

	m_static1->GetClientRect(&rc);

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR; 

	dc1=m_static1->GetDC();


	if (m_feature->MinutiaNum>0)   //绘制特征点
	{
		for (int z=0;z<m_feature->MinutiaNum;z++)
		{
			dc1->DrawEdge(CRect((m_feature->MinutiaArr[z].x)-5,360-(m_feature->MinutiaArr[z].y)-5,(m_feature->MinutiaArr[z].x)+5,
				360-(m_feature->MinutiaArr[z].y)+5),EDGE_BUMP ,BF_TOPLEFT|BF_TOPRIGHT  );
		}
	}

	if(pNMListView->iItem != -1) 
	{ 
		CString strtemp; 
		strtemp.Format("单击的是第%d行第%d列", 
			pNMListView->iItem, pNMListView->iSubItem); 
		// AfxMessageBox(strtemp); 

		CBrush* pOldBrush = (CBrush*)dc1->SelectObject(&pen);  

		dc1->Rectangle(CRect((m_feature->MinutiaArr[ m_feature->MinutiaNum-pNMListView->iItem].x)-5,360-(m_feature->MinutiaArr[ m_feature->MinutiaNum-pNMListView->iItem].y)-5,(m_feature->MinutiaArr[m_feature->MinutiaNum-pNMListView->iItem].x)+5,
			360-(m_feature->MinutiaArr[m_feature->MinutiaNum-pNMListView->iItem].y)+5)
			);	
		dc1->SelectObject(pOldBrush);
	} 



	*pResult = 0; 
}
