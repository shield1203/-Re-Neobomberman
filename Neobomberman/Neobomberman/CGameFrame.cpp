#include"framework.h"
#include"CGameFrame.h"

CGameFrame::CGameFrame(HDC hBackbuffer) 
{
	this->hBackbuffer = hBackbuffer;

	dwAlphaTime = 0;

	hFadeDC = CreateBmpDC("Resource\\Fade.bmp");

	BlendFunction.BlendOp = AC_SRC_OVER;
	BlendFunction.BlendFlags = 0;
	BlendFunction.AlphaFormat = 0;
	BlendFunction.SourceConstantAlpha = nAlpha;

	bFadeIn = false;
	bFadeOut = false;
}

CGameFrame::~CGameFrame() 
{
	ReleaseDC(g_hWnd, hFadeDC);
	hFadeDC = nullptr;
}

void CGameFrame::FadeOut() 
{ // °Ë°Ô
	if (nAlpha < ALPHA_MAX) 
	{
		nAlpha += ALPHA_SPEED;
		BlendFunction.SourceConstantAlpha = nAlpha;
	}
	else 
	{
		bFadeOut = false;
	}
}

void CGameFrame::FadeIn() 
{ // ¹à°Ô
	if (nAlpha > ALPHA_MIN)
	{
		nAlpha -= ALPHA_SPEED;
		BlendFunction.SourceConstantAlpha = nAlpha;
	}
	else 
	{
		bFadeIn = false;
	}
}