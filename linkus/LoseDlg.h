#pragma once
#define WIN_WIDTH 300
#define WIN_HEIGHT 200

// CLoseDlg 对话框

class CLoseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoseDlg)

public:
	CLoseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoseDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOSE_DIALOG };
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
};
