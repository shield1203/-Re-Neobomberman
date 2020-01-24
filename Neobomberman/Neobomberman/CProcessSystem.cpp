#include"framework.h"
#include"CProcessSystem.h"

#include"CResourceManager.h"
#include"CGameFrame.h"
#include"CIntro.h"
#include"CModeSelect.h"
#include"CBattleSystem.h"
#include"CStorySystem.h"

CProcessSystem::CProcessSystem()
{
	GetWindowRect(g_hWnd, &WinRect);
	HBITMAP hBitmap;
	HDC hdc;

	hdc = GetDC(g_hWnd);
	hBackBuffer = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, WinRect.right - WinRect.left, WinRect.bottom - WinRect.top);
	SelectObject(hBackBuffer, (HBITMAP)hBitmap);
	DeleteObject(hBitmap);
	hBitmap = nullptr;
	ReleaseDC(g_hWnd, hdc);
	hdc = nullptr;

	m_Process = new CIntro(g_hWnd, hBackBuffer);
	CResourceManager::getInstance()->LoadStepData(STEP_INTRO);
}

CProcessSystem::~CProcessSystem()
{
	DeleteDC(hBackBuffer);
	hBackBuffer = nullptr;
}

void CProcessSystem::Process()
{
	Init();
	Update();
	Render();
}

void CProcessSystem::Init()
{
	if (m_GameStep != m_PrevGameStep)
	{
		SafeDelete(m_Process);
		CResourceManager::getInstance()->ReleaseData();

		switch (m_GameStep)
		{
		case STEP_INTRO:
			m_Process = new CIntro(hBackBuffer);
			break;
		case STEP_MODE_SELECT:
			m_Process = new CModeSelect(hBackBuffer);
			break;
		case STEP_BATTLE:
			m_Process = new CBattleSystem(hBackBuffer);
			break;
		case STEP_STORY:
			m_Process = new CStorySystem(hBackBuffer);
			break;
		}

		m_Process->Init();
		CResourceManager::getInstance()->LoadStepData(m_GameStep);

		m_PrevGameStep = m_GameStep;
	}
}

void CProcessSystem::Update()
{
	m_GameStep = m_Process->Update();
}

void CProcessSystem::Render()
{
	HDC hdc = GetDC(g_hWnd);

	m_Process->Render();

	BitBlt(hdc, 0, 0, WinRect.right - WinRect.left, WinRect.bottom - WinRect.top, hBackBuffer, 0, 0, SRCCOPY);
	ReleaseDC(g_hWnd, hdc);
	hdc = nullptr;
}