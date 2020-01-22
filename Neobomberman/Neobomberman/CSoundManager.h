#pragma once

class CSoundManager {
private:
	static CSoundManager* Inst;
	CSoundManager();

	System* pSystem;

	// Sound
	vector<Sound*> pBGM;
	vector<Sound*> pEffect;

	// Channel
	vector<Channel*> pChBGM; // 8가지
	vector<Channel*> pChEffect; // 9가지

	SOUDN_BGM m_BGM = INTRO_BGM;
	SOUND_EFFRCT m_Effect = SOUND_COIN;
public:
	static CSoundManager* getInstance();

	void LoadSoundData();
	void StartBGM(SOUDN_BGM BGM);
	void StopBGM();
	void StartEffect(SOUND_EFFRCT Sound);
	void StopEffect();

	~CSoundManager();
};