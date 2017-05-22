#include "stdafx.h"
#include "GameLogic.h"
#include "GameControl.h"

CGameLogic::CGameLogic()
{
	m_nVexNum = 0;

}


CGameLogic::~CGameLogic()
{
}

int** CGameLogic::InitMap()
{
	// ��ȡ��ͼ��С�ͻ�ɫ
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;

	// �����ڴ�����
	int** pGameMap = new int*[nRows];
	if (NULL == pGameMap)
	{
		throw (_T("�ڴ�����쳣��\n"));
	}
	else
	{
		for (int i = 0; i < nRows; i++)
		{
			pGameMap[i] = new int[nCols];
			if (NULL == pGameMap)
			{
				throw (_T("�ڴ�����쳣��\n"));
			}
			memset(pGameMap[i], NULL, sizeof(int) * nCols);
		}
	}

	// ���ٻ�ɫ
	if ((nRows * nCols) % (nPicNum * 2) != 0)
	{
		ReleaseMap(pGameMap);
		throw (_T("��Ϸ��ɫ����Ϸ��ͼ��С��ƥ�䣡"));
	}
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0;
	for (int i = 0; i < nPicNum; i++)
	{
		// �ظ���
		for (int j = 0; j < nRepeatNum; j++)
		{
			pGameMap[nCount / nCols][nCount % nCols] = i;
			nCount++;
		}
	}

	// ��������
	srand((int)time(NULL));
	// ������⽻����������
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// ����õ���������
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// ����������ֵ
		int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2/nCols][nIndex2 % nCols];
		pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
	}
	return pGameMap;
}

void CGameLogic::ReleaseMap(int** &pGameMap)
{
	for (int i = 0; i < CGameControl::s_nRows; i++)
	{
		delete[]pGameMap[i];
	}
	delete[]pGameMap;
}

void CGameLogic::PushVertex(Vertex v) {
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}

void CGameLogic::PopVertex() {
	m_avPath[m_nVexNum] = {0,0,0};
	m_nVexNum--;
}

void CGameLogic::ClearStack() {
	m_nVexNum = 0;
	for (int i = 0; i < 4; i++) {
		m_avPath[i] = { 0,0,0 };
	}
}

bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2)
{
	PushVertex(v1);
	// X ֱ����ʽ
	if (v1.row == v2.row) 
	{
		//�������ͨ����ջ���˳�
		if (!LinkInRow(pGameMap, v1, v2)) {
			ClearStack();
			return false;
		}
		PushVertex(v2);
		return true;
	}
	//Y ֱ����ʽ
	if (v1.col == v2.col)
	{
		//�������ͨ����ջ���˳�
		if (!LinkInCol(pGameMap, v1, v2)) {
			ClearStack();
			return false;
		}
		PushVertex(v2);
		return true;
	}
	else {
		if (!OneCornerLink(pGameMap, v1, v2) && !TwoCornerLink(pGameMap, v1, v2)) {
			ClearStack();
			return false;
		}
		PushVertex(v2);
		return true;
	}
	ClearStack();
	return false;
}

bool CGameLogic::LinkInRow(int** pGameMap, Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow = v1.row;
	//��֤ nCol1 ��ֵС�� nCol2
	if (nCol1 > nCol2)
	{
		//���ݽ���
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}
	//ֱͨ
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2) return true;
		if (pGameMap[nRow][i] != BLANK) break;
	}
	return false;
}

bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol = v1.col;
	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}
	//ֱͨ
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2) return true;
		if (pGameMap[i][nCol] != BLANK) break;
	}
	return false;
}

bool CGameLogic::LineX(int** pGameMap, int nRow, int nCol1, int nCol2) {
	Vertex v1,v2;
	v1.row = nRow;
	v1.col = nCol1;
	v2.row = nRow;
	v2.col = nCol2;
	return LinkInRow(pGameMap,v1,v2);
}

bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol) {
	Vertex v1, v2;
	v1.row = nRow1;
	v1.col = nCol;
	v2.row = nRow2;
	v2.col = nCol;
	return LinkInCol(pGameMap, v1, v2);
}

bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	// ֱ���ܹ����ӣ���ô����һ��������������к����ཻ�ĵ㣬ֻ����������Ϊ�գ����п���ʵ�ֶ���ֱ������
		if (pGameMap[v1.row][v2.col] == BLANK)
		{
			if (LineY(pGameMap, v1.row, v2.row, v2.col) && LineX(pGameMap, v1.row, v1.col,v2.col))
			{
				Vertex v = { v1.row, v2.col, BLANK };
				PushVertex(v);
				return true;
			}
		}
	if (pGameMap[v2.row][v1.col] == BLANK)
	{
		if (LineY(pGameMap, v1.row, v2.row, v1.col) && LineX(pGameMap, v2.row, v1.col,v2.col))
		{
			Vertex v = { v2.row, v1.col, BLANK };
			PushVertex(v);
			return true;
		}
	}
	return false;
}

bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	for (int nCol = 0; nCol < CGameControl::s_nCols; nCol++)
	{
		// �ҵ�һ���� Y ��ƽ�е���ͨ�߶�
		if (pGameMap[v1.row][nCol] == BLANK && pGameMap[v2.row][nCol] == BLANK)
		{
			if (LineY(pGameMap, v1.row, v2.row, nCol))
			{
				if (LineX(pGameMap, v1.row, v1.col, nCol) && LineX(pGameMap, v2.row,v2.col, nCol))
				{
					// ����ڵ�
					Vertex vx1 = { v1.row, nCol, BLANK };
					Vertex vx2 = { v2.row, nCol, BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow < CGameControl::s_nRows; nRow++)
	{
		// �ҵ�һ���� X ��ƽ�е���ͨ�߶�
		if (pGameMap[nRow][v1.col] == BLANK && pGameMap[nRow][v2.col] == BLANK)
		{
			if (LineX(pGameMap, nRow, v1.col, v2.col))
			{
				if (LineY(pGameMap, nRow, v1.row, v1.col) && LineY(pGameMap, nRow,v2.row, v2.col))
				{
					// ����ڵ�
					Vertex vx1 = { nRow, v1.col, BLANK };
					Vertex vx2 = { nRow, v2.col, BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	return false;
}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	int num = m_nVexNum;
	for (int i = 0; i < num; i++)
	{
		avPath[i] = m_avPath[i];
	}
	ClearStack();
	return num;
}

void CGameLogic::Clear(int** pGameMap, Vertex v1, Vertex v2) {
	pGameMap[v1.row][v1.col] = BLANK;
	pGameMap[v2.row][v2.col] = BLANK;
}