#pragma once

class CGameFrame;

class CProcessManager {
private:
	HWND hProcWnd;
	HDC hBackBuffer;
	RECT WinRect;

	CGameFrame *m_Process = nullptr;

	GAME_STEP m_GameStep = STEP_INTRO, m_PrevGameStep = STEP_INTRO;
public:
	void Process();
	void Init();
	void Update();
	void Render();

	CProcessManager(HWND hWnd);
	~CProcessManager();
};