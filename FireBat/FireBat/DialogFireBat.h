#pragma once
#include "DialogSetRule.h"

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
	HICON m_hIcon;
	HMODULE m_hNIDS;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	// ��Ŷ �м� ����� ����ϴ� Edit ��Ʈ�� ���ڿ� ����
	CString m_cstrAnalysisResult;
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSettingRules();
	afx_msg void OnBnClickedButtonTestLoad();
	afx_msg void OnBnClickedButtonTestFree();
};
