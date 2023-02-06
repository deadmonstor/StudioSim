#pragma once
#include <string>
#include "FunctionHandler.h"

class AnimatedSpriteRenderer;
class SpriteComponent;
class Light;
class GameObject;
NEW_EMPTY_EVENT(OnEngineStart);
NEW_EMPTY_EVENT(OnEngineUpdate);
NEW_EMPTY_EVENT(OnEngineStop);
NEW_EMPTY_EVENT(OnEngineRender);

enum DebugEvent
{
	DebugRenderGrid,	
	DebugPlaySound,	
	DebugKeyEvents,	
	DebugMouseEvents,	
	DebugMouseLight,	
	DebugLightColor,	
	DebugPauseGame,	
	DebugChangeScene,	
	DebugNoclip,	
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

class OnCharacterDown : public OnKey
{
public:
	OnCharacterDown( unsigned int key) : OnKey(key, 0) {}
};

class OnCharacterUp : public OnKey
{
public:
	OnCharacterUp( unsigned int key) : OnKey(key, 0) {}
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