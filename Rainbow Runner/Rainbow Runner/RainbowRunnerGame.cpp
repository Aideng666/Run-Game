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

		m_cam = entity;
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
		float shrinkY = tempSpr.GetWidth() / 1.f + 14;

		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, -13.f),
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
			CollisionIDs::Environment(), (0x0), 2, false);

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
			CollisionIDs::Environment(), (0x0), 2, false);

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
	//Platform 12
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(3950.f, -75.f, 100.f));

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(5750.f, -27, 100.f));

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(6000.f, -20, 100.f));

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
	//Platform 35
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(6400.f, -70, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 35");

		platforms[35] = entity;
	}
	//Platform 36
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(6600.f, -70, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 36");

		platforms[36] = entity;
	}
	//Platform 37
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(6800.f, -65, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 37");

		platforms[37] = entity;
	}
	//Platform 38
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(7010.f, -55, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 38");

		platforms[38] = entity;
	}
	//Platform 39
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(7160.f, -48, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 39");

		platforms[39] = entity;
	}
	//Platform 40
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(7310.f, -41, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 40");

		platforms[40] = entity;
	}
	//Platform 41
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(7460.f, -34, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 41");

		platforms[41] = entity;
	}
	//Platform 42
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(7610.f, -27, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 42");

		platforms[42] = entity;
	}
	//Platform 43
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(7760.f, -20, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 43");

		platforms[43] = entity;
	}
	//Platform 44
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(7910.f, -13, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 44");

		platforms[44] = entity;
	}
	//Platform 45
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(8060.f, -6, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 45");

		platforms[45] = entity;
	}
	//Platform 46
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(8210.f, 1, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 46");

		platforms[46] = entity;
	}
	//Platform 47
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(8360.f, 8, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 47");

		platforms[47] = entity;
	}
	//Platform 48
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(8600.f, 8, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 48");

		platforms[48] = entity;
	}
	//Platform 49
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(8810.f, -80, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 49");

		platforms[49] = entity;
	}
	//Platform 50
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(8970.f, -70, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 50");

		platforms[50] = entity;
	}
	//Platform 51
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(9130.f, -60, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 51");

		platforms[51] = entity;
	}
	//Platform 52
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(9290.f, -50, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 52");

		platforms[52] = entity;
	}
	//Platform 53
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(9450.f, -40, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 53");

		platforms[53] = entity;
	}
	//Platform 54
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(9680.f, -30, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 54");

		platforms[54] = entity;
	}
	//Platform 55
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(9900.f, -30, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 55");

		platforms[55] = entity;
	}
	//Platform 56
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(10100.f, -50, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 56");

		platforms[56] = entity;
	}
	//Platform 57
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(10250.f, -50, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 57");

		platforms[57] = entity;
	}
	//Platform 58
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(10400.f, -30, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 58");

		platforms[58] = entity;
	}
	//Platform 59
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(10550.f, -30, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 59");

		platforms[59] = entity;
	}
	//Platform 60
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(10700.f, -30, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 60");

		platforms[60] = entity;
	}
	//Platform 61
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(10850.f, -30, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 61");

		platforms[61] = entity;
	}
	//Platform 62
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(11060.f, -30, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 62");

		platforms[62] = entity;
	}
	//Platform 63
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(11060.f, -30, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 63");

		platforms[63] = entity;
	}
	//Platform 64
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(11220.f, -70, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 64");

		platforms[64] = entity;
	}
	//Platform 65
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "RedPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(11220.f, 0, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 3, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 65");

		platforms[65] = entity;
	}
	//Platform 66
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "BluePlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(11420.f, 0, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 2, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 66");

		platforms[66] = entity;
	}
	//Platform 67
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "YellowPlatformS.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(11420.f, -70, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 1, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 67");

		platforms[67] = entity;
	}
	//Platform 68
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(11620.f, -35, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_LX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECLX) * 2.f),
			CollisionIDs::Environment(), (0x0), 0, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Platform 68");

		platforms[68] = entity;
	}
	//Final Platform
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "FinalPlatform.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(11820.f, -35, 100.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = SHRINK_SX;
		float shrinkY = ((tempSpr.GetHeight() / 2.f) + SHRINK_Y);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f, (tempSpr.GetHeight() / SHRINK_VECSX) * 2.f),
			CollisionIDs::Environment(), (0x0), 4, false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Final Platform");

		platforms[69] = entity;
	}

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
int RainbowRunnerGame::GetPlatform35()
{
	return platforms[35];
}
int RainbowRunnerGame::GetPlatform36()
{
	return platforms[36];
}
int RainbowRunnerGame::GetPlatform37()
{
	return platforms[37];
}
int RainbowRunnerGame::GetPlatform38()
{
	return platforms[38];
}
int RainbowRunnerGame::GetPlatform39()
{
	return platforms[39];
}
int RainbowRunnerGame::GetPlatform40()
{
	return platforms[40];
}
int RainbowRunnerGame::GetPlatform41()
{
	return platforms[41];
}
int RainbowRunnerGame::GetPlatform42()
{
	return platforms[42];
}
int RainbowRunnerGame::GetPlatform43()
{
	return platforms[43];
}
int RainbowRunnerGame::GetPlatform44()
{
	return platforms[44];
}
int RainbowRunnerGame::GetPlatform45()
{
	return platforms[45];
}
int RainbowRunnerGame::GetPlatform46()
{
	return platforms[46];
}
int RainbowRunnerGame::GetPlatform47()
{
	return platforms[47];
}
int RainbowRunnerGame::GetPlatform48()
{
	return platforms[48];
}
int RainbowRunnerGame::GetPlatform49()
{
	return platforms[49];
}
int RainbowRunnerGame::GetPlatform50()
{
	return platforms[50];
}
int RainbowRunnerGame::GetPlatform51()
{
	return platforms[51];
}
int RainbowRunnerGame::GetPlatform52()
{
	return platforms[52];
}
int RainbowRunnerGame::GetPlatform53()
{
	return platforms[53];
}
int RainbowRunnerGame::GetPlatform54()
{
	return platforms[54];
}
int RainbowRunnerGame::GetPlatform55()
{
	return platforms[55];
}
int RainbowRunnerGame::GetPlatform56()
{
	return platforms[56];
}
int RainbowRunnerGame::GetPlatform57()
{
	return platforms[57];
}
int RainbowRunnerGame::GetPlatform58()
{
	return platforms[58];
}
int RainbowRunnerGame::GetPlatform59()
{
	return platforms[59];
}
int RainbowRunnerGame::GetPlatform60()
{
	return platforms[60];
}
int RainbowRunnerGame::GetPlatform61()
{
	return platforms[61];
}
int RainbowRunnerGame::GetPlatform62()
{
	return platforms[62];
}
int RainbowRunnerGame::GetPlatform63()
{
	return platforms[63];
}
int RainbowRunnerGame::GetPlatform64()
{
	return platforms[64];
}
int RainbowRunnerGame::GetPlatform65()
{
	return platforms[65];
}
int RainbowRunnerGame::GetPlatform66()
{
	return platforms[66];
}
int RainbowRunnerGame::GetPlatform67()
{
	return platforms[67];
}
int RainbowRunnerGame::GetPlatform68()
{
	return platforms[68];
}
int RainbowRunnerGame::GetPlatform69()
{
	return platforms[69];
}
#pragma endregion

int RainbowRunnerGame::GetStart()
{
	return m_start;
}
int RainbowRunnerGame::GetCam()
{
	return m_cam;
}

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
