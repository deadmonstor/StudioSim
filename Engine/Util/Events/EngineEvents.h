#pragma once
#include "FunctionHandler.h"
#include "Core/Components/SpriteRenderer.h"

class AnimatedSpriteRenderer;
class Light;
class GameObject;
NEW_EMPTY_EVENT(OnEngineStart);
NEW_EMPTY_EVENT(OnEngineUpdate);
NEW_EMPTY_EVENT(OnEngineStop);

enum DebugEvent
{
	DebugRenderGrid,	
	DebugPlaySound,	
	DebugKeyEvents,	
	DebugMouseEvents,	
	DebugMouseLight,	
	DebugLightColor,	
	DebugChangeScene,	
};

class OnDebugEventChanged : public Griddy::Event
{
public:
	OnDebugEventChanged(const DebugEvent key) : key(key) {}
	DebugEvent key;
};

class OnSceneChangeRequested : public Griddy::Event
{
public:
	OnSceneChangeRequested(const std::string key) : key(key) {}
	std::string key;
};

class OnSceneChanged : public Griddy::Event
{
public:
	OnSceneChanged(const std::string key) : key(key) {}
	std::string key;
};

#pragma region Key Events
class OnKey : public Griddy::Event
{
public:
	OnKey(const int key, const int scancode) : key(key), scancode(scancode) {}
	int key;
	int scancode;
};

class OnKeyDown : public OnKey
{
public:
	OnKeyDown(const int key, const int scancode) : OnKey(key, scancode) {}
};

class OnKeyUp : public OnKey
{
public:
	OnKeyUp(const int key, const int scancode) : OnKey(key, scancode) {}
};

class OnKeyRepeat : public OnKey
{
public:
	OnKeyRepeat(const int key, const int scancode) : OnKey(key, scancode) {}
};

#pragma endregion 
#pragma region Mouse Events
class OnMouse : public Griddy::Event
{
public:
	OnMouse(const int key, const int action) : key(key), action(action) {}
	int key;
	int action;
};

class OnMouseDown : public OnMouse
{
public:
	OnMouseDown(const int key, const int action) : OnMouse(key, action) {}
};

class OnMouseUp : public OnMouse
{
public:
	OnMouseUp(const int key, const int action) : OnMouse(key, action) {}
};
#pragma endregion

class OnFileDropCallback : public Griddy::Event
{
public:
	OnFileDropCallback(const int count, const char** paths) : count(count), paths(paths) {}
	int count;
	const char** paths;
};

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

class OnGameObjectRemoved : public Griddy::Event
{
public:
	explicit OnGameObjectRemoved(GameObject* _gameObject) : gameObject(_gameObject) {}
	GameObject* gameObject;
};

class OnAnimationEnded : public Griddy::Event
{
public:
	explicit OnAnimationEnded(AnimatedSpriteRenderer* _animatedSpriteRenderer) : animatedSpriteRenderer(_animatedSpriteRenderer) {}
	AnimatedSpriteRenderer* animatedSpriteRenderer;
};