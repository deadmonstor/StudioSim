#pragma once
#include "Util/SingletonTemplate.h"
#include "Library/glfw3.h"

class KeyboardInput : public SingletonTemplate<KeyboardInput>
{
public:
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		//Add more keys here if you want switch or if statements
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
			std::cout << "e\n";
	}
};
