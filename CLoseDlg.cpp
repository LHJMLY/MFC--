// CLoseDlg.cpp: 实现文件
//

#include "pch.h"
#include "EmpSystem.h"
#include "afxdialogex.h"
#include "CLoseDlg.h"
#include "InfoFile.h"


// CLoseDlg 对话框

IMPLEMENT_DYNAMIC(CLoseDlg, CDialogEx)

CLoseDlg::CLoseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_PWD, pParent)
	, m_newpwd1(_T(""))
	, m_surenewpwd1(_T(""))
{

}

CLoseDlg::~CLoseDlg()
{
}

void CLoseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_newpwd1);
	DDX_Text(pDX, IDC_EDIT2, m_surenewpwd1);
}


BEGIN_MESSAGE_MAP(CLoseDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoseDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoseDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CLoseDlg 消息处理程序


void CLoseDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_surenewpwd1.IsEmpty() || m_newpwd1.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}
	if (m_surenewpwd1 != m_newpwd1)
	{
		MessageBox(TEXT("新密码与确定密码不一致"));
		return;
	}
	if (MessageBox(TEXT("确定修改吗？"), 0, 1) == IDOK)
	{
		CInfoFile file;
		CString name, pwd;
		file.ReadLogin(name, pwd);
		CStringA tmp, tmp2;
		tmp = name;
		tmp2 = m_newpwd1;
		file.WritePwd(tmp.GetBuffer(), tmp2.GetBuffer());
		MessageBox(TEXT("修改成功！"));
		m_newpwd1.Empty();
		m_surenewpwd1.Empty();
		UpdateData(0);
	}
	CDialog::OnCancel();
}


void CLoseDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
