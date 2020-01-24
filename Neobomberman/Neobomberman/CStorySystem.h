#pragma once

class CGameScene;
class CStory;

class CStorySystem : public CGameFrame{
private:

public:
	HDC hBackbuffer;

	GAME_STEP gameStep;
	STORY_STEP storyStep;

	CGameScene* GameScene = nullptr;
	CStory* Story = nullptr;

	virtual void Init();
	virtual GAME_STEP Update();
	virtual void Render();

	CStorySystem(HDC);
	~CStorySystem();
};