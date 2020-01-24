#pragma once

class CGameFrame;

class CProcessSystem {
private:
	HDC hBackBuffer;
	RECT WinRect;

	CGameFrame *m_Process = nullptr;

	GAME_STEP m_GameStep = STEP_INTRO, m_PrevGameStep = STEP_INTRO;
public:
	void Process();
	void Init();
	void Update();
	void Render();

	CProcessSystem();
	~CProcessSystem();
};