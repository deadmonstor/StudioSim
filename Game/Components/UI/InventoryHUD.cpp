﻿#include "InventoryHUD.h"

#include "InventoryIconButton.h"
#include "UIManager.h"
#include "../Player/PlayerController.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Events/Events.h"

void InventoryHUD::createHUD()
{
	if (hasLoaded)
		return;

	if (sceneChangeID == -1)
		sceneChangeID = Griddy::Events::subscribe(this, &InventoryHUD::onSceneChange);

	if (!ResourceManager::HasTexture("inventoryBackground"))
		ResourceManager::LoadTexture("Sprites/UI/Background.png", "inventoryBackground");

	const auto topLeft =
					glm::vec2(0, Renderer::getViewportSize().y);

	const auto MiddleLeft =
					glm::vec2(0, Renderer::getViewportSize().y / 2);

	const auto MiddleRight =
					glm::vec2(Renderer::getViewportSize().x, Renderer::getViewportSize().y / 2);
	
	const auto topRight =
					glm::vec2(Renderer::getViewportSize().x, Renderer::getViewportSize().y);

	const auto bottomRight =
					glm::vec2(Renderer::getViewportSize().x, 0);

	const auto topMiddle =
					glm::vec2((Renderer::getViewportSize().x / 2), Renderer::getViewportSize().y);
                    
    const auto bottomLeft = 
                    glm::vec2(0, 0);
	
	int y = 0;
	for (int i = 1; i <= 20; i++)
	{
		slots.push_back(createButton(MiddleRight - glm::vec2{100, 0} - (glm::vec2{(i % 5) * 50, y * 50}), nullptr));

		if (i != 0 && i % 5 == 0)
			y++;
	}

	weaponSlot = createButton(MiddleRight - glm::vec2{100, 0} - (glm::vec2{200, -125}), nullptr);
	armourSlot = createButton(MiddleRight - glm::vec2{100, 0} - (glm::vec2{100, -125}), nullptr);
	spellSlot = createButton(MiddleRight - glm::vec2{100, 0} - (glm::vec2{0, -125}), nullptr);
	
	UIManager::Instance()->sortOrder();
	
	backgroundPanelInventory = UIManager::Instance()->createUIElement<Panel>("backgroundPanelInventory");
	backgroundPanelEquip = UIManager::Instance()->createUIElement<Panel>("backgroundPanelEquip");
	backgroundPanelInventoryText = UIManager::Instance()->createUIElement<TextComponent>("backgroundPanelInventoryText");
	currentInventoryText = UIManager::Instance()->createUIElement<TextComponent>("currentInventoryText");
	currentInventoryTextOnline = UIManager::Instance()->createUIElement<TextComponent>("currentInventoryTextOnline");
	hasLoaded = true;
}

InventoryIconButton* InventoryHUD::createButton(const glm::vec2& pos, Item* item)
{
	InventoryIconButton* button = UIManager::Instance()->createUIElement<InventoryIconButton>(
		"Inventory_" + std::to_string(pos.x) + " " + std::to_string(pos.y),
		ResourceManager::GetTexture("whitetexture"),
		item);
	
	button->getTransform()->setPosition(pos);
	button->getTransform()->setSize({50, 50});
	button->setColor({1, 1, 1});
	button->setLit(false);
	button->setSortingOrder(3);
	button->shouldRender = shouldRender;
	
	return button;
}

void InventoryHUD::updateHUD()
{
	if (!hasLoaded)
		return;

	const auto topLeft =
					glm::vec2(0, Renderer::getViewportSize().y);

	const auto MiddleLeft =
					glm::vec2(0, Renderer::getViewportSize().y / 2);

	const auto MiddleRight =
					glm::vec2(Renderer::getViewportSize().x, Renderer::getViewportSize().y / 2);
	
	const auto topRight =
					glm::vec2(Renderer::getViewportSize().x, Renderer::getViewportSize().y);

	const auto bottomRight =
					glm::vec2(Renderer::getViewportSize().x, 0);

	const auto topMiddle =
					glm::vec2((Renderer::getViewportSize().x / 2), Renderer::getViewportSize().y);
                    
	const auto bottomLeft = 
					glm::vec2(0, 0);

	// =============================== BACKGROUND PANEL EQUIP ===============================
	backgroundPanelEquip->shouldRender = shouldRender;
	backgroundPanelEquip->getTransform()->setPosition(MiddleRight + glm::vec2(0, 150));
	backgroundPanelEquip->getTransform()->setSize({350, 150});
	backgroundPanelEquip->setTexture(ResourceManager::GetTexture("inventoryBackground"));
	backgroundPanelEquip->setPivot(Pivot::RightCenter);
	backgroundPanelEquip->setColor({0.8, 0.45f, 0.48f});
	backgroundPanelEquip->setSortingOrder(2);
	
	// =============================== BACKGROUND PANEL ===============================
	backgroundPanelInventory->shouldRender = shouldRender;
	backgroundPanelInventory->getTransform()->setPosition(MiddleRight + glm::vec2(0, -50));
	backgroundPanelInventory->getTransform()->setSize({350, 250});
	backgroundPanelInventory->setTexture(ResourceManager::GetTexture("inventoryBackground"));
	backgroundPanelInventory->setPivot(Pivot::RightCenter);
	backgroundPanelInventory->setColor({0.41f, 0.45f, 0.48f});
	backgroundPanelInventory->setSortingOrder(2);
	
	// =============================== BACKGROUND PANEL INVENTORY TEXT ===============================
	glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize("Inventory", 0.5f);
	backgroundPanelInventoryText->shouldRender = shouldRender;
	backgroundPanelInventoryText->getTransform()->setPosition(MiddleRight - glm::vec2{sizeOfText.x / 2, -50} - (glm::vec2{350, 0} / 2.0f));
	backgroundPanelInventoryText->getTransform()->setSize(sizeOfText);
	backgroundPanelInventoryText->setText("Inventory");
	backgroundPanelInventoryText->setScale(0.5f);
	backgroundPanelInventoryText->setSortingOrder(5);
	backgroundPanelInventoryText->setColor({1,1,1});
	
	// =============================== SLOTS  ===============================
	sizeOfText = TextRenderer::Instance()->renderTextSize("Weapon      Armour     Spells", 0.7f);
	currentInventoryText->shouldRender = shouldRender;
	currentInventoryText->getTransform()->setPosition(MiddleRight - glm::vec2{sizeOfText.x / 2, -175} - (glm::vec2{350, 0} / 2.0f));
	currentInventoryText->getTransform()->setSize(sizeOfText);
	currentInventoryText->setText("Weapon      Armour      Spells");
	currentInventoryText->setScale(0.7f);
	currentInventoryText->setSortingOrder(4);
	currentInventoryText->setColor({0,0,0});

	sizeOfText = TextRenderer::Instance()->renderTextSize("Weapon      Armour     Spells", 0.709f);
	currentInventoryTextOnline->shouldRender = shouldRender;
	currentInventoryTextOnline->getTransform()->setPosition(MiddleRight - glm::vec2{sizeOfText.x / 2, -175} - (glm::vec2{350, 0} / 2.0f));
	currentInventoryTextOnline->getTransform()->setSize(sizeOfText);
	currentInventoryTextOnline->setText("Weapon      Armour      Spells");
	currentInventoryTextOnline->setScale(0.709f);
	currentInventoryTextOnline->setSortingOrder(5);
	currentInventoryTextOnline->setColor({1 ,1, 1});

	Inventory* inventory = PlayerController::Instance()->myInventory;
	int y = 0;
	for (int i = 0; i < 20; i++)
	{
		InventoryIconButton* slot = slots[i];

		const int testI = i + 1;
		slot->shouldRender = shouldRender;
		slot->getTransform()->setPosition(MiddleRight - glm::vec2{100, 12.5} - (glm::vec2{(testI % 5) * 50, y * 50}));
		
		if (inventory->items.size() > i && inventory->items[i] != nullptr)
		{
			slot->setItem(inventory->items[i]);
		}
		else
		{
			slot->setItem(nullptr);
		}
		
		if (testI != 0 && testI % 5 == 0)
			y++;
	}
	
	weaponSlot->getTransform()->setPosition(MiddleRight - glm::vec2{100, 0} - (glm::vec2{205, -100}));
	armourSlot->getTransform()->setPosition(MiddleRight - glm::vec2{100, 0} - (glm::vec2{100, -100}));
	spellSlot->getTransform()->setPosition(MiddleRight - glm::vec2{100, 0} - (glm::vec2{-5, -100}));

	weaponSlot->shouldRender = shouldRender;
	weaponSlot->setItem(inventory->getFirstItemWithEquipSlot(EquipSlot::WEAPON));
	
	armourSlot->shouldRender = shouldRender;
	armourSlot->setItem(inventory->getFirstItemWithEquipSlot(EquipSlot::ARMOUR));
	
	spellSlot->shouldRender = shouldRender;
	spellSlot->setItem(inventory->getFirstItemWithEquipSlot(EquipSlot::SPELL));
	
}

void InventoryHUD::onSceneChange(OnSceneChanged* event)
{
	slots.clear();
	hasLoaded = false;
}
