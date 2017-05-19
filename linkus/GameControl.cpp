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