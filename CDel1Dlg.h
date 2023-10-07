#pragma once
#include "afxdialogex.h"


// CDel1Dlg 对话框

class CDel1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDel1Dlg)

public:
	CDel1Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDel1Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_DEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CButton m_iddel;
	CButton m_namedel;
public:
	afx_msg void OnBnClickedButton2();
private:
	CString m_numorname;
public:
	afx_msg void OnBnClickedButton1();
};
