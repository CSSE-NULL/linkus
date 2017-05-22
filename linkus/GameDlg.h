#pragma once
#include"GameControl.h"
#define GAMEWND_WIDTH 800
#define GAMEWND_HEIGHT 600
// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	HICON m_hIcon;
	CDC m_dcMem; //�ڴ� DC
	CDC m_dcBG; // ���� DC
	CDC m_dcElement; // Ԫ���ڴ� DC
	CDC m_dcMask; // �����ڴ� DC
	CPoint m_ptGameTop; //��Ϸ����ʼ�㣨��Ϸ��һ��ͼƬ�Ķ�������,��������ڴ��ڿͻ�����
	CSize m_sizeElem; // Ԫ��ͼƬ�Ĵ�С
	CRect m_rtGameRect; //��Ϸ�����С(������Ϊ��Ϸ���������С�����ǵ����滭���ߣ����ܻᳬ��ͼƬ����һ����Χ)
	CGameControl m_GameC; // ��Ϸ������
	bool m_bFirstPoint;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void  InitBackground();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	HCURSOR OnQueryDragIcon();
	void UpdateWindow();
	void InitElement();
	void UpdateMap();
	void DrawTipLine(Vertex asvPath[4], int nVexnum);
	void DrawTipFrame(int nRow, int nCol);
	afx_msg void OnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
