#pragma once
/////////////
// LINKING //
/////////////
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "msimg32.lib") // TransparentBlt 사용
#pragma comment(lib, "fmod_vc.lib")

//////////////
// INCLUDES //
//////////////
#include<Windows.h>
#include<Vfw.h>
#include<string>
#include<vector>
#include<list>
#include<ctime>
#include<cstdlib>
using namespace std;

///////////////////////////
//         SOUND         //
///////////////////////////
#include"inc/fmod.hpp"
using namespace FMOD;

enum WINDOW_SIZE { WIN_LEFT = 0, WIN_TOP = 0, WIN_RIGHT = 1216, WIN_BOTTOM = 896 };

enum GAME_STEP { STEP_INTRO, STEP_MODE_SELECT, STEP_BATTLE, STEP_STORY };

enum TRANS_COLOR { R_COLOR = 0, G_COLOR = 248, B_COLOR = 0, R_BOMBER = 255, G_BOMBER = 0, B_BOMBER = 255 };

enum KEY_VALUE { KEY_1 = 0x31, KEY_2 = 0x32, KEY_3 = 0x33, KEY_5 = 0x35, KEY_A = 0x41, KEY_S = 0x53, KEY_R = 0x52, KEY_D = 0x44, KEY_F = 0x46, KEY_G = 0x47, // 2P
	KEY_K = 0x4B, KEY_L = 0x4C }; // 1P 

// ModeSelect
enum SELECTOR_STATE { SELECTOR_IDLE = 1, SELECTOR_MOVE = 150, SELECTOR_SELECT = 0, SELECTOR_MOVE_MAX = 450, SELECTOR_SELECT_MAX = 1200 };

enum MOVE_WAY { WAY_STOP, WAY_UP, WAY_DOWN, WAY_LEFT, WAY_RIGHT };

enum SELECT_MODE { SELECT_STORY, SELECT_BATTLE = 715 };

// MapSelect
enum MAP_SELECTOR { MAP_SELECTOR_WIDTH = 577, MAP_SELECTOR_HEIGHT = 609, MAP_SELECTOR_MAX = 2308 };

// PlayerState
enum PLAYER_DIRECTION { PLAYER_DOWN = 0 , PLAYER_LEFT = 256, PLAYER_UP = 512 , PLAYER_RIGHT = 768, PLAYER_DIE = 448 };

enum PLAYER_STATE { P_STATE_MOVE = 0, P_STATE_DASH = 64, P_STATE_DIE = 576 };

// BattleManager
enum BATTLE_STEP { BATTLE_MAP_SELECT, BATTLE_BOMBER_SELECT, BATTLE_PLAY, BATTLE_RESULT };

enum PLAYER { NONE_PLAYER, PLAYER_P1AI, PLAYER_P2AI, PLAYER_P1, PLAYER_P2 };

enum TYLE {	NONE_TYLE, TYLE01, TYLE02, TYLE03, TYLE04, TYLE05, TYLE06, TYLE07, TYLE08, TYLE09, TYLE10, TYLE11, TYLE12, TYLE13, TYLE14,
	TYLE15, TYLE16, TYLE17, TYLE18, TYLE19, TYLE20, TYLE21, TYLE22, TYLE23 };

enum OBJECT { NONE_OBJECT, OBJECT01, OBJECT02, OBJECT03, OBJECT04, OBJECT05, OBJECT06, OBJECT07 };

enum BLOCK { NONE_BLOCK, BLOCK01, BLOCK02, BLOCK03 };

enum BOMBER { WHITEBOMBER, BLACKBOMBER, REDBOMBER, BLUEBOMBER, RUBBER, FAKE, CAT, HONEY, HAYATE, KOTTETU, GOLD, ATOMIC }; // 봄버맨 이름

enum ITEM { FIRE, BOMB = 92, ITEM_MAX = 512 };

enum BOMB_DIRECTION { BOMB_CONETER = 16, BOMB_UP = 32, BOMB_UP_ADGE = 48, BOMB_DOWN = 64, BOMB_DOWN_ADGE = 80, BOMB_LEFT = 96, BOMB_LEFT_ADGE = 112, BOMB_RIGHT = 128, BOMB_RIGHT_ADGE = 144 };

enum GAME_RESULT_OBJECT { RESULT_TEXT, RESULT_AUDIENCE = 92, RESULT_CROWN = 220 };

// StoryManager
enum STORY_STEP { STORY_SCENE, STORY_PLAY, STORY_END };

enum ENEMY_KIND { Matango = 0, SeekerBalloon = 160, GingerBreadman = 192 };

// Sound
enum SOUDN_BGM { INTRO_BGM, SELECT_BGM, BATTLE_MAP1_BGM, BATTLE_MAP2_BGM, BATTLE_RESULT_BGM, GAME_SCENE_BGM, STAGE1_BGM, STAGE_CLEAR_BGM }; // 8

enum SOUND_EFFRCT { SOUND_COIN, SOUND_BUTTON, SOUND_SELECT, SOUND_ITEM, SOUND_WALK, SOUND_SET_BOMB, SOUND_BOOM, SOUND_WIN, SOUND_READY }; // 9