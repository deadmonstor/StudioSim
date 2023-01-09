#pragma once
#include "FunctionHandler.h"

class SpriteComponent;
class Light;

class OnSpriteRendererComponentStarted : public Griddy::Event
{
public:
	explicit OnSpriteRendererComponentStarted(SpriteComponent* spriteRenderer) : spriteRenderer(spriteRenderer) {}
	SpriteComponent* spriteRenderer;
};

class OnSpriteRendererComponentRemoved : public Griddy::Event
{
public:
	explicit OnSpriteRendererComponentRemoved(SpriteComponent* spriteRenderer) : spriteRenderer(spriteRenderer) {}
	SpriteComponent* spriteRenderer;
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