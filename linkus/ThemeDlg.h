#pragma once


// CThemeDlg 对话框

class CThemeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThemeDlg)

public:
	CThemeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CThemeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THEME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedFruit();
	afx_msg void OnClickedAnimal();
};
