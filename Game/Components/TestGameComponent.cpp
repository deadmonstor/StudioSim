#include "TestGameComponent.h"
#include "Core/Component.h"
#include "Util/Logger.h"

void TestGameComponent::start()
{
	Component::start();
	LOG_INFO("TestGameComponent::start()"); 
}

void TestGameComponent::update()
{
	Component::update();
}

void TestGameComponent::lateUpdate()
{
	Component::lateUpdate();
}

void TestGameComponent::render()
{
	Component::render();
}