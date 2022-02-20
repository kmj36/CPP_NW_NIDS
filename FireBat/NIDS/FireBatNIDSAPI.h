// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// NIDS_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.

#ifdef NIDS_EXPORTS
#define NIDS_API __declspec(dllexport)
#else
#define NIDS_API __declspec(dllimport)
#endif

class NIDS_API CFireBatIDS {
private:
	pcap_if_t *m_pAlldev;
	pcap_if_t *m_pDevice;
	char m_pszErrbuf[PCAP_ERRBUF_SIZE];
	pcap_t *m_hPcapHandle;
public:
	CFireBatIDS();
	~CFireBatIDS();
public:
	int FBinit();
	int FBclose();
};