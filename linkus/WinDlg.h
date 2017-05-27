#pragma once
#define WIN_WIDTH 300
#define WIN_HEIGHT 200

// CWinDlg 对话框

class CWinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWinDlg)

public:
	CWinDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWinDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDC m_dcMem; //内存 DC
	void UpdateWindow(); //更新窗口
	void InitBackground(); //初始化背景
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
};
