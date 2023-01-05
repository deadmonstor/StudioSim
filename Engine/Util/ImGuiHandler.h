#pragma once
#include <string>
#include <vector>

#include "SingletonTemplate.h"

class ImGuiHandler : public SingletonTemplate<ImGuiHandler>
{
	std::vector<std::string> m_vLog;
public:
	void init();
	void update();
	void render();
	void addLog(const std::string &);
	void cleanup();
};
