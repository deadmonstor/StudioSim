#pragma once
#include <string>


#include "Util/SingletonTemplate.h"

struct GLFWwindow;
class WindowManager : public SingletonTemplate<WindowManager>
{
	GLFWwindow* window = nullptr;

	//Create window
public:
	GLFWwindow* GetWindow() const { return window; }
	void SetWindowTitle(std::string title)const;

	bool createWindow(const std::string &windowName);
	void cleanup()const;
};
