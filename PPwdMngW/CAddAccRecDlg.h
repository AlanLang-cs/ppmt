#pragma once
#include "afxdialogex.h"


// CAddAccRecDlg 对话框

class CAddAccRecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddAccRecDlg)

public:
	CAddAccRecDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddAccRecDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_comboAccType;
public:
	CString m_cstrAccName;
	CString m_cstrAccNo;
	CString m_cstrAccPwd;
	CString m_cstrAccMemo;
	CString m_cstrAccUrl;
	struct AccHeadM* m_pstAccHeadM;
	struct UsrFHead* m_pstUsrFHead;
	unsigned char* m_pcaKey;
	afx_msg void OnBnClickedButtonAddconfirm();
	afx_msg void OnBnClickedButtonAddcancel();
	afx_msg void OnCbnSelchangeComboAddacctype();
	afx_msg void OnEnChangeEditAddaccname();
};
