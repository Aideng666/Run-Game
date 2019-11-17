#pragma once

#include "Scene.h"

class RulesScene : public Scene
{
public:
	RulesScene(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
};