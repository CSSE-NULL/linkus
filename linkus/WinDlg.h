#pragma once
#define WIN_WIDTH 300
#define WIN_HEIGHT 200

// CWinDlg �Ի���

class CWinDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWinDlg)

public:
	CWinDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWinDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CDC m_dcMem; //�ڴ� DC
	void UpdateWindow(); //���´���
	void InitBackground(); //��ʼ������
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
};
