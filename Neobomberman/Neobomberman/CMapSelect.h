#pragma once
#include"CBattleManager.h"
#include"CGameFrame.h"
#include"tinyxml.h"

using namespace std;

typedef struct MiniMap {
	string strFileName;
	HDC hMiniMapDC;
};

class CMapSelect : public CGameFrame {
private:
	HDC hBackgroundDC;
	HDC hSelectorDC;
	HDC hNumDC;

	DWORD dwCurTime;
	DWORD dwAni;
	DWORD dwAniTime;
	DWORD dwButtonTime;
public:
	int nSelect;
	vector<MiniMap*> miniMap;
	string strMapFileName;

	void LoadMiniMap();
	void CheckKey();
	void SetAni();

	void Init(); // 첨 시작 초기화
	//void Init(asasas);
	void Update();
	void Render();

	CMapSelect(HWND hWnd, HDC hBackbuffer);
	~CMapSelect();
};