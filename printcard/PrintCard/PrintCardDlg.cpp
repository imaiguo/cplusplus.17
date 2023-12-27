
// PrintCardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PrintCard.h"
#include "PrintCardDlg.h"
#include "afxdialogex.h"
#include "Dlg_add.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPrintCardDlg 对话框


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


// CPrintCardDlg 消息处理程序

BOOL CPrintCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	char* pListName[][2] = {{"序号", "40"},{"姓名", "100"},{"性别", "50"},{"区排", "155"},{"end","end"}};
	for (int i = 0; strcmp(pListName[i][0],"end") != 0; i++)
	{
		m_list.InsertColumn (i, pListName[i][0], LVCFMT_LEFT, atoi(pListName[i][1]));
	}

	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT);

	m_Tip.SetWindowTextA(" 每次可以打印10个牌子,已经录入:0/10");
	m_list.MoveWindow(0,0,350,300);
	MoveWindow(0,0,350,400);
	CenterWindow();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPrintCardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPrintCardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPrintCardDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CPrintCardDlg::OnBnClickedButtonPrint()
{
	//获取当前的程序运行路径
	char buf[256]={0};
	GetModuleFileName(0,buf,256);
	CString strPath=buf;
	int pos=strPath.ReverseFind('\\');
	strPath=strPath.Left(pos);

	CSize	pointGroup[3];
	int	ipoint[3][2] = {
		{::GetPrivateProfileInt("参数配置","姓名x",0,strPath+"\\config.ini"),::GetPrivateProfileInt("参数配置","姓名y",0,strPath+"\\config.ini")},              
		{::GetPrivateProfileInt("参数配置","性别x",0,strPath+"\\config.ini"),::GetPrivateProfileInt("参数配置","性别y",0,strPath+"\\config.ini")},             
		{::GetPrivateProfileInt("参数配置","区排x",0,strPath+"\\config.ini"),::GetPrivateProfileInt("参数配置","区排y",0,strPath+"\\config.ini")}           
		};

	for(int i = 0;i< 3;i++)
	{
		pointGroup[i].cx = ipoint[i][0];
		pointGroup[i].cy = ipoint[i][1];
	}


	//每英寸水平逻辑像素数
	CDC* pDC = GetDC();
	int screenx = pDC->GetDeviceCaps(LOGPIXELSX);
	int screeny = pDC->GetDeviceCaps(LOGPIXELSY);

	//要打印的数据
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
		//获取当前打印机的页边距,防止打印的背景图片和文字错位
		int leftmargin = dc.GetDeviceCaps(PHYSICALOFFSETX);
		int toptmargin = dc.GetDeviceCaps(PHYSICALOFFSETY);
		CRect rect(0,0,dc.GetDeviceCaps(PHYSICALWIDTH),dc.GetDeviceCaps(PHYSICALHEIGHT));	

		//逻辑像素-x
		//逻辑像素-y
		int printx = dc.GetDeviceCaps(LOGPIXELSX);	
		int printy = dc.GetDeviceCaps(LOGPIXELSY);	
		dc.StartDoc("打印胸牌");
		dc.SetBkMode(TRANSPARENT);

		//获取当前打印设备和屏幕设备的分辨率的比值
		double ratex = (double)(printx)/screenx;
		double ratey = (double)(printy)/screeny;

		//装载bmp背景图片
		BITMAP back;
		HBITMAP bitmap_back= (HBITMAP)::LoadImage(AfxGetInstanceHandle(),strPath+"\\img\\back.bmp",IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		CBitmap cbmap;
		cbmap.Attach(bitmap_back);
		BITMAP bp;
		cbmap.GetBitmap(&bp);

		//背景的打印
		CDC memdc;
		memdc.CreateCompatibleDC(&dc);
		memdc.SelectObject(&cbmap);

		//设置字体
		CFont titlefont,bodyfont;
		bodyfont.CreatePointFont(150,"宋体",&dc);
		dc.SelectObject(&bodyfont);
		CRect itemrect;

		int i,j,p,iCount=0;
		for(i=0;i<5;i++)
		{
			for(j=0;j<2;j++)
			{
				//背景的打印
				dc.StretchBlt((j*360+50)*ratex-leftmargin,(10+220*i)*ratey-toptmargin,bp.bmWidth*printx/200,bp.bmHeight*printy/200,&memdc,0,0,bp.bmWidth,bp.bmHeight,SRCCOPY);	
				//汉字打印
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
		//打印结束
	}
}


void CPrintCardDlg::OnBnClickedButtonAdd()
{
	int icount=m_list.GetItemCount();
	if(icount >= 10)
	{
		MessageBox("无法再添加，请先点击打印后做清除操作","提示",MB_OK|MB_ICONINFORMATION);
		return;
	}

	CDlg_add dlg(this);
	dlg.DoModal();
}


void CPrintCardDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	m_Tip.SetWindowTextA(" 每次可以打印10个牌子,已经录入:0/10");
}
