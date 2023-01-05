#pragma once
#include "Core/Component.h"

class SpriteRenderer final : public Component
{
public:
	~SpriteRenderer() override;
	void start() override;
	void update() override;
	void lateUpdate() override;
	void render() override;
private:
	unsigned int quadVAO;
};
