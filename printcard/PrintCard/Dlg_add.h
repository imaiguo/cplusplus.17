#pragma once
#include "afxwin.h"


// CDlg_add �Ի���

class CDlg_add : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_add)

public:
	CDlg_add(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_add();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSex;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedOk();
	CEdit m_Name;
	CEdit m_AreName;
};
