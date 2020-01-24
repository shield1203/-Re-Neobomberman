#pragma once
#include"framework.h"

class CGameFrame;
class CResourceManager;

enum BACKGROUND : unsigned int { BACKGROUND_STORY, BACKGROUND_BATTLE };
enum SPRITES { SELECTOR, SELECT_CIRCLE };
enum SETTING : unsigned int { CHECK_KEY_TIME = 150, CHECK_MOVE_TIME = 10, CHECK_MOVE_ANI_TIME = 170, CHECK_SELECT_ANI_TIME = 50, CHECK_CIRCLE_ANI_TIME = 37 };

enum MODE { STORY, BATTLE = 715 };
enum SELECTOR_STATE : unsigned int { IDLE = 1, MOVE = 150, SELECT = 0, MOVE_SPEED = 8, MOVE_MIN_YPOS = 380, MOVE_MAX_YPOS = 700, MOVE_ANI_MAX = 450, CIRCLE_MAX = 1200, MIDDLE = 540 };
enum CIRCLE_STATE : unsigned int { STORY_YPOS = 350, BATTLE_YPOS = 680 };

class CModeSelect : public CGameFrame 
{
private:
	GAME_STEP m_gameStep = STEP_MODE_SELECT;
	MODE m_curSelectedMode = STORY;

	CResourceManager* m_ResourceManeger = nullptr;

	SELECTOR_STATE m_selectorState = IDLE;
	MOVE_WAY m_selectorWay = WAY_STOP;
	bool bSelect = false;

	unsigned int m_curTime = 0; // 계속 갱신되는 시간
	unsigned int m_buttonTime = 0;
	unsigned int m_moveTime = 0;
public:
	CModeSelect(HDC);
	~CModeSelect();

	void CheckPressKey();
	void CheckSelectedMode();
	void SetAni();
	void Move();

	virtual void Init();
	virtual GAME_STEP Update();
	virtual void Render();
};