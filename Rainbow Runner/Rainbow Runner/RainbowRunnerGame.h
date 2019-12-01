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
	int GetPlatform13();
	int GetPlatform14();
	int GetPlatform15();
	int GetPlatform16();
	int GetPlatform17();
	int GetPlatform18();
	int GetPlatform19();
	int GetPlatform20();
	int GetPlatform21();
	int GetPlatform22();
	int GetPlatform23();
	int GetPlatform24();
	int GetPlatform25();
	int GetPlatform26();
	int GetPlatform27();
	int GetPlatform28();
	int GetPlatform29();
	int GetPlatform30();
	int GetPlatform31();
	int GetPlatform32();
	int GetPlatform33();
	int GetPlatform34();

	int GetStart();

	int GetRedBack();
	int GetBlueBack();
	int GetGreenBack();

	const float SHRINK_LX = 238.f;
	const float SHRINK_SX = 305.f;
	const float SHRINK_Y = 98.f;
	const float SHRINK_VECLX = 64.f;
	const float SHRINK_VECSX = 64.f;

private:
	int m_background;
	int m_background2;
	int m_player;

	int m_redBack;
	int m_blueBack;
	int m_greenBack;

	int m_start;

	int platforms[40];
};