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
	DeleteDC(hFadeDC);
	hFadeDC = nullptr;
}

void CGameFrame::FadeOut() 
{ // °Ë°Ô
	if (nAlpha < 255) {
		nAlpha += 15;
		BlendFunction.SourceConstantAlpha = nAlpha;
	}
	else {
		bFadeOut = false;
	}
}

void CGameFrame::FadeIn() 
{ // ¹à°Ô
	if (nAlpha > 0) {
		nAlpha -= 15;
		BlendFunction.SourceConstantAlpha = nAlpha;
	}
	else {
		bFadeIn = false;
	}
}