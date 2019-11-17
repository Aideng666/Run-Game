#pragma once

#include "Scene.h"

class RainbowRunner : public Scene
{
public:
	RainbowRunner(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
};
