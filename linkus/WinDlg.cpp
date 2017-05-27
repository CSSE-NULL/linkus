// WinDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "linkus.h"
#include "WinDlg.h"
#include "afxdialogex.h"


// CWinDlg 对话框

IMPLEMENT_DYNAMIC(CWinDlg, CDialogEx)

CWinDlg::CWinDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WIN_DIALOG, pParent)
{

}

CWinDlg::~CWinDlg()
{
}

void CWinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWinDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CWinDlg 消息处理程序


BOOL CWinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitBackground();
	UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CWinDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // 绘制背景图片
	dc.BitBlt(0, 0, WIN_WIDTH, WIN_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
}

void CWinDlg::UpdateWindow()
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
	MoveWindow(0, 0, WIN_WIDTH + nSpanWidth, WIN_HEIGHT +
		nSpanHeight);
	// 设置对话框显示是，在 windows 窗口正中央。
	CenterWindow();
}

void CWinDlg::InitBackground() {
	CBitmap bmpwIN;
	bmpwIN.LoadBitmapW(IDB_WIN_BG);

	// 获得当前对话框的视频内存
	CClientDC dc(this);
	// 创建与视频内存兼容的内存 DC
	m_dcMem.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcMem.SelectObject(bmpwIN);
	// 调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // 获得窗口大小
	this->GetClientRect(rtClient); // 获得客户区大小
								   // 标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// 设置窗口大小
	MoveWindow(0, 0, WIN_WIDTH + nSpanWidth, WIN_HEIGHT + nSpanHeight);
}

