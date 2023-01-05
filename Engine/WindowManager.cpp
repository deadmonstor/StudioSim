#include "WindowManager.h"
#include <Windows.h>
#include <glad/glad.h> 
#include "Library/glfw3.h"
#include "Util/Logger.h"

void error_callback(const int error, const char *msg)
{
	std::string s;
	s = " [" + std::to_string(error) + "] " + msg + '\n';
	LOG_ERROR(s);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void WindowManager::SetWindowTitle(const std::string& title) const
{
	if (window == nullptr)
	{
		LOG_ERROR("Failed to set window title");
		return;
	}

	glfwSetWindowTitle(window, title.c_str());
}

void WindowManager::SetWindowSize(const std::pair<int, int> value) const
{
	if (window == nullptr)
	{
		LOG_ERROR("Failed to set window size");
		return;
	}

	glfwSetWindowSize(window, value.first, value.second);
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

	window = glfwCreateWindow(1, 1, windowName.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		LOG_ERROR("Failed to create GLFW window");
		return false;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		LOG_ERROR("Failed to initialize GLAD");
		return false;
	} 
	
	return true;
}

void WindowManager::cleanup() const
{
	if (window != nullptr)
	{
		glfwDestroyWindow(window);
	}
}

void WindowManager::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

