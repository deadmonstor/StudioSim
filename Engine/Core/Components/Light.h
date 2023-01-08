#pragma once
#include "Core/Component.h"

class Light final : public Component
{
public:
	void start() override;
	~Light();
};
