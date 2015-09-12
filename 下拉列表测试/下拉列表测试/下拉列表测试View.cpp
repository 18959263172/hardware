// 下拉列表测试View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "下拉列表测试.h"

#include "下拉列表测试Doc.h"
#include "下拉列表测试View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CFormView)

BEGIN_MESSAGE_MAP(CMyView, CFormView)
	//{{AFX_MSG_MAP(CMyView)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
	: CFormView(CMyView::IDD)
{
	//{{AFX_DATA_INIT(CMyView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMyView::~CMyView()
{
}

void CMyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyView)
	DDX_Control(pDX, IDC_COMBO1, m_combobox);
	//}}AFX_DATA_MAP
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();


	//添加4条记录
	m_combobox.AddString("2012年07月03日");
	m_combobox.AddString("2012年07月01日");
	m_combobox.AddString("2012年07月05日");
	m_combobox.AddString("2012年07月04日");

	//设置选中项为第0号
	m_combobox.SetCurSel(0);





}

/////////////////////////////////////////////////////////////////////////////
// CMyView printing

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMyView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

//当用户单击或者选择某项时触发
void CMyView::OnSelchangeCombo1() 
{
	CString str;
	//获得指定序号的文本，序号由GetCurSel()获得用户当前选定的项序号
	m_combobox.GetLBText(m_combobox.GetCurSel(),str);
	MessageBox(str);
	
}
