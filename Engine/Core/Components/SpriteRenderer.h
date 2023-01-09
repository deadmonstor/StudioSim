#pragma once
#include <Core/Renderer/texture.h>
#include "Core/Component.h"
#include "Core/Renderer/Shader.h"

class SpriteRenderer : public Component
{
	glm::vec3 color = glm::vec3(1.0f);
	Shader shader; 
	Texture texture;
	Texture normals;
public:
	~SpriteRenderer() override;
	
	void start() override;
	void createBuffers();
	void update() override;
	void lateUpdate() override;
	void getDebugInfo(std::string*) override;
	
	void setColor(glm::vec3 color);
	glm::vec3 getColor() const { return color; }
	
	Shader getShader() const;
	void setShader(Shader shader);
	void setLit(bool lit);

	Texture getTexture() const { return texture; }
	void setTexture(const Texture texture) { this->texture = texture; }
	
	Texture getNormals() const { return normals; }
	void setNormals(const Texture normals) { this->normals = normals; }
};
