#pragma once
#include <string>


#include "Util/SingletonTemplate.h"

struct GLFWwindow;
class WindowManager : public SingletonTemplate<WindowManager>
{
	GLFWwindow* window = nullptr;
public:
	GLFWwindow* GetWindow() const { return window; }
	
	// TODO: Change this to vector when we have it
	void SetWindowSize(std::pair<int, int>) const;
	void SetWindowTitle(const std::string& title) const;
	bool createWindow(const std::string &windowName);
	void cleanup() const;
	void render();
};
