#include "ImGuiHandler.h"
#include <sstream>
#include "Core/Renderer/Renderer.h"
#include "Library/imgui/imgui_impl_glfw.h"
#include "Library/imgui/imgui_impl_opengl3.h"

void ImGuiHandler::init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(Renderer::GetWindow(), true);
}

void ImGuiHandler::update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
;
	// Make m_vLog into a string with newlines
	std::string sLog;
	for (auto& s : m_vLog)
	{
		sLog += s + "\n";
	}

	ImGui::Begin("Logging Window");
	ImGui::Text("%s", sLog.c_str());
	ImGui::End();
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