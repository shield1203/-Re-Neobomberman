#include"CIntro.h"

#include"CGameFrame.h"
#include"CSoundSystem.h"
#include"CResourceManager.h"

CIntro::CIntro(HDC hBackbuffer) : CGameFrame(hBackbuffer) 
{ 
	m_ResourceManeger = CResourceManager::getInstance();
}

CIntro::~CIntro() 
{
}

void CIntro::Init() 
{
	CSoundSystem::getInstance()->StopBGM();
	CSoundSystem::getInstance()->StartBGM(INTRO_BGM);
}

GAME_STEP CIntro::Update() 
{
	nCurTime = GetTickCount64();
	CheckCoin();
	CheckKey();

	return m_GameStep;
}

void CIntro::CheckKey()
{
	if (GetKeyState(KEY_5) < 0 && nCurTime - nButtonTime > 150) 
	{ // 코인 투입!
		nButtonTime = nCurTime;

		if (nCoin < 100) 
		{
			nCoin++;
			bCoin = true;
		}
		CSoundSystem::getInstance()->StopBGM();
		CSoundSystem::getInstance()->StartEffect(SOUND_COIN);
	}
	else if (GetKeyState(KEY_1) < 0 && nCurTime - nButtonTime > 150) 
	{
		nButtonTime = nCurTime;

		if (nCoin > 0) 
		{
			m_GameStep = STEP_MODE_SELECT;
		}
	}
}

void CIntro::CheckCoin() 
{
	if (nCurTime - nTextTime > 200 && nCoin == 0) 
	{
		nTextTime = nCurTime;
		if (bCoin) 
		{
			bCoin = false;
		}
		else 
		{
			bCoin = true;
		}
	}
}

void CIntro::Render()
{
	m_ResourceManeger->DrawingBackground(hBackbuffer, BACKGROUND01);

	if (bCoin)
	{
		m_ResourceManeger->DrawingSprite(hBackbuffer, PUSH_1P_START);
	}

	if (nCoin >= 2)
	{
		m_ResourceManeger->DrawingSprite(hBackbuffer, CRADITS);
	}
	else
	{
		m_ResourceManeger->DrawingSprite(hBackbuffer, CRADIT);
	}

	TransparentBlt(hBackbuffer, 1114, 865, 28, 32, hNumberDC, (nCoin / 10) * 28, 0, 28, 32, RGB(R_COLOR, G_COLOR, B_COLOR));
	TransparentBlt(hBackbuffer, 1142, 865, 28, 32, hNumberDC, (nCoin % 10) * 28, 0, 28, 32, RGB(R_COLOR, G_COLOR, B_COLOR));
}