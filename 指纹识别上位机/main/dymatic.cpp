// dymatic.cpp : 实现文件
//

#include "stdafx.h"
#include "main.h"
#include "dymatic.h"


// dymatic 对话框

IMPLEMENT_DYNAMIC(dymatic, CDialog)

dymatic::dymatic(CWnd* pParent /*=NULL*/)
	: CDialog(dymatic::IDD, pParent)
{

}

dymatic::~dymatic()
{
}

void dymatic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dymatic, CDialog)
END_MESSAGE_MAP()


// dymatic 消息处理程序
