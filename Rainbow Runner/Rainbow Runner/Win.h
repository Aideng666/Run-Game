#pragma once

#include "Scene.h"

class Win : public Scene
{
public:
	Win(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
};
