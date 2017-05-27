// LoseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "linkus.h"
#include "LoseDlg.h"
#include "afxdialogex.h"


// CLoseDlg 对话框

IMPLEMENT_DYNAMIC(CLoseDlg, CDialogEx)

CLoseDlg::CLoseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOSE_DIALOG, pParent)
{

}

CLoseDlg::~CLoseDlg()
{
}

void CLoseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoseDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLoseDlg 消息处理程序


BOOL CLoseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitBackground();
	UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoseDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0, 0, WIN_WIDTH, WIN_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
}

void CLoseDlg::UpdateWindow()
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

void CLoseDlg::InitBackground() {
	CBitmap bmpwIN;
	bmpwIN.LoadBitmapW(IDB_LOSE_BG);

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
