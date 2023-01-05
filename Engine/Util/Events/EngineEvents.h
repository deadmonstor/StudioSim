﻿#pragma once
#include "FunctionHandler.h"

NEW_EMPTY_EVENT(OnEngineStart);
NEW_EMPTY_EVENT(OnEngineUpdate);
NEW_EMPTY_EVENT(OnEngineStop);

class OnKey : public Disunity::Event
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