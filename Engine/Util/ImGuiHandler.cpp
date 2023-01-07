#include "ImGuiHandler.h"

#include "Core/SceneManager.h"
#include "Core/Grid/GridSystem.h"
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

void ImGuiHandler::ImGUIGridSystem() const
{
	for (GridSystem* gridSystem = GridSystem::Instance();
		const auto& [x, mapHolder] : gridSystem->internalMap)
	{
		std::string xString = "X: " + std::to_string(x);
					
		if (ImGui::TreeNode(xString.c_str()))
		{
			for (const auto& [y, gridHolder] : mapHolder)
			{
				std::string yString = "Y: " + std::to_string(y);
					
				if (ImGui::TreeNode(yString.c_str()))
				{
					if (Tile* tile = gridHolder->tile)
					{
						auto* tileString = new std::string("");
						tile->getDebugInfo(tileString);
						ImGui::Text("%s", tileString->c_str());
					}
					else
					{
						ImGui::Text("Tile: NULL");
					}
					ImGui::TreePop();
				}
			}
						
			ImGui::TreePop();
		}
	}
}

void ImGuiHandler::ImGUIGameObjects() const
{
	ImGui::Text("GameObjects:");

	for (const std::vector<GameObject*>* gameObjectsList = &SceneManager::Instance()->currentScene->gameObjects;
		const auto& curGameObject : *gameObjectsList)
	{
		if (ImGui::TreeNode(curGameObject->getName().c_str()))
		{
			for (const auto& curComponent : curGameObject->components)
			{
				if (ImGui::TreeNode(curComponent->name.c_str()))
				{
					std::string debugString;
					curComponent->getDebugInfo(&debugString);
					ImGui::Text("%s", debugString.c_str());
					ImGui::TreePop();
				}
			}
					
			ImGui::TreePop();
		}
	}
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
				Griddy::Events::invoke<OnDebugEventChanged>(DebugRenderGrid);
			}

			if (ImGui::Button("Debug Play Sound"))
			{
				Griddy::Events::invoke<OnDebugEventChanged>(DebugPlaySound);
			}

			if (ImGui::Button("Debug Key Events"))
			{
				Griddy::Events::invoke<OnDebugEventChanged>(DebugKeyEvents);
			}

			if (ImGui::Button("Debug Mouse Events"))
			{
				Griddy::Events::invoke<OnDebugEventChanged>(DebugMouseEvents);
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
			ImGui::Image((void *)(intptr_t)dice.ID, ImVec2((float)dice.Width * 5, (float)dice.Height * 5));
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("GameObject Window"))
		{
			ImGUIGameObjects();
			
			if (ImGui::TreeNode("GridSystem"))
			{
				ImGUIGridSystem();
				ImGui::TreePop();
			}
			
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