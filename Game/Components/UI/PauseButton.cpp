#include "PauseButton.h"
#include "Engine.h"

PauseButton::PauseButton(const Texture& _texture) : ButtonComponent(_texture)
{

}

void PauseButton::onClick()
{
	setColor({ 1, 0, 0 });
	Griddy::Engine::setPaused(true);
}


