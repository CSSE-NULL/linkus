#pragma once
#include"GameLogic.h"
class CGameControl
{
public:
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
	Vertex m_svSelFst; // 选中的第一个点
	Vertex m_svSelSec; // 选中的第二个点
	CGameControl();
	~CGameControl();
	int** m_pGameMap ; // 游戏地图数组指针
	CGameLogic m_GameLogic; // 游戏逻辑操作对象
	void StartGame(void); // 开始游戏
	int GetElement(int nRow, int nCol); // 得到某一个元素
	void SetFirstPoint(int nRow, int nCol); // 设置第一个点
	void SetSecPoint(int nRow, int nCol); // 设置第二个点
	bool Link(Vertex avPath[4], int &nVexnum); // 消子判断(路径暂定为 2 个顶点，后面再对该函数进行修订)
	bool IsWin(void); // 判断是否获胜
};

