#pragma once

#include "Scene.h"

class RainbowRunnerGame : public Scene
{
public:
	RainbowRunnerGame(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;

	int GetBackground();
	int GetBackground2();

private:
	int m_background;
	int m_background2;
};
