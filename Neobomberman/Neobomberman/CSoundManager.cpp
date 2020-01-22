#include"framework.h"
#include"CSoundManager.h"
#include"tinyxml.h"

CSoundManager* CSoundManager::Inst = nullptr;

CSoundManager* CSoundManager::getInstance() 
{
	if (Inst == nullptr) {
		Inst = new CSoundManager();
	}

	return Inst;
}

CSoundManager::CSoundManager() 
{
	System_Create(&pSystem);
	pSystem->init(17, FMOD_INIT_NORMAL, nullptr);

	LoadSoundData();
}

CSoundManager::~CSoundManager() 
{
	/*for (auto i : pChBGM)
	{
		i->stop();
	}*/
	for (int i = 0; i < pChBGM.size(); i++)
	{
		pChBGM[i]->stop();
		pBGM[i]->release();
	}

	for (int i = 0; i < pChEffect.size(); i++) 
	{
		pChEffect[i]->stop();
		pEffect[i]->release();
	}

	pSystem->close();
	pSystem->release();
}

void CSoundManager::LoadSoundData()
{
	TiXmlDocument doc;
	doc.LoadFile("SoundData.xml");

	TiXmlElement* pRoot = doc.FirstChildElement("Sound");
	if (!pRoot) return;

	// BGM 데이터 가져오기
	TiXmlElement* pElem = pRoot->FirstChildElement("BGM");
	TiXmlAttribute* pAttrib = nullptr;
	pAttrib = pElem->FirstAttribute();

	int nSoundCount = pAttrib->IntValue(); // BGM개수
	pBGM.resize(nSoundCount);
	pChBGM.resize(nSoundCount);

	pElem = pRoot->FirstChildElement("BGM")->FirstChildElement("Data");

	for (int i = 0; i < pBGM.size(); i++)
	{
		pSystem->createSound(pElem->GetText(), FMOD_LOOP_NORMAL, 0, &pBGM[i]);
		pElem = pElem->NextSiblingElement();
	}

	// Effect Sound 데이터 가져오기
	pElem = pRoot->FirstChildElement("Effect");
	pAttrib = pElem->FirstAttribute();

	nSoundCount = pAttrib->IntValue(); // EffectSound개수
	pEffect.resize(nSoundCount);
	pChEffect.resize(nSoundCount);

	pElem = pRoot->FirstChildElement("Effect")->FirstChildElement("Data");

	for (int i = 0; i < pEffect.size(); i++) 
	{
		pSystem->createSound(pElem->GetText(), FMOD_DEFAULT, 0, &pEffect[i]);
		pElem = pElem->NextSiblingElement();
	}
}

void CSoundManager::StartBGM(SOUDN_BGM BGM) 
{	
	m_BGM = BGM;
	pSystem->playSound(pBGM[m_BGM], 0, false, &pChBGM[static_cast<int>(m_BGM)]);
}

void CSoundManager::StopBGM() 
{
	pChBGM[static_cast<int>(m_BGM)]->stop();
}

void CSoundManager::StartEffect(SOUND_EFFRCT Sound) 
{
	m_Effect = Sound;
	pSystem->playSound(pEffect[static_cast<int>(m_Effect)], 0, false, &pChEffect[static_cast<int>(m_Effect)]);
}

void CSoundManager::StopEffect()
{
	pChEffect[static_cast<int>(m_Effect)]->stop();
}