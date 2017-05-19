#pragma once
#include"GameLogic.h"
class CGameControl
{
public:
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
	CGameControl();
	~CGameControl();
	int** m_pGameMap ; // 游戏地图数组指针
	CGameLogic m_GameLogic; // 游戏逻辑操作对象
	void StartGame(void); // 开始游戏
	int GetElement(int nRow, int nCol); // 得到某一个元素
};

