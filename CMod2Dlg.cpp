// CMod2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "EmpSystem.h"
#include "afxdialogex.h"
#include "CMod2Dlg.h"
#include "InfoFile.h"


// CMod2Dlg 对话框

IMPLEMENT_DYNAMIC(CMod2Dlg, CDialogEx)

CMod2Dlg::CMod2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_MOD2, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_age(_T(""))
	, m_workname(_T(""))
{

}

CMod2Dlg::~CMod2Dlg()
{
}

void CMod2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_age);
	DDX_Text(pDX, IDC_EDIT4, m_workname);
}


BEGIN_MESSAGE_MAP(CMod2Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CMod2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMod2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMod2Dlg 消息处理程序


void CMod2Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CMod2Dlg::OnBnClickedButton1()
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
		if (it->id == _tcstol(m_id, NULL, 10) && _tcstol(m_id, NULL, 10) != _tcstol(global_num2, NULL, 10))
		{
			MessageBox(TEXT("已有职工号，职工号不能重复！"));
			return;
		}
	}
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (it->id == _tcstol(global_num, NULL, 10))
		{
			it->name = CW2A(m_name);
			it->id = _tcstol(m_id, NULL, 10);
			it->age = _tcstol(m_age, NULL, 10);
			it->work_name = CW2A(m_workname);
			MessageBox(TEXT("修改成功！"));
			m_name.Empty();
			m_id.Empty();
			m_age.Empty();
			m_workname.Empty();
			UpdateData(0);
		}
		if (it->name.c_str() == global_name)
		{
			it->name = CW2A(m_name);
			it->id = _tcstol(m_id, NULL, 10);
			it->age = _tcstol(m_age, NULL, 10);
			it->work_name = CW2A(m_workname);
			MessageBox(TEXT("修改成功！"));
			m_name.Empty();
			m_id.Empty();
			m_age.Empty();
			m_workname.Empty();
			UpdateData(0);
		}
		if (it->id == _tcstol(global_num2, NULL, 10))
		{
			it->name = CW2A(m_name);
			it->id = _tcstol(m_id, NULL, 10);
			it->age = _tcstol(m_age, NULL, 10);
			it->work_name = CW2A(m_workname);
			m_name.Empty();
			m_id.Empty();
			m_age.Empty();
			m_workname.Empty();
			UpdateData(0);
			MessageBox(TEXT("修改成功！"));
		}
	}
	file.WirteDocline();
	CDialog::OnCancel();
}
