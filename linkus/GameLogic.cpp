#include "stdafx.h"
#include "GameLogic.h"
#include "GameControl.h"

CGameLogic::CGameLogic()
{
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
		pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 /
			nCols][nIndex2 % nCols];
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


