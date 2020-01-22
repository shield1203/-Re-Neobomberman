#include"framework.h"
#include"CProcessManager.h"

#include"CGameFrame.h"
#include"CIntro.h"
#include"CModeSelect.h"
#include"CBattleManager.h"
#include"CStoryManager.h"

CProcessManager::CProcessManager(HWND hWnd) 
{
	GetWindowRect(hWnd, &WinRect);
	hProcWnd = hWnd;

	HBITMAP hBitmap;
	HDC hdc;

	hdc = GetDC(hWnd);
	hBackBuffer = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, WinRect.right - WinRect.left, WinRect.bottom - WinRect.top);
	SelectObject(hBackBuffer, (HBITMAP)hBitmap);
	DeleteObject(hBitmap);
	hBitmap = nullptr;
	ReleaseDC(hWnd, hdc);
	hdc = nullptr;

	m_Process = new CIntro(hProcWnd, hBackBuffer);
}

CProcessManager::~CProcessManager() 
{
	DeleteDC(hBackBuffer);
	hBackBuffer = nullptr;
}

void CProcessManager::Process() 
{
	Init();
	Update();
	Render();
}

void CProcessManager::Init()
{
	if (m_GameStep != m_PrevGameStep)
	{
		delete m_Process;
		m_Process = nullptr;

		switch (m_PrevGameStep)
		{
		case STEP_INTRO:
			m_Process = new CIntro(hProcWnd, hBackBuffer);
			break;
		case STEP_MODE_SELECT:
			m_Process = new CModeSelect(hProcWnd, hBackBuffer);
			break;
		case STEP_BATTLE:
			m_Process = new CBattleManager(hProcWnd, hBackBuffer);
			break;
		case STEP_STORY:
			m_Process = new CStory(hProcWnd, hBackBuffer);
			break;
		}

		m_Process->Init();

		m_PrevGameStep = m_GameStep;
	}
}

void CProcessManager::Update() 
{
	m_GameStep = m_Process->Update();
}

void CProcessManager::Render() 
{
	HDC hdc = GetDC(hProcWnd);

	m_Process->Render();

	BitBlt(hdc, 0, 0, WinRect.right - WinRect.left, WinRect.bottom - WinRect.top, hBackBuffer, 0, 0, SRCCOPY);
	ReleaseDC(hProcWnd, hdc);
	hdc = nullptr;
}