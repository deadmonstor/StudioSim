#pragma once
#include "Core\Components\AI\Behaviour.h"
#include <Library/glm/ext/vector_float2.hpp>
#include "PlayerController.h"

class PlayerMovementBehaviour : public Behaviour
{
public:
	glm::fvec2 moveDir;
	glm::fvec2 origPos = {0, 0};
	glm::vec2 targetPos;

private:
	void Act() override;
	void onKeyDownResponse(Griddy::Event*);
	void onKeyUpResponse(Griddy::Event*);

protected:
	FunctionMap CreateFunctionMap() override;

	
};

