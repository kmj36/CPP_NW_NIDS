// NIDS.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "FireBatNIDSAPI.h"

/* ����
// ������ ������ �����Դϴ�.
NIDS_API int nNIDS=0;

// ������ �Լ��� �����Դϴ�.
NIDS_API int fnNIDS(void)
{
	return 42;
}

// ������ Ŭ������ �������Դϴ�.
// Ŭ���� ���Ǹ� ������ NIDS.h�� �����Ͻʽÿ�.
CNIDS::CNIDS()
{
	return;
}
*/

CFireBatIDS::CFireBatIDS() :
	m_pAlldev(NULL)
	,m_pDevice(NULL)
	,m_hPcapHandle(NULL)
{
	::ZeroMemory(m_pszErrbuf, sizeof(char) * PCAP_ERRBUF_SIZE);
}

CFireBatIDS::~CFireBatIDS()
{
}

int CFireBatIDS::FBinit()
{
	if(pcap_findalldevs(&m_pAlldev, errbuf) == -1)

}

int CFireBatIDS::FBclose()
{

}