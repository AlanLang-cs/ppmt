
// PPwdMngWDlg.cpp: 实现文件
//


#include "pch.h"
#include "framework.h"
#include "PPwdMngW.h"
//#include "cCommon.h"
#include "PPwdMngWDlg.h"
#include "afxdialogex.h"
#include "CNewUsrDlg.h"
#include "cApi.h"
#include "CAccRecsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPPwdMngWDlg 对话框



CPPwdMngWDlg::CPPwdMngWDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PPWDMNGW_DIALOG, pParent)
	, m_cstrUsrName(_T(""))
	, m_cstrUsrPwd(_T(""))
	, m_cstrKeyFile(_T(""))
	, m_cstrAccFile(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iErrTimes = 0;
}

void CPPwdMngWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USRNAME, m_cstrUsrName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_cstrUsrPwd);
	DDX_Text(pDX, IDC_EDIT_KEYFILE, m_cstrKeyFile);
	DDX_Text(pDX, IDC_EDIT_ACCFILE, m_cstrAccFile);
}

BEGIN_MESSAGE_MAP(CPPwdMngWDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEWUSR, &CPPwdMngWDlg::OnBnClickedButtonNewusr)
	ON_BN_CLICKED(IDC_BUTTON_BRSKEYFILE, &CPPwdMngWDlg::OnBnClickedButtonBrskeyfile)
	ON_BN_CLICKED(IDC_BUTTON_BSRACCFILE, &CPPwdMngWDlg::OnBnClickedButtonBsraccfile)
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &CPPwdMngWDlg::OnBnClickedButtonConfirm)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CPPwdMngWDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CPPwdMngWDlg 消息处理程序

BOOL CPPwdMngWDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPPwdMngWDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPPwdMngWDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPPwdMngWDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPPwdMngWDlg::OnBnClickedButtonNewusr()
{
	CNewUsrDlg cdlgNewUsr;

	cdlgNewUsr.DoModal();
	return;
	// TODO: 在此添加控件通知处理程序代码
}



void CPPwdMngWDlg::OnBnClickedButtonBrskeyfile()
{
	CFileDialog cdlgFile(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files(*.*)|*.*||"), AfxGetMainWnd());

	if (cdlgFile.DoModal() == IDOK)
	{
		m_cstrKeyFile = cdlgFile.GetPathName();
		SetDlgItemTextA(IDC_EDIT_KEYFILE, m_cstrKeyFile);


		//UpdateData(TRUE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CPPwdMngWDlg::OnBnClickedButtonBsraccfile()
{
	CFileDialog cdlgFile(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files(*.*)|*.*||"), AfxGetMainWnd());

	if (cdlgFile.DoModal() == IDOK)
	{
		m_cstrAccFile = cdlgFile.GetPathName();
		SetDlgItemTextA(IDC_EDIT_ACCFILE, m_cstrAccFile );


		//UpdateData(TRUE);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CPPwdMngWDlg::OnBnClickedButtonConfirm()
{
	struct UsrFHead stUsrFHead;
	struct AccHeadM stAccHeadM[ACC_MAX];
	char* pcaUsrName=NULL;
	unsigned char* pcaPwd = NULL;

	memset(&stUsrFHead, 0x00, sizeof(struct UsrFHead));
	memset(stAccHeadM, 0x00, sizeof(stAccHeadM));

	UpdateData(TRUE);

	if (m_cstrUsrName.GetLength() == 0 ||
		m_cstrUsrPwd.GetLength() == 0 ||
		m_cstrKeyFile.GetLength() == 0 ||
		m_cstrAccFile.GetLength() == 0)
	{
		AfxMessageBox("输入项不能为空，请重新输入！");
		return;
	}
	if (m_cstrUsrName.GetLength() > USRNAME_LEN - 1)
	{
		AfxMessageBox("用户名过长，请重新输入！");
		return;
	}
	if (m_cstrUsrPwd.GetLength() != USRPWD_LEN)
	{
		AfxMessageBox("用户密码长度错误，请重新输入！");
		return;
	}
	if (GetKey((char *)m_cstrKeyFile.GetString(), m_caKey) != 0)
	{
		AfxMessageBox("密钥读取失败!");
		return;
	}

	if (GetAccType("AccType.cfg", stAccHeadM) != 0)
	{
		AfxMessageBox("账户类别文件读取失败!");
		return;
	}
	if (AccFileRead((char*)m_cstrAccFile.GetString(), &stUsrFHead, stAccHeadM) !=0 )
	{
		AfxMessageBox("账户文件读取失败!");
		return;
	}

	pcaUsrName = (char *) m_cstrUsrName.GetString();
	pcaPwd = (unsigned char*)m_cstrUsrPwd.GetString();
	BlockEncrypt(m_caKey, pcaPwd, pcaPwd, USRPWD_LEN);
	if (memcmp(stUsrFHead.strUsrName , pcaUsrName, m_cstrUsrName.GetLength()) !=0 || 
		memcmp(stUsrFHead.strPassword , pcaPwd , USRPWD_LEN) != 0)
	{
		m_iErrTimes++;
		if (m_iErrTimes > 3)
		{
			AfxMessageBox("输入错误次数超限，退出程序!");
			EndDialog(IDCANCEL);
			return;
		}
		else
		{
			AfxMessageBox("用户名或密码输入错误，请重新输入!");
			return;
		}
		
	}

	CAccRecsDlg cdlgAccRecs;
	cdlgAccRecs.m_pstAccHeadM = stAccHeadM;
	cdlgAccRecs.m_pstUsrFHead = &stUsrFHead;
	cdlgAccRecs.m_pcaKey = m_caKey;
	cdlgAccRecs.m_pcaAccFileName = (char *)m_cstrAccFile.GetString();
	if (cdlgAccRecs.DoModal() == IDCANCEL)
	{
		FreeMem(stAccHeadM);
		EndDialog(IDCANCEL);
		return;
	}
	return;
}


void CPPwdMngWDlg::OnBnClickedButtonCancel()
{
	EndDialog(IDCANCEL);
	return;
	// TODO: 在此添加控件通知处理程序代码
}
