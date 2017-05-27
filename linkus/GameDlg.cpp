// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "linkus.h"
#include "GameDlg.h"
#include "afxdialogex.h"
// CGameDlg �Ի���

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


// CGameDlg ��Ϣ�������
void CGameDlg::InitBackground(void)
{
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_GAME_BG);

	// ��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcBG.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcMem.SelectObject(bmpMain);
	m_dcBG.SelectObject(bmpMain);
	// �������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // ��ô��ڴ�С
	this->GetClientRect(rtClient); // ��ÿͻ�����С
								   // ����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// ���ô��ڴ�С
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT + nSpanHeight);
}

void CGameDlg::OnPaint()
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
		// ���� CPaintDC ����
		CPaintDC dc(this);
		// ���Ʊ���ͼƬ
		dc.BitBlt(0, 0, GAMEWND_WIDTH, GAMEWND_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	m_pro.SetRange(0, m_nMax);//��������Χ
	m_pro.SetStep(m_nStep);//����������
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackground();
	InitElement();
	UpdateWindow();
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CGameDlg::UpdateWindow(void)
{
	// �������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // ��ô��ڴ�С
	this->GetClientRect(rtClient); // ��ÿͻ�����С
	// ����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// ���ô��ڴ�С
	MoveWindow(0, 0, GAMEWND_WIDTH + nSpanWidth, GAMEWND_HEIGHT +
		nSpanHeight);
	// ���öԻ�����ʾ�ǣ��� windows ���������롣
	CenterWindow();
}

void CGameDlg::InitElement(void)
{
	// ��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);
	// ���� BMP ͼƬ��Դ
	HANDLE hBmp = ::LoadImageW(NULL, _T("theme\\picture\\fruit_element.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC
	m_dcElement.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcElement.SelectObject(hBmp);
	// �������� BMP ͼƬ��Դ
	HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\fruit_mask.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC
	m_dcMask.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcMask.SelectObject(hMask);
}

void CGameDlg::UpdateMap(void)
{
	// ����ͼƬ�Ķ���������ͼƬ��С
	//��ȡ����������
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
			// �õ�ͼƬ��ŵ�ֵ
			int nElemVal = m_GameC.GetElement(i, j);
			if (nElemVal == BLANK) {
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
					&m_dcBG, 0, 0, WHITENESS);
			continue;
			}
			//��ˢ�±�����Ϊ��������׼����
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcBG, 0, 0, WHITENESS);
			// ��������������򣬱߱�����ͼ������Ϊ 1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			// ��Ԫ��ͼƬ���룬�߱�����ͼ������ΪԪ��ͼƬ
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcElement, 0, nElemVal * nElemH, SRCAND);
		}
	}
}

void CGameDlg::DrawTipFrame(int nRow, int nCol) {
	CClientDC dc(this);//ѡ����ǰ��ͼ����
	CPen pen(PS_SOLID, 2, RGB(255,0,0));//��һ֧��ɫ��ϸΪ2�ı�
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

//��������
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
	// ��������
	srand((int)time(NULL));
	// ������⽻����������
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// ����õ���������
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// ����������ֵ
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}
}

void CGameDlg::OnClickedBtnStart()
{
	if (!m_bPlaying) {  //�տ�ʼ��Ϸ
		m_GameC.StartGame();
		UpdateMap();
		Invalidate();
		SetTimer(1, 1000, NULL);//���ý���������ʱ��
		m_bPlaying = true;
		GetDlgItem(IDC_TIME_PROGRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PERCENT)->ShowWindow(SW_SHOW);
	}
	else {
		SetTimer(1, 1000, NULL);//���ý���������ʱ��	
	}
	//�رտ�ʼ��Ϸ��ť����������ť
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_TIP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(TRUE);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{

	Vertex avPath[4]; int nVexnum;
	// �ж������������
	if (point.y < m_rtGameRect.top || point.y > m_rtGameRect.bottom || point.x < m_rtGameRect.left || point.x > m_rtGameRect.right)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else{
		if (m_GameC.IsWin()) {  //�Ѿ�ʤ��ʱ����(������û������)
			m_bPlaying = false;
			GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
			KillTimer(1);
			CWinDlg dlg;
			dlg.DoModal();

		}
		int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
		int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
		if (m_bFirstPoint) // ��һ����
		{
			m_GameC.SetFirstPoint(nRow,nCol);
			if (m_GameC.GetElement(nRow, nCol) != BLANK) DrawTipFrame(nRow, nCol);
		}
		else if(m_GameC.GetElement(nRow,nCol)!=BLANK)// �ڶ�����
		{
			DrawTipFrame(nRow, nCol);
			m_GameC.SetSecPoint(nRow, nCol);
			// �����ж�
			bool bSuc = m_GameC.Link(avPath, nVexnum);
			if (bSuc == true)
			{
				// ����ʾ��
				DrawTipLine(avPath, nVexnum);
				Sleep(100);
				// ���µ�ͼ
				UpdateMap();
				InvalidateRect(m_rtGameRect,0);
				
			}
			else {
				// ���µ�ͼ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CProgressCtrl*pProgCtrl = (CProgressCtrl*)GetDlgItem(IDC_TIME_PROGRESS);
	int nPrePos = pProgCtrl->StepIt();//ȡ�ø���ǰλ��
	if (nPrePos == m_nMax) {
		m_bPlaying = false;
		GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		pProgCtrl->SetPos(0);
		KillTimer(1);
		CLoseDlg dlg;
		dlg.DoModal();
	}
	wchar_t test[10];
	wint_t nPercent = m_nMax - nPrePos;//���޸�
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
					if (m_GameC.GetElement(i, j) != BLANK && m_GameC.GetElement(i, j) == m_GameC.GetElement(i , j+1)) {//���������ʱ
						DrawTipFrame(i, j);
						DrawTipFrame(i, j+1);
						Sleep(100);
						islink = true;
					}
					else if (m_GameC.GetElement(i, j) != BLANK && m_GameC.GetElement(i, j) == m_GameC.GetElement(i+1, j)) {//���������ʱ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CGameDlg::OnClickedHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
