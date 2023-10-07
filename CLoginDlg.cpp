// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "EmpSystem.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "CLoseDlg.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_user(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Control(pDX, IDC_EDIT2, m_pwd);
	DDX_Control(pDX, IDC_BUTTON3, m_hide);
	DDX_Control(pDX, IDC_BUTTON1, m_login);
	DDX_Control(pDX, IDC_BUTTON2, m_cancel);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO1, &CLoginDlg::OnBnClickedRadio1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON3, &CLoginDlg::OnBnClickedButton3)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strl;
	m_pwd.GetWindowText(strl);
	if (m_user.IsEmpty() || strl.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (name == m_user)
	{
		if (pwd == strl)
		{
			CDialog::OnCancel();
		}
		else
		{
			MessageBox(TEXT("密码有误"));
		}
	}
	else
	{
		MessageBox(TEXT("用户名有误"));
	}
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// TODO:  在此添加额外的初始化
	SetTimer(1, 10, NULL);
	SetBackgroundImage(IDB_BITMAP26);       //设置背景图
	m_login.LoadBitmaps(IDB_BITMAP6, IDB_BITMAP8, IDB_BITMAP7, IDB_BITMAP9);
	m_login.SizeToContent();          //根据图片的大小设置按钮
	m_cancel.LoadBitmaps(IDB_BITMAP10, IDB_BITMAP12, IDB_BITMAP11, IDB_BITMAP13);
	m_cancel.SizeToContent();          //根据图片的大小设置按钮
	m_pwd.SetPasswordChar(_T('*'));
	m_hide.LoadBitmaps(IDB_BITMAP2);
	m_hide.SizeToContent();          

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}


void CLoginDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	CLoseDlg dlg;
	dlg.DoModal();
}




//取消按钮
void CLoginDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
	exit(0);       //直接退出程序
}


//显示密码和隐藏密码的图标变化
bool m_bStart = TRUE;
void CLoginDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bStart ^= TRUE;         //c语言的位操作
	if (m_bStart == false)
	{
		m_pwd.SetPasswordChar(NULL);
		m_hide.LoadBitmaps(IDB_BITMAP1);
		m_hide.SizeToContent();
	}
	else
	{
		m_pwd.SetPasswordChar(_T('*'));
		m_hide.LoadBitmaps(IDB_BITMAP2);
		m_hide.SizeToContent();
	}
	m_pwd.RedrawWindow(NULL, NULL);
}


int CLoginDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetClassLong(GetSafeHwnd(), GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));
	return 0;
}


void CLoginDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		POINT p;
		GetCursorPos(&p);
		CWnd* hwnd;
		hwnd = WindowFromPoint(p);
		CWnd* hwnd2 = GetDlgItem(IDC_BUTTON1);
		CWnd* hwnd3 = GetDlgItem(IDC_BUTTON2);
		if (hwnd == hwnd2)
		{
			if (GetFocus() != hwnd2)
			{
				hwnd2->SetFocus();
			}
		}
		else if (hwnd == hwnd3)
		{
			if (GetFocus() != hwnd3)
			{
				hwnd3->SetFocus();
			}
		}
		else
		{
			if (GetFocus() == hwnd2)
			{
				GetDlgItem(IDC_STATIC)->SetFocus();
			}
			if (GetFocus() == hwnd3)
			{
				GetDlgItem(IDC_STATIC)->SetFocus();
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}
