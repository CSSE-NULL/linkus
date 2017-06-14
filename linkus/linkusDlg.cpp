
// linkusDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "linkus.h"
#include "linkusDlg.h"
#include "afxdialogex.h"
#include "GameDlg.h"
#include "ThemeDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int ClinkusDlg::theme = 0; //默认主题为水果

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ClinkusDlg 对话框



ClinkusDlg::ClinkusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LINKUS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClinkusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ClinkusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BTN_RELAX, &ClinkusDlg::OnBnClicked_BTN_RELAX)
	ON_BN_CLICKED(IDC_BTN_BASIC, &ClinkusDlg::OnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_RELAX, &ClinkusDlg::OnClickedBtnRelax)
	ON_BN_CLICKED(IDC_BTN_LEVEL, &ClinkusDlg::OnClickedBtnLevel)
	ON_BN_CLICKED(IDC_BTN_HELP, &ClinkusDlg::OnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_RANK, &ClinkusDlg::OnClickedBtnRank)
	ON_BN_CLICKED(IDC_BTN_SETTING, &ClinkusDlg::OnClickedBtnSetting)
END_MESSAGE_MAP()


// ClinkusDlg 消息处理程序

BOOL ClinkusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
		InitBackground();
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ClinkusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ClinkusDlg::OnPaint()
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
		// 创建 CPaintDC 对象
		CPaintDC dc(this);
		// 绘制背景图片
		dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR ClinkusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ClinkusDlg::InitBackground(void)
{
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_MAIN_BG);

	// 获得当前对话框的视频内存
	CClientDC dc(this);
	// 创建与视频内存兼容的内存 DC
	m_dcMem.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcMem.SelectObject(bmpMain);

	// 调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // 获得窗口大小
	this->GetClientRect(rtClient); // 获得客户区大小
								   // 标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// 设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	CenterWindow();
}

//void ClinkusDlg::OnBnClicked_BTN_RELAX()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void ClinkusDlg::OnClickedBtnBasic()
{
	
	CGameDlg dlg;
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}



void ClinkusDlg::OnClickedBtnRelax()
{
;
	CGameDlg dlg(NULL,1);
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}


void ClinkusDlg::OnClickedBtnLevel()
{
	CGameDlg dlg(NULL, 2);
	ShowWindow(SW_HIDE);
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}

void ClinkusDlg::OnClickedBtnHelp()
{
	MessageBox(_T("关于三种模式：\
一. 基本模式：时限300秒，规定时间内完成即可胜利 \
二. 休闲模式：无时间限制\
三, 关卡模式: 总共七关，每一关的图片数量和种类比前一关多，时间也比前一关多10秒"
), _T("帮助"), MB_OK);
}


void ClinkusDlg::OnClickedBtnRank()
{
	MessageBox(_T("你是第一，不用看了^_^"), _T("排行榜"), MB_OK);
}


void ClinkusDlg::OnClickedBtnSetting()
{
	CThemeDlg dlg;
	dlg.DoModal();
}
