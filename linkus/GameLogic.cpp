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
	// 获取地图大小和花色
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;

	// 开辟内存区域
	int** pGameMap = new int*[nRows];
	if (NULL == pGameMap)
	{
		throw (_T("内存操作异常！\n"));
	}
	else
	{
		for (int i = 0; i < nRows; i++)
		{
			pGameMap[i] = new int[nCols];
			if (NULL == pGameMap)
			{
				throw (_T("内存操作异常！\n"));
			}
			memset(pGameMap[i], NULL, sizeof(int) * nCols);
		}
	}

	// 多少花色
	if ((nRows * nCols) % (nPicNum * 2) != 0)
	{
		ReleaseMap(pGameMap);
		throw (_T("游戏花色与游戏地图大小不匹配！"));
	}
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0;
	for (int i = 0; i < nPicNum; i++)
	{
		// 重复数
		for (int j = 0; j < nRepeatNum; j++)
		{
			pGameMap[nCount / nCols][nCount % nCols] = i;
			nCount++;
		}
	}

	// 设置种子
	srand((int)time(NULL));
	// 随机任意交换两个数字
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < nVertexNum; i++)
	{
		// 随机得到两个坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		// 交换两个数值
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


