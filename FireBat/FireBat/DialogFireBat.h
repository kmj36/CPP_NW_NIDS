#pragma once


// CDialogFireBat ��ȭ �����Դϴ�.

class CDialogFireBat : public CDialog
{
	DECLARE_DYNAMIC(CDialogFireBat)

public:
	CDialogFireBat(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogFireBat();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_FIREBAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
