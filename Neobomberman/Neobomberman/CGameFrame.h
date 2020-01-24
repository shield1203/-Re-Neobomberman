#pragma once

class CGameFrame 
{
protected:
	HDC hBackbuffer;
	HDC hFadeDC;

	bool bFadeIn;
	bool bFadeOut;

	int nAlpha;
	DWORD dwAlphaTime;
	BLENDFUNCTION BlendFunction;
	
	void FadeOut();
	void FadeIn();

public:
	virtual void Init() {};
	virtual GAME_STEP Update() {};
	virtual void Render() {};

	void FadeOut();
	void FadeIn();

	CGameFrame(HDC);
	~CGameFrame();
};