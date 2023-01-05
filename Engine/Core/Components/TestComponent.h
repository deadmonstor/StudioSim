#pragma once
#include "../Component.h"

class TestComponent : public Component
{
public:
	~TestComponent() override {};
	
	void start() override;
	void update() override;
	void lateUpdate() override;
	void render() override;
};
