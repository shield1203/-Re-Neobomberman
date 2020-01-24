#include"framework.h"
#include"CResourceManager.h"
#include"tinyxml.h"

CResourceManager* CResourceManager::Inst = nullptr;

CResourceManager* CResourceManager::getInstance()
{
	if (Inst == nullptr) {
		Inst = new CResourceManager();
	}

	return Inst;
}

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
	ReleaseData();
}

void CResourceManager::LoadStepData(GAME_STEP step)
{
	m_curStep = step;

	TiXmlDocument doc;
	doc.LoadFile("ResourceData.xml");

	TiXmlElement* pRoot = doc.FirstChildElement("Resource");
	if (!pRoot) return;

	const char* strElem = nullptr;

	switch (m_curStep)
	{
	case STEP_INTRO:
		strElem = "Intro";
		break;
	case STEP_MODE_SELECT:
		strElem = "ModeSelect";
		break;
	case STEP_STORY:
		strElem = "Story";
		break;
	case STEP_BATTLE:
		strElem = "Battle";
		break;
	}

	TiXmlElement* pElem = pRoot->FirstChildElement(strElem);
	TiXmlAttribute* pAttrib = nullptr;
	pAttrib = pElem->FirstAttribute();

	m_ImageCount = pAttrib->IntValue();
	pAttrib = pAttrib->Next();

	int nBackgroundCount = pAttrib->IntValue();
	pAttrib = pAttrib->Next();

	int nSpriteCount = pAttrib->IntValue();
	pAttrib = pAttrib->Next();

	m_hImageDC.resize(m_ImageCount);
	m_backgroundData.resize(nBackgroundCount);
	m_spriteData.resize(nSpriteCount);

	pElem = pRoot->FirstChildElement(strElem)->FirstChildElement("ImagePath");
	for (auto dc : m_hImageDC)
	{
		dc = CreateBmpDC(pElem->GetText());
		pElem = pElem->NextSiblingElement();;
	}

	pElem = pRoot->FirstChildElement(strElem)->FirstChildElement("BackgroundData");
	for (auto backgroundNum : m_backgroundData)
	{
		pAttrib = pElem->FirstAttribute();
		backgroundNum = new unsigned int(pAttrib->IntValue());
		pElem = pElem->NextSiblingElement();
	}

	pElem = pRoot->FirstChildElement(strElem)->FirstChildElement("SpriteData");
	for (auto spriteData : m_spriteData)
	{
		spriteData = new SpriteData();

		pAttrib = pElem->FirstAttribute();
		spriteData->imageNum = pAttrib->IntValue();
		pAttrib->Next();

		// 게임내 좌표
		spriteData->xpos = pAttrib->IntValue();
		pAttrib->Next();

		spriteData->ypos = pAttrib->IntValue();
		pAttrib->Next();

		spriteData->width = pAttrib->IntValue();
		pAttrib->Next();

		spriteData->high = pAttrib->IntValue();
		pAttrib->Next();

		// 이미지내에서 좌표
		spriteData->originXpos = pAttrib->IntValue();
		pAttrib->Next();

		spriteData->originYpos = pAttrib->IntValue();
		pAttrib->Next();

		spriteData->originWidth = pAttrib->IntValue();
		pAttrib->Next();

		spriteData->originHigh = pAttrib->IntValue();
		pAttrib->Next();

		// 제외 색상
		spriteData->r = pAttrib->IntValue();
		pAttrib->Next();

		spriteData->g = pAttrib->IntValue();
		pAttrib->Next();

		spriteData->b = pAttrib->IntValue();
		pAttrib->Next();

		pElem = pElem->NextSiblingElement();
	}
}

HDC CResourceManager::CreateBmpDC(const char* filename)
{
	HBITMAP hBitmap;
	HDC hdc = GetDC(g_hWnd);
	HDC hMemDC = CreateCompatibleDC(hdc);
	hBitmap = (HBITMAP)LoadImage(NULL, TEXT(filename), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	SelectObject(hMemDC, hBitmap);
	DeleteObject(hBitmap);
	ReleaseDC(g_hWnd, hdc);
	return hMemDC;
}

void CResourceManager::ReleaseData()
{
	for (auto dc : m_hImageDC)
	{
		ReleaseDC(g_hWnd, dc);
	}
	m_hImageDC.clear();

	for (auto backgroundNum : m_backgroundData)
	{
		SafeDelete(backgroundNum);
	}
	m_backgroundData.clear();

	for (auto spriteData : m_spriteData)
	{
		SafeDelete(spriteData);
	}
	m_spriteData.clear();
}

void CResourceManager::DrawingBackground(HDC Backbuffer, unsigned int backgroundNum)
{
	BitBlt(Backbuffer, 0, 0, WIN_RIGHT, WIN_LEFT, m_hImageDC[*m_backgroundData[backgroundNum]], 0, 0, SRCCOPY);
}

void CResourceManager::DrawingSprite(HDC Backbuffer, unsigned int spriteNum)
{
	TransparentBlt(Backbuffer, m_spriteData[spriteNum]->xpos, m_spriteData[spriteNum]->ypos, m_spriteData[spriteNum]->width, m_spriteData[spriteNum]->high, 
		m_hImageDC[m_spriteData[spriteNum]->imageNum], m_spriteData[spriteNum]->originXpos, m_spriteData[spriteNum]->originYpos, m_spriteData[spriteNum]->originWidth, m_spriteData[spriteNum]->originHigh,
		RGB(m_spriteData[spriteNum]->r, m_spriteData[spriteNum]->g, m_spriteData[spriteNum]->b));
}