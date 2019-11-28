#include "PhysicsSystem.h"

void PhysicsSystem::Update(entt::registry * reg)
{
	auto view = reg->view<PhysicsBody, Transform>();

	for (auto entity : view)
	{
		auto& physBod = view.get<PhysicsBody>(entity);
		auto& trans = view.get<Transform>(entity);

		physBod.Update(&trans, Timer::deltaTime);
	}

	Run(reg);
}

void PhysicsSystem::Run(entt::registry * reg)
{
	auto view = reg->view<PhysicsBody, Transform>();

	for (auto entity : view)
	{
		auto& trans1 = view.get<Transform>(entity);
		auto& body1 = view.get<PhysicsBody>(entity);

		Box worldPosB;

		switch (body1.GetBodyType())
		{
		case BodyType::BOX:
			worldPosB.m_center = trans1.GetPosition() + vec3(body1.GetCenterOffset().x, body1.GetCenterOffset().y, 0.f);
			worldPosB.m_bottomLeft = trans1.GetPosition() + vec3(body1.GetBottomLeft().x, body1.GetBottomLeft().y, 0.f);
			worldPosB.m_topRight = trans1.GetPosition() + vec3(body1.GetTopRight().x, body1.GetTopRight().y, 0.f);
			worldPosB.m_bottomRight = vec3(worldPosB.m_topRight.x, worldPosB.m_bottomLeft.y, 0.f);
			worldPosB.m_topLeft = vec3(worldPosB.m_bottomLeft.x, worldPosB.m_topRight.y, 0.f);
			break;
		}

		if (body1.GetDynamic())
		{
			for (auto entity2 : view)
			{
				if (entity != entity2)
				{
					auto& trans2 = view.get<Transform>(entity2);
					auto& body2 = view.get<PhysicsBody>(entity2);

					Box worldPosB2;
					
					switch (body2.GetBodyType())
					{
					case BodyType::BOX:
						worldPosB2.m_center = trans2.GetPosition() + vec3(body2.GetCenterOffset().x, body2.GetCenterOffset().y, 0.f);
						worldPosB2.m_bottomLeft = trans2.GetPosition() + vec3(body2.GetBottomLeft().x, body2.GetBottomLeft().y, 0.f);
						worldPosB2.m_topRight = trans2.GetPosition() + vec3(body2.GetTopRight().x, body2.GetTopRight().y, 0.f);
						worldPosB2.m_bottomRight = vec3(worldPosB2.m_topRight.x, worldPosB2.m_bottomLeft.y, 0.f);
						worldPosB2.m_topLeft = vec3(worldPosB2.m_bottomLeft.x, worldPosB2.m_topRight.y, 0.f);
						break;
					}
					
					if (body1.GetBodyType() == BodyType::BOX)
					{
						if (body2.GetBodyType() == BodyType::BOX)
						{
							//Perform BOX-BOX collision
							if (BoxBoxCollision(std::pair<PhysicsBody&, Box>(body1, worldPosB), std::pair<PhysicsBody&, Box>(body2, worldPosB2)))
							{
								if (body1.GetColour() == body2.GetColour() || body2.GetColour() == 0 || body2.GetColour() == 4)
								{
									trans1.SetPosition(trans1.GetPosition() + (-body1.GetVelocity() * (Timer::deltaTime)));

									body1.SetAcceleration(vec3(0.f, 0.f, 0.f));
									body1.SetVelocity(vec3(0.f, 0.f, 0.f));
									if (body2.GetColour() == 4)
									{
										body1.SetColour(4);
									}
								}									
							}	
						}
					}																												
				}
			}
		}
	}
}

bool PhysicsSystem::BoxBoxCollision(std::pair<PhysicsBody&, Box> group1, std::pair<PhysicsBody&, Box> group2)
{
	if (group1.first.GetCollideID() & group2.first.GetBodyID())
	{
		bool axisXCollide = group1.second.m_bottomRight.x >= group2.second.m_bottomLeft.x &&
			group2.second.m_bottomRight.x >= group1.second.m_bottomLeft.x;

		bool axisYCollide = group1.second.m_topLeft.y >= group2.second.m_bottomLeft.y &&
			group2.second.m_topLeft.y >= group1.second.m_bottomLeft.y;

		return axisXCollide && axisYCollide;
	}
	else
	{
		return false;
	}
}

void PhysicsSystem::Init()
{
	physicsDrawShader.Load("./assets/shader/PhysicsDraw.vert", "./assets/shader/PhysicsDraw.frag");
}

void PhysicsSystem::Draw(entt::registry * reg)
{
	auto view = reg->view<PhysicsBody, Transform>();
	auto& cam = reg->get<Camera>(EntityIdentifier::MainCamera());

	if (PhysicsBody::GetDraw())
	{
		for (auto entity : view)
		{
			auto& physBody = view.get<PhysicsBody>(entity);
			auto& trans = view.get<Transform>(entity);

			Transform temp = trans;
			temp.SetScale(vec3(physBody.GetWidth(), physBody.GetHeight(), 1.f));
			temp.SetPosition(temp.GetPosition() + vec3(physBody.GetCenterOffset().x, physBody.GetCenterOffset().y, 0.f));
			temp.SetPositionZ(100.f);

			temp.Update();

			std::string fileName = "Masks/";

			if (physBody.GetBodyType() == BodyType::BOX)
			{
				fileName += "SquareMask.png";
			}

			Texture* mask = TextureManager::FindTexture(fileName);

			//Binds the draw shader
			physicsDrawShader.Bind();

			//Sends the uniforms we need for drawing the bodies
			physicsDrawShader.SendUniform("uView", cam.GetView());
			physicsDrawShader.SendUniform("uProj", cam.GetProjection());
			physicsDrawShader.SendUniform("uModel", temp.GetLocalToWorldMatrix());
			physicsDrawShader.SendUniform("uColor", vec4(1.f, 0.f, 0.f, 0.3f));

			mask->Bind(0);

			//Draws the body
			physBody.DrawBody();

			mask->Unbind(0);

			//Unbinds the shader
			physicsDrawShader.Unbind();
		}
	}
}
