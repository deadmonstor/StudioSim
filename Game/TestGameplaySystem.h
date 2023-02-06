#pragma once
#include <string>
#include "ScoreSystem.h"
#include "Shop.h"
#include "Components/EnemyComponent.h"
#include "Components/FireballComponent.h"
#include "Core/Input.h"
#include "Core/SceneManager.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Components/AI/StateMachine.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/SingletonTemplate.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Components/Player/PlayerController.h"
#include "Components/TurnManager.h"
#include "Components/UI/HUD.h"
#include "Tiles/LightTile.h"
#include "Tiles/TestTile.h"
#include "Tiles/TeleportTile.h"

class TestGameplaySystem : public SingletonTemplate<TestGameplaySystem>
{
	
};
