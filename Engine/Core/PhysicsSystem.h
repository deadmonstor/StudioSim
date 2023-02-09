#pragma once
#include "Util/SingletonTemplate.h"
#include "Core/GameObject.h"
#include "Core/Components/Transform.h"
#include "Util/Time.h"

class PhysicsSystem : public SingletonTemplate<PhysicsSystem>
{
public:
	bool checkBoxCollision(const Transform &gameObject1, const Transform &gameObject2)
	{
		//AABB - AABB Collision
		//To Do Cache Position to reduce calls
		bool collisionXAxis = gameObject1.getPosition().x + gameObject1.getScale().x >= gameObject2.getPosition().x &&
							  gameObject2.getPosition().x + gameObject2.getScale().x >= gameObject1.getPosition().x;

		bool collisionYAxis = gameObject1.getPosition().y + gameObject1.getScale().y >= gameObject2.getPosition().y &&
							  gameObject2.getPosition().y + gameObject2.getScale().y >= gameObject1.getPosition().y;

		return collisionXAxis && collisionYAxis;
	}

	void resolveCollision(Transform& gameObject1, Transform& gameObject2)

	{
		float x_overlap = (gameObject1.getScale().x + gameObject2.getScale().x) - (gameObject1.getPosition().x - gameObject2.getPosition().x);
		float y_overlap = (gameObject1.getScale().y + gameObject2.getScale().y) - (gameObject2.getPosition().y - gameObject2.getPosition().y);

		if (x_overlap < y_overlap) {
			if (gameObject1.getPosition().x < gameObject2.getPosition().x)
			{
				gameObject1.setPosition(gameObject1.getPosition() - x_overlap / 2);
				//position_.x -= x_overlap / 2.0f;
				gameObject2.setPosition(gameObject2.getPosition() + x_overlap / 2);
				//other.position_.x += x_overlap / 2.0f;
			}
			else {
				gameObject1.setPosition(gameObject1.getPosition() + x_overlap / 2);
				//position_.x += x_overlap / 2.0f;
				gameObject2.setPosition(gameObject2.getPosition() - x_overlap / 2);
				//other.position_.x -= x_overlap / 2.0f;
			}
		}
		else {
			if (gameObject1.getPosition().y < gameObject2.getPosition().y) {
				gameObject1.setPosition(gameObject1.getPosition() - y_overlap / 2);
				//position_.y -= y_overlap / 2.0f;
				gameObject2.setPosition(gameObject2.getPosition() + y_overlap / 2);
				//other.position_.y += y_overlap / 2.0f;
			}
			else {
				gameObject1.setPosition(gameObject1.getPosition() + y_overlap / 2);
				//position_.y += y_overlap / 2.0f;
				gameObject2.setPosition(gameObject2.getPosition() - y_overlap / 2);
				//other.position_.y -= y_overlap / 2.0f;
			}
		}
	}
	void applyGravity(Transform &gameObject)
	{
		glm::vec2 currentPos = gameObject.getPosition();
		gameObject.setPosition(glm::vec2(currentPos.x, currentPos.y + (gravityConstant * Time::Instance()->getDeltaTime())));
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

