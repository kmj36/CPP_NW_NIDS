// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� _EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// NIDS_API �Լ��� DLL���� �������� ������ ����, �� DLL��
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
#include "FireBatIDS.h"

#ifdef NIDS_EXPORTS
#define NIDS_API __declspec(dllexport)
#else
#define NIDS_API __declspec(dllimport)
#endif

/* ����
// �� Ŭ������ NIDS.dll���� ������ ���Դϴ�.
class NIDS_API CNIDS {
public:
	CNIDS(void);
	// TODO: ���⿡ �޼��带 �߰��մϴ�.
};

extern NIDS_API int nNIDS;

NIDS_API int fnNIDS(void);
*/

extern NIDS_API CFireBatIDS test;