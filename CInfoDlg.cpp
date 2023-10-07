// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "EmpSystem.h"
#include "CInfoDlg.h"
#include "InfoFile.h"
#include "CAddDlg.h"
#include "CDel1Dlg.h"
#include "CMod1Dlg.h"
#include "CMod2Dlg.h"
#include <regex>
#include "ButtonPNG.h"

// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(DIALOG_INFO)
	, m_search(_T(""))
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);

	DDX_Text(pDX, IDC_EDIT2, m_search);
	DDX_Control(pDX, IDC_BUTTON8, m_bitmapbtn);
	DDX_Control(pDX, IDC_EDIT1, m_num);
	DDX_Control(pDX, IDC_BUTTON6, m_clear);
	DDX_Control(pDX, IDC_BUTTON1, m_rise);
	DDX_Control(pDX, IDC_BUTTON2, m_down);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInfoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CInfoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CInfoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CInfoDlg::OnBnClickedButton5)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CInfoDlg::OnNMRClickList1)
	ON_COMMAND(ID_32771, &CInfoDlg::On32771)
	ON_BN_CLICKED(IDC_BUTTON4, &CInfoDlg::OnBnClickedButton4)
	ON_COMMAND(ID_32772, &CInfoDlg::On32772)
	ON_BN_CLICKED(IDC_BUTTON7, &CInfoDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CInfoDlg::OnBnClickedButton8)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_COMMAND(ID_APP_EXIT, &CInfoDlg::OnAppExit)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg 消息处理程序


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	SetTimer(1, 10, NULL);
	LoadPicture(m_image, IDB_PNG1);
	m_clear.LoadBitmaps(IDB_BITMAP5, IDB_BITMAP15, IDB_BITMAP14, IDB_BITMAP16);
	m_clear.SizeToContent();          //根据图片的大小设置按钮
	m_rise.LoadBitmaps(IDB_BITMAP17, IDB_BITMAP19, IDB_BITMAP18, IDB_BITMAP20);
	m_rise.SizeToContent();          //根据图片的大小设置按钮
	m_down.LoadBitmaps(IDB_BITMAP22, IDB_BITMAP23, IDB_BITMAP21, IDB_BITMAP24);
	m_down.SizeToContent();          //根据图片的大小设置按钮
	m_bitmapbtn.LoadBitmaps(IDB_BITMAP3, IDB_BITMAP4);
	m_bitmapbtn.SizeToContent();          //根据图片的大小设置按钮
	CInfoFile file1;
	file1.ReadDocline();
	//类型转换
	int j = file1.ls.size();
	string str2 = to_string(j);
	CString str3 = (CString)str2.c_str();
	GetDlgItem(IDC_EDIT1)->SetWindowText(str3);      //给编辑框赋值
	UpdateData(0);
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);     //设置默认单选框
	// TODO: 在此添加专用代码和/或调用基类
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化表头
	CString field[] = { _T("工号"), _T("姓名"), _T("年龄"), _T("职位") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 194);
	}

	CInfoFile file;
	file.ReadDocline(); //读取员工信息

	//添加数据
	int i = 0;
	CString str;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		str.Format(_T("%d"), it->id);
		m_list.InsertItem(i, str);
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());
		str.Format(_T("%d"), it->age);
		m_list.SetItemText(i, column++, str);
		m_list.SetItemText(i, column++, (CString)it->work_name.c_str());
		i++;
	}
}

void CInfoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		UpdateData(1);
		CInfoFile file;
		file.ReadDocline();
		if (file.ls.size() > 1)
		{
			if (MessageBox(TEXT("升序之后你将无法找回原来的顺序，确定升序吗？"), 0, 1) == IDOK)
			{
				file.ls.sort([](msg& a, msg& b)->bool {return a.age < b.age; });
				MessageBox(TEXT("升序成功！"));
				file.WirteDocline();
				m_list.DeleteAllItems();
				while (m_list.DeleteColumn(0));
				OnInitialUpdate();
				CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
			}
		}
		else if (file.ls.size() == 1)
		{
			MessageBox(TEXT("只有一个元素，升什么序，乱搞？"));
			return;
		}
		else
		{
			MessageBox(TEXT("一个元素都没有，你升序给我睇睇？"));
		}
	}
	if (IsDlgButtonChecked(IDC_RADIO2))
	{
		UpdateData(1);
		CInfoFile file;
		file.ReadDocline();
		if (file.ls.size() > 1)
		{
			if (MessageBox(TEXT("升序之后你将无法找回原来的顺序，确定升序吗？"), 0, 1) == IDOK)
			{
				file.ls.sort([](msg& a, msg& b)->bool {return a.id < b.id; });
				MessageBox(TEXT("升序成功！"));
				file.WirteDocline();
				m_list.DeleteAllItems();
				while (m_list.DeleteColumn(0));
				OnInitialUpdate();
				CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
			}
		}
		else if (file.ls.size() == 1)
		{
			MessageBox(TEXT("只有一个元素，升什么序，乱搞？"));
			return;
		}
		else
		{
			MessageBox(TEXT("一个元素都没有，你升序给我睇睇？"));
		}
	}
}


void CInfoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsDlgButtonChecked(IDC_RADIO1))
	{
		UpdateData(1);
		CInfoFile file;
		file.ReadDocline();
		if (file.ls.size() > 1)
		{
			if (MessageBox(TEXT("降序之后你将无法找回原来的顺序，确定降序吗？"), 0, 1) == IDOK)
			{
				file.ls.sort([](msg& a, msg& b)->bool {return a.age > b.age; });
				MessageBox(TEXT("降序成功！"));
				file.WirteDocline();
				m_list.DeleteAllItems();
				while (m_list.DeleteColumn(0));
				OnInitialUpdate();
				CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
			}
		}
		else if (file.ls.size() == 1)
		{
			MessageBox(TEXT("只有一个元素，降什么序，乱搞？"));
			return;
		}
		else
		{
			MessageBox(TEXT("一个元素都没有，你降序给我睇睇？"));
		}
	}
	if (IsDlgButtonChecked(IDC_RADIO2))
	{
		UpdateData(1);
		CInfoFile file;
		file.ReadDocline();
		if (file.ls.size() > 1)
		{
			if (MessageBox(TEXT("降序之后你将无法找回原来的顺序，确定降序吗？"), 0, 1) == IDOK)
			{
				file.ls.sort([](msg& a, msg& b)->bool {return a.id > b.id; });
				MessageBox(TEXT("降序成功！"));
				file.WirteDocline();
				m_list.DeleteAllItems();
				while (m_list.DeleteColumn(0));
				OnInitialUpdate();
				CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
			}
		}
		else if (file.ls.size() == 1)
		{
			MessageBox(TEXT("只有一个元素，降什么序，乱搞？"));
			return;
		}
		else
		{
			MessageBox(TEXT("一个元素都没有，你降序给我睇睇？"));
		}
	}
}


void CInfoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddDlg dlg;
	dlg.DoModal();
	m_list.DeleteAllItems();
	while (m_list.DeleteColumn(0));
	OnInitialUpdate();
}


void CInfoDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CInfoFile file;
	file.ReadDocline();
	if (MessageBox(TEXT("清空后数据将无法找回,确认清空吗？"), 0, 1) == IDOK)
	{
		file.ls.clear();
		MessageBox(TEXT("清空成功！"));
		file.WirteDocline();
		m_list.DeleteAllItems();
		while (m_list.DeleteColumn(0));
		OnInitialUpdate();
	}
}


void CInfoDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CDel1Dlg dlg;
	dlg.DoModal();
	m_list.DeleteAllItems();
	while (m_list.DeleteColumn(0));
	OnInitialUpdate();
}


void CInfoDlg::OnNMRClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nItem = pNMItemActivate->iItem;
	if (m_list.GetSelectedCount() <= 0)
		return;//判断右键是否有内容
	CMenu menu;
	POINT pt = { 0 };
	GetCursorPos(&pt);//得到鼠标点击位置 
	menu.LoadMenu(IDR_MENU1);//菜单资源ID 
	menu.GetSubMenu(0)->TrackPopupMenu(0, pt.x, pt.y, this);
	*pResult = 0;
}


void CInfoDlg::On32771()
{
	// TODO: 在此添加命令处理程序代码
	UpdateData(1);
	int nIndex = m_list.GetSelectionMark();   //获取选中行的行号
	CString s = m_list.GetItemText(nIndex, 0);   //获取第0列内容
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (it->id == _tcstol(s, NULL, 10))
		{
			file.ls.erase(it);
			break;
		}
	}
	file.WirteDocline();
	UpdateData(0);
	m_list.DeleteAllItems();
	while (m_list.DeleteColumn(0));
	OnInitialUpdate();
	MessageBox(TEXT("删除成功！"));
}


void CInfoDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CMod1Dlg dlg;
	dlg.DoModal();
	m_list.DeleteAllItems();
	while (m_list.DeleteColumn(0));
	OnInitialUpdate();
}


CString global_num2;          //文件作用域，用来传值
void CInfoDlg::On32772()
{
	// TODO: 在此添加命令处理程序代码
	UpdateData(1);
	int nIndex = m_list.GetSelectionMark();   //获取选中行的行号
	global_num2 = m_list.GetItemText(nIndex, 0);   //获取第0列内容
	CMod2Dlg dlg;
	dlg.DoModal();
	m_list.DeleteAllItems();
	while (m_list.DeleteColumn(0));
	OnInitialUpdate();
}


void CInfoDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	while (m_list.DeleteColumn(0));
	OnInitialUpdate();
}


void CInfoDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	if (m_search.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空！"));
		return;
	}
	m_list.DeleteAllItems();
	while (m_list.DeleteColumn(0));
	CString field[] = { _T("工号"), _T("姓名"), _T("年龄"), _T("职位") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 194);
	}
	string strl = CT2A(m_search.GetString());
	string pattern = "(.)*" + strl + "(.)*";
	regex r(pattern, regex::icase);
	smatch results;
	CInfoFile file;
	file.ReadDocline();
	int m = 0;
	CString str;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (regex_search(it->name, results, r))
		{
			str.Format(_T("%d"), it->id);
			m_list.InsertItem(m, str);
			int column = 1;
			m_list.SetItemText(m, column++, (CString)it->name.c_str());
			str.Format(_T("%d"), it->age);
			m_list.SetItemText(m, column++, str);
			m_list.SetItemText(m, column++, (CString)it->work_name.c_str());
			m++;
		}
	}
	m_num.SetReadOnly(0);      //取消只读
	//进行类型转换，m是个数
	string str2 = to_string(m);
	CString str3 = (CString)str2.c_str();
	GetDlgItem(IDC_EDIT1)->SetWindowText(str3);
	m_num.SetReadOnly(1);     //重新设置只读
	m_search.Empty();        //清空数据
	file.WirteDocline();
}

//定时器响应函数
void CInfoDlg::OnTimer(UINT_PTR nIDEvent)
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
		CWnd* hwnd4 = GetDlgItem(IDC_BUTTON6);
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
		else if (hwnd == hwnd4)
		{
			if (GetFocus() != hwnd4)
			{
				hwnd4->SetFocus();
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
			if (GetFocus() == hwnd4)
			{
				GetDlgItem(IDC_STATIC)->SetFocus();
			}
		}
	}
	CFormView::OnTimer(nIDEvent);
}


void CInfoDlg::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
	drawPicOnPait(&m_image, this, 0, 0);
}


void CInfoDlg::OnAppExit()
{
	// TODO: 在此添加命令处理程序代码
	exit(0);
}
