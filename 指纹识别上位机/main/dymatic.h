#pragma once


// dymatic 对话框

class dymatic : public CDialog
{
	DECLARE_DYNAMIC(dymatic)

public:
	dymatic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~dymatic();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
