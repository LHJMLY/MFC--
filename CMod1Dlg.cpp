// CMod1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "EmpSystem.h"
#include "afxdialogex.h"
#include "CMod1Dlg.h"
#include "InfoFile.h"
#include "CMod2Dlg.h"


// CMod1Dlg 对话框

IMPLEMENT_DYNAMIC(CMod1Dlg, CDialogEx)

CMod1Dlg::CMod1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_MOD1, pParent)
	, m_idorname(_T(""))
{

}

CMod1Dlg::~CMod1Dlg()
{
}

void CMod1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_id);
	DDX_Control(pDX, IDC_RADIO2, m_name);
	DDX_Text(pDX, IDC_EDIT1, m_idorname);
}


BEGIN_MESSAGE_MAP(CMod1Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CMod1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMod1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMod1Dlg 消息处理程序


void CMod1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


BOOL CMod1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//设置全局变量，为了传值
CString global_num;
CString global_name;
void CMod1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	if (m_idorname.IsEmpty())
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
			MessageBox(TEXT("一个员工都没有，修改什么？"));
			return;
		}
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
		{
			if (it->id == _tcstol(m_idorname, NULL, 10))
			{
				i = 1;
				GetDlgItemText(IDC_EDIT1, global_num);
				CDialog::OnCancel();
				CMod2Dlg dlg;
				dlg.DoModal();			
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
			MessageBox(TEXT("一个员工都没有，修改什么？"));
			return;
		}
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
		{
			if ((CString)it->name.c_str() == m_idorname)
			{
				i = 1;
				GetDlgItemText(IDC_EDIT1, global_name);
				CDialog::OnCancel();
				CMod2Dlg dlg;
				dlg.DoModal();
			}
		}
		if (i == 0)
		{
			MessageBox(TEXT("没有这个人！"));
		}
	}
}
