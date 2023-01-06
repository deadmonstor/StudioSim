#pragma once
#include <string>
#include <vector>

#include "SingletonTemplate.h"
#include "Library/glfw3.h"

class ImGuiHandler : public SingletonTemplate<ImGuiHandler>
{
	std::vector<std::string> m_vLog;
public:
	void init();
	void update();
	void render();
	void addLog(const std::string &);
	void cleanup();

	struct Image
	{
		const char *filename;
		GLuint texture;
		int width, height;
	};
	std::vector<Image> m_Images;
};
