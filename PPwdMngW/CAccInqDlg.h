#pragma once
#include "afxdialogex.h"


// CAccInqDlg 对话框

class CAccInqDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccInqDlg)

public:
	CAccInqDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAccInqDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INQ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_cstrAccInqTypes;
	CString m_cstrAccInqNames;
	CString m_cstrAccInqNums;
	CString m_cstrAccInqPwd;
	CString m_cstrAccInqMemo;
	CString m_cstrAccInqUrls;
	CString m_cstrAccInqNo;
	
	afx_msg void OnBnClickedButtonUpdconfirm();
	afx_msg void OnBnClickedButtonDelconfirm();
	afx_msg void OnBnClickedButtonInqcancel();
	afx_msg void OnEnChangeEditInqaccpwd();
};
