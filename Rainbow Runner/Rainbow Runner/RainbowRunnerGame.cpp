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

	//Player
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-130.f, 10.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 2.f - 1;
		float shrinkY = tempSpr.GetWidth() / 1.f + 10;

		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, -10.f),
			CollisionIDs::Player(), (CollisionIDs::Enemy() | CollisionIDs::Environment()), true);

		tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(85.f);
		tempPhsBody.SetGravity(true);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Runner Animations");
		ECS::SetIsMainPlayer(entity, true);

		m_player = entity;
	}

	//Start Signal
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Start.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 216, 49);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(10.f, 52.f, 100.f));


		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Down to Start");

		m_start = entity;
	}

	//Platforms
	//Level 1
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
			CollisionIDs::Environment(), (0x0), 0, false);

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(135.f, -73.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(307.f, -45.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(470.f, -45.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(633.f, -45.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(830.f, -45.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

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

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1020.f, -30.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 6");

		platforms[6] = entity;
	}
	//Platform 7
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1180.f, -17.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 7");

		platforms[7] = entity;
	}
	//Platform 8
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1340.f, -17.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 8");

		platforms[8] = entity;
	}
	//Platform 9
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1510.f, -7.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 9");

		platforms[9] = entity;
	}
	//Platform 10
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1680.f, 0.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 10");

		platforms[10] = entity;
	}
	//Platform 11
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(1880.f, 15.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 11");

		platforms[11] = entity;
	}
	////Platform 12
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(2080.f, 15.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 12");

		platforms[12] = entity;
	}
	//Platform 13
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(2300.f, -70.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 13");

		platforms[13] = entity;
	}
	//Platform 14
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(2500.f, -55.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 14");

		platforms[14] = entity;
	}
	//Platform 15
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(2670.f, -45.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 15");

		platforms[15] = entity;
	}
	//Platform 16
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(2830.f, -30.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 16");

		platforms[16] = entity;
	}
	//Platform 17
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3000.f, -27.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 17");

		platforms[17] = entity;
	}
	//Platform 18
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3200.f, -27.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 18");

		platforms[18] = entity;
	}
	//Platform 19
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3400.f, -27.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 19");

		platforms[19] = entity;
	}
	//Platform 20
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3580.f, -27.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 20");

		platforms[20] = entity;
	}
	//Platform 21
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3750.f, -27.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 21");

		platforms[21] = entity;
	}
	//Platform 22
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3960.f, -75.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 22");

		platforms[22] = entity;
	}
	//Platform 23
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(4180.f, -75.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 23");

		platforms[23] = entity;
	}
	//Platform 24
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(4380.f, -75.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 24");

		platforms[24] = entity;
	}
	//Platform 25
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(4580.f, -75.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 25");

		platforms[25] = entity;
	}
	//Platform 26
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(4780.f, -75.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 26");

		platforms[26] = entity;
	}
	//Platform 27
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(4980.f, -60.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 27");

		platforms[27] = entity;
	}
	//Platform 28
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(5180.f, -50.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 28");

		platforms[28] = entity;
	}
	//Platform 29
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(5380.f, -40.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 29");

		platforms[29] = entity;
	}
	//Platform 30
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(5580.f, -30.f, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 30");

		platforms[30] = entity;
	}
	//Platform 31
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(5720.f, -27, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 31");

		platforms[31] = entity;
	}
	//Platform 32
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(5860.f, -2, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 32");

		platforms[32] = entity;
	}
	//Platform 33
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(6000.f, -13, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 33");

		platforms[33] = entity;
	}
	//Platform 34
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(6200.f, 0, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 34");

		platforms[34] = entity;
	}

#pragma region Coloured Backgrounds
	//Red Colour Back
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "RedBackground2.png";
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

		std::string fileName = "BlueBackground2.png";
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

		std::string fileName = "GreenBackground2.png";
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

int RainbowRunnerGame::GetPlatformS()
{
	return platforms[0];
}

int RainbowRunnerGame::GetPlatform1()
{
	return platforms[1];
}

int RainbowRunnerGame::GetPlatform2()
{
	return platforms[2];
}
int RainbowRunnerGame::GetPlatform3()
{
	return platforms[3];
}
int RainbowRunnerGame::GetPlatform4()
{
	return platforms[4];
}
int RainbowRunnerGame::GetPlatform5()
{
	return platforms[5];
}
int RainbowRunnerGame::GetPlatform6()
{
	return platforms[6];
}
int RainbowRunnerGame::GetPlatform7()
{
	return platforms[7];
}
int RainbowRunnerGame::GetPlatform8()
{
	return platforms[8];
}
int RainbowRunnerGame::GetPlatform9()
{
	return platforms[9];
}
int RainbowRunnerGame::GetPlatform10()
{
	return platforms[10];
}
int RainbowRunnerGame::GetPlatform11()
{
	return platforms[11];
}
int RainbowRunnerGame::GetPlatform12()
{
	return platforms[12];
}
int RainbowRunnerGame::GetPlatform13()
{
	return platforms[13];
}
int RainbowRunnerGame::GetPlatform14()
{
	return platforms[14];
}
int RainbowRunnerGame::GetPlatform15()
{
	return platforms[15];
}
int RainbowRunnerGame::GetPlatform16()
{
	return platforms[16];
}
int RainbowRunnerGame::GetPlatform17()
{
	return platforms[17];
}
int RainbowRunnerGame::GetPlatform18()
{
	return platforms[18];
}
int RainbowRunnerGame::GetPlatform19()
{
	return platforms[19];
}
int RainbowRunnerGame::GetPlatform20()
{
	return platforms[20];
}
int RainbowRunnerGame::GetPlatform21()
{
	return platforms[21];
}
int RainbowRunnerGame::GetPlatform22()
{
	return platforms[22];
}
int RainbowRunnerGame::GetPlatform23()
{
	return platforms[23];
}
int RainbowRunnerGame::GetPlatform24()
{
	return platforms[24];
}
int RainbowRunnerGame::GetPlatform25()
{
	return platforms[25];
}
int RainbowRunnerGame::GetPlatform26()
{
	return platforms[26];
}
int RainbowRunnerGame::GetPlatform27()
{
	return platforms[27];
}
int RainbowRunnerGame::GetPlatform28()
{
	return platforms[28];
}
int RainbowRunnerGame::GetPlatform29()
{
	return platforms[29];
}
int RainbowRunnerGame::GetPlatform30()
{
	return platforms[30];
}
int RainbowRunnerGame::GetPlatform31()
{
	return platforms[31];
}
int RainbowRunnerGame::GetPlatform32()
{
	return platforms[32];
}
int RainbowRunnerGame::GetPlatform33()
{
	return platforms[33];
}
int RainbowRunnerGame::GetPlatform34()
{
	return platforms[34];
}
int RainbowRunnerGame::GetStart()
{
	return m_start;
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
