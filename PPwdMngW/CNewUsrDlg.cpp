// CNewUsrDlg.cpp: 实现文件
//

#include "pch.h"
#include "PPwdMngW.h"
#include "afxdialogex.h"
#include "CNewUsrDlg.h"
#include "cCommon.h"
#include "cApi.h"

// CNewUsrDlg 对话框

IMPLEMENT_DYNAMIC(CNewUsrDlg, CDialogEx)

CNewUsrDlg::CNewUsrDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NEWUSR, pParent)
	, m_cstrKeyFullName(_T(""))
	, m_cstrAccFileName(_T(""))
	, m_cstrNewUsr(_T(""))
	, m_cstrPwd1(_T(""))
	, m_cstrPwd2(_T(""))
{

}

CNewUsrDlg::~CNewUsrDlg()
{
}

void CNewUsrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEWKEY, m_cstrKeyFullName);
	DDX_Text(pDX, IDC_EDIT_NEWACC, m_cstrAccFileName);
	DDX_Text(pDX, IDC_EDIT_NEWUSR, m_cstrNewUsr);
	DDX_Text(pDX, IDC_EDIT_PWD1, m_cstrPwd1);
	DDX_Text(pDX, IDC_EDIT_PWD2, m_cstrPwd2);
}


BEGIN_MESSAGE_MAP(CNewUsrDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_NEWKEY, &CNewUsrDlg::OnBnClickedButtonNewkey)
	ON_BN_CLICKED(IDC_BUTTON_NEWACCFILE, &CNewUsrDlg::OnBnClickedButtonNewaccfile)
	ON_BN_CLICKED(IDC_BUTTON_NSCONFIRM, &CNewUsrDlg::OnBnClickedButtonNsconfirm)
	ON_BN_CLICKED(IDC_BUTTON_NSCANCEL, &CNewUsrDlg::OnBnClickedButtonNscancel)
END_MESSAGE_MAP()


// CNewUsrDlg 消息处理程序


void CNewUsrDlg::OnBnClickedButtonNewkey()
{
	CFileDialog cdlgFile(FALSE, _T("txt"), _T("新建文件.txt"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files(*.*)|*.*||"), AfxGetMainWnd());

	if (cdlgFile.DoModal() == IDOK)
	{
		m_cstrKeyFullName = cdlgFile.GetPathName();
		SetDlgItemTextA(IDC_EDIT_NEWKEY, m_cstrKeyFullName);
		//SetDlgItemTextA(IDC_EDIT_KEYFILE, "hello world"); 

		//UpdateData(TRUE);
	}
	// TODO: 在此添加控件通知处理程序代码
}





void CNewUsrDlg::OnBnClickedButtonNewaccfile()
{
	CFileDialog cdlgFile(FALSE, _T("txt"), _T("新建文件.txt"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files(*.*)|*.*||"), AfxGetMainWnd());

	if (cdlgFile.DoModal() == IDOK)
	{
		m_cstrAccFileName = cdlgFile.GetPathName();
		SetDlgItemTextA(IDC_EDIT_NEWACC, m_cstrAccFileName);
		

		//UpdateData(TRUE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CNewUsrDlg::OnBnClickedButtonNsconfirm()
{
	unsigned char caKey[USRPWD_LEN] = { 0 };
	struct UsrFHead stUsrFHead;

	memset(&stUsrFHead, 0x00, sizeof(struct UsrFHead));

	UpdateData(TRUE);

	if (m_cstrNewUsr.GetLength() == 0 ||
		m_cstrPwd1.GetLength() == 0 || m_cstrPwd2.GetLength() == 0 ||
		m_cstrKeyFullName.GetLength() == 0 ||
		m_cstrAccFileName.GetLength() == 0)
	{
		AfxMessageBox("输入项不能为空，请重新输入！");
		return;
	}

	if (m_cstrNewUsr.GetLength() > USRNAME_LEN - 1)
	{
		AfxMessageBox("用户名过长，请重新输入！");
		return;
	}

	if (m_cstrPwd1.GetLength() != USRPWD_LEN)
	{
		AfxMessageBox("用户密码长度错误，请重新输入！");
		return;
	}

	if (m_cstrPwd1 != m_cstrPwd2)
	{
		AfxMessageBox("两次输入密码不一致，请重新输入！");
		return;
	}

	if (GenKey((char*)m_cstrKeyFullName.GetString(), caKey) != 0)
	{
		AfxMessageBox("生成密钥错误！请检查密钥文件名设置是否合适!");
		return;
	}

	unsigned char caUsrPwd[USRPWD_LEN];
	BlockEncrypt(caKey, (unsigned char*)m_cstrPwd1.GetString(),
		caUsrPwd, USRPWD_LEN);
	memcpy(stUsrFHead.strUsrName, m_cstrNewUsr.GetString(), m_cstrNewUsr.GetLength());
	memcpy(stUsrFHead.strPassword,caUsrPwd, USRPWD_LEN);
	stUsrFHead.iTotal = 0;
	if (AccFileWrite((char *)m_cstrAccFileName.GetString(), &stUsrFHead, NULL) != 0)
	{
		AfxMessageBox("个人账户文件生成失败，请检查文件所在文件夹及文件名是否正确!");
		return;
	}

	AfxMessageBox("密钥文件及个人账户文件生成成功，并返回!");
	EndDialog(IDOK);


}


void CNewUsrDlg::OnBnClickedButtonNscancel()
{
	EndDialog(IDCANCEL);
	// TODO: 在此添加控件通知处理程序代码
}
