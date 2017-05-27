// WinDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "linkus.h"
#include "WinDlg.h"
#include "afxdialogex.h"


// CWinDlg �Ի���

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


// CWinDlg ��Ϣ�������


BOOL CWinDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitBackground();
	UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CWinDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // ���Ʊ���ͼƬ
	dc.BitBlt(0, 0, WIN_WIDTH, WIN_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
}

void CWinDlg::UpdateWindow()
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
	MoveWindow(0, 0, WIN_WIDTH + nSpanWidth, WIN_HEIGHT +
		nSpanHeight);
	// ���öԻ�����ʾ�ǣ��� windows ���������롣
	CenterWindow();
}

void CWinDlg::InitBackground() {
	CBitmap bmpwIN;
	bmpwIN.LoadBitmapW(IDB_WIN_BG);

	// ��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);
	// ��������Ƶ�ڴ���ݵ��ڴ� DC
	m_dcMem.CreateCompatibleDC(&dc);
	// ��λͼ��Դѡ�� DC
	m_dcMem.SelectObject(bmpwIN);
	// �������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // ��ô��ڴ�С
	this->GetClientRect(rtClient); // ��ÿͻ�����С
								   // ����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// ���ô��ڴ�С
	MoveWindow(0, 0, WIN_WIDTH + nSpanWidth, WIN_HEIGHT + nSpanHeight);
}

