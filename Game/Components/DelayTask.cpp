#include "DelayTask.h"

#include "Core/GameObject.h"
#include "Util/Time.h"

DelayTask::DelayTask(const int speed, const std::function<void()>& _onComplete)
{
	this->speed = speed;
	onComplete = _onComplete;
}

void DelayTask::start()
{
	
}

void DelayTask::update()
{
	if (hasFinished)
		return;

	internalTimer += static_cast<float>(Time::getDeltaTime()) * speed;
	
	if (internalTimer >= 1.0f)
	{
		onComplete();
		hasFinished = true;
	}
}

void DelayTask::destroy()
{

}

void DelayTask::createTask(GameObject* object, const float speed, const std::function<void()>& _onComplete)
{
	if (!object->hasComponent(typeid(DelayTask)))
	{
		object->addComponent<DelayTask>(speed, _onComplete);
	}

	auto* flash = object->getComponent<DelayTask>();
	flash->onComplete = _onComplete;
	flash->setSpeed(speed);
	flash->hasFinished = false;
	flash->internalTimer =0.0f;
}
