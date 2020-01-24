#pragma once

struct SpriteData
{
	// ������ �̹����� ��ȣ
	unsigned int imageNum; 

	// ȭ��� ��ǥ
	int xpos, ypos; 
	unsigned int width, high;

	// �̹����� ��ǥ
	unsigned int originXpos, originYpos, originWidth, originHigh;

	// ���� �÷���
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
