#pragma once
#include"framework.h"

class CGameFrame;
class CResourceManager;

enum BACKGROUND : unsigned int { BACKGROUND01 };
enum SPRITES { PUSH_1P_START, CRADIT, CRADITS, COIN_COUNT };

class CIntro : public CGameFrame 
{
private:
	GAME_STEP m_GameStep = STEP_INTRO;

	CResourceManager* m_ResourceManeger = nullptr;

	int nCurTime = 0;
	int nButtonTime = 0;
	int nTextTime = 0;
	int nCoin = 0;

	bool bCoin = false;
public:
	CIntro(HDC hBackbuffer);
	~CIntro();

	void CheckKey();
	void CheckCoin();

	virtual void Init();
	virtual GAME_STEP Update();
	virtual void Render();
};