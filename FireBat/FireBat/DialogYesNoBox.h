#pragma once


// CDialogYesNoBox ��ȭ �����Դϴ�.

class CDialogYesNoBox : public CDialog
{
	DECLARE_DYNAMIC(CDialogYesNoBox)

public:
	CDialogYesNoBox(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogYesNoBox();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_YESNOBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
