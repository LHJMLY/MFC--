#pragma once



// CLoseDlg 对话框

class CLoseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoseDlg)

public:
	CLoseDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoseDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_PWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	CString m_newpwd1;
	CString m_surenewpwd1;
public:
	afx_msg void OnBnClickedButton2();
};
