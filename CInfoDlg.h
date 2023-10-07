#pragma once



// CInfoDlg 窗体视图

class CInfoDlg : public CFormView
{
	DECLARE_DYNCREATE(CInfoDlg)

protected:
	CInfoDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CInfoDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_INFO };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_list;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnNMRClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void On32771();
	afx_msg void OnBnClickedButton4();
	afx_msg void On32772();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
private:
	CString m_search;
	CBitmapButton m_bitmapbtn;
	CEdit m_num;
	CBitmapButton m_clear;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	CBitmapButton m_rise;
	CBitmapButton m_down;
	CImage m_image;
public:
	afx_msg void OnPaint();
	afx_msg void OnAppExit();
};


