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


// CGameDlg ��Ϣ�������
void CGameDlg::InitBackground(void)
{
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_GAME_BG);

	// ��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC
	m_dcMem.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcMem.SelectObject(bmpMain);

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
	int nElemH = 40;
	int nElemW = 40;
	int nLeft = 20;
	int nTop = 50;
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			// �õ�ͼƬ��ŵ�ֵ
			int nElemVal = m_GameC.GetElement(i, j);
			// ��������������򣬱߱�����ͼ������Ϊ 1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
			// ��Ԫ��ͼƬ���룬�߱�����ͼ������ΪԪ��ͼƬ
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
