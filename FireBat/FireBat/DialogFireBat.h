#pragma once
#include "DialogSetRule.h"
#include "DialogYesNoBox.h"
#include "FireBatNIDS.h"
#include "afxwin.h"
#define UM_UPDATEDATA (WM_USER+1)

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
	CWinThread* m_hIDSThread;
	enum ThreadStatus
	{
		RUNNING = 0,
		PAUSE = 1,
		STOP = 2
	};
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ȭ�鿡 ���� ĸó ��Ȳ�� �����ִ� ���ڿ�
	CString m_strDisplay;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	// ��Ŷ �м� ����� ����ϴ� Edit ��Ʈ�� ���ڿ� ����
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSettingRules();
	afx_msg void OnBnClickedButtonCaptureStart();
	afx_msg void OnBnClickedButtonCaptureStop();
	afx_msg void OnBnClickedButtonLogSetting();
	afx_msg LRESULT OnUpdateDataFalse(WPARAM wParam, LPARAM lParam);
	static LRESULT TestThreadFunc(LPVOID pArg);
};
