// DialogFireBat.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FireBat.h"
#include "DialogFireBat.h"


// CDialogFireBat ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogFireBat, CDialog)

CDialogFireBat::CDialogFireBat(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFireBat::IDD, pParent)
	, m_hIDSThread(NULL)
	, m_strDisplay(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDialogFireBat::~CDialogFireBat()
{
}

void CDialogFireBat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SHOW_RESULT, m_strDisplay);
}


BEGIN_MESSAGE_MAP(CDialogFireBat, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDialogFireBat::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SETTING_RULES, &CDialogFireBat::OnBnClickedButtonSettingRules)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE_START, &CDialogFireBat::OnBnClickedButtonCaptureStart)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE_STOP, &CDialogFireBat::OnBnClickedButtonCaptureStop)
	ON_BN_CLICKED(IDC_BUTTON_LOG_SETTING, &CDialogFireBat::OnBnClickedButtonLogSetting)
	ON_MESSAGE(UM_UPDATEDATA, &CDialogFireBat::OnUpdateDataFalse)
END_MESSAGE_MAP()


// CDialogFireBat �޽��� ó�����Դϴ�.

BOOL CDialogFireBat::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.	
}

void CDialogFireBat::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}



void CDialogFireBat::OnBnClickedButtonCaptureStart()
{
	if(m_hIDSThread)
	{
		CDialogYesNoBox Dlgyesnobox;
		INT Result = Dlgyesnobox.DoModal();
		return;
	}

	m_hIDSThread = AfxBeginThread((AFX_THREADPROC)TestThreadFunc, this);

	if(!m_hIDSThread)
	{
		AfxMessageBox(_T("�����带 �ʱ�ȭ�� �� �����ϴ�."));
		return;
	}

	m_hIDSThread->m_bAutoDelete = FALSE;
		
}

void CDialogFireBat::OnBnClickedButtonCaptureStop()
{

}

void CDialogFireBat::OnBnClickedButtonSettingRules()
{
	CDialogSetRule Dlg;
	INT nDlgResult = Dlg.DoModal();

	if(nDlgResult == IDOK)
	{
		
	}
}

void CDialogFireBat::OnBnClickedButtonLogSetting()
{
	
}

void CDialogFireBat::OnBnClickedButtonClear()
{

}

LRESULT CDialogFireBat::OnUpdateDataFalse(WPARAM wParam, LPARAM lParam)
{
	UpdateData(FALSE);
	return 0;
}

LRESULT CDialogFireBat::TestThreadFunc(LPVOID pArg)
{
	return 0xDEADBEEF;
}