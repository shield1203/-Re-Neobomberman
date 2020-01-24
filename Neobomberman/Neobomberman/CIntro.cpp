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
	m_curTime = GetTickCount64();
	CheckCoin();
	CheckPressKey();

	return m_gameStep;
}

void CIntro::CheckPressKey()
{
	if (GetKeyState(KEY_5) < 0 && m_curTime - nButtonTime > CHECK_KEY_TIME)
	{ // 코인 투입!
		nButtonTime = m_curTime;

		if (m_curCoinCount <= MAX_COIN)
		{
			m_curCoinCount++;
			bCoinBlink = true;
		}
		CSoundSystem::getInstance()->StopBGM();
		CSoundSystem::getInstance()->StartEffect(SOUND_COIN);
	}
	else if (GetKeyState(KEY_1) < 0 && m_curTime - nButtonTime > CHECK_KEY_TIME)
	{
		nButtonTime = m_curTime;

		if (m_curCoinCount > 0)
		{
			m_gameStep = STEP_MODE_SELECT;
		}
	}
}

void CIntro::CheckCoin() 
{
	if (m_curTime - m_ResourceManeger->m_spriteData[PUSH_1P_START]->time > CHECK_COIN_TIME && m_curCoinCount == 0)
	{
		m_ResourceManeger->m_spriteData[PUSH_1P_START]->time = m_curTime;
		if (bCoinBlink)
		{
			bCoinBlink = false;
		}
		else 
		{
			bCoinBlink = true;
		}
	}
}

void CIntro::Render()
{
	SpriteData spriteData;

	m_ResourceManeger->DrawingBackground(hBackbuffer, BACKGROUND01);

	if (bCoinBlink)
	{
		m_ResourceManeger->DrawingSprite(hBackbuffer, PUSH_1P_START);
	}

	if (m_curCoinCount >= 2)
	{
		m_ResourceManeger->DrawingSprite(hBackbuffer, CRADITS);
	}
	else
	{
		m_ResourceManeger->DrawingSprite(hBackbuffer, CRADIT);
	}

	m_ResourceManeger->GetSpriteData(spriteData, COIN_COUNT);
	spriteData.originXpos = (m_curCoinCount / 10) * COIN_SPACE;
	m_ResourceManeger->DrawingSprite(hBackbuffer, spriteData);
	spriteData.xpos += COIN_SPACE;
	spriteData.originXpos = (m_curCoinCount % 10) * COIN_SPACE;
	m_ResourceManeger->DrawingSprite(hBackbuffer, spriteData);
}