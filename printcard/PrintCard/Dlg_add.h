#pragma once
#include "afxwin.h"


// CDlg_add 对话框

class CDlg_add : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_add)

public:
	CDlg_add(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_add();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSex;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedOk();
	CEdit m_Name;
	CEdit m_AreName;
};
