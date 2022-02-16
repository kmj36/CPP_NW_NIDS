// DialogFireBat.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FireBat.h"
#include "DialogFireBat.h"


// CDialogFireBat ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogFireBat, CDialog)

CDialogFireBat::CDialogFireBat(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFireBat::IDD, pParent)
	, m_cstrAnalysisResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDialogFireBat::~CDialogFireBat()
{
}

void CDialogFireBat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SHOW_RESULT, m_cstrAnalysisResult);
}


BEGIN_MESSAGE_MAP(CDialogFireBat, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDialogFireBat::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SETTING_RULES, &CDialogFireBat::OnBnClickedButtonSettingRules)
	ON_BN_CLICKED(IDC_BUTTON_TEST_LOAD, &CDialogFireBat::OnBnClickedButtonTestLoad)
	ON_BN_CLICKED(IDC_BUTTON_TEST_FREE, &CDialogFireBat::OnBnClickedButtonTestFree)
END_MESSAGE_MAP()


// CDialogFireBat �޽��� ó�����Դϴ�.

BOOL CDialogFireBat::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_cstrAnalysisResult += _T("�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ�׽�Ʈ");
	

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
void CDialogFireBat::OnBnClickedButtonClear()
{
	m_cstrAnalysisResult.Empty();
	UpdateData(FALSE);
}

void CDialogFireBat::OnBnClickedButtonSettingRules()
{
	CDialogSetRule Dlg;
	INT nDlgResult = Dlg.DoModal();

	if(nDlgResult == IDOK)
	{
		
	}
}

void CDialogFireBat::OnBnClickedButtonTestLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_hNIDS = LoadLibrary(_T("NIDS.dll"));
}

void CDialogFireBat::OnBnClickedButtonTestFree()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	FreeLibrary(m_hNIDS);
}
