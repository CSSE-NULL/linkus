#pragma once
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
	int** InitMap();
	void ReleaseMap(int** &pGameMap);
};

