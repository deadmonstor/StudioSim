#pragma once
#include <map>
#include <string>
#include "Util/SingletonTemplate.h"
#include <iostream>
#include <type_traits>

class Panel;

class UIManager : public SingletonTemplate<UIManager>
{
	std::map<std::string, Panel*> UIElements;

public:
	void render();
	void clear();

	template<typename T, typename... Args>
	std::enable_if_t<std::is_base_of_v<Panel, T>, T*> createUIElement(const std::string& name, Args... args)
	{
		UIElements[name] = new T(args...);
		return static_cast<T*>(UIElements[name]);
	}
};

