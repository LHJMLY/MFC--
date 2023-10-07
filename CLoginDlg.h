#pragma once
#include "afxdialogex.h"
#include "InfoFile.h"

// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_user;
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnBnClickedRadio1();
	virtual void OnCancel();
private:
	CEdit m_pwd;
	CBitmapButton m_hide;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CBitmapButton m_login;
	CBitmapButton m_cancel;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
