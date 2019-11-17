#include "RainbowRunner.h"

RainbowRunner::RainbowRunner(std::string name)
	: Scene(name)
{
}

void RainbowRunner::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//Main Camera
	{
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);

		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	}

	////Main Menu Screen
	//{
	//	auto entity = ECS::CreateEntity();
	//	
	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);

	//	std::string fileName = "Main Menu.png";
	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

	//	unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
	//	ECS::SetUpIdentifier(entity, bitHolder, "Main Menu");
	//}

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

int RainbowRunner::GetBackground()
{
	return m_background;
}

int RainbowRunner::GetBackground2()
{
	return m_background2;
}