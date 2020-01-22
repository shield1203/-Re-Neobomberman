#pragma once
#include"framework.h"

enum  AA { asd };

class CIntro : public CGameFrame {
private:
	

	HDC hIntroDC = nullptr;
	HDC hNumberDC = nullptr;
	HDC hTextDC = nullptr;

	GAME_STEP m_GameStep = STEP_INTRO;

	int nCurTime = 0;
	int nButtonTime = 0;
	int nTextTime = 0;
	int nCoin = 0;

	bool bCoin = false;
public:
	CIntro(HWND hWnd, HDC hBackbuffer);
	~CIntro();

	void PressKey();
	void CheckCoin();

	virtual void Init();
	virtual void LoadData();
	virtual GAME_STEP Update();
	virtual void Render();
};