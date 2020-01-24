#include"CModeSelect.h"

#include"CGameFrame.h"
#include"CSoundSystem.h"
#include"CResourceManager.h"

CModeSelect::CModeSelect(HDC hBackbuffer) : CGameFrame(hBackbuffer)
{
	m_ResourceManeger = CResourceManager::getInstance();
}

CModeSelect::~CModeSelect() 
{
}

void CModeSelect::Init()
{
	nAlpha = ALPHA_MAX;
	bFadeIn = true;
	bFadeOut = false;
	BlendFunction.SourceConstantAlpha = nAlpha;

	CSoundSystem::getInstance()->StopBGM();
	CSoundSystem::getInstance()->StartBGM(SELECT_BGM);
}

void CModeSelect::CheckPressKey()
{
	if ((GetKeyState(VK_UP) < 0) && m_curTime - m_buttonTime > CHECK_KEY_TIME)
	{
		m_buttonTime = m_curTime;
		m_selectorState = MOVE;
		m_selectorWay = WAY_UP;

		CSoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	}
	else if ((GetKeyState(VK_DOWN) < 0) && m_curTime - m_buttonTime > CHECK_KEY_TIME)
	{
		m_buttonTime = m_curTime;
		m_selectorState = MOVE;
		m_selectorWay = WAY_DOWN;

		CSoundSystem::getInstance()->StartEffect(SOUND_BUTTON);
	}
	else if ((GetKeyState(KEY_K) < 0) && m_curTime - m_buttonTime > CHECK_KEY_TIME && m_selectorWay == WAY_STOP)
	{
		m_buttonTime = m_curTime;
		m_selectorState = SELECT;
		m_ResourceManeger->m_spriteData[SELECTOR]->originXpos = 0;

		CSoundSystem::getInstance()->StartEffect(SOUND_SELECT);
	}
}

void CModeSelect::CheckSelectedMode()
{
	if (m_ResourceManeger->m_spriteData[SELECTOR]->ypos < MIDDLE)
	{
		m_curSelectedMode = STORY;
		m_ResourceManeger->m_spriteData[SELECT_CIRCLE]->ypos = STORY_YPOS;
	}
	else
	{
		m_curSelectedMode = BATTLE;
		m_ResourceManeger->m_spriteData[SELECT_CIRCLE]->ypos = BATTLE_YPOS;
	}
}

void CModeSelect::SetAni() 
{
	switch (m_selectorState)
	{
		case MOVE:
			if (m_curTime - m_ResourceManeger->m_spriteData[SELECTOR]->time > CHECK_MOVE_ANI_TIME && m_selectorWay != WAY_STOP)
			{
				m_ResourceManeger->m_spriteData[SELECTOR]->time = m_curTime;

				if (m_ResourceManeger->m_spriteData[SELECTOR]->originXpos < MOVE_ANI_MAX)
				{
					m_ResourceManeger->m_spriteData[SELECTOR]->originXpos += m_ResourceManeger->m_spriteData[SELECTOR]->originWidth;
				}
				else
				{
					m_ResourceManeger->m_spriteData[SELECTOR]->originXpos = 0;
				}
			}
			break;
		case SELECT:
			if (m_curTime - m_ResourceManeger->m_spriteData[SELECTOR]->time > CHECK_SELECT_ANI_TIME)
			{
				m_ResourceManeger->m_spriteData[SELECTOR]->time = m_curTime;

				if (m_ResourceManeger->m_spriteData[SELECTOR]->originXpos == CIRCLE_MAX)
				{
					m_ResourceManeger->m_spriteData[SELECTOR]->originXpos = 0;
					bSelect = true;
					m_ResourceManeger->m_spriteData[SELECTOR]->originYpos = IDLE;
				}
				else
				{
					m_ResourceManeger->m_spriteData[SELECTOR]->originXpos += m_ResourceManeger->m_spriteData[SELECTOR]->originWidth;
				}
			}
			break;
	}



	if (m_curTime - m_ResourceManeger->m_spriteData[SELECT_CIRCLE]->time > CHECK_CIRCLE_ANI_TIME && bSelect)
	{
		m_ResourceManeger->m_spriteData[SELECT_CIRCLE]->time = m_curTime;
		if (m_ResourceManeger->m_spriteData[SELECT_CIRCLE]->originXpos != CIRCLE_MAX)
		{
			m_ResourceManeger->m_spriteData[SELECT_CIRCLE]->originXpos += m_ResourceManeger->m_spriteData[SELECT_CIRCLE]->originWidth;

			if (m_ResourceManeger->m_spriteData[SELECT_CIRCLE]->originXpos == CIRCLE_MAX)
			{
				bFadeOut = true;
			}
		}
	}
}

void CModeSelect::Move() 
{
	if (m_curTime - m_moveTime > CHECK_MOVE_TIME)
	{
		m_moveTime = m_curTime;
		switch (m_selectorWay)
		{
			case WAY_UP:
				if (m_ResourceManeger->m_spriteData[SELECTOR]->ypos > MOVE_MIN_YPOS)
				{
					m_ResourceManeger->m_spriteData[SELECTOR]->ypos -= MOVE_SPEED;
				}
				else
				{
					m_selectorWay = WAY_STOP;
					m_ResourceManeger->m_spriteData[SELECTOR]->ypos = MOVE_MIN_YPOS;
					m_ResourceManeger->m_spriteData[SELECTOR]->originXpos = 0;
				}
				break;
			case WAY_DOWN:
				if (m_ResourceManeger->m_spriteData[SELECTOR]->ypos < MOVE_MAX_YPOS)
				{
					m_ResourceManeger->m_spriteData[SELECTOR]->ypos += MOVE_SPEED;
				}
				else {
					m_selectorWay = WAY_STOP;
					m_ResourceManeger->m_spriteData[SELECTOR]->ypos = MOVE_MAX_YPOS;
					m_ResourceManeger->m_spriteData[SELECTOR]->originXpos = 0;
				}
				break;
		break;
		}

		m_ResourceManeger->m_spriteData[SELECTOR]->originYpos = m_selectorWay;
	}
}

GAME_STEP CModeSelect::Update() 
{
	m_curTime = GetTickCount64();

	if (!bSelect && m_selectorState != SELECT && !bFadeIn && !bFadeOut)
	{
		CheckPressKey();
		Move();
	}

	if (bFadeIn && m_curTime - dwAlphaTime > ALPHA_CHECK_TIME)
	{
		dwAlphaTime = m_curTime;
		FadeIn();
	}

	if (bFadeOut && m_curTime - dwAlphaTime > ALPHA_CHECK_TIME)
	{
		dwAlphaTime = m_curTime;
		FadeOut();

		if (!bFadeOut) 
		{
			if (m_curSelectedMode == BATTLE)
			{
				m_gameStep = STEP_BATTLE;
			}
			else if(m_curSelectedMode == STORY)
			{
				m_gameStep = STEP_STORY;
			}
		}
	}

	SetAni();

	return m_gameStep;
}

void CModeSelect::Render() 
{
	if (m_curSelectedMode == STORY)
	{
		m_ResourceManeger->DrawingBackground(hBackbuffer, BACKGROUND_STORY);
	}
	else 
	{
		m_ResourceManeger->DrawingBackground(hBackbuffer, BACKGROUND_BATTLE);
	}

	m_ResourceManeger->DrawingSprite(hBackbuffer, SELECTOR);

	if (bSelect)
	{
		m_ResourceManeger->DrawingSprite(hBackbuffer, SELECT_CIRCLE);
	}

	if (bFadeIn || bFadeOut) 
	{
		AlphaBlend(hBackbuffer, 0, 0, WIN_RIGHT, WIN_BOTTOM, hFadeDC, 0, 0, WIN_RIGHT, WIN_BOTTOM, BlendFunction);
	}
}