// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "linkus.h"
#include "GameDlg.h"
#include"GameControl.h"
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
	ON_WM_LBUTTONUP()
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
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
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

void CGameDlg::OnClickedBtnStart()
{
	m_GameC.StartGame();
	UpdateMap();
	Invalidate();
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{

	Vertex avPath[4]; int nVexnum;

	// �ж������������
	if (point.y < m_rtGameRect.top || point.y > m_rtGameRect.bottom || point.x < m_rtGameRect.left || point.x > m_rtGameRect.right)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else {
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
