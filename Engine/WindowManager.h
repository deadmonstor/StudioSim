#pragma once
#include "Library/glfw3.h"
#include "Util/SingletonTemplate.h"

class WindowManager : public SingletonTemplate<WindowManager>
{
	GLFWwindow* window;

	//Create window
public:
	GLFWwindow* GetWindow() const { return window; }
	
	bool CreateWindow_Diff();
};
