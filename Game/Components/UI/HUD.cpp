#include "HUD.h"

#include "ButtonComponent.h"
#include "TextComponent.h"
#include "UIManager.h"
#include "../Player/PlayerController.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"
#include "Core/AudioEngine.h"

void HUD::createHUD()
{
	if (hasLoaded)
		return;

	if (sceneChangeID == -1)
		sceneChangeID = Griddy::Events::subscribe(this, &HUD::onSceneChange);

	if (playerChangedID == -1)
		playerChangedID = Griddy::Events::subscribe(this, &HUD::onPlayerChanged);
	
	ResourceManager::LoadTexture("Sprites\\Armour\\BasicArmourChest.png", "BasicArmourChestInventoryUI");
	inventoryButton =
		UIManager::Instance()->createUIElement<InventoryButton>("inventoryButton", ResourceManager::GetTexture("BasicArmourChestInventoryUI"));

	ResourceManager::LoadTexture("Sprites\\Armour\\TopArmourBoots.png", "TopArmourBoots");
	ResourceManager::LoadTexture("Sprites\\Weapons\\Sword.png", "SwordInventoryUI");
	weaponButton =
		UIManager::Instance()->createUIElement<ButtonComponent>("weaponButton", ResourceManager::GetTexture("TopArmourBoots"));

	ResourceManager::LoadTexture("Sprites\\Weapons\\Potion0.png", "healthIcon");
	healthIcon = UIManager::Instance()->createUIElement<Panel>("healthIcon");
	healthText = UIManager::Instance()->createUIElement<TextComponent>("healthText");
	
	ResourceManager::LoadTexture("Sprites\\Weapons\\Potion1.png", "ManaIcon");
	manaIcon = UIManager::Instance()->createUIElement<Panel>("manaIcon");
	manaText = UIManager::Instance()->createUIElement<TextComponent>("manaText");
	coinsText = UIManager::Instance()->createUIElement<TextComponent>("coinsText");
	
	ResourceManager::LoadTexture("Sprites\\Coins\\coin3.png", "coinsIcon");
	coinsIcon = UIManager::Instance()->createUIElement<Panel>("coinsIcon");
	xpText = UIManager::Instance()->createUIElement<TextComponent>("xpText");
	levelText = UIManager::Instance()->createUIElement<TextComponent>("levelText");

	//Audio Controls
	ResourceManager::LoadTexture("Sprites\\Audio\\Plus.png", "plusIcon");
	plusAudioButton =
		UIManager::Instance()->createUIElement<MasterAudioPlusButton>("plusAudioButton", ResourceManager::GetTexture("plusIcon"));

	ResourceManager::LoadTexture("Sprites\\Audio\\Minus.png", "minusIcon");
	minusAudioButton =
		UIManager::Instance()->createUIElement<MasterAudioMinusButton>("minusAudioButton", ResourceManager::GetTexture("minusIcon"));

	audioText = UIManager::Instance()->createUIElement<TextComponent>("audioText");

	//Pause Button
	ResourceManager::LoadTexture("Sprites\\pauseButton.png", "pauseButton");
	pauseButton = UIManager::Instance()->createUIElement<PauseButton>("pauseButton", ResourceManager::GetTexture("pauseButton"));

	hasLoaded = true;
}

void HUD::updateHUD()
{
	if (healthText == nullptr || manaText == nullptr || coinsText == nullptr || coinsIcon == nullptr || xpText == nullptr || levelText == nullptr || audioText == nullptr)
	{
		return;
	}

	const PlayerController* playerController = PlayerController::Instance();
	if (playerController == nullptr)
	{
		return;
	}

	const PlayerStats* playerStats = playerController->playerStats;
	if (playerStats == nullptr)
	{
		return;
	}
	
	const auto topLeft =
					glm::vec2(0, Renderer::getViewportSize().y);

	const auto MiddleLeft =
					glm::vec2(0, Renderer::getViewportSize().y / 2);

	const auto topRight =
					glm::vec2(Renderer::getViewportSize().x, Renderer::getViewportSize().y);

	const auto bottomRight =
					glm::vec2(Renderer::getViewportSize().x, 0);

	const auto topMiddle =
					glm::vec2((Renderer::getViewportSize().x / 2), Renderer::getViewportSize().y);
                    
    const auto bottomLeft = 
                    glm::vec2(0, 0);

	// =============================================Update Audio Text ==========================================
	plusAudioButton->getTransform()->setPosition(bottomLeft - glm::vec2{ -60, -10 });
	plusAudioButton->getTransform()->setSize(glm::vec2(50, 50));
	plusAudioButton->setPivot(Pivot::BottomRight);

	minusAudioButton->getTransform()->setPosition(bottomLeft - glm::vec2{ -120, -10 });
	minusAudioButton->getTransform()->setSize(glm::vec2(50, 50));
	minusAudioButton->setPivot(Pivot::BottomRight);
	
	// =============================================Update Inventory Button ======================================
	inventoryButton->getTransform()->setPosition(bottomRight);
	inventoryButton->getTransform()->setSize(glm::vec2(100, 100));
	inventoryButton->setPivot(Pivot::BottomRight);
	
	// =============================================Update Weapon Button =========================================
	weaponButton->getTransform()->setPosition(bottomRight - glm::vec2{100, 0});
	weaponButton->getTransform()->setSize(glm::vec2(100, 100));
	weaponButton->setPivot(Pivot::BottomRight);

	int offset = 15;

#ifdef _DEBUG
	offset = 35;
#endif
	
	// =============================================Update health icon=============================================
	healthIcon->getTransform()->setPosition(topLeft - glm::vec2{-20, offset});
	healthIcon->getTransform()->setSize({50, 50});
	healthIcon->setTexture(ResourceManager::GetTexture("healthIcon"));
	healthIcon->setPivot(Pivot::TopLeft);
	
	// =============================================Update mana icon===============================================
	manaIcon->getTransform()->setPosition(topLeft - glm::vec2{-20, 75 + offset});
	manaIcon->getTransform()->setSize({50, 50});
	manaIcon->setTexture(ResourceManager::GetTexture("ManaIcon"));
	manaIcon->setPivot(Pivot::TopLeft);
	
	// =============================================Update coins icon=============================================
	coinsIcon->getTransform()->setSize({50, 50});
	coinsIcon->setTexture(ResourceManager::GetTexture("coinsIcon"));
	coinsIcon->setPivot(Pivot::TopRight);

	// =============================================Update pause icon=============================================
	pauseButton->getTransform()->setPosition(MiddleLeft + glm::vec2{45, 125});
	pauseButton->getTransform()->setSize({ 30, 30 });
	pauseButton->setTexture(ResourceManager::GetTexture("pauseButton"));
	pauseButton->setPivot(Pivot::Center);

	// =============================================Update health text=============================================
	const int health = playerStats->currentHealth;
	const int maxHealth = playerStats->maxHealth;
	
	auto sizeOfText = TextRenderer::Instance()->renderTextSize(std::to_string(health) + "/" + std::to_string(maxHealth), 1);
	auto position = topLeft - glm::vec2{-75, sizeOfText.y} - glm::vec2{0, offset};
	
	healthText->getTransform()->setPosition(position);
	healthText->getTransform()->setSize(sizeOfText);
	healthText->setText(" " + std::to_string(health) + "/" + std::to_string(maxHealth));
	
	// =============================================Update mana text===============================================
	const int mana = playerStats->currentMana;
	const int maxMana = playerStats->maxMana;
	
	sizeOfText = TextRenderer::Instance()->renderTextSize(std::to_string(mana) + "/" + std::to_string(maxMana), 1);
	position.y -= sizeOfText.y;
	position.y -= 38;
	
	manaText->getTransform()->setPosition(position);
	manaText->getTransform()->setSize(sizeOfText);
	manaText->setText(" " + std::to_string(mana) + "/" + std::to_string(maxMana));

	// =============================================Update coins text==============================================
	const int coins = playerStats->coinsHeld;
	
	sizeOfText = TextRenderer::Instance()->renderTextSize(std::to_string(coins), 1);
	position = topRight - glm::vec2{sizeOfText.x, sizeOfText.y} - glm::vec2{25, offset};
	
	coinsText->getTransform()->setPosition(position);
	coinsText->getTransform()->setSize(sizeOfText);
	coinsText->setText(" " + std::to_string(coins));
	
	// =============================================Update coins icon=============================================
	position = topRight - glm::vec2{sizeOfText.x, 0} - glm::vec2{28, offset};
	coinsIcon->getTransform()->setPosition(position);
	
	// =============================================Update xp text===============================================
	const int xp = playerStats->currentEXP;
	const int maxXp = playerStats->maxEXP;
	
	sizeOfText = TextRenderer::Instance()->renderTextSize("XP: " + std::to_string(xp) + "/" + std::to_string(maxXp), 1);
	position = topMiddle - glm::vec2{sizeOfText.x / 2, sizeOfText.y} - glm::vec2{0, offset};
	
	xpText->getTransform()->setPosition(position);
	xpText->getTransform()->setSize(sizeOfText);
	xpText->setText(" XP: " + std::to_string(xp) + "/" + std::to_string(maxXp));

	// =============================================Update level text=============================================
	const int level = playerStats->level;

	sizeOfText = TextRenderer::Instance()->renderTextSize("Level: " + std::to_string(level), 1);
	position = bottomRight - glm::vec2{25, -75} + glm::vec2{-sizeOfText.x, sizeOfText.y};
	
	levelText->getTransform()->setPosition(position);
	levelText->getTransform()->setSize(sizeOfText);
	levelText->setText(" Level: " + std::to_string(level));

	// =============================================Update audio text===============================================
	const float audioLevel = AudioEngine::Instance()->getChannelVolume("Master Channel") * 100 / 100;
	
	sizeOfText = TextRenderer::Instance()->renderTextSize("Volume: " + std::format("{:.2f}", audioLevel), 0.5);
	position = bottomLeft - glm::vec2{ -5, sizeOfText.y } - glm::vec2{ -10, -70 - sizeOfText.y };

	audioText = UIManager::Instance()->createUIElement<TextComponent>("audioText");
	audioText->getTransform()->setPosition(position);
	audioText->getTransform()->setSize(sizeOfText);
	audioText->setText("Volume: " + std::format("{:.2f}", audioLevel));
}

void HUD::onSceneChange(OnSceneChanged*)
{
	hasLoaded = false;
}

void HUD::onPlayerChanged(const OnPlayerControllerFSMUpdate* event)
{
	if (event->key ==  "PlayerMovementBehaviour")
	{
		weaponButton->setTexture(ResourceManager::GetTexture("TopArmourBoots"));
	}
	else if (event->key ==  "PlayerAttackBehaviour")
	{
		weaponButton->setTexture(ResourceManager::GetTexture("SwordInventoryUI"));
	}
	else if (event->key ==  "PlayerSpellBehaviour")
	{
		weaponButton->setTexture(ResourceManager::GetTexture("Fireball1"));
	}
}
