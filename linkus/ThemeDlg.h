#pragma once


// CThemeDlg �Ի���

class CThemeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThemeDlg)

public:
	CThemeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThemeDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THEME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedFruit();
	afx_msg void OnClickedAnimal();
};
