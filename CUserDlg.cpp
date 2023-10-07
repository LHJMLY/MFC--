// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "EmpSystem.h"
#include "CUserDlg.h"
#include "InfoFile.h"
#include "ButtonPNG.h"

// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_name(_T(""))
	, m_pwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_BUTTON3, m_hide1);
	DDX_Control(pDX, IDC_BUTTON4, m_hide2);
	DDX_Control(pDX, IDC_EDIT3, m_newpwd);
	DDX_Control(pDX, IDC_EDIT4, m_surenewpwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserDlg::OnBnClickedButton4)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	LoadPicture(m_imgbk, IDB_PNG2);
	m_newpwd.SetPasswordChar(_T('*'));
	m_hide1.LoadBitmaps(IDB_BITMAP2);
	m_hide1.SizeToContent();
	m_surenewpwd.SetPasswordChar(_T('*'));
	m_hide2.LoadBitmaps(IDB_BITMAP2);
	m_hide2.SizeToContent();
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	m_name = name;
	UpdateData(0);
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str1;
	m_newpwd.GetWindowText(str1);
	CString str2;
	m_surenewpwd.GetWindowText(str2);
	if (str1.IsEmpty() || str2.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}
	if (str1 != str2)
	{
		MessageBox(TEXT("新密码与确定密码不一致"));
		return;
	}
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (pwd == str1)
	{
		MessageBox(TEXT("新密码与旧密码不能一致"));
		return;
	}
	if (MessageBox(TEXT("确定修改吗？"), 0, 1) == IDOK)
	{
		CStringA tmp, tmp2;
		tmp = name;
		tmp2 = str1;
		file.WritePwd(tmp.GetBuffer(), tmp2.GetBuffer());
		MessageBox(TEXT("修改成功！"));
		str1.Empty();
		str2.Empty();
		UpdateData(0);
		return;
	}
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str1;
	m_newpwd.GetWindowText(str1);
	CString str2;
	m_surenewpwd.GetWindowText(str2);
	str1.Empty();
	str2.Empty();
	UpdateData(0);
}

bool m_bStart1 = TRUE;
void CUserDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bStart1 ^= TRUE;         //c语言的位操作
	if (m_bStart1 == false)
	{
		m_newpwd.SetPasswordChar(NULL);
		m_hide1.LoadBitmaps(IDB_BITMAP1);
		m_hide1.SizeToContent();
	}
	else
	{
		m_newpwd.SetPasswordChar(_T('*'));
		m_hide1.LoadBitmaps(IDB_BITMAP2);
		m_hide1.SizeToContent();
	}
	m_newpwd.RedrawWindow(NULL, NULL);
}

bool m_bStart2 = TRUE;
void CUserDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bStart2 ^= TRUE;         //c语言的位操作
	if (m_bStart2 == false)
	{
		m_surenewpwd.SetPasswordChar(NULL);
		m_hide2.LoadBitmaps(IDB_BITMAP1);
		m_hide2.SizeToContent();
	}
	else
	{
		m_surenewpwd.SetPasswordChar(_T('*'));
		m_hide2.LoadBitmaps(IDB_BITMAP2);
		m_hide2.SizeToContent();
	}
	m_surenewpwd.RedrawWindow(NULL, NULL);
}


void CUserDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
	drawPicOnPait(&m_imgbk, this, 0, 0);
}
