//length of array
#define USRNAME_LEN 20
#define USRPWD_LEN 8
#define USR_MAX 10
#define ACC_MAX 20
#define ACCTYPE_LEN 2
#define ACCNAME_LEN 20
#define ACCNUM_LEN 20
#define ACCPWD_LEN 24
#define ACCMEMO_LEN 50
#define ACCURL_LEN 20
#define ACCTYPE_LEN 2
#define ACCTYPENAME_LEN 20

// return code
#define FILE_ERR -1
#define FAIL_ADERR -2
#define FILE_MTCHERR -3
#define FAIL_READERR -4
#define FAIL_DELETEERR -5
#define FAIL_SEARCHERR -6
#define FAIL_UPDERR -7
#define FAIL_ACCTYPEERR -8
// test code 
#define TSTUSR_MAX 1
#define TSTACC_MAX 10

//�Ի��򷵻�ֵ
#define IDUPD 3
#define IDDEL 4
//

// �����˻������ļ�ͷ�ṹ
struct UsrFHead
{
	char strUsrName[USRNAME_LEN];//�û���
	unsigned char strPassword[USRPWD_LEN];//�û�����
	int iTotal;//�˻��ܼ�¼��
	unsigned char caMac[USRPWD_LEN];//�ļ�У���루8�ֽڣ�
};

// �����˻������ļ��˻�����¼�ṹ
struct AccHead
{
	char strAccoutType[ACCTYPE_LEN + 1];//�˻�������
	char strAccTypeName[ACCTYPENAME_LEN];//�������
	int iNum;//�˻���¼��
};

//�����˻������ļ��˻���Ϣ��¼�ṹ
struct AccInfRec
{
	short iAccNo;//�˻�˳�����
	char strAccName[ACCNAME_LEN];//�˻�����
	char strAccNumber[ACCNUM_LEN];//�˺�
	unsigned char caAccPwd[ACCPWD_LEN];//�˻�����
	char strAccMemo[ACCMEMO_LEN];//�˻���ע
	char strAccURL[ACCURL_LEN];//��ַ/APP
};

//�ڴ����ݽṹ--����
struct AccHeadM
{
	char strAccoutType[ACCTYPE_LEN+1];//�˻�������
	char strAccTypeName[ACCTYPENAME_LEN];//�������
	int iNum;//�˻���¼��
	struct AccInfRecM *pstAccInfRecM;//�˻���¼����ͷָ��
};

//�ڴ����ݽṹ--����ڵ�
struct AccInfRecM
{
	struct AccInfRec stAccInfRec;//�˻���Ϣ��¼
	struct AccInfRecM *pstNext;//��һ���ڵ�ָ��
};

