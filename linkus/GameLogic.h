#pragma once
#include"global.h"

class CGameLogic {
public:
	CGameLogic();
	~CGameLogic();
	int** InitMap();
	Vertex m_avPath[4]; //保存在进行连接判断时所经过的顶点
	int m_nVexNum;     //顶点数
	void ReleaseMap(int** &pGameMap);
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2); //判断是否连通
	void Clear(int** pGameMap, Vertex v1, Vertex v2); // 消子
	int GetVexPath(Vertex avPath[4]); //得到路径，返回的是顶点数
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2); //判断横向是否连通
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2); //判断纵向是否连通
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2); //一个拐点连通判断
	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol); //直线连通 Y 轴
	bool LineX(int** pGameMap, int nRow, int nCol1, int nCol2); //直线连通 X 轴
	void PushVertex(Vertex v); //添加一个路径顶点
	void PopVertex(); //取出一个顶点
	void ClearStack(); //清除栈
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2); //三条直线消子判断
	bool IsBlank(int** pGameMap); // 判断图中顶点是不是全为空
};