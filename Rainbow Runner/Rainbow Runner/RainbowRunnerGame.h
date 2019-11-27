#pragma once

#include "Scene.h"

class RainbowRunnerGame : public Scene
{
public:
	RainbowRunnerGame(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	int GetBackground();
	int GetBackground2();
	int GetPlayer();

	int GetPlatformS();
	int GetPlatform1();
	int GetPlatform2();
	int GetPlatform3();
	int GetPlatform4();
	int GetPlatform5();
	int GetPlatform6();
	int GetPlatform7();
	int GetPlatform8();
	int GetPlatform9();
	int GetPlatform10();
	int GetPlatform11();
	int GetPlatform12();


	int GetRedBack();
	int GetBlueBack();
	int GetGreenBack();

	const float SHRINK_LX = 238.f;
	const float SHRINK_SX = 305.f;
	const float SHRINK_Y = 88.f;
	const float SHRINK_VECLX = 256.f;
	const float SHRINK_VECSX = 512.f;

private:
	int m_background;
	int m_background2;
	int m_player;

	int m_redBack;
	int m_blueBack;
	int m_greenBack;

	int platforms[20];
};