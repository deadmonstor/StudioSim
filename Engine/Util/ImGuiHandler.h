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
	void ImGUIGridSystem() const;
	void ImGUIGameObjects() const;
	void ImGUILayers() const;
	void update();
	void addLog(const std::string &);
	void onKeyDown(int key, int scancode, int action, int mods);
	static void render();
	static void cleanup();

	struct Image
	{
		const char *filename;
		GLuint texture;
		int width, height;
	};
	
	std::vector<Image> m_Images;
};
