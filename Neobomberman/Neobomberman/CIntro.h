#pragma once
#include"framework.h"

class CGameFrame;
class CResourceManager;

enum BACKGROUND : unsigned int { BACKGROUND01 };
enum SPRITES { PUSH_1P_START, CRADIT, CRADITS, COIN_COUNT };
enum SETTING : unsigned int { COIN_SPACE = 28, CHECK_COIN_TIME = 200, CHECK_KEY_TIME = 150, MAX_COIN = 99 };

class CIntro : public CGameFrame 
{
private:
	GAME_STEP m_gameStep = STEP_INTRO;

	CResourceManager* m_ResourceManeger = nullptr;

	unsigned int m_curTime = 0;
	unsigned int nButtonTime = 0;
	unsigned int m_curCoinCount = 0;

	bool bCoinBlink = false;
public:
	CIntro(HDC);
	~CIntro();

	void CheckPressKey();
	void CheckCoin();

	virtual void Init();
	virtual GAME_STEP Update();
	virtual void Render();
};