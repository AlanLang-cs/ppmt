// CAccRecsDlg.cpp: 实现文件
//

#include "pch.h"
#include "PPwdMngW.h"
#include "afxdialogex.h"
#include "CAccRecsDlg.h"
#include "cCommon.h"
#include "cApi.h"
#include "CAddAccRecDlg.h"
#include "CAccInqDlg.h"


// CAccRecsDlg 对话框

IMPLEMENT_DYNAMIC(CAccRecsDlg, CDialogEx)

CAccRecsDlg::CAccRecsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ACCRECS, pParent)
{
	m_pstAccHeadM = NULL;
	m_pstUsrFHead = NULL;
	m_pcaKey = NULL;
}

CAccRecsDlg::~CAccRecsDlg()
{
}

BOOL CAccRecsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listAccRecs.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_listAccRecs.SetView(LVS_REPORT);
	m_listAccRecs.InsertColumn(0, _T("账户类别"),LVCFMT_LEFT, 100);
	m_listAccRecs.InsertColumn(1, _T("记录号"), LVCFMT_LEFT, 100);
	m_listAccRecs.InsertColumn(2, _T("账户名称"), LVCFMT_LEFT, 200);
	m_listAccRecs.InsertColumn(3, _T("账号"), LVCFMT_LEFT, 200);
	m_listAccRecs.InsertColumn(4, _T("账户备注"), LVCFMT_LEFT, 200);
	m_listAccRecs.InsertColumn(5, _T("账户网址/APP"), LVCFMT_LEFT, 200);

	ShowList();
	/*
	int iRow = m_listAccRecs.InsertItem(0, _T("银行卡"));
	m_listAccRecs.SetItemText(iRow, 1, _T("001"));
	m_listAccRecs.SetItemText(iRow, 2, _T("aaa"));
	m_listAccRecs.SetItemText(iRow, 3, _T("bbb"));
	m_listAccRecs.SetItemText(iRow, 4, _T("ccc"));
	m_listAccRecs.SetItemText(iRow, 5, _T("ddd"));
	*/
	
	
	return TRUE;
}

void CAccRecsDlg::ShowList()
{
	struct AccInfRecM* pstTemp = NULL;
	int i = 0;
	int iRow = 0;
	char caAccNo[10] = {0};

	m_listAccRecs.DeleteAllItems();

	for (i = 0; i < ACC_MAX; i++)
	{
		pstTemp = m_pstAccHeadM[i].pstAccInfRecM;
		
		if (pstTemp == NULL)
		{
			continue;
		}
		while (pstTemp != NULL)
		{
			iRow = m_listAccRecs.InsertItem(0, _T(m_pstAccHeadM[i].strAccTypeName));
			sprintf_s(caAccNo, 10, "%03d", pstTemp->stAccInfRec.iAccNo);
			m_listAccRecs.SetItemText(iRow, 1, _T(caAccNo));
			m_listAccRecs.SetItemText(iRow, 2, _T(pstTemp->stAccInfRec.strAccName));
			m_listAccRecs.SetItemText(iRow, 3, _T(pstTemp->stAccInfRec.strAccNumber));
			m_listAccRecs.SetItemText(iRow, 4, _T(pstTemp->stAccInfRec.strAccMemo));
			m_listAccRecs.SetItemText(iRow, 5, _T(pstTemp->stAccInfRec.strAccURL));
			pstTemp = pstTemp->pstNext;
		}
		
	}
	return;
}

void CAccRecsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ACCRECS, m_listAccRecs);
}


BEGIN_MESSAGE_MAP(CAccRecsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAccRecsDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_INQUPDDEL, &CAccRecsDlg::OnBnClickedButtonInqupddel)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, &CAccRecsDlg::OnBnClickedButtonReturn)
END_MESSAGE_MAP()





// CAccRecsDlg 消息处理程序


void CAccRecsDlg::OnBnClickedButtonAdd()
{
	CAddAccRecDlg cdlgAddAccRec;
	cdlgAddAccRec.m_pstAccHeadM = m_pstAccHeadM;
	cdlgAddAccRec.m_pstUsrFHead = m_pstUsrFHead;
	cdlgAddAccRec.m_pcaKey = m_pcaKey;


	if (cdlgAddAccRec.DoModal() == IDCANCEL)
	{
		if (AccFileWrite(m_pcaAccFileName, m_pstUsrFHead, m_pstAccHeadM) != 0)
		{
			AfxMessageBox("写入个人账户文件失败!");
			return;
		}
		ShowList();

	}
	return;
	// TODO: 在此添加控件通知处理程序代码
}




void CAccRecsDlg::OnBnClickedButtonInqupddel()
{
	CAccInqDlg cdlgInqAccRec;
	struct AccInfRec stAccInfRec;
	unsigned char caAccPwd[ACCPWD_LEN] = { 0 };

	memset(&stAccInfRec, 0x00, sizeof(stAccInfRec));

	POSITION posCur = m_listAccRecs.GetFirstSelectedItemPosition();
	if (posCur != NULL)
	{
		int iItem = m_listAccRecs.GetNextSelectedItem(posCur);
		cdlgInqAccRec.m_cstrAccInqTypes = m_listAccRecs.GetItemText(iItem, 0);
		cdlgInqAccRec.m_cstrAccInqNo = m_listAccRecs.GetItemText(iItem, 1);
		cdlgInqAccRec.m_cstrAccInqNames = m_listAccRecs.GetItemText(iItem, 2);
		cdlgInqAccRec.m_cstrAccInqNums = m_listAccRecs.GetItemText(iItem, 3);
		cdlgInqAccRec.m_cstrAccInqMemo = m_listAccRecs.GetItemText(iItem, 4);
		cdlgInqAccRec.m_cstrAccInqUrls = m_listAccRecs.GetItemText(iItem, 5);
		
		stAccInfRec.iAccNo = atoi(cdlgInqAccRec.m_cstrAccInqNo.GetBuffer());
		
		if (InqAccRec((char*)cdlgInqAccRec.m_cstrAccInqTypes.GetString(),
			m_pstAccHeadM, &stAccInfRec) != 0)
		{
			AfxMessageBox("查询账户记录失败!");
			return;
		}
		
		BlockDecrypt(m_pcaKey, stAccInfRec.caAccPwd, caAccPwd, ACCPWD_LEN );	//解密
		cdlgInqAccRec.m_cstrAccInqPwd.SetString((char *)caAccPwd, ACCPWD_LEN);
	}
	else
	{
		AfxMessageBox("未选择账户记录，请重新选择!");
		return;
	}

	INT_PTR iRtnCode = cdlgInqAccRec.DoModal();
	switch (iRtnCode)
	{
	case IDUPD:
		memset(caAccPwd, 0x00, sizeof(caAccPwd));
		//memcpy(caAccPwd, cdlgInqAccRec.m_cstrAccInqPwd.GetString(),
		//	cdlgInqAccRec.m_cstrAccInqPwd.GetLength());w
		BlockEncrypt(m_pcaKey, (unsigned char*)cdlgInqAccRec.m_cstrAccInqPwd.GetString(),
			caAccPwd, ACCPWD_LEN);		//加密
		memcpy(stAccInfRec.caAccPwd, caAccPwd, ACCPWD_LEN);	
		strcpy_s(stAccInfRec.strAccMemo, cdlgInqAccRec.m_cstrAccInqMemo.GetString()); 
		if (UpdAccRec((char*)cdlgInqAccRec.m_cstrAccInqTypes.GetString(),
			m_pstAccHeadM, &stAccInfRec) != 0)
		{
			AfxMessageBox("账户记录修改失败!");
			return;
		}
		break;
	case IDDEL:
		if (DelAccRec((char*)cdlgInqAccRec.m_cstrAccInqTypes.GetString(),
			m_pstAccHeadM, &stAccInfRec) != 0)
		{
			AfxMessageBox("账户记录删除失败!");
			return;
		}
		break;
	case IDCANCEL:
		return;
	}

	if (AccFileWrite(m_pcaAccFileName, m_pstUsrFHead, m_pstAccHeadM) != 0)
	{
		AfxMessageBox("写入个人账户文件失败!");
		return;
	}
	ShowList();
	return;
}


void CAccRecsDlg::OnBnClickedButtonReturn()
{
	EndDialog(IDCANCEL);
}
