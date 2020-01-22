#pragma once

class CGameFrame {
protected:
	HWND hWnd;
	HDC hBackbuffer;
	HDC hFadeDC;

	bool bFadeIn;
	bool bFadeOut;

	int nAlpha;
	DWORD dwAlphaTime;
	BLENDFUNCTION BlendFunction;

	HDC CreateBmpDC(const char* filename);
	
	void FadeOut();
	void FadeIn();

public:
	virtual void Init() {};
	virtual void LoadData() {};
	virtual GAME_STEP Update() {};
	virtual void Render() {};

	void FadeOut();
	void FadeIn();

	CGameFrame(HWND hWnd, HDC hBackbuffer);
	~CGameFrame();
};