#pragma once

struct SpriteData
{
	// 참고할 이미지의 번호
	unsigned int imageNum; 

	// 화면상 좌표
	int xpos, ypos; 
	unsigned int width, high;

	// 이미지상 좌표
	unsigned int originXpos, originYpos, originWidth, originHigh;

	// 제외 컬러값
	unsigned int r, g, b;
};

class CResourceManager
{
private:
	static CResourceManager* Inst;
	CResourceManager();

	GAME_STEP m_curStep;
public:
	unsigned int m_ImageCount = 0;
	vector<HDC> m_hImageDC;
	vector<unsigned int*> m_backgroundData;
	vector<SpriteData*> m_spriteData;
public:
	static CResourceManager* getInstance();

	void LoadStepData(GAME_STEP);
	HDC CreateBmpDC(const char*);
	void ReleaseData();

	void DrawingBackground(HDC, unsigned int);
	void DrawingSprite(HDC, unsigned int);

	~CResourceManager();
};
