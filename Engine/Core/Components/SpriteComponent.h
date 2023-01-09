#pragma once
#include <Core/Renderer/texture.h>
#include "Core/Component.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Shader.h"
#include "Core/Renderer/SortingLayer.h"

class SpriteComponent : public Component
{
	glm::vec3 color = glm::vec3(1.0f);
	Shader shader;
	Texture texture;
	Texture normals;

	int sortingOrder = 0;
	SortingLayer sortingLayer = Renderer::getDefaultSortingLayer();
public:
	~SpriteComponent() override;

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
	void setTexture(const Texture _texture) { this->texture = _texture; }

	Texture getNormals() const { return normals; }
	void setNormals(const Texture _normals) { this->normals = _normals; }

	int getSortingOrder() const { return sortingOrder; }
	void setSortingOrder(const int _sortingOrder) { this->sortingOrder = _sortingOrder; }

	SortingLayer getSortingLayer() const { return sortingLayer; }
	void setSortingLayer(SortingLayer _sortingLayer) { this->sortingLayer = std::move(_sortingLayer); }
};
