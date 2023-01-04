#include "WindowManager.h"
#include <Windows.h>
#include "Library/glfw3.h"
#include "Util/Logger.h"

void error_callback(const int error, const char *msg)
{
	std::string s;
	s = " [" + std::to_string(error) + "] " + msg + '\n';
	LOG_ERROR(s);
}

void WindowManager::SetWindowTitle(const std::string title) const
{
	if (window == nullptr)
	{
		LOG_ERROR("Failed to set window title");
		return;
	}

	glfwSetWindowTitle(window, title.c_str());
}

bool WindowManager::createWindow(const std::string &windowName)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		LOG_ERROR("Failed to create init GLFW");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(800, 600, windowName.c_str(), NULL, NULL);
	if (window == nullptr)
	{
		LOG_ERROR("Failed to create GLFW window");
		return false;
	}

	glfwMakeContextCurrent(window);
	return true;
}

void WindowManager::cleanup() const
{
	if (window != nullptr)
	{
		glfwDestroyWindow(window);
	}
}
