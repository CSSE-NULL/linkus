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
	int** m_pGameMap ; // ��Ϸ��ͼ����ָ��
	CGameLogic m_GameLogic; // ��Ϸ�߼���������
	void StartGame(void); // ��ʼ��Ϸ
	int GetElement(int nRow, int nCol); // �õ�ĳһ��Ԫ��
};

