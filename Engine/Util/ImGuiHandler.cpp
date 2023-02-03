#include "ImGuiHandler.h"

#include "Engine.h"
#include "../../Game/Components/TurnManager.h"
#include "Core/SceneManager.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/Lighting.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/ResourceManager.h"
#include "Events/EngineEvents.h"
#include "Events/Events.h"
#include "Library/imgui/imgui_impl_glfw.h"
#include "Library/imgui/imgui_impl_opengl3.h"

static SpriteComponent* pausedSprite;
void ImGuiHandler::init()
{
#if (NDEBUG)
	return;
#endif
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	//ImGui::StyleCustom();
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(Renderer::getWindow(), true);

	pausedSprite = new SpriteComponent();
	const Texture pause = ResourceManager::LoadTexture("Sprites\\pause.png", "pause");
	pausedSprite->setTexture(pause);
	pausedSprite->setLit(false);
}

void ImGuiHandler::ImGUIGridSystem() const
{
	for (GridSystem* gridSystem = GridSystem::Instance(); const auto& [gridID, gridLayer] : gridSystem->gridLayers)
	{
		if (ImGui::TreeNode(std::to_string(gridID).c_str()))
		{
			for (const auto& [x, mapHolder] : gridLayer->internalMap)
			{
				std::string xString = "X: " + std::to_string(x);

				if (ImGui::TreeNode(xString.c_str()))
				{
					for (const auto& [y, gridHolder] : mapHolder)
					{
						std::string yString = "Y: " + std::to_string(y);
					
						if (ImGui::TreeNode(yString.c_str()))
						{
							if (Tile* tile = gridHolder->tile; tile != nullptr && tile->getTexture().Height != 0 && tile->getTexture().Width != 0)
							{
								auto* tileString = new std::string("");
								tile->getDebugInfo(tileString);
								ImGui::Indent();
								ImGui::Text("%s", tileString->c_str());
								ImGui::Unindent();
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

			ImGui::TreePop();
		}
	}
}

void ImGuiHandler::ImGUIGameObjects() const
{
	ImGui::Text("GameObjects:");

	for (const std::vector<GameObject*>* gameObjectsList = &SceneManager::Instance()->getScene()->gameObjects;
		const auto& curGameObject : *gameObjectsList)
	{
		if (ImGui::TreeNode(curGameObject->getName().c_str()))
		{
			for (const auto& curComponent : curGameObject->components)
			{
				if (ImGui::TreeNode(curComponent->getName().c_str()))
				{
					std::string debugString;
					curComponent->getDebugInfo(&debugString);
					ImGui::Indent();
					if (!debugString.empty())
						ImGui::Text("%s", debugString.c_str());
					ImGui::Unindent();
					ImGui::TreePop();
				}
			}
					
			ImGui::TreePop();
		}
	}
}

void ImGuiHandler::ImGUILayers() const
{
	ImGui::Text("Layers:");
	
	std::map<std::string, SortingLayer*> layers = Renderer::Instance()->sortingLayers;
	std::vector<std::pair<std::string, SortingLayer*>> layersVector(layers.begin(), layers.end());
	std::ranges::sort(layersVector,
	  [](const std::pair<std::string, SortingLayer*>& a, const std::pair<std::string, SortingLayer*>& b)
	  {
	      return a.second->getOrder() < b.second->getOrder();
	  });
	
	for (const auto& [layerName, layer] : layersVector)
	{
		if (ImGui::TreeNode(layerName.c_str()))
		{
			ImGui::Indent();
			ImGui::Text("Order: %d", layer->getOrder());
			ImGui::Unindent();
			ImGui::TreePop();
		}
	}
}

static bool showDebugLog;
static bool showDebugImage;
static bool showDebugGameObjects;
static bool showDebugLayers;
static bool showDebugInventory;
static bool showDebugLighting;

static std::map<std::string, bool*> showDebugComponents
{
	{"Debug Log", &showDebugLog},
	{"Debug Image", &showDebugImage},
	{"Debug Game Objects", &showDebugGameObjects},
	{"Debug Layers", &showDebugLayers},
	{"Debug Inventory", &showDebugInventory},
	{"Debug Lighting", &showDebugLighting}
};

static std::map<std::string, DebugEvent> debugSettings
{
	{"Debug Render Grid", DebugRenderGrid},
	{"Debug Play Sound", DebugPlaySound},
	{"Debug Key Events", DebugKeyEvents},
	{"Debug Mouse Events", DebugMouseEvents},
	{"Debug Mouse Light", DebugMouseLight},
	{"Debug Light Color", DebugLightColor},
	{"Debug Pause Game", DebugPauseGame}
};

static std::map<std::string, std::string> debugScenes
{
	{"Debug Main Menu", "mainMenu"},
	{"Debug Level 1", "level1"},
	{"Debug Level 2", "level2"},
	{"Debug Victory", "victoryScreen"},
	{"Debug Defeat", "defeatScreen"},
};

void ImGuiHandler::update()
{
#if (NDEBUG)
	return;
#endif
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if(ImGui::BeginMainMenuBar())
	{
		ImGui::Text("DEV MODE |");
		
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				Griddy::Engine::Instance()->shutdown();
			}
			
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Debug"))
		{
			for (auto& [name, debugEvent] : debugSettings)
			{
				if(ImGui::MenuItem(name.c_str()))
				{
					Griddy::Events::invoke<OnDebugEventChanged>(debugEvent);
				}
			}
			
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scenes"))
		{
			for (auto& [name, sceneName] : debugScenes)
			{
				if(ImGui::MenuItem(name.c_str()))
				{
					Griddy::Events::invoke<OnSceneChangeRequested>(sceneName);
				}
			}
			
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Windows"))
		{
			for (auto& [name, show] : showDebugComponents)
			{
				if(ImGui::MenuItem(name.c_str(), "", show))
				{
					*show = true;
				}
			}
			
			ImGui::EndMenu();
		}
		
		ImGui::EndMainMenuBar();
	}

	if (showDebugLog)
	{
		if (ImGui::Begin("Logging Window", &showDebugLog))
		{
			if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar))
			{
				std::string sLog;
			
				for (auto it = m_vLog.rbegin(); it != m_vLog.rend(); ++it)
				{
					sLog += *it;
				}
			
				ImGui::TextUnformatted(sLog.c_str());
				ImGui::EndChild();
			}
		}
		ImGui::End();
	}
	
	if (showDebugImage) 
	{
		if (ImGui::Begin("Image Window", &showDebugImage))
		{
			const auto dice = ResourceManager::GetTexture("engine");
			ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(dice.ID)), ImVec2(static_cast<float>(dice.Width) * 5, static_cast<float>(dice.Height) * 5));
		}
		ImGui::End();
	}

	if (showDebugGameObjects)
	{
		if (ImGui::Begin("GameObject Window", &showDebugGameObjects))
		{
			ImGUIGameObjects();
		
			if (ImGui::TreeNode("GridSystem"))
			{
				ImGUIGridSystem();
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Turn Manager"))
			{
				TurnManager::Instance()->debugString();
				ImGui::TreePop();
			}
		
		}
		ImGui::End();
	}
	
	if (showDebugLayers)
	{
		if (ImGui::Begin("Layers Window", &showDebugLayers))
		{
			ImGUILayers();
		}
		ImGui::End();
	}

	if (showDebugInventory)
	{
		if (ImGui::Begin("Inventory Window", &showDebugInventory))
		{
			
		}

		ImGui::End();
	}

	if (showDebugLighting)
	{
		if (ImGui::Begin("Lighting Window", &showDebugLighting))
		{
			const glm::vec4 ambientLighting = Lighting::Instance()->getAmbientColor();
			const auto debugAmbientLighting = new float[4] {ambientLighting.r, ambientLighting.g, ambientLighting.b, ambientLighting.a};
			ImGui::ColorEdit4("AmbientLighting", debugAmbientLighting);

			if (abs(ambientLighting.r - debugAmbientLighting[0]) > 0.01f ||
				abs(ambientLighting.g - debugAmbientLighting[1]) > 0.01f ||
				abs(ambientLighting.b - debugAmbientLighting[2]) > 0.01f ||
				abs(ambientLighting.a - debugAmbientLighting[3]) > 0.01f)
			{
				Lighting::Instance()->setAmbientColor(glm::vec4(debugAmbientLighting[0], debugAmbientLighting[1], debugAmbientLighting[2], debugAmbientLighting[3]));
				Renderer::Instance()->resetShaders();
			}

			delete[] debugAmbientLighting;
		}

		ImGui::End();
	}
}

void ImGuiHandler::render()
{
#if (NDEBUG)
	return;
#endif

	if (Griddy::Engine::isPaused())
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			Renderer::Instance()->renderSprite(pausedSprite, {0, 0}, {142, 39}, 0);
		glDisable(GL_BLEND);
	}
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
void ImGuiHandler::addLog(const std::string &log)
{
	if (m_vLog.size() > 1000)
	{
		m_vLog.erase(m_vLog.begin());
	}
	
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

void ImGuiHandler::onKeyDown(const int key, const int scancode, const int action, const int mods)
{
#if (NDEBUG)
	return;
#endif

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		Griddy::Events::invoke<OnDebugEventChanged>(DebugPauseGame);
	}

	if (key == GLFW_KEY_F8 && action == GLFW_PRESS)
	{
		Griddy::Events::invoke<OnSceneChangeRequested>("level1");
	}

	if (key == GLFW_KEY_F9 && action == GLFW_PRESS)
	{
		Griddy::Events::invoke<OnSceneChangeRequested>("level2");
	}

	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		Griddy::Events::invoke<OnDebugEventChanged>(DebugNoclip);
	}
}
