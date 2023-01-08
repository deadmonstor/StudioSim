#pragma once
#include "FunctionHandler.h"
#include "Core/Components/SpriteRenderer.h"

class Light;

class OnSpriteRendererComponentStarted : public Griddy::Event
{
public:
	explicit OnSpriteRendererComponentStarted(SpriteRenderer* spriteRenderer) : spriteRenderer(spriteRenderer) {}
	SpriteRenderer* spriteRenderer;
};

class OnSpriteRendererComponentRemoved : public Griddy::Event
{
public:
	explicit OnSpriteRendererComponentRemoved(SpriteRenderer* spriteRenderer) : spriteRenderer(spriteRenderer) {}
	SpriteRenderer* spriteRenderer;
};

class OnLightComponentStarted : public Griddy::Event
{
public:
	explicit OnLightComponentStarted(Light* light) : light(light) {}
	Light* light;
};

class OnLightComponentRemoved : public Griddy::Event
{
public:
	explicit OnLightComponentRemoved(Light* light) : light(light) {}
	Light* light;
};