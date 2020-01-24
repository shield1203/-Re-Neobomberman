#include"CStorySystem.h"
#include"framework.h"
#include"CGameFrame.h"

#include"CGameScene.h"
#include"CStory.h"

CStorySystem::CStorySystem(HDC hBackbuffer) : CGameFrame(hBackbuffer)
{
	this->hBackbuffer = hBackbuffer;

	gameStep = STEP_STORY;
	storyStep = STORY_SCENE;

	GameScene = new CGameScene();
}

CStorySystem::~CStorySystem() 
{
	delete GameScene;
}

void CStorySystem::Init() {
	gameStep = STEP_STORY;
	storyStep = STORY_SCENE;
}

GAME_STEP CStorySystem::Update() 
{
	switch (storyStep) 
	{
		case STORY_SCENE: {
			if (GameScene == nullptr) {
				GameScene = new CGameScene(hBackbuffer);
			}
			storyStep = GameScene->Update();
			break;
		}
		case STORY_PLAY: {
			storyStep = Story->Update();
			break;
		}
	}

	switch (storyStep) 
	{ // ½ºÅÜÀÌ ¹Ù²ğ¶§ ÇÒ´ç
		case STORY_PLAY: {
			if (Story == nullptr) {
				Story = new CStory(hBackbuffer);
			}
			break;
		}
		case STORY_END: {
			delete GameScene;
			delete Story;
			GameScene = nullptr;
			Story = nullptr;

			return STEP_INTRO;
		}
	}

	return gameStep;
}

void CStorySystem::Render()
{
	switch (storyStep) 
	{
		case STORY_SCENE: {
			if (GameScene == nullptr) {
				GameScene = new CGameScene(hBackbuffer);
			}
			GameScene->Render();
			break;
		}
		case STORY_PLAY: {
			Story->Render();
			break;
		}
	}
}