﻿// DialogFireBat.cpp: 구현 파일
//

#include "stdafx.h"
#include "FireBat.h"
#include "afxdialogex.h"
#include "DialogFireBat.h"


// CDialogFireBat 대화 상자

IMPLEMENT_DYNAMIC(CDialogFireBat, CDialog)

CDialogFireBat::CDialogFireBat(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_FIREBAT, pParent)
	, m_hPcap(NULL)
	, m_pThread(NULL)
	, m_lpszErrbuf("")
	, m_CS()
	, m_ThreadStatus(THREAD_STOP)
	, m_index(0)
{
}

CDialogFireBat::~CDialogFireBat()
{
}

void CDialogFireBat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOGTEXT, m_ctrlListLogText);
	DDX_Control(pDX, IDC_STATE, m_ctrlStaticStateText);
}


BEGIN_MESSAGE_MAP(CDialogFireBat, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDialogFireBat::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDialogFireBat::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CDialogFireBat::OnBnClickedButtonPause)
END_MESSAGE_MAP()


// CDialogFireBat 메시지 처리기

BOOL CDialogFireBat::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlListLogText.InsertColumn(0, _T("순서"), LVCFMT_LEFT, 40);
	m_ctrlListLogText.InsertColumn(1, _T("프로토콜"), LVCFMT_LEFT, 80);
	m_ctrlListLogText.InsertColumn(2, _T("출발지"), LVCFMT_LEFT, 120);
	m_ctrlListLogText.InsertColumn(3, _T("도착지"), LVCFMT_LEFT, 120);
	m_ctrlListLogText.InsertColumn(4, _T("정보"), LVCFMT_LEFT, 380);

	m_ctrlStaticStateText.SetWindowText(_T("상태: 중지"));
	return TRUE;
}

void CDialogFireBat::OnBnClickedButtonStart()
{
	if (m_pThread)
	{
		AfxMessageBox(_T("FireBatNIDS 이(가) 실행 중입니다."));
		return;
	}

	m_DlgDevSel = new CDialogDeviceSelect;
	m_DlgRuleSet = new CDialogRuleSet;
	m_DlgPcapFile = new CFileDialog(false, _T("pcap"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("Pcap Files(*.pcap)|*.pcap|All Files(*.*)|*.*||"), NULL);

	if (m_DlgDevSel->DoModal() == IDCANCEL)
		return;

	if (m_DlgRuleSet->DoModal() == IDCANCEL)
		return;

	if (m_DlgPcapFile->DoModal() == IDCANCEL)
		return;
	strSavePath = m_DlgPcapFile->GetPathName();

	m_ctrlListLogText.DeleteAllItems();
	m_index = 0;

	m_ThreadStatus = THREAD_RUNNING;
	m_pThread = AfxBeginThread(CaptureThreadFunc, (LPVOID)this);
	if (m_pThread == NULL)
	{
		AfxMessageBox(_T("시작하지 못했습니다."));
		m_ThreadStatus = THREAD_STOP;
		m_ctrlStaticStateText.SetWindowText(_T("상태: 중지"));
		return;
	}

	m_ctrlStaticStateText.SetWindowText(_T("상태: 동작중."));
}

UINT CDialogFireBat::CaptureThreadFunc(LPVOID lpParam)
{
	CDialogFireBat* PThis = (CDialogFireBat*)lpParam;
	bool bIsError = false;

	PThis->m_CS.Lock();

	if (!bIsError && ((PThis->m_hPcap = pcap_open_live((CStringA)PThis->m_DlgDevSel->m_strDeviceID, 65536, 1, 1000, PThis->m_lpszErrbuf)) == NULL))
	{
		AfxMessageBox(_T("디바이스를 열 수 없습니다."));
		bIsError = true;
	}

	if (!bIsError && (pcap_compile(PThis->m_hPcap, &PThis->m_fcode, (CStringA)PThis->m_DlgRuleSet->m_strFilterRule, 1, PCAP_NETMASK_UNKNOWN) < 0))
	{
		AfxMessageBox(_T("규칙을 설정하는 과정에서 오류가 발생했습니다."));
		bIsError = true;
	}

	if (!bIsError && (pcap_setfilter(PThis->m_hPcap, &PThis->m_fcode) < 0))
	{
		AfxMessageBox(_T("규칙을 적용하는 과정에서 오류가 발생했습니다."));
		bIsError = true;
	}

	if (!bIsError && ((PThis->m_dumpfile = pcap_dump_open(PThis->m_hPcap, (CStringA)PThis->strSavePath)) == NULL))
	{
		AfxMessageBox(_T("저장 경로를 열 수 없습니다."));
		bIsError = true;
	}

	if (bIsError)
	{
		PThis->m_ThreadStatus = THREAD_STOP;
		PThis->m_pThread = NULL;
		PThis->m_CS.Unlock();
		delete PThis->m_DlgDevSel;
		delete PThis->m_DlgRuleSet;
		delete PThis->m_DlgPcapFile;
		return -1;
	}

	pcap_loop(PThis->m_hPcap, 0, packet_handler, (u_char*)PThis);

	pcap_close(PThis->m_hPcap);
	pcap_freecode(&PThis->m_fcode);
	PThis->m_pThread = NULL;

	PThis->m_CS.Unlock();
	delete PThis->m_DlgDevSel;
	delete PThis->m_DlgRuleSet;
	delete PThis->m_DlgPcapFile;
	return 0;
}

void CDialogFireBat::packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
	CDialogFireBat* TThis = (CDialogFireBat*)param;
	pcap_dump((u_char*)TThis->m_dumpfile, header, pkt_data);

	CString strResult, strIndex, strSrc, strDst, strInfo;
	strIndex.Format(_T("%u"), TThis->m_index + 1);

	hdr_t pkth = PacketAnalyzing(pkt_data);
	
	TThis->m_ctrlListLogText.InsertItem(TThis->m_index, strIndex);

	switch(pkth.type)
	{
		case ARP:
			TThis->m_ctrlListLogText.SetItem(TThis->m_index, 1, LVIF_TEXT, _T("ARP"), NULL, NULL, NULL, NULL);
			break;

		case IPV4_TCP:
		case IPV6_TCP:
			TThis->m_ctrlListLogText.SetItem(TThis->m_index, 1, LVIF_TEXT, _T("TCP"), NULL, NULL, NULL, NULL);
			break;

		case IPV4_UDP:
		case IPV6_UDP:
			TThis->m_ctrlListLogText.SetItem(TThis->m_index, 1, LVIF_TEXT, _T("UDP"), NULL, NULL, NULL, NULL);
			break;

		case IPV4_TCP_ICMP:
			TThis->m_ctrlListLogText.SetItem(TThis->m_index, 1, LVIF_TEXT, _T("ICMP"), NULL, NULL, NULL, NULL);
			break;

		case IPV6_TCP_ICMP:
			TThis->m_ctrlListLogText.SetItem(TThis->m_index, 1, LVIF_TEXT, _T("ICMPv6"), NULL, NULL, NULL, NULL);
			break;
	}

	switch(pkth.type)
	{
	case ARP:
		strSrc.Format(_T("%02X:%02X:%02X:%02X:%02X:%02X"),
			pkth.eth->eth_src_mac[0],
			pkth.eth->eth_src_mac[1],
			pkth.eth->eth_src_mac[2],
			pkth.eth->eth_src_mac[3],
			pkth.eth->eth_src_mac[4],
			pkth.eth->eth_src_mac[5]);

		strDst.Format(_T("%02X:%02X:%02X:%02X:%02X:%02X"),
			pkth.eth->eth_dst_mac[0],
			pkth.eth->eth_dst_mac[1],
			pkth.eth->eth_dst_mac[2],
			pkth.eth->eth_dst_mac[3],
			pkth.eth->eth_dst_mac[4],
			pkth.eth->eth_dst_mac[5]);

		TThis->m_ctrlListLogText.SetItem(TThis->m_index, 2, LVIF_TEXT, strSrc, NULL, NULL, NULL, NULL);
		TThis->m_ctrlListLogText.SetItem(TThis->m_index, 3, LVIF_TEXT, strDst, NULL, NULL, NULL, NULL);
		break;

	case IPV4_TCP:
	case IPV4_UDP:
	case IPV4_TCP_ICMP:
		strSrc.Format(_T("%0d.%0d.%0d.%0d"),
			pkth.ip4h->ip4_src_ip[0],
			pkth.ip4h->ip4_src_ip[1],
			pkth.ip4h->ip4_src_ip[2],
			pkth.ip4h->ip4_src_ip[3]);

		strDst.Format(_T("%0d.%0d.%0d.%0d"),
			pkth.ip4h->ip4_dst_ip[0],
			pkth.ip4h->ip4_dst_ip[1],
			pkth.ip4h->ip4_dst_ip[2],
			pkth.ip4h->ip4_dst_ip[3]);

		TThis->m_ctrlListLogText.SetItem(TThis->m_index, 2, LVIF_TEXT, strSrc, NULL, NULL, NULL, NULL);
		TThis->m_ctrlListLogText.SetItem(TThis->m_index, 3, LVIF_TEXT, strDst, NULL, NULL, NULL, NULL);
		break;

	case IPV6_TCP:
	case IPV6_UDP:
	case IPV6_TCP_ICMP:
		strSrc.Format(_T("%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x"),
			ntohs(pkth.ip6h->ip6_src_ip[0]),
			ntohs(pkth.ip6h->ip6_src_ip[1]),
			ntohs(pkth.ip6h->ip6_src_ip[2]),
			ntohs(pkth.ip6h->ip6_src_ip[3]),
			ntohs(pkth.ip6h->ip6_src_ip[4]),
			ntohs(pkth.ip6h->ip6_src_ip[5]),
			ntohs(pkth.ip6h->ip6_src_ip[6]),
			ntohs(pkth.ip6h->ip6_src_ip[7]));

		strDst.Format(_T("%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x"),
			ntohs(pkth.ip6h->ip6_dst_ip[0]),
			ntohs(pkth.ip6h->ip6_dst_ip[1]),
			ntohs(pkth.ip6h->ip6_dst_ip[2]),
			ntohs(pkth.ip6h->ip6_dst_ip[3]),
			ntohs(pkth.ip6h->ip6_dst_ip[4]),
			ntohs(pkth.ip6h->ip6_dst_ip[5]),
			ntohs(pkth.ip6h->ip6_dst_ip[6]),
			ntohs(pkth.ip6h->ip6_dst_ip[7]));

		TThis->m_ctrlListLogText.SetItem(TThis->m_index, 2, LVIF_TEXT, strSrc, NULL, NULL, NULL, NULL);
		TThis->m_ctrlListLogText.SetItem(TThis->m_index, 3, LVIF_TEXT, strDst, NULL, NULL, NULL, NULL);
		break;
	}

	switch (pkth.type) // TODO: 정보 출력
	{
	case ARP:

		break;
	case IPV4_TCP:

		break;
	case IPV4_UDP:

		break;
	case IPV4_TCP_ICMP:

		break;
	case IPV6_TCP:

		break;
	case IPV6_UDP:

		break;
	case IPV6_TCP_ICMP:

		break;
	}

	TThis->m_index++;

	while (TThis->m_ThreadStatus == THREAD_PAUSE);
}

void CDialogFireBat::OnBnClickedButtonStop()
{
	if (m_ThreadStatus == THREAD_STOP)
		return;

	m_ThreadStatus = THREAD_STOP;
	m_ctrlStaticStateText.SetWindowText(_T("상태: 중지"));
	pcap_breakloop(m_hPcap);
}

void CDialogFireBat::OnBnClickedButtonPause()
{
	if (m_ThreadStatus == THREAD_PAUSE)
	{
		m_ThreadStatus = THREAD_RUNNING;
		m_ctrlStaticStateText.SetWindowText(_T("상태: 동작중."));
		return;
	}

	if (m_ThreadStatus == THREAD_RUNNING)
	{
		m_ThreadStatus = THREAD_PAUSE;
		m_ctrlStaticStateText.SetWindowText(_T("상태: 일시정지"));
		return;
	}
}