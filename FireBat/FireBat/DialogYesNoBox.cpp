// DialogYesNoBox.cpp : ���� �����Դϴ�.
// TODO

#include "stdafx.h"
#include "FireBat.h"
#include "DialogYesNoBox.h"


// CDialogYesNoBox ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogYesNoBox, CDialog)

CDialogYesNoBox::CDialogYesNoBox(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogYesNoBox::IDD, pParent)
{

}

CDialogYesNoBox::~CDialogYesNoBox()
{
}

void CDialogYesNoBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogYesNoBox, CDialog)
END_MESSAGE_MAP()


// CDialogYesNoBox �޽��� ó�����Դϴ�.
