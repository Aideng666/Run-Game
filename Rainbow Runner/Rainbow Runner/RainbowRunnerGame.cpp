#include "RainbowRunnerGame.h"
#include "PhysicsBody.h"

RainbowRunnerGame::RainbowRunnerGame(std::string name)
	: Scene(name)
{
}

void RainbowRunnerGame::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//Game Camera
	{
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);

		ECS::AttachComponent<Camera>(entity);
		//ECS::AttachComponent<HorizontalScroll>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit() | EntityIdentifier::HoriScrollCameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Game Camera");
		ECS::SetIsMainCamera(entity, true);

		//ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		//ECS::GetComponent<HorizontalScroll>(entity).SetOffest(15.f);
	}

#pragma region PLAYER
	//Runner Sprite
	{
		auto moving = File::LoadJSON("runner.json");

		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainPlayer(entity);

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RunnerSprites.png";
		auto &animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);

		animController.AddAnimation(moving["run"]);
		animController.GetAnimation(0).SetRepeating(true);
		animController.AddAnimation(moving["jump"]);
		animController.GetAnimation(1).SetRepeating(false);

		animController.SetActiveAnim(0);

		auto &anim = animController.GetAnimation(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 35, 50, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-130.f, 0.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 2.f;
		float shrinkY = tempSpr.GetWidth() / 2.f;

		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, 0.f),
			CollisionIDs::Player(), (CollisionIDs::Enemy() | CollisionIDs::Environment()), true);

		tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(85.f);
		tempPhsBody.SetGravity(true);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Runner Animations");
		ECS::SetIsMainPlayer(entity, true);

		m_player = entity;
	}

#pragma endregion

#pragma region PLATFORMS
	//Platforms
	//Starting Platform
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-100.f, -73.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Starting Platform");

		platforms[0] = entity;
	}
	//Platform 1
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(84.f, -73.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 1");

		platforms[1] = entity;
	}
	//Platform 2
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(250.f, -40.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 2");

		platforms[2] = entity;
	}
	//Platform 3
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(380.f, -40.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 3");

		platforms[3] = entity;
	}
	//Platform 4
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(620.f, -60.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 4");

		platforms[4] = entity;
	}
	//Platform 5
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(800.f, -60.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 5");

		platforms[5] = entity;
	}
	//Platform 6
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1000.f, -60.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 6");

		platforms[6] = entity;
	}
#pragma endregion

#pragma region Coloured Backgrounds
	//Red Colour Back
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "RedBackground.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Red Background");

		m_redBack = entity;
	}
	//Blue Colour Back
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "BlueBackground.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Blue Background");

		m_blueBack = entity;
	}
	//Green Colour Back
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "GreenBackground.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 0.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Green Background");

		m_greenBack = entity;
	}
#pragma endregion

#pragma region BACKGROUNDS
	//Background #1
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Space Background.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 50.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Space Background 1");

		m_background = entity;
	}
	//Background #2
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Space Background.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(384.f, 0.f, 50.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Space Background 2");

		m_background2 = entity;
	}
#pragma endregion

	//ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

#pragma region Functions
int RainbowRunnerGame::GetBackground()
{
	return m_background;
}

int RainbowRunnerGame::GetBackground2()
{
	return m_background2;
}

int RainbowRunnerGame::GetPlayer()
{
	return m_player;
}

int RainbowRunnerGame::GetPlatform1()
{
	return platforms[0];
}

int RainbowRunnerGame::GetPlatform2()
{
	return platforms[1];
}

int RainbowRunnerGame::GetPlatform3()
{
	return platforms[2];
}
int RainbowRunnerGame::GetPlatform4()
{
	return platforms[3];
}
int RainbowRunnerGame::GetPlatform5()
{
	return platforms[4];
}
int RainbowRunnerGame::GetPlatform6()
{
	return platforms[5];
}
int RainbowRunnerGame::GetPlatform7()
{
	return platforms[6];
}
#pragma endregion

int RainbowRunnerGame::GetRedBack()
{
	return m_redBack;
}
int RainbowRunnerGame::GetBlueBack()
{
	return m_blueBack;
}
int RainbowRunnerGame::GetGreenBack()
{
	return m_greenBack;
}