#include "UI/InventoryButton.h"
#include "Engine.h"
#include "Core/AudioEngine.h"
#include "UI/InventoryHUD.h"

InventoryButton::InventoryButton(const Texture& _texture) : ButtonComponent(_texture)
{

}

void InventoryButton::onClick()
{
	AudioEngine::Instance()->playSound("Sounds\\Click.wav", false, 0.2f, 0, 0, AudioType::SoundEffect);
	setColor({ 1, 0, 0 });
	
	InventoryHUD::Instance()->shouldRender = !InventoryHUD::Instance()->shouldRender;
}