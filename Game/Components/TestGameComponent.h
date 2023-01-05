#pragma once
#include "Core/Component.h"

class TestGameComponent : public Component
{
public:
	~TestGameComponent() override = default;

	void start() override;
	void update() override;
	void lateUpdate() override;
	void render() override;
};
