#pragma once
#include "Core/Component.h"

class TestGameComponent : public Component
{
public:
	void start() override;
	void update() override;
	void lateUpdate() override;
	void render() override;
};
