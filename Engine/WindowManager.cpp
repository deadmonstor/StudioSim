#include "WindowManager.h"
#include "Util/Logger.h"

bool WindowManager::CreateWindow_Diff()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	window = glfwCreateWindow(800, 600, "test", NULL, NULL);
	if (window == nullptr)
	{
		LOG_ERROR("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	return true;
}