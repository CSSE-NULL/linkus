#pragma once
#include"GameControl.h"
#include"WinDlg.h"
#include"GameLogic.h"
#include "LoseDlg.h"
#define GAMEWND_WIDTH 800
#define GAMEWND_HEIGHT 600
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	HICON m_hIcon;
	CDC m_dcMem; //内存 DC
	CDC m_dcBG; // 背景 DC
	CDC m_dcElement; // 元素内存 DC
	CDC m_dcMask; // 掩码内存 DC
	CPoint m_ptGameTop; //游戏区起始点（游戏第一张图片的顶点坐标,坐标相对于窗口客户区）
	CSize m_sizeElem; // 元素图片的大小
	CRect m_rtGameRect; //游戏区域大小(该区域为游戏更新区域大小，考虑到后面画的线，可能会超出图片区域一定范围)
	CGameControl m_GameC; // 游戏控制类
	bool m_bFirstPoint; //判断是否为第一个点
	bool m_bPlaying; // 游戏状态标识
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	int m_nMax, m_nStep;//进度条范围和步长
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
	void Rearrange();//进行重排
	afx_msg void OnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedBtnRearrange();
	CProgressCtrl m_pro;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedPercent();
	afx_msg void OnClickedPause();
	afx_msg void OnClickedTip();
	afx_msg void OnClickedSetting();
	afx_msg void OnClickedHelp();
};
