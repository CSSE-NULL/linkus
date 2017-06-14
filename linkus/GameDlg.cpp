// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "linkus.h"
#include "linkusDlg.h"
#include "GameDlg.h"
#include "afxdialogex.h"
// CGameDlg 对话框
int CGameDlg::level = 1;

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent,int md)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	mode = md;
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
	level = 1;
	m_bPause = false;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIME_PROGRESS, m_pro);
	DDX_Control(pDX, IDC_LEVEL, m_level);
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
	ON_WM_CTLCOLOR(IDC_LEVEL,&CGameDlg::OnCtlColor)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序
void CGameDlg::InitBackground(void)
{
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(bkg);

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
	PlaySound(L"E:\\Algorithms\\算法实验\\linkus\\linkus\\res\\bkg.wav", NULL, SND_FILENAME | SND_ASYNC);

	switch (mode)//设置不同模式下的标题
	{
	case 0:
		this->SetWindowText(_T("欢乐连连看——基本模式"));
		break;
	case 1:
		this->SetWindowText(_T("欢乐连连看——休闲模式"));
		break;
	case 2:
		this->SetWindowText(_T("欢乐连连看——关卡模式"));
		break;
	default:
		break;
	}
	SetTheme();//设置主题
	m_GameC.s_nPicNum = 20;//以下三条设置目的是退出关卡模式后不影响其他模式
	m_GameC.s_nRows = 10;
	m_GameC.s_nCols = 16;
	m_font.CreatePointFont(150, L"华文行楷");//设置字体
	m_brush.CreateSolidBrush(RGB(0, 126, 202));
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LEVEL)->ShowWindow(SW_HIDE);//隐藏关卡显示
	m_nMax = 300;
	m_nStep = 1;
	m_pro.SetRange(0, m_nMax);//进度条范围
	m_pro.SetStep(m_nStep);//进度条步长
	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();
	UpdateWindow();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, TRUE);		// 设置小图标

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
	HANDLE hBmp = ::LoadImageW(NULL, elem,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建与视频内存兼容的内存 DC
	m_dcElement.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcElement.SelectObject(hBmp);
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
	if (!m_bPlaying && !m_bPause) {  //刚开始游戏时
		if (mode == 2) {
			SetLevel();
		}
		m_GameC.StartGame();
		UpdateMap();
		Invalidate();
		SetTimer(1, 1000, NULL);//设置进度条更新时钟
		m_bPlaying = true;
		if (mode != 1) {
			GetDlgItem(IDC_TIME_PROGRESS)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_PERCENT)->ShowWindow(SW_SHOW);
		}
		else{
			GetDlgItem(IDC_TIME_PROGRESS)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PERCENT)->ShowWindow(SW_HIDE);
		}
		}
		
	else { //当是从暂停游戏恢复时
		SetTimer(1, 1000, NULL);//设置进度条更新时钟
		m_bPause = false;
		m_bPlaying = true;
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
	//当游戏正在进行中（未暂停或结束）
	if (m_bPlaying) {
	// 判断鼠标点击的区域
	if (point.y < m_rtGameRect.top || point.y > m_rtGameRect.bottom || point.x < m_rtGameRect.left || point.x > m_rtGameRect.right)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else{
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
				if (m_GameC.IsWin() ) {  //已经胜利时处理(进度条没有走完)
					GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
					m_pro.SetPos(0);
					KillTimer(1);
					if (mode == 2) {  //当为关卡模式时
						m_bPlaying = true;//游戏未结束，进入下一关
						level++;
						SetLevel();
						GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
						UpdateMap();
						InvalidateRect(m_rtGameRect, 0);
					}
					else {//当为普通模式时
						m_bPlaying = false;
						CWinDlg dlg;
						dlg.DoModal();
					}
				}
			}
				// 更新地图
				UpdateMap();
				InvalidateRect(m_rtGameRect);
		}
		m_bFirstPoint = !m_bFirstPoint;
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
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
	m_bPlaying = false;
	m_bPause = true;
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(FALSE);
	KillTimer(1);
}

//响应提示按钮
void CGameDlg::OnClickedTip()
{
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int islink = false;

	for (int i = 0; i < nRows-1; i++)
	{
		if (!islink) { //当未出现相邻可相连的情况时，持续搜索直至找完所有图片
			for (int j = 0; j < nCols - 1; j++)
			{
				if (!islink) {
					//当横向相邻时，画提示框并置变量为真以结束循环
					if (m_GameC.GetElement(i, j) != BLANK && m_GameC.GetElement(i, j) == m_GameC.GetElement(i , j+1)) {//当横向可消时
						DrawTipFrame(i, j);
						DrawTipFrame(i, j+1);
						Sleep(100);
						islink = true;
					}
					//当纵向相邻时，画提示框并置变量为真以结束循环
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
	MessageBox(_T("无需额外设置"),_T("设置"),MB_OK);
}

void CGameDlg::OnClickedHelp()
{
	MessageBox(_T("点击两张同样的图片，能用三条线以下连接均可消除（边界除外）"),_T("帮助"), MB_OK);
}

HBRUSH CGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (m_level.m_hWnd == pWnd->m_hWnd)
	{
		pDC->SetBkColor(RGB(0, 126, 202));
		pDC->SelectObject(&m_font);
		return m_brush;
	}
	return hbr;
}

//设置相关关卡的内容信息
void CGameDlg::SetLevel() {
	if (level <= 7) {
		if (level % 2 != 0) {//当level为奇数时，将行列设置为偶数
			CGameControl::s_nRows = 3 + level;
			CGameControl::s_nCols = 9 + level;
		}
		else { //当level为偶数时，将行列设置为偶数以防无法形成游戏界面（成对图片个数不为整数）
			CGameControl::s_nRows = 4 + level;
			CGameControl::s_nCols = 10 + level;
		}


	for (int i = level + 4; i <= 20; i++) {
		if ((CGameControl::s_nRows*CGameControl::s_nCols) % (i * 2) == 0) {
			m_GameC.s_nPicNum = i;
			wchar_t test[10];
			wsprintf(test, L"第%d关", level);
			GetDlgItem(IDC_LEVEL)->SetWindowText(test);
			GetDlgItem(IDC_LEVEL)->ShowWindow(SW_SHOW);
			m_nMax = 60 + 10 * level;
			m_pro.SetRange(0, m_nMax);//进度条范围
			break;
		}

	}
	m_GameC.StartGame();
	UpdateMap();
	Invalidate();
	SetTimer(1, 1000, NULL);//设置进度条更新时钟
	m_bPlaying = true;
	}
	else {
		MessageBox(_T("恭喜通关！"),_T("通关"));
		m_bPlaying = false;
	}


}


//设置主题
void CGameDlg::SetTheme() {
	int theme = ClinkusDlg::theme;
	switch (theme)
	{
	case 0:
	{
		wsprintf(elem,_T("theme\\picture\\fruit_element.bmp"));
		bkg = IDB_GAME_BG;
		break;
	}
	case 1:
	{
		wsprintf(elem, _T("theme\\picture\\animal_element.bmp"));
		bkg = IDB_GAME2_BG;
		break;
	}
	default:
		break;
	}
}