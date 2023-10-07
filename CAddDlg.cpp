// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "EmpSystem.h"
#include "afxdialogex.h"
#include "CAddDlg.h"
#include "InfoFile.h"


// CAddDlg 对话框

IMPLEMENT_DYNAMIC(CAddDlg, CDialogEx)

CAddDlg::CAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_ADD, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_age(_T(""))
	, m_workname(_T(""))
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_age);
	DDX_Text(pDX, IDC_EDIT4, m_workname);
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CAddDlg 消息处理程序


void CAddDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	if (m_name.IsEmpty() || m_age.IsEmpty() || m_id.IsEmpty() || m_workname.IsEmpty())
	{
		MessageBox(TEXT("输入信息不能为空！"));
		return;
	}
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (it->id == _tcstol(m_id, NULL, 10))
		{
			MessageBox(TEXT("已有职工号，职工号不能重复！"));
			return;
		}
	}
	file.Addline(_tcstol(m_id, NULL, 10), m_name, _tcstol(m_age, NULL, 10), m_workname);
	file.WirteDocline();
	MessageBox(TEXT("添加成功！"));
	m_name.Empty();
	m_id.Empty();
	m_age.Empty();
	m_workname.Empty();
	UpdateData(0);
	CDialog::OnCancel();
}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
