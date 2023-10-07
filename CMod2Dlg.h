#pragma once
#include "afxdialogex.h"
extern CString global_num;
extern CString global_name;
extern CString global_num2;
// CMod2Dlg 对话框

class CMod2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMod2Dlg)

public:
	CMod2Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMod2Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_MOD2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
private:
	CString m_id;
	CString m_name;
	CString m_age;
	CString m_workname;
public:
	afx_msg void OnBnClickedButton1();
};
