// CDel1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "EmpSystem.h"
#include "afxdialogex.h"
#include "CDel1Dlg.h"
#include "InfoFile.h"

// CDel1Dlg 对话框

IMPLEMENT_DYNAMIC(CDel1Dlg, CDialogEx)

CDel1Dlg::CDel1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_DEL, pParent)
	, m_numorname(_T(""))
{

}

CDel1Dlg::~CDel1Dlg()
{
}

void CDel1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_iddel);
	DDX_Control(pDX, IDC_RADIO2, m_namedel);
	DDX_Text(pDX, IDC_EDIT1, m_numorname);
}


BEGIN_MESSAGE_MAP(CDel1Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CDel1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDel1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDel1Dlg 消息处理程序


BOOL CDel1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE

}


void CDel1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CDel1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	if (m_numorname.IsEmpty())
	{
		MessageBox(TEXT("内容不能为空！"));
		return;
	}
	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		UpdateData(1);
		CInfoFile file;
		file.ReadDocline();
		int i = 0;
		if (file.ls.size() == 0)
		{
			MessageBox(TEXT("一个员工都没有，删除什么？"));
			return;
		}
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
		{
			if (it->id == _tcstol(m_numorname, NULL, 10))
			{
				i = 1;
				if (MessageBox(TEXT("确定删除吗？"), 0, 1) == IDOK)
				{
					file.ls.erase(it);
					file.WirteDocline();
					CDialog::OnCancel();
					return;
				}
			}
		}
		if (i == 0)
		{
			MessageBox(TEXT("没有这个人！"));
		}
	}
	if (IsDlgButtonChecked(IDC_RADIO2))
	{
		UpdateData(1);
		CInfoFile file;
		file.ReadDocline();
		int i = 0;
		if (file.ls.size() == 0)
		{
			MessageBox(TEXT("一个员工都没有，删除什么？"));
			return;
		}
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
		{
			if ((CString)it->name.c_str() == m_numorname)
			{
				i = 1;
				if (MessageBox(TEXT("确定删除吗？"), 0, 1) == IDOK)
				{
					file.ls.erase(it);
					file.WirteDocline();
					CDialog::OnCancel();
					return;
				}
			}
		}
		if (i == 0)
		{
			MessageBox(TEXT("没有这个人！"));
		}
	}
}
