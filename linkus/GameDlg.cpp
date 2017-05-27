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
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;
	m_rtGameRect.left = 45;
	m_rtGameRect.top = 45;
	m_rtGameRect.right = 695;
	m_rtGameRect.bottom = 455;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bFirstPoint = true;
	m_bPlaying = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIME_PROGRESS, m_pro);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_REARRANGE, &CGameDlg::OnClickedBtnRearrange)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PAUSE, &CGameDlg::OnClickedPause)
	ON_BN_CLICKED(IDC_TIP, &CGameDlg::OnClickedTip)
	ON_BN_CLICKED(IDC_SETTING, &CGameDlg::OnClickedSetting)
	ON_BN_CLICKED(IDC_HELP, &CGameDlg::OnClickedHelp)
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
	m_dcBG.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcMem.SelectObject(bmpMain);
	m_dcBG.SelectObject(bmpMain);
	// 调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // 获得窗口大小
	this->GetClientRect(rtClient); // 获得客户区大小
								   // 标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// 设置窗口大小
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT + nSpanHeight);
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
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(FALSE);
	m_nMax = 300;
	m_nStep = 1;
	m_pro.SetRange(0, m_nMax);//进度条范围
	m_pro.SetStep(m_nStep);//进度条步长
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
	int nElemH = m_sizeElem.cy;
	int nElemW = m_sizeElem.cx;
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			// 得到图片编号的值
			int nElemVal = m_GameC.GetElement(i, j);
			if (nElemVal == BLANK) {
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
					&m_dcBG, 0, 0, WHITENESS);
			continue;
			}
			//先刷新背景（为后续重排准备）
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcBG, 0, 0, WHITENESS);
			// 将背景与掩码相或，边保留，图像区域为 1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			// 与元素图片相与，边保留，图像区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcElement, 0, nElemVal * nElemH, SRCAND);
		}
	}
}

void CGameDlg::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);//选定当前画图环境
	CPen pen(PS_SOLID, 2, RGB(255,0,0));//做一支红色粗细为2的笔
	CPen* pOldPen = dc.SelectObject(&pen);
	int left = m_ptGameTop.x + nCol*m_sizeElem.cx;
	int top = m_ptGameTop.y + nRow*m_sizeElem.cy;
	int right = left + m_sizeElem.cx;
	int bottom = top + m_sizeElem.cy;
	dc.MoveTo(left,top);
	dc.LineTo(left,bottom);
	dc.LineTo(right,bottom);
	dc.LineTo(right,top);
	dc.LineTo(left,top);
	dc.SelectObject(pOldPen);
}

//画连接线
void CGameDlg::DrawTipLine(Vertex asvPath[4], int nVexnum) {
	CClientDC ndc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen* pPen = ndc.SelectObject(&penLine);
	ndc.MoveTo(m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	for (int i = 1; i < nVexnum; i++)
	{
		ndc.LineTo(m_ptGameTop.x + asvPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + asvPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	ndc.SelectObject(pPen);
}

void CGameDlg::Rearrange() {
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int** pGameMap = m_GameC.m_pGameMap;
	// 设置种子
	srand((int)time(NULL));
	// 随机任意交换两个数字
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// 随机得到两个坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// 交换两个数值
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}
}

void CGameDlg::OnClickedBtnStart()
{
	if (!m_bPlaying) {  //刚开始游戏
		m_GameC.StartGame();
		UpdateMap();
		Invalidate();
		SetTimer(1, 1000, NULL);//设置进度条更新时钟
		m_bPlaying = true;
		GetDlgItem(IDC_TIME_PROGRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PERCENT)->ShowWindow(SW_SHOW);
	}
	else {
		SetTimer(1, 1000, NULL);//设置进度条更新时钟	
	}
	//关闭开始游戏按钮，打开其他按钮
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(TRUE);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{

	Vertex avPath[4]; int nVexnum;
	// 判断鼠标点击的区域
	if (point.y < m_rtGameRect.top || point.y > m_rtGameRect.bottom || point.x < m_rtGameRect.left || point.x > m_rtGameRect.right)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else{
		if (m_GameC.IsWin()) {  //已经胜利时处理(进度条没有走完)
			m_bPlaying = false;
			GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
			KillTimer(1);
			CWinDlg dlg;
			dlg.DoModal();

		}
		int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
		int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
		if (m_bFirstPoint) // 第一个点
		{
			m_GameC.SetFirstPoint(nRow,nCol);
			if (m_GameC.GetElement(nRow, nCol) != BLANK) DrawTipFrame(nRow, nCol);
		}
		else if(m_GameC.GetElement(nRow,nCol)!=BLANK)// 第二个点
		{
			DrawTipFrame(nRow, nCol);
			m_GameC.SetSecPoint(nRow, nCol);
			// 连子判断
			bool bSuc = m_GameC.Link(avPath, nVexnum);
			if (bSuc == true)
			{
				// 画提示线
				DrawTipLine(avPath, nVexnum);
				Sleep(100);
				// 更新地图
				UpdateMap();
				InvalidateRect(m_rtGameRect,0);
				
			}
			else {
				// 更新地图
				UpdateMap();
				InvalidateRect(m_rtGameRect);
			}
		}
		m_bFirstPoint = !m_bFirstPoint;
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

}

void CGameDlg::OnClickedBtnRearrange()
{
	Rearrange();
	UpdateMap();
	Invalidate();
}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CProgressCtrl*pProgCtrl = (CProgressCtrl*)GetDlgItem(IDC_TIME_PROGRESS);
	int nPrePos = pProgCtrl->StepIt();//取得更新前位置
	if (nPrePos == m_nMax) {
		m_bPlaying = false;
		GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		pProgCtrl->SetPos(0);
		KillTimer(1);
		CLoseDlg dlg;
		dlg.DoModal();
	}
	wchar_t test[10];
	wint_t nPercent = m_nMax - nPrePos;//可修改
	wsprintf(test, L"%d", nPercent);
	GetDlgItem(IDC_PERCENT)->SetWindowText(test);
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::OnClickedPause()
{
	m_bPlaying = true;
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(FALSE);
	KillTimer(1);
}

void CGameDlg::OnClickedTip()
{
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int islink = false;

	for (int i = 0; i < nRows-1; i++)
	{
		if (!islink) {
			for (int j = 0; j < nCols - 1; j++)
			{
				if (!islink) {
					if (m_GameC.GetElement(i, j) != BLANK && m_GameC.GetElement(i, j) == m_GameC.GetElement(i , j+1)) {//当横向可消时
						DrawTipFrame(i, j);
						DrawTipFrame(i, j+1);
						Sleep(100);
						islink = true;
					}
					else if (m_GameC.GetElement(i, j) != BLANK && m_GameC.GetElement(i, j) == m_GameC.GetElement(i+1, j)) {//当纵向可消时
						DrawTipFrame(i, j);
						DrawTipFrame(i+1, j );
						Sleep(100);
						islink = true;
					}
				}
			}
		}
		else {
			UpdateMap();
			Invalidate();
		}
	}
}

void CGameDlg::OnClickedSetting()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGameDlg::OnClickedHelp()
{
	// TODO: 在此添加控件通知处理程序代码
}
