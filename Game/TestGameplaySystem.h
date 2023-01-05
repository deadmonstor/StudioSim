#pragma once
#include "Components/TestGameComponent.h"
#include "Core/SceneManager.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

class TestGameplaySystem : public SingletonTemplate<TestGameplaySystem>
{
public:
	void TestFunc(OnEngineStart*)
	{
		auto* test = SceneManager::Instance()->createGameObject(glm::vec2 { 0, 0 } );
		test->addComponent(new TestGameComponent());
	}

	void TestKeyDown(const OnKeyDown* KeyDownEvent)
	{
		const char* str = glfwGetKeyName(KeyDownEvent->key, KeyDownEvent->scancode);
		if (!str) return;
		std::string strs(str);
		LOG_INFO("Down: " + strs);
	}

	void TestKeyUp(const OnKeyUp* KeyUpEvent)
	{
		const char* str = glfwGetKeyName(KeyUpEvent->key, KeyUpEvent->scancode);
		if (!str) return;
		std::string strs(str);
		LOG_INFO("Up: " + strs);
	}

	void TestKeyRepeat(const OnKeyRepeat* KeyRepeatEvent)
	{
		const char* str = glfwGetKeyName(KeyRepeatEvent->key, KeyRepeatEvent->scancode);
		if (!str) return;
		std::string strs(str);
		LOG_INFO("Repeat: " + strs);
	}
};
