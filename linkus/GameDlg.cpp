// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "linkus.h"
#include "linkusDlg.h"
#include "GameDlg.h"
#include "afxdialogex.h"
// CGameDlg �Ի���
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


// CGameDlg ��Ϣ�������
void CGameDlg::InitBackground(void)
{
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(bkg);

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
	PlaySound(L"E:\\Algorithms\\�㷨ʵ��\\linkus\\linkus\\res\\bkg.wav", NULL, SND_FILENAME | SND_ASYNC);

	switch (mode)//���ò�ͬģʽ�µı���
	{
	case 0:
		this->SetWindowText(_T("������������������ģʽ"));
		break;
	case 1:
		this->SetWindowText(_T("������������������ģʽ"));
		break;
	case 2:
		this->SetWindowText(_T("���������������ؿ�ģʽ"));
		break;
	default:
		break;
	}
	SetTheme();//��������
	m_GameC.s_nPicNum = 20;//������������Ŀ�����˳��ؿ�ģʽ��Ӱ������ģʽ
	m_GameC.s_nRows = 10;
	m_GameC.s_nCols = 16;
	m_font.CreatePointFont(150, L"�����п�");//��������
	m_brush.CreateSolidBrush(RGB(0, 126, 202));
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LEVEL)->ShowWindow(SW_HIDE);//���عؿ���ʾ
	m_nMax = 300;
	m_nStep = 1;
	m_pro.SetRange(0, m_nMax);//��������Χ
	m_pro.SetStep(m_nStep);//����������
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackground();
	InitElement();
	UpdateWindow();
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, TRUE);		// ����Сͼ��

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
	HANDLE hBmp = ::LoadImageW(NULL, elem,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC
	m_dcElement.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcElement.SelectObject(hBmp);
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
	if (!m_bPlaying && !m_bPause) {  //�տ�ʼ��Ϸʱ
		if (mode == 2) {
			SetLevel();
		}
		m_GameC.StartGame();
		UpdateMap();
		Invalidate();
		SetTimer(1, 1000, NULL);//���ý���������ʱ��
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
		
	else { //���Ǵ���ͣ��Ϸ�ָ�ʱ
		SetTimer(1, 1000, NULL);//���ý���������ʱ��
		m_bPause = false;
		m_bPlaying = true;
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
	//����Ϸ���ڽ����У�δ��ͣ�������
	if (m_bPlaying) {
	// �ж������������
	if (point.y < m_rtGameRect.top || point.y > m_rtGameRect.bottom || point.x < m_rtGameRect.left || point.x > m_rtGameRect.right)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	else{
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
				if (m_GameC.IsWin() ) {  //�Ѿ�ʤ��ʱ����(������û������)
					GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
					m_pro.SetPos(0);
					KillTimer(1);
					if (mode == 2) {  //��Ϊ�ؿ�ģʽʱ
						m_bPlaying = true;//��Ϸδ������������һ��
						level++;
						SetLevel();
						GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
						UpdateMap();
						InvalidateRect(m_rtGameRect, 0);
					}
					else {//��Ϊ��ͨģʽʱ
						m_bPlaying = false;
						CWinDlg dlg;
						dlg.DoModal();
					}
				}
			}
				// ���µ�ͼ
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
	m_bPlaying = false;
	m_bPause = true;
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TIP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(FALSE);
	KillTimer(1);
}

//��Ӧ��ʾ��ť
void CGameDlg::OnClickedTip()
{
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int islink = false;

	for (int i = 0; i < nRows-1; i++)
	{
		if (!islink) { //��δ�������ڿ����������ʱ����������ֱ����������ͼƬ
			for (int j = 0; j < nCols - 1; j++)
			{
				if (!islink) {
					//����������ʱ������ʾ���ñ���Ϊ���Խ���ѭ��
					if (m_GameC.GetElement(i, j) != BLANK && m_GameC.GetElement(i, j) == m_GameC.GetElement(i , j+1)) {//���������ʱ
						DrawTipFrame(i, j);
						DrawTipFrame(i, j+1);
						Sleep(100);
						islink = true;
					}
					//����������ʱ������ʾ���ñ���Ϊ���Խ���ѭ��
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
	MessageBox(_T("�����������"),_T("����"),MB_OK);
}

void CGameDlg::OnClickedHelp()
{
	MessageBox(_T("�������ͬ����ͼƬ�������������������Ӿ����������߽���⣩"),_T("����"), MB_OK);
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

//������عؿ���������Ϣ
void CGameDlg::SetLevel() {
	if (level <= 7) {
		if (level % 2 != 0) {//��levelΪ����ʱ������������Ϊż��
			CGameControl::s_nRows = 3 + level;
			CGameControl::s_nCols = 9 + level;
		}
		else { //��levelΪż��ʱ������������Ϊż���Է��޷��γ���Ϸ���棨�ɶ�ͼƬ������Ϊ������
			CGameControl::s_nRows = 4 + level;
			CGameControl::s_nCols = 10 + level;
		}


	for (int i = level + 4; i <= 20; i++) {
		if ((CGameControl::s_nRows*CGameControl::s_nCols) % (i * 2) == 0) {
			m_GameC.s_nPicNum = i;
			wchar_t test[10];
			wsprintf(test, L"��%d��", level);
			GetDlgItem(IDC_LEVEL)->SetWindowText(test);
			GetDlgItem(IDC_LEVEL)->ShowWindow(SW_SHOW);
			m_nMax = 60 + 10 * level;
			m_pro.SetRange(0, m_nMax);//��������Χ
			break;
		}

	}
	m_GameC.StartGame();
	UpdateMap();
	Invalidate();
	SetTimer(1, 1000, NULL);//���ý���������ʱ��
	m_bPlaying = true;
	}
	else {
		MessageBox(_T("��ϲͨ�أ�"),_T("ͨ��"));
		m_bPlaying = false;
	}


}


//��������
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