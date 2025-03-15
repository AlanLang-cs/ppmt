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

//对话框返回值
#define IDUPD 3
#define IDDEL 4
//

// 个人账户数据文件头结构
struct UsrFHead
{
	char strUsrName[USRNAME_LEN];//用户名
	unsigned char strPassword[USRPWD_LEN];//用户密码
	int iTotal;//账户总记录数
	unsigned char caMac[USRPWD_LEN];//文件校验码（8字节）
};

// 个人账户数据文件账户类别记录结构
struct AccHead
{
	char strAccoutType[ACCTYPE_LEN + 1];//账户类别编码
	char strAccTypeName[ACCTYPENAME_LEN];//类别名称
	int iNum;//账户记录数
};

//个人账户数据文件账户信息记录结构
struct AccInfRec
{
	short iAccNo;//账户顺序编码
	char strAccName[ACCNAME_LEN];//账户名称
	char strAccNumber[ACCNUM_LEN];//账号
	unsigned char caAccPwd[ACCPWD_LEN];//账户密码
	char strAccMemo[ACCMEMO_LEN];//账户备注
	char strAccURL[ACCURL_LEN];//网址/APP
};

//内存数据结构--数组
struct AccHeadM
{
	char strAccoutType[ACCTYPE_LEN+1];//账户类别编码
	char strAccTypeName[ACCTYPENAME_LEN];//类别名称
	int iNum;//账户记录数
	struct AccInfRecM *pstAccInfRecM;//账户记录链表头指针
};

//内存数据结构--链表节点
struct AccInfRecM
{
	struct AccInfRec stAccInfRec;//账户信息记录
	struct AccInfRecM *pstNext;//下一个节点指针
};

