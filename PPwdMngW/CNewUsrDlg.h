#pragma once
#include "afxdialogex.h"


// CNewUsrDlg 对话框

class CNewUsrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewUsrDlg)

public:
	CNewUsrDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNewUsrDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NEWUSR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonNewkey();

	CString m_cstrKeyFullName;
	CString m_cstrAccFileName;
	afx_msg void OnBnClickedButtonNewaccfile();
	CString m_cstrNewUsr;
	CString m_cstrPwd1;
	CString m_cstrPwd2;
	afx_msg void OnBnClickedButtonNsconfirm();
	afx_msg void OnBnClickedButtonNscancel();
};
