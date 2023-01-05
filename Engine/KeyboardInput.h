#pragma once
#include "Util/SingletonTemplate.h"
#include "Library/glfw3.h"

class KeyboardInput : public SingletonTemplate<KeyboardInput>
{
public:
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	}
};
