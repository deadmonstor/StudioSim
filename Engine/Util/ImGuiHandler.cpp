#include "ImGuiHandler.h"
#include <sstream>
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/ResourceManager.h"
#include "Events/EngineEvents.h"
#include "Events/Events.h"
#include "Library/imgui/imgui_impl_glfw.h"
#include "Library/imgui/imgui_impl_opengl3.h"

void ImGuiHandler::init()
{
#if (NDEBUG)
	return;
#endif
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(Renderer::GetWindow(), true);
}

void ImGuiHandler::update()
{
#if (NDEBUG)
	return;
#endif
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	if (ImGui::BeginTabBar("TabBar"))
	{
		// Make m_vLog into a string with newlines
		std::string sLog;
		for (auto& s : m_vLog)
		{
			sLog += s + "\n";
		}
		
		if (ImGui::BeginTabItem("Debug Settings Window"))
		{
			if (ImGui::Button("Debug Render Grid"))
			{
				Griddy::Events::invoke(new OnDebugEventChanged(DebugRenderGrid));
			}

			if (ImGui::Button("Play Sound"))
			{
				Griddy::Events::invoke(new OnDebugEventChanged(DebugPlaySound));
			}
			
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Logging Window"))
		{
			ImGui::Text("%s", sLog.c_str());
			ImGui::EndTabItem();
		}
		
		if (ImGui::BeginTabItem("Image Window"))
		{
			const auto dice = ResourceManager::GetTexture("engine");
			ImGui::Image((void *)(intptr_t)dice.ID, ImVec2((float)dice.Width, (float)dice.Height));
			ImGui::EndTabItem();
		}
		
		ImGui::EndTabBar();
	}
}

void ImGuiHandler::render()
{
#if (NDEBUG)
	return;
#endif
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiHandler::addLog(const std::string &log)
{
	m_vLog.push_back(log);
}

void ImGuiHandler::cleanup()
{
#if (NDEBUG)
	return;
#endif
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
}