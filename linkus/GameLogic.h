#pragma once
#include"global.h"

class CGameLogic {
public:
	CGameLogic();
	~CGameLogic();
	int** InitMap();
	Vertex m_avPath[4]; //�����ڽ��������ж�ʱ�������Ķ���
	int m_nVexNum;     //������
	void ReleaseMap(int** &pGameMap);
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2); //�ж��Ƿ���ͨ
	void Clear(int** pGameMap, Vertex v1, Vertex v2); // ����
	int GetVexPath(Vertex avPath[4]); //�õ�·�������ص��Ƕ�����
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2); //�жϺ����Ƿ���ͨ
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2); //�ж������Ƿ���ͨ
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2); //һ���յ���ͨ�ж�
	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol); //ֱ����ͨ Y ��
	bool LineX(int** pGameMap, int nRow, int nCol1, int nCol2); //ֱ����ͨ X ��
	void PushVertex(Vertex v); //���һ��·������
	void PopVertex(); //ȡ��һ������
	void ClearStack(); //���ջ
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2); //����ֱ�������ж�
	bool IsBlank(int** pGameMap); // �ж�ͼ�ж����ǲ���ȫΪ��
};