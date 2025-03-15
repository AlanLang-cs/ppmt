
// PPwdMngWDlg.h: 头文件
//
#include "cCommon.h"

#pragma once


// CPPwdMngWDlg 对话框
class CPPwdMngWDlg : public CDialogEx
{
// 构造
public:
	CPPwdMngWDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PPWDMNGW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonNewusr();
	CString m_cstrUsrName;
	CString m_cstrUsrPwd;
	CString m_cstrKeyFile;
	CString m_cstrAccFile;
	int m_iErrTimes;
	unsigned char m_caKey[USRPWD_LEN];
	afx_msg void OnBnClickedButtonBrskeyfile();
	afx_msg void OnBnClickedButtonBsraccfile();
	afx_msg void OnBnClickedButtonConfirm();
	afx_msg void OnBnClickedButtonCancel();

};
