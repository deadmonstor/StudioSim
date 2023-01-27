#pragma once
#include "Util/SingletonTemplate.h"
#include "Core/GameObject.h"
#include "Core/Components/Transform.h"
#include "Util/Time.h"

class PhysicsSystem : public SingletonTemplate<PhysicsSystem>
{
public:
	bool checkBoxCollision(GameObject gameObject1, GameObject gameObject2)
	{
		//AABB - AABB Collision
		//To Do Cache Position to reduce calls
		bool collisionXAxis = gameObject1.getTransform()->getPosition().x + gameObject1.getTransform()->GetScale().x >= gameObject2.getTransform()->getPosition().x &&
							  gameObject2.getTransform()->getPosition().x + gameObject2.getTransform()->GetScale().x >= gameObject1.getTransform()->getPosition().x;

		bool collisionYAxis = gameObject1.getTransform()->getPosition().y + gameObject1.getTransform()->GetScale().y >= gameObject2.getTransform()->getPosition().y &&
							  gameObject2.getTransform()->getPosition().y + gameObject2.getTransform()->GetScale().y >= gameObject1.getTransform()->getPosition().y;

		return collisionXAxis && collisionYAxis;
	}

	void applyGravity(GameObject gameObject)
	{
		glm::vec2 currentPos = gameObject.getTransform()->getPosition();
		gameObject.getTransform()->setPosition(glm::vec2(currentPos.x, currentPos.y + (gravityConstant * Time::Instance()->getDeltaTime())));
	}

	void setGravity(float gravity)
	{
		gravityConstant = gravity;
	}

	float const getGravity()
	{
		return gravityConstant;
	}

private:
	float gravityConstant = 9.81f;
};

