#pragma once
#include "Core/Components/SpriteComponent.h"

class Panel : public SpriteComponent
{
	Transform* transform;
public:
	Panel(); 

	bool shouldRender = true;
	virtual void render();
	
	void SetTexture(const Texture& texture);
	void SetShader(const Shader& shader);
	
	Transform* getTransform() const { return transform; }
};
