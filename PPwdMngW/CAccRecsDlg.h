#pragma once
#include "afxdialogex.h"


// CAccRecsDlg 对话框

class CAccRecsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccRecsDlg)

public:
	CAccRecsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAccRecsDlg();
	virtual BOOL OnInitDialog();
	virtual void ShowList();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ACCRECS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	struct AccHeadM* m_pstAccHeadM;
	struct UsrFHead* m_pstUsrFHead;
	unsigned char* m_pcaKey;
	char* m_pcaAccFileName;
	
	CListCtrl m_listAccRecs;
	afx_msg void OnBnClickedButtonInqupddel();
	afx_msg void OnBnClickedButtonReturn();
};
