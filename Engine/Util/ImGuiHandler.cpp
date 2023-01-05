#include "ImGuiHandler.h"


#include <iterator>
#include <sstream>

#include "../Library/imgui/imgui_impl_glfw.h"
#include "../Library/imgui/imgui_impl_opengl3.h"
#include "../WindowManager.h"

void ImGuiHandler::init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(WindowManager::Instance()->GetWindow(), true);
}

void ImGuiHandler::update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Make m_vLog into a string with newlines
	std::string sLog;
	for (auto& s : m_vLog)
	{
		sLog += s + "\n";
	}

	ImGui::Text("%s", sLog.c_str());
}

void ImGuiHandler::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiHandler::addLog(const std::string &log)
{
	m_vLog.push_back(log);
}

void ImGuiHandler::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
}