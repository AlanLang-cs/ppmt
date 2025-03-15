// CAccInqDlg.cpp: 实现文件
//

#include "pch.h"
#include "PPwdMngW.h"
#include "afxdialogex.h"
#include "CAccInqDlg.h"
#include "cCommon.h"

// CAccInqDlg 对话框

IMPLEMENT_DYNAMIC(CAccInqDlg, CDialogEx)

CAccInqDlg::CAccInqDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INQ, pParent)
	, m_cstrAccInqTypes(_T(""))
	, m_cstrAccInqNames(_T(""))
	, m_cstrAccInqNums(_T(""))
	, m_cstrAccInqPwd(_T(""))
	, m_cstrAccInqMemo(_T(""))
	, m_cstrAccInqUrls(_T(""))
{

}

CAccInqDlg::~CAccInqDlg()
{
}

void CAccInqDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_INQACCTYPES, m_cstrAccInqTypes);
	DDX_Text(pDX, IDC_STATIC_INQACCNAMES, m_cstrAccInqNames);
	DDX_Text(pDX, IDC_STATIC_INQACCNUMS, m_cstrAccInqNums);
	DDX_Text(pDX, IDC_EDIT_INQACCPWD, m_cstrAccInqPwd);
	DDX_Text(pDX, IDC_EDIT_INQACCMEMO, m_cstrAccInqMemo);
	DDX_Text(pDX, IDC_STATIC_INQACCURLS, m_cstrAccInqUrls);
}


BEGIN_MESSAGE_MAP(CAccInqDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDCONFIRM, &CAccInqDlg::OnBnClickedButtonUpdconfirm)
	ON_BN_CLICKED(IDC_BUTTON_DELCONFIRM, &CAccInqDlg::OnBnClickedButtonDelconfirm)
	ON_BN_CLICKED(IDC_BUTTON_INQCANCEL, &CAccInqDlg::OnBnClickedButtonInqcancel)
	ON_EN_CHANGE(IDC_EDIT_INQACCPWD, &CAccInqDlg::OnEnChangeEditInqaccpwd)
END_MESSAGE_MAP()





void CAccInqDlg::OnBnClickedButtonUpdconfirm()
{
	UpdateData(TRUE);

	if (m_cstrAccInqPwd.GetLength() > ACCPWD_LEN - 1)
	{
		AfxMessageBox("账户密码长度超限，请重新输入！", MB_OK, 0);
		return;
	}
	if (m_cstrAccInqMemo.GetLength() > ACCMEMO_LEN - 1)
	{
		AfxMessageBox("账户备注长度超限，请重新输入！");
		return;
	}
	EndDialog(IDUPD);
}


void CAccInqDlg::OnBnClickedButtonDelconfirm()
{
	EndDialog(IDDEL);
}


void CAccInqDlg::OnBnClickedButtonInqcancel()
{
	EndDialog(IDCANCEL);
}


void CAccInqDlg::OnEnChangeEditInqaccpwd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
