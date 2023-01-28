#include "HUD.h"

#include "ButtonComponent.h"
#include "TextComponent.h"
#include "UIManager.h"
#include "../Player/PlayerController.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"

void HUD::createHUD()
{
	const auto topLeft =
					glm::vec2(0, Renderer::getWindowSize().y) / Renderer::Instance()->getAspectRatio();

	const auto topRight =
					glm::vec2(Renderer::getWindowSize().x, Renderer::getWindowSize().y) / Renderer::Instance()->getAspectRatio();

	const auto topMiddle =
					glm::vec2((Renderer::getWindowSize().x / 2), Renderer::getWindowSize().y) / Renderer::Instance()->getAspectRatio();
	
	const auto bottomLeft =
		glm::vec2(0, 0);

	const auto bottomRight =
		glm::vec2(Renderer::getWindowSize().x, 0) / Renderer::Instance()->getAspectRatio();

	ResourceManager::LoadTexture("Sprites\\Armour\\BasicArmourChest.png", "BasicArmourChestInventoryUI");
	ButtonComponent* inventoryButton =
		UIManager::Instance()->createUIElement<ButtonComponent>("inventoryButton", ResourceManager::GetTexture("BasicArmourChestInventoryUI"));
	
	inventoryButton->getTransform()->setPosition(bottomRight);
	inventoryButton->getTransform()->setSize(glm::vec2(200, 200));
	inventoryButton->setPivot(Pivot::BottomRight);
	
	ResourceManager::LoadTexture("Sprites\\Weapons\\Spellbook4.png", "SpellbookInventoryUI");
	ButtonComponent* spellsButton =
		UIManager::Instance()->createUIElement<ButtonComponent>("spellsButton", ResourceManager::GetTexture("SpellbookInventoryUI"));
	
	spellsButton->getTransform()->setPosition(bottomRight - glm::vec2{200, 0});
	spellsButton->getTransform()->setSize(glm::vec2(100, 100));
	spellsButton->setPivot(Pivot::BottomRight);

	ResourceManager::LoadTexture("Sprites\\Weapons\\Sword.png", "SwordInventoryUI");
	ButtonComponent* weaponButton =
		UIManager::Instance()->createUIElement<ButtonComponent>("weaponButton", ResourceManager::GetTexture("SwordInventoryUI"));
	
	weaponButton->getTransform()->setPosition(bottomRight - glm::vec2{300, 0});
	weaponButton->getTransform()->setSize(glm::vec2(100, 100));
	weaponButton->setPivot(Pivot::BottomRight);

	ResourceManager::LoadTexture("Sprites\\Weapons\\Potion1.png", "healthIcon");
	auto* healthIcon = UIManager::Instance()->createUIElement<Panel>("healthIcon");
	healthIcon->getTransform()->setPosition(topLeft - glm::vec2{-20, 35});
	healthIcon->getTransform()->setSize({50, 50});
	healthIcon->setTexture(ResourceManager::GetTexture("healthIcon"));
	healthIcon->setPivot(Pivot::TopLeft);
	
	healthText = UIManager::Instance()->createUIElement<TextComponent>("healthText");
	
	ResourceManager::LoadTexture("Sprites\\Weapons\\Potion2.png", "ManaIcon");
	auto* manaIcon = UIManager::Instance()->createUIElement<Panel>("manaIcon");
	manaIcon->getTransform()->setPosition(topLeft - glm::vec2{-20, 110});
	manaIcon->getTransform()->setSize({50, 50});
	manaIcon->setTexture(ResourceManager::GetTexture("ManaIcon"));
	manaIcon->setPivot(Pivot::TopLeft);
	
	manaText = UIManager::Instance()->createUIElement<TextComponent>("manaText");
	coinsText = UIManager::Instance()->createUIElement<TextComponent>("coinsText");
	
	ResourceManager::LoadTexture("Sprites\\Weapons\\Potion3.png", "coinsIcon");
	coinsIcon = UIManager::Instance()->createUIElement<Panel>("coinsIcon");
	coinsIcon->getTransform()->setSize({50, 50});
	coinsIcon->setTexture(ResourceManager::GetTexture("coinsIcon"));
	coinsIcon->setPivot(Pivot::TopRight);

	xpText = UIManager::Instance()->createUIElement<TextComponent>("xpText");
}

void HUD::updateHUD()
{
	if (healthText == nullptr || manaText == nullptr || coinsText == nullptr || coinsIcon == nullptr || xpText == nullptr)
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
					glm::vec2(0, Renderer::getWindowSize().y) / Renderer::Instance()->getAspectRatio();

	const auto topRight =
					glm::vec2(Renderer::getWindowSize().x, Renderer::getWindowSize().y) / Renderer::Instance()->getAspectRatio();

	const auto topMiddle =
					glm::vec2((Renderer::getWindowSize().x / 2), Renderer::getWindowSize().y) / Renderer::Instance()->getAspectRatio();

	// =============================================Update health text=============================================
	int health = playerStats->currentHealth;
	int maxHealth = playerStats->maxHealth;
	
	auto sizeOfText = TextRenderer::Instance()->renderTextSize(std::to_string(health) + "/" + std::to_string(maxHealth), 1);
	auto position = topLeft - glm::vec2{-75, sizeOfText.y} - glm::vec2{0, 38};
	
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
	position = topRight - glm::vec2{sizeOfText.x, sizeOfText.y} - glm::vec2{25, 38};
	
	coinsText->getTransform()->setPosition(position);
	coinsText->getTransform()->setSize(sizeOfText);
	coinsText->setText(" " + std::to_string(coins));
	
	// =============================================Update coins icon=============================================
	position = topRight - glm::vec2{sizeOfText.x, 0} - glm::vec2{28, 35};
	coinsIcon->getTransform()->setPosition(position);
	
	// =============================================Update xp text===============================================
	const int xp = playerStats->currentEXP;
	const int maxXp = playerStats->maxEXP;
	
	sizeOfText = TextRenderer::Instance()->renderTextSize("XP: " + std::to_string(xp) + "/" + std::to_string(maxXp), 1);
	position = topMiddle - glm::vec2{sizeOfText.x / 2, sizeOfText.y} - glm::vec2{0, 31}; 
	
	xpText = UIManager::Instance()->createUIElement<TextComponent>("xpText");
	xpText->getTransform()->setPosition(position);
	xpText->getTransform()->setSize(sizeOfText);
	xpText->setText(" XP: " + std::to_string(xp) + "/" + std::to_string(maxXp));
}