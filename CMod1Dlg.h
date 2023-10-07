#pragma once
#include "afxdialogex.h"


// CMod1Dlg 对话框

class CMod1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMod1Dlg)

public:
	CMod1Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMod1Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_MOD1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CButton m_id;
	CButton m_name;
	CString m_idorname;
public:
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
