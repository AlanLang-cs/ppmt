// CAddAccRecDlg.cpp: 实现文件
//

#include "pch.h"
#include "PPwdMngW.h"
#include "afxdialogex.h"
#include "CAddAccRecDlg.h"
#include "cCommon.h"
#include "cApi.h"


// CAddAccRecDlg 对话框

IMPLEMENT_DYNAMIC(CAddAccRecDlg, CDialogEx)

CAddAccRecDlg::CAddAccRecDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, m_cstrAccName(_T(""))
	, m_cstrAccNo(_T(""))
	, m_cstrAccPwd(_T(""))
	, m_cstrAccMemo(_T(""))
	, m_cstrAccUrl(_T(""))
{
	 m_pstAccHeadM = NULL;
	 m_pstUsrFHead = NULL;
	 m_pcaKey = NULL;
}

CAddAccRecDlg::~CAddAccRecDlg()
{
}

BOOL CAddAccRecDlg::OnInitDialog()
{
	int iL = 0;
	CDialogEx::OnInitDialog();
	
	while (m_pstAccHeadM[iL].strAccoutType[0] != 0 && iL < ACC_MAX)		//修改标记！！！
	{
		m_comboAccType.AddString(_T(m_pstAccHeadM[iL].strAccTypeName));
		iL++;
	}
	m_comboAccType.SetCurSel(0);

	return TRUE;
}

void CAddAccRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ADDACCTYPE, m_comboAccType);
	DDX_Text(pDX, IDC_EDIT_ADDACCNAME, m_cstrAccName);
	DDX_Text(pDX, IDC_EDIT_ADDACCNUM, m_cstrAccNo);
	DDX_Text(pDX, IDC_EDIT_ADDACCPWD, m_cstrAccPwd);
	DDX_Text(pDX, IDC_EDIT_ADDACCMEMO, m_cstrAccMemo);
	DDX_Text(pDX, IDC_EDIT_ADDACCURL, m_cstrAccUrl);
}


BEGIN_MESSAGE_MAP(CAddAccRecDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDCONFIRM, &CAddAccRecDlg::OnBnClickedButtonAddconfirm)
	ON_BN_CLICKED(IDC_BUTTON_ADDCANCEL, &CAddAccRecDlg::OnBnClickedButtonAddcancel)
	ON_CBN_SELCHANGE(IDC_COMBO_ADDACCTYPE, &CAddAccRecDlg::OnCbnSelchangeComboAddacctype)
	ON_EN_CHANGE(IDC_EDIT_ADDACCNAME, &CAddAccRecDlg::OnEnChangeEditAddaccname)
END_MESSAGE_MAP()


// CAddAccRecDlg 消息处理程序


void CAddAccRecDlg::OnBnClickedButtonAddconfirm()
{
	UpdateData(TRUE);

	if (m_cstrAccName.GetLength() == 0 ||
		m_cstrAccNo.GetLength() == 0 ||
		m_cstrAccPwd.GetLength() == 0)
	{
		AfxMessageBox("账户名、账号、账户密码不能为空，请重新输入！");
		return;
	}
	if (m_cstrAccName.GetLength() > ACCNAME_LEN-1)
	{
		AfxMessageBox("账户名长度超限，请重新输入！");
		return;
	}
	if (m_cstrAccNo.GetLength() > ACCNUM_LEN-1)
	{
		AfxMessageBox("账号长度超限，请重新输入！");
		return;
	}
	if (m_cstrAccPwd.GetLength() > ACCPWD_LEN-1)
	{
		AfxMessageBox("账户密码长度超限，请重新输入！");
		return;
	}
	if (m_cstrAccMemo.GetLength() > ACCMEMO_LEN-1)
	{
		AfxMessageBox("账户备注长度超限，请重新输入！");
		return;
	}
	if (m_cstrAccUrl.GetLength() > ACCURL_LEN-1)
	{
		AfxMessageBox("账户网址或APP名称长度超限，请重新输入！");
		return;
	}
	
	unsigned char caAccPwd[ACCPWD_LEN] = { 0 };		//后续加密使用
	BlockEncrypt(m_pcaKey, (unsigned char*)m_cstrAccPwd.GetString(),
		caAccPwd, ACCPWD_LEN);
	int iSel = m_comboAccType.GetCurSel();
	CString cstrAccType;
	m_comboAccType.GetLBText(iSel, cstrAccType);
	struct AccInfRec stAccInfRec;
	memset(&stAccInfRec, 0x00, sizeof(struct AccInfRec));
	memcpy(stAccInfRec.strAccName, m_cstrAccName.GetString(), m_cstrAccName.GetLength());
	memcpy(stAccInfRec.strAccNumber, m_cstrAccNo.GetString(), m_cstrAccNo.GetLength());
	memcpy(stAccInfRec.caAccPwd, caAccPwd, ACCPWD_LEN);
	memcpy(stAccInfRec.strAccMemo, m_cstrAccMemo.GetString(), m_cstrAccMemo.GetLength());
	memcpy(stAccInfRec.strAccURL, m_cstrAccUrl.GetString(), m_cstrAccUrl.GetLength());
	if (AddAccRec((char*)cstrAccType.GetString(), m_pstAccHeadM, &stAccInfRec) == 0)
	{
		AfxMessageBox("添加成功！继续添加下一条记录，或点击保存并返回");
		m_cstrAccName.SetString("");
		m_cstrAccNo.SetString("");
		m_cstrAccPwd.SetString("");
		m_cstrAccMemo.SetString("");
		m_cstrAccUrl.SetString("");
		UpdateData(FALSE);
		return;
	}
	else
	{
		AfxMessageBox("添加失败！");
		return;
	}


}


void CAddAccRecDlg::OnBnClickedButtonAddcancel()
{
	EndDialog(IDCANCEL);
}


void CAddAccRecDlg::OnCbnSelchangeComboAddacctype()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CAddAccRecDlg::OnEnChangeEditAddaccname()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
