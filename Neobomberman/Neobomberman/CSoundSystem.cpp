#include"framework.h"
#include"CSoundSystem.h"
#include"tinyxml.h"

CSoundSystem* CSoundSystem::Inst = nullptr;

CSoundSystem* CSoundSystem::getInstance()
{
	if (Inst == nullptr) {
		Inst = new CSoundSystem();
	}
	
	return Inst;
}

CSoundSystem::CSoundSystem()
{
	System_Create(&pSystem);
	pSystem->init(17, FMOD_INIT_NORMAL, nullptr);

	LoadSoundData();
}

CSoundSystem::~CSoundSystem()
{
	for (auto bgm : m_BGM)
	{
		bgm.pChannel->stop();
		bgm.pSound->release();
	}

	for (auto effect : m_effect)
	{
		effect.pChannel->stop();
		effect.pSound->release();
	}

	pSystem->close();
	pSystem->release();
}

void CSoundSystem::LoadSoundData()
{
	TiXmlDocument doc;
	doc.LoadFile("SoundData.xml");

	TiXmlElement* pRoot = doc.FirstChildElement("Sound");
	if (!pRoot) return;

	// BGM 데이터 가져오기
	TiXmlElement* pElem = pRoot->FirstChildElement("BGM");
	TiXmlAttribute* pAttrib = nullptr;
	pAttrib = pElem->FirstAttribute();

	m_BGMTrackCount = pAttrib->IntValue(); // BGM개수
	m_BGM.resize(m_BGMTrackCount);

	pElem = pRoot->FirstChildElement("BGM")->FirstChildElement("SoundPath");

	for (auto sound : m_BGM)
	{
		pSystem->createSound(pElem->GetText(), FMOD_LOOP_NORMAL, 0, &sound.pSound);
		pElem = pElem->NextSiblingElement();
	}

	// Effect Sound 데이터 가져오기
	pElem = pRoot->FirstChildElement("Effect");
	pAttrib = pElem->FirstAttribute();

	m_effectTrackCount = pAttrib->IntValue(); // EffectSound개수
	m_effect.resize(m_effectTrackCount);

	pElem = pRoot->FirstChildElement("Effect")->FirstChildElement("SoundPath");

	for (auto effect : m_effect)
	{
		pSystem->createSound(pElem->GetText(), FMOD_DEFAULT, 0, &effect.pSound);
		pElem = pElem->NextSiblingElement();
	}
}

void CSoundSystem::StartBGM(SOUDN_BGM BGM)
{	
	m_curPlayBGM = BGM;
	pSystem->playSound(m_BGM[m_curPlayBGM].pSound, 0, false, &m_BGM[m_curPlayBGM].pChannel);
}

void CSoundSystem::StopBGM()
{
	m_BGM[m_curPlayBGM].pChannel->stop();
}

void CSoundSystem::StartEffect(SOUND_EFFRCT Sound)
{
	m_curPlayEffect = Sound;
	pSystem->playSound(m_effect[m_curPlayEffect].pSound, 0, false, &m_effect[m_curPlayEffect].pChannel);
}

void CSoundSystem::StopEffect()
{
	m_effect[m_curPlayEffect].pChannel->stop();
}