#pragma once
#define WIN_WIDTH 300
#define WIN_HEIGHT 200

// CLoseDlg �Ի���

class CLoseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoseDlg)

public:
	CLoseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoseDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOSE_DIALOG };
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
};
