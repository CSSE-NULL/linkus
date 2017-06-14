
// linkusDlg.h : 头文件
//

#pragma once
// ClinkusDlg 对话框
class ClinkusDlg : public CDialogEx
{
// 构造
public:
	static int theme; //设置主题
	ClinkusDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINKUS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CDC m_dcMem;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void InitBackground();
	

public:
//	afx_msg void OnBnClicked_BTN_RELAX();
	afx_msg void OnClickedBtnBasic();
	afx_msg void OnClickedBtnRelax();
	afx_msg void OnClickedBtnLevel();
	afx_msg void OnClickedBtnHelp();
	afx_msg void OnClickedBtnRank();
	afx_msg void OnClickedBtnSetting();
};
