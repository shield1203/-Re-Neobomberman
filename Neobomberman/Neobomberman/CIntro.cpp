#include"CIntro.h"
#include"CGameFrame.h"
#include"CSoundManager.h"
#include"tinyxml.h"

CIntro::CIntro(HWND hWnd, HDC hBackbuffer) : CGameFrame(hWnd, hBackbuffer) 
{ 
}

CIntro::~CIntro() 
{
	DeleteDC(hIntroDC); 
	hIntroDC = nullptr;
	DeleteDC(hNumberDC);
	hNumberDC = nullptr;
	DeleteDC(hTextDC);
	hTextDC = nullptr;
}

void CIntro::Init() 
{
	LoadData();

	CSoundManager::getInstance()->StopBGM();
	CSoundManager::getInstance()->StartBGM(INTRO_BGM);
}

void CIntro::LoadData()
{
	TiXmlDocument doc;
	doc.LoadFile("ResourceData.xml");

	TiXmlElement* pRoot = doc.FirstChildElement("Resource");
	if (!pRoot) return;

	TiXmlElement* pElem = pRoot->FirstChildElement("Intro")->FirstChildElement("Data");
	hIntroDC = CreateBmpDC(pElem->GetText());
	pElem = pElem->NextSiblingElement();
	hNumberDC = CreateBmpDC(pElem->GetText());
	pElem = pElem->NextSiblingElement();
	hTextDC = CreateBmpDC(pElem->GetText());
}

GAME_STEP CIntro::Update() 
{
	nCurTime = GetTickCount64();
	CheckCoin();
	PressKey();

	return m_GameStep;
}

void CIntro::Render() 
{
	BitBlt(hBackbuffer, 0, 0, WIN_RIGHT, WIN_BOTTOM, hIntroDC, 0, 0, SRCCOPY);

	if (bCoin) {
		TransparentBlt(hBackbuffer, 448, 578, 415, 32, hTextDC, 0, 0, 415, 32, RGB(R_COLOR, G_COLOR, B_COLOR)); // PUSH P1 START
	}

	if (nCoin >= 2) {
		TransparentBlt(hBackbuffer, 870, 865, 224, 32, hTextDC, 0, 64, 224, 32, RGB(R_COLOR, G_COLOR, B_COLOR));
	}
	else {
		TransparentBlt(hBackbuffer, 870, 865, 192, 32, hTextDC, 0, 32, 192, 32, RGB(R_COLOR, G_COLOR, B_COLOR)); // 크래딧
	}

	TransparentBlt(hBackbuffer, 1114, 865, 28, 32, hNumberDC, (nCoin / 10) * 28, 0, 28, 32, RGB(R_COLOR, G_COLOR, B_COLOR));
	TransparentBlt(hBackbuffer, 1142, 865, 28, 32, hNumberDC, (nCoin % 10) * 28, 0, 28, 32, RGB(R_COLOR, G_COLOR, B_COLOR));
}

void CIntro::PressKey() 
{
	if (GetKeyState(KEY_5) < 0 && nCurTime - nButtonTime > 150) { // 코인 투입!
		nButtonTime = nCurTime;

		if (nCoin < 100) {
			nCoin++;
			bCoin = true;
		}
		CSoundManager::getInstance()->StopBGM();
		CSoundManager::getInstance()->StartEffect(SOUND_COIN);
	}
	else if (GetKeyState(KEY_1) < 0 && nCurTime - nButtonTime > 150) {
		nButtonTime = nCurTime;

		if (nCoin > 0) {
			m_GameStep = STEP_MODE_SELECT;
		}
	}
}

void CIntro::CheckCoin() 
{
	if (nCurTime - nTextTime > 200 && nCoin == 0) {
		nTextTime = nCurTime;
		if (bCoin) {
			bCoin = false;
		}
		else {
			bCoin = true;
		}
	}
}