#include "stdafx.h"
#include "GameControl.h"
int CGameControl::s_nRows = 10;
int CGameControl::s_nCols = 16;
int CGameControl::s_nPicNum = 20;


CGameControl::CGameControl()
{
	m_pGameMap = new int*[10];
	for (int i = 0; i < 10; i++) m_pGameMap[i] = new int[16];
}

CGameControl::~CGameControl()
{
}

void CGameControl::StartGame() {
	m_pGameMap=m_GameLogic.InitMap();
}

int CGameControl::GetElement(int nRow, int nCol) {
	return m_pGameMap[nRow][nCol];
}

bool CGameControl::Link(Vertex avPath[4], int &nVexnum)
{
	// 判断是否同一张图片
	if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col)
	{
		return false;
	}
	// 判断图片是否相同
	if (m_pGameMap[m_svSelFst.row][m_svSelFst.col] != m_pGameMap[m_svSelSec.row][m_svSelSec.col])
	{
		return false;
	}
	// 判断是否连通
	if (m_GameLogic.IsLink(m_pGameMap, m_svSelFst, m_svSelSec))
	{
		// 消子
		m_GameLogic.Clear(m_pGameMap, m_svSelFst, m_svSelSec);
		// 返回路径顶点
		nVexnum = m_GameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}

void CGameControl::SetFirstPoint(int nRow, int nCol) {
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
	m_svSelFst.info = GetElement(nRow,nCol);
}

void CGameControl::SetSecPoint(int nRow, int nCol) {
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
	m_svSelSec.info = GetElement(nRow, nCol);
}