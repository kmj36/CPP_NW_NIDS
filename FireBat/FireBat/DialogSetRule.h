#pragma once


// CDialogSetRule ��ȭ �����Դϴ�.

class CDialogSetRule : public CDialog
{
	DECLARE_DYNAMIC(CDialogSetRule)

public:
	CDialogSetRule(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogSetRule();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_SET_RULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
