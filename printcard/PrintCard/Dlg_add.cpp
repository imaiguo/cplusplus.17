// Dlg_add.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PrintCard.h"
#include "Dlg_add.h"
#include "afxdialogex.h"
#include "PrintCardDlg.h"


// CDlg_add �Ի���

IMPLEMENT_DYNAMIC(CDlg_add, CDialogEx)

CDlg_add::CDlg_add(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg_add::IDD, pParent)
{

}

CDlg_add::~CDlg_add()
{
}

void CDlg_add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_Name);
	DDX_Control(pDX, IDC_EDIT4, m_AreName);
}


BEGIN_MESSAGE_MAP(CDlg_add, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CDlg_add::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlg_add::OnBnClickedRadio2)
	ON_BN_CLICKED(IDOK, &CDlg_add::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg_add ��Ϣ�������




void CDlg_add::OnBnClickedRadio1()
{
	m_strSex = "����";
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlg_add::OnBnClickedRadio2()
{
	m_strSex = "���";
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDlg_add::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if("" == m_strSex || 0 == m_Name.GetWindowTextLengthA() || 0 == m_AreName.GetWindowTextLengthA()) 
	{
		MessageBox("��д����Ϣ����ȫ","��ʾ",MB_OK|MB_ICONINFORMATION);
		return;
	}

	CPrintCardDlg *pDlg= (CPrintCardDlg*)GetParent();
	int icount=pDlg->m_list.GetItemCount();
	
	CString strTemp;
	strTemp.Format("%d",icount+1);
	pDlg->m_list.InsertItem(icount,strTemp);

	m_Name.GetWindowTextA(strTemp);
	pDlg->m_list.SetItemText(icount,1,strTemp);
	pDlg->m_list.SetItemText(icount,2,m_strSex);
	m_AreName.GetWindowTextA(strTemp);
	pDlg->m_list.SetItemText(icount,3,strTemp);
	strTemp.Format(" ÿ�ο��Դ�ӡ10������,�Ѿ�¼��:%d/10",icount+1);
	pDlg->m_Tip.SetWindowTextA(strTemp);
	CDialogEx::OnOK();
}
