#include "RainbowRunnerGame.h"

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
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Game Camera");
		ECS::SetIsMainCamera(entity, true);
	}

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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-40.f, -55.f, 100.f));//-40.f, -55.f, 100.f

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = tempSpr.GetWidth() / 2.f;
		float shrinkY = tempSpr.GetWidth() / 2.f;

		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(0.f,0.f),
			CollisionIDs::Player(), (CollisionIDs::Enemy() | CollisionIDs::Environment()), true);

		tempPhsBody.SetFriction(0.15f);
		tempPhsBody.SetMaxVelo(60.f);
		tempPhsBody.SetGravity(true);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Runner Animations");
		ECS::SetIsMainPlayer(entity, true);

		m_player = entity;
	}

	//Platforms
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		std::string fileName = "GreyPlatformL.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 256, 183);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, -160.f, -10.f));//50.f, -35.f, 100.f

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = (tempSpr.GetHeight() / 2.f);
		tempPhsBody = PhysicsBody(float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY),
			vec2(10.f, (tempSpr.GetHeight() / 16.f) * 2.f),
			CollisionIDs::Environment(), (0x0), false);

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Large Grey Platform");	
	}

	//Background #1
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Space Background.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));
		
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(384.f, 0.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Space Background 2");

		m_background2 = entity;
	}
}

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