#pragma once

#include "Scene.h"

class RulesSection : public Scene
{
public:
	RulesSection(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
};