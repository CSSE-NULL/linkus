#pragma once
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include"GameControl.h"
#include"WinDlg.h"
#include "LoseDlg.h"
#include "afxwin.h"
#define GAMEWND_WIDTH 800
#define GAMEWND_HEIGHT 600
// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL,int mode=0);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	int mode; //ģʽ
	int bkg; //����ID
	TCHAR elem[100]; //Ԫ����Դ·��
	CBrush m_brush;
	CFont m_font;
	HICON m_hIcon;
	CDC m_dcMem; //�ڴ� DC
	CDC m_dcBG; // ���� DC
	CDC m_dcElement; // Ԫ���ڴ� DC
	CDC m_dcMask; // �����ڴ� DC
	CPoint m_ptGameTop; //��Ϸ����ʼ�㣨��Ϸ��һ��ͼƬ�Ķ�������,��������ڴ��ڿͻ�����
	CSize m_sizeElem; // Ԫ��ͼƬ�Ĵ�С
	CRect m_rtGameRect; //��Ϸ�����С(������Ϊ��Ϸ���������С�����ǵ����滭���ߣ����ܻᳬ��ͼƬ����һ����Χ)
	CGameControl m_GameC; // ��Ϸ������
	bool m_bFirstPoint; //�ж��Ƿ�Ϊ��һ����
	bool m_bPlaying; // ��Ϸ״̬��ʶ
	bool m_bPause; //��Ϸ��ͣ��ʶ
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	int m_nMax, m_nStep;//��������Χ�Ͳ���
	void  InitBackground();
	void SetLevel(); //���õȼ�
	void SetTheme(); //��������
	DECLARE_MESSAGE_MAP()
public:
	static int level; //�ؿ�
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	HCURSOR OnQueryDragIcon();
	void UpdateWindow();
	void InitElement();
	void UpdateMap();
	void DrawTipLine(Vertex asvPath[4], int nVexnum);
	void DrawTipFrame(int nRow, int nCol);
	void Rearrange();//��������
	afx_msg void OnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedBtnRearrange();
	CProgressCtrl m_pro;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedPause();
	afx_msg void OnClickedTip();
	afx_msg void OnClickedSetting();
	afx_msg void OnClickedHelp();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_level;
};
