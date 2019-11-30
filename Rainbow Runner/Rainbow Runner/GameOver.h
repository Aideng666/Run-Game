#pragma once

#include "Scene.h"

class GameOver : public Scene
{
public:
	GameOver(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
};