#pragma once


// dymatic �Ի���

class dymatic : public CDialog
{
	DECLARE_DYNAMIC(dymatic)

public:
	dymatic(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~dymatic();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
