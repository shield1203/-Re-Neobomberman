#pragma once
class CMapSelect;
class CBomberSelect;
class CBattle;
class CBattleResult;

class CBattleSystem {
private:
	

public:
	
	HDC hBackbuffer;

	GAME_STEP gameStep;
	BATTLE_STEP battleStep;

	CMapSelect* MapSelect;
	CBomberSelect* BomberSelect;
	CBattle* Battle;
	CBattleResult* BattleResult;

	void Init();
	GAME_STEP Update();
	void Render();

	CBattleSystem(HDC hBackbuffer);
	~CBattleSystem();
};