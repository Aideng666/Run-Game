#include "RulesScene.h"

RulesScene::RulesScene(std::string name)
	: Scene(name)
{
}

void RulesScene::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;

	ECS::AttachRegister(m_sceneReg);

	float aspectRatio = windowWidth / windowHeight;

	//Rules Screen Camera
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Camera>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Rules Camera");
	}

	//Rules Screen Image
	{
		auto entity = ECS::CreateEntity();

		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		std::string fileName = "Rules Menu.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 384, 200);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 100.f));

		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Rules Selection");
	}
}