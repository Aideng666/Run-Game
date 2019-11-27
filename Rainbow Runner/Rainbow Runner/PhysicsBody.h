#pragma once

#include <GL/glew.h>
#include "JSON.h"
#include "Vector.h"
#include "VertexManager.h"
#include "EntityIdentifier.h"
#include "Transform.h"

enum class BodyType
{
	BOX,

	NUM_TYPES
};

struct CollisionIDs
{
public:
	static unsigned int Player();
	static unsigned int Environment();
	static unsigned int Enemy();

private:
	static unsigned int m_playerID;
	static unsigned int m_environmentID;
	static unsigned int m_enemyID;
};

class PhysicsBody
{
public:
	PhysicsBody() {};
	PhysicsBody(vec2 botLeft, vec2 topRight, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic = false);
	PhysicsBody(float width, float height, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic = false);
	PhysicsBody(float width, float height, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, int colour, bool isDynamic = false);

	void Update(Transform* trans, float dt);

	void ApplyForce(vec3 force);

	void InitBody();
	void DrawBody();

	vec3 GetForce() const;
	vec3 GetAcceleration() const;
	float GetMaxVelo() const;
	vec3 GetVelocity() const;
	float GetFriction() const;
	static vec3 GetGravityAcceleration();
	bool GetGravity() const;

	float GetMass() const;

	BodyType GetBodyType() const;
	vec2 GetCenterOffset() const;
	vec2 GetBottomLeft() const;
	vec2 GetBottomRight() const;
	vec2 GetTopLeft() const;
	vec2 GetTopRight() const;
	float GetWidth() const;
	float GetHeight() const;

	unsigned int GetBodyID() const;
	unsigned int GetCollideID() const;

	bool GetDynamic() const;

	static bool GetDraw();
	static void SetDraw(bool drawBodies);

	int GetColour();
	void SetColour(int colour);

	void SetForce(vec3 force);
	void SetAcceleration(vec3 accel);
	void SetMaxVelo(float velo);
	void SetVelocity(vec3 velo);

	void SetFriction(float fric);

	static void SetGravityAcceleration(vec3 grav);
	void SetGravity(bool grav);

	void SetMass(float mass);

	void SetBodyType(BodyType type);
	void SetCenterOffset(vec2 cent);
	void SetBottomLeft(vec2 BL);
	void SetBottomRight(vec2 BR);
	void SetTopLeft(vec2 TL);
	void SetTopRight(vec2 TR);
	void SetWidth(float width);
	void SetHeight(float height);

	void SetBodyID(unsigned int bodyID);
	void SetCollideID(unsigned int collideID);

	void SetDynamic(bool isDynamic);

private:
	static bool m_drawBodies;

	GLuint m_vao = GL_NONE;
	GLuint m_vboPos = GL_NONE;

	vec3 m_appliedForce = vec3(0.f, 0.f, 0.f);
	vec3 m_frictionForce = vec3(0.f, 0.f, 0.f);
	vec3 m_netForce = vec3(0.f, 0.f, 0.f);
	vec3 m_acceleration = vec3(0.f, 0.f, 0.f);
	float m_maxVelo = 20.f;
	vec3 m_velocity = vec3(0.f, 0.f, 0.f);

	float m_friction = 0.35f;

	static vec3 m_gravityAcceleration;
	bool m_applyGravity = false;

	float m_mass = 1.f;

	BodyType m_bodyType = BodyType::BOX;
	vec2 m_centerOffset = vec2();
	vec2 m_bottomLeft = vec2();
	vec2 m_bottomRight = vec2();
	vec2 m_topLeft = vec2();
	vec2 m_topRight = vec2();
	float m_width = 0.f;
	float m_height = 0.f;

	unsigned int m_bodyID;
	unsigned int m_collideID;
	bool m_dynamic = false;

	int m_colour;
};

//Sends body TO json file
inline void to_json(nlohmann::json& j, const PhysicsBody& phys)
{
	//Stores the body type
	j["BodyType"] = phys.GetBodyType();
	//Center offest
	j["CenterOffest"] = { phys.GetCenterOffset().x, phys.GetCenterOffset().y };
	//Stores corners
	j["BottomLeft"] = { phys.GetBottomLeft().x, phys.GetBottomLeft().y };
	j["BottomRight"] = { phys.GetBottomRight().x, phys.GetBottomRight().y };
	j["TopLeft"] = { phys.GetTopLeft().x, phys.GetTopLeft().y };
	j["TopRight"] = { phys.GetTopRight().x, phys.GetTopRight().y };
	//Height and Width
	j["Width"] = phys.GetWidth();
	j["Height"] = phys.GetHeight();

	//Max Velocity
	j["MaxVelo"] = phys.GetMaxVelo();

	//Friction Strength
	j["Friction"] = phys.GetFriction();

	//Gravity Enabled?
	j["Gravity"] = phys.GetGravity();

	//Collision type (body id) and what this body collides *with*
	j["BodyID"] = phys.GetBodyID();
	j["CollideID"] = phys.GetCollideID();

	//Sets whether the object is moving
	j["IsDynamic"] = phys.GetDynamic();
}

//Reads body in FROM json file
inline void from_json(const nlohmann::json& j, PhysicsBody& phys)
{
	//Sets body type
	phys.SetBodyType(j["BodyType"]);
	//Set the center offset
	phys.SetCenterOffset(vec2(j["CenterOffset"][0], j["CenterOffset"][1]));
	//Sets corners
	phys.SetBottomLeft(vec2(j["BottomLeft"][0], j["BottomLeft"][1]));
	phys.SetBottomRight(vec2(j["BottomRight"][0], j["BottomRight"][1]));
	phys.SetTopLeft(vec2(j["TopLeft"][0], j["TopLeft"][1]));
	phys.SetTopRight(vec2(j["TopRight"][0], j["TopRight"][1]));
	//Set width and height
	phys.SetWidth(j["Width"]);
	phys.SetHeight(j["Height"]);

	//Sets Max velocity
	phys.SetMaxVelo(j["MaxVelo"]);

	//Sets friction strength
	phys.SetFriction(j["Friction"]);

	//Set does gravity affect this body?
	phys.SetGravity(j["Gravity"]);

	//Sets collision type (body id) and what this body collides *with*
	phys.SetBodyID(j["BodyID"]);
	phys.SetCollideID(j["CollideID"]);

	//Set whether or not the object is moving
	phys.SetDynamic(j["IsDynamic"]);
}