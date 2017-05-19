// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "linkus.h"
#include "GameDlg.h"
#include "afxdialogex.h"
// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序
void CGameDlg::InitBackground(void)
{
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_GAME_BG);

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
}

void CGameDlg::OnPaint()
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
		dc.BitBlt(0, 0, GAMEWND_WIDTH, GAMEWND_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();
	UpdateWindow();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::UpdateWindow(void)
{
	// 调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // 获得窗口大小
	this->GetClientRect(rtClient); // 获得客户区大小
	// 标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// 设置窗口大小
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT +
		nSpanHeight);
	// 设置对话框显示是，在 windows 窗口正中央。
	CenterWindow();
}

void CGameDlg::InitElement(void)
{
	// 获得当前对话框的视频内存
	CClientDC dc(this);
	// 加载 BMP 图片资源
	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\fruit_element.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建与视频内存兼容的内存 DC
	m_dcElement.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcElement.SelectObject(hBmp);
	// 加载掩码 BMP 图片资源
	HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\fruit_mask.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建与视频内存兼容的内存 DC
	m_dcMask.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcMask.SelectObject(hMask);
}

void CGameDlg::UpdateMap(void)
{
	// 计算图片的顶点坐标与图片大小
	//获取行数和列数
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nElemH = 40;
	int nElemW = 40;
	int nLeft = 20;
	int nTop = 50;
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			// 得到图片编号的值
			int nElemVal = m_GameC.GetElement(i, j);
			// 将背景与掩码相或，边保留，图像区域为 1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			// 与元素图片相与，边保留，图像区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcElement, 0, nElemVal * nElemH, SRCAND);
		}
	}
}

void CGameDlg::OnClickedBtnStart()
{
	m_GameC.StartGame();
	UpdateMap();
	Invalidate();
}
