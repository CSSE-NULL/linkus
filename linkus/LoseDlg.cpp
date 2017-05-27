// LoseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "linkus.h"
#include "LoseDlg.h"
#include "afxdialogex.h"


// CLoseDlg �Ի���

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


// CLoseDlg ��Ϣ�������


BOOL CLoseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitBackground();
	UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CLoseDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.BitBlt(0, 0, WIN_WIDTH, WIN_HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
}

void CLoseDlg::UpdateWindow()
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

void CLoseDlg::InitBackground() {
	CBitmap bmpwIN;
	bmpwIN.LoadBitmapW(IDB_LOSE_BG);

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
