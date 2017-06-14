// ThemeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "linkus.h"
#include "linkusDlg.h"
#include "ThemeDlg.h"
#include "afxdialogex.h"


// CThemeDlg 对话框

IMPLEMENT_DYNAMIC(CThemeDlg, CDialogEx)

CThemeDlg::CThemeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THEME_DIALOG, pParent)
{

}

CThemeDlg::~CThemeDlg()
{
}

void CThemeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CThemeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_FRUIT, &CThemeDlg::OnClickedFruit)
	ON_BN_CLICKED(IDC_ANIMAL, &CThemeDlg::OnClickedAnimal)
END_MESSAGE_MAP()


// CThemeDlg 消息处理程序


void CThemeDlg::OnClickedFruit()
{
	ClinkusDlg::theme = 0;
}

void CThemeDlg::OnClickedAnimal(){
	ClinkusDlg::theme = 1;
}
