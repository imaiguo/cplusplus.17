
// PrintCardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PrintCard.h"
#include "PrintCardDlg.h"
#include "afxdialogex.h"
#include "Dlg_add.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPrintCardDlg �Ի���


CPrintCardDlg::CPrintCardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrintCardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrintCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_list);
	DDX_Control(pDX, IDC_LIST_DATA, m_list);
	DDX_Control(pDX, IDC_STATIC_TIP, m_Tip);
}

BEGIN_MESSAGE_MAP(CPrintCardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPrintCardDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &CPrintCardDlg::OnBnClickedButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CPrintCardDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CPrintCardDlg::OnBnClickedButtonDel)
END_MESSAGE_MAP()


// CPrintCardDlg ��Ϣ�������

BOOL CPrintCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	char* pListName[][2] = {{"���", "40"},{"����", "100"},{"�Ա�", "50"},{"����", "155"},{"end","end"}};
	for (int i = 0; strcmp(pListName[i][0],"end") != 0; i++)
	{
		m_list.InsertColumn (i, pListName[i][0], LVCFMT_LEFT, atoi(pListName[i][1]));
	}

	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT);

	m_Tip.SetWindowTextA(" ÿ�ο��Դ�ӡ10������,�Ѿ�¼��:0/10");
	m_list.MoveWindow(0,0,350,300);
	MoveWindow(0,0,350,400);
	CenterWindow();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPrintCardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPrintCardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPrintCardDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CPrintCardDlg::OnBnClickedButtonPrint()
{
	//��ȡ��ǰ�ĳ�������·��
	char buf[256]={0};
	GetModuleFileName(0,buf,256);
	CString strPath=buf;
	int pos=strPath.ReverseFind('\\');
	strPath=strPath.Left(pos);

	CSize	pointGroup[3];
	int	ipoint[3][2] = {
		{::GetPrivateProfileInt("��������","����x",0,strPath+"\\config.ini"),::GetPrivateProfileInt("��������","����y",0,strPath+"\\config.ini")},              
		{::GetPrivateProfileInt("��������","�Ա�x",0,strPath+"\\config.ini"),::GetPrivateProfileInt("��������","�Ա�y",0,strPath+"\\config.ini")},             
		{::GetPrivateProfileInt("��������","����x",0,strPath+"\\config.ini"),::GetPrivateProfileInt("��������","����y",0,strPath+"\\config.ini")}           
		};

	for(int i = 0;i< 3;i++)
	{
		pointGroup[i].cx = ipoint[i][0];
		pointGroup[i].cy = ipoint[i][1];
	}


	//ÿӢ��ˮƽ�߼�������
	CDC* pDC = GetDC();
	int screenx = pDC->GetDeviceCaps(LOGPIXELSX);
	int screeny = pDC->GetDeviceCaps(LOGPIXELSY);

	//Ҫ��ӡ������
	CString InfoData[10][3];
	int icount=m_list.GetItemCount();
	for(int j=0;j < 10 && j < icount; j++)
	{
		m_list.GetItemText(j,1);
		InfoData[j][0] = m_list.GetItemText(j,1);
		InfoData[j][1] = m_list.GetItemText(j,2);
		InfoData[j][2] = m_list.GetItemText(j,3);
	}

	CPrintDialog m_printdlg(false);
	if (m_printdlg.DoModal()==IDOK)
	{
		CDC dc;		
		dc.Attach(m_printdlg.GetPrinterDC());	
		CRect resttest;
		dc.GetBoundsRect(resttest,0);
		//��ȡ��ǰ��ӡ����ҳ�߾�,��ֹ��ӡ�ı���ͼƬ�����ִ�λ
		int leftmargin = dc.GetDeviceCaps(PHYSICALOFFSETX);
		int toptmargin = dc.GetDeviceCaps(PHYSICALOFFSETY);
		CRect rect(0,0,dc.GetDeviceCaps(PHYSICALWIDTH),dc.GetDeviceCaps(PHYSICALHEIGHT));	

		//�߼�����-x
		//�߼�����-y
		int printx = dc.GetDeviceCaps(LOGPIXELSX);	
		int printy = dc.GetDeviceCaps(LOGPIXELSY);	
		dc.StartDoc("��ӡ����");
		dc.SetBkMode(TRANSPARENT);

		//��ȡ��ǰ��ӡ�豸����Ļ�豸�ķֱ��ʵı�ֵ
		double ratex = (double)(printx)/screenx;
		double ratey = (double)(printy)/screeny;

		//װ��bmp����ͼƬ
		BITMAP back;
		HBITMAP bitmap_back= (HBITMAP)::LoadImage(AfxGetInstanceHandle(),strPath+"\\img\\back.bmp",IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		CBitmap cbmap;
		cbmap.Attach(bitmap_back);
		BITMAP bp;
		cbmap.GetBitmap(&bp);

		//�����Ĵ�ӡ
		CDC memdc;
		memdc.CreateCompatibleDC(&dc);
		memdc.SelectObject(&cbmap);

		//��������
		CFont titlefont,bodyfont;
		bodyfont.CreatePointFont(150,"����",&dc);
		dc.SelectObject(&bodyfont);
		CRect itemrect;

		int i,j,p,iCount=0;
		for(i=0;i<5;i++)
		{
			for(j=0;j<2;j++)
			{
				//�����Ĵ�ӡ
				dc.StretchBlt((j*360+50)*ratex-leftmargin,(10+220*i)*ratey-toptmargin,bp.bmWidth*printx/200,bp.bmHeight*printy/200,&memdc,0,0,bp.bmWidth,bp.bmHeight,SRCCOPY);	
				//���ִ�ӡ
				for(p = 0; p < 3;p++)
				{
					int imove_x = (pointGroup[p].cx +  j*360)*ratex-leftmargin;
					int imove_y = (pointGroup[p].cy + i*220)*ratey-toptmargin;
					itemrect.CopyRect(rect);
					itemrect.DeflateRect(imove_x ,imove_y,0,0);
					dc.DrawText(InfoData[iCount][p],itemrect,DT_LEFT);
				}
				iCount++;
			}
		}
		memdc.DeleteDC();
		cbmap.DeleteObject();
		
		dc.EndDoc();
		titlefont.DeleteObject();
		bodyfont.DeleteObject();
		//��ӡ����
	}
}


void CPrintCardDlg::OnBnClickedButtonAdd()
{
	int icount=m_list.GetItemCount();
	if(icount >= 10)
	{
		MessageBox("�޷�����ӣ����ȵ����ӡ�����������","��ʾ",MB_OK|MB_ICONINFORMATION);
		return;
	}

	CDlg_add dlg(this);
	dlg.DoModal();
}


void CPrintCardDlg::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_list.DeleteAllItems();
	m_Tip.SetWindowTextA(" ÿ�ο��Դ�ӡ10������,�Ѿ�¼��:0/10");
}
