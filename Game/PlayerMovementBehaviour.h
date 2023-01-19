#pragma once
#include "Core\Components\AI\Behaviour.h"
#include <Library/glm/ext/vector_float2.hpp>

class PlayerMovementBehaviour : public Behaviour
{
public:
	glm::vec2 moveDir;
	glm::vec2 origPos;
	glm::vec2 targetPos;

private:
	void Act() override;
	void onKeyDownResponse(const Griddy::Event*);

protected:
	FunctionMap CreateFunctionMap() override;

	
};

