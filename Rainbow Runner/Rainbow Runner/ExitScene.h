#pragma once

#include "Scene.h"

class ExitScene : public Scene
{
public:
	ExitScene(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
};