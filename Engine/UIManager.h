#pragma once
#include <map>
#include <string>
#include "Util/SingletonTemplate.h"
#include <iostream>

class Panel;

class UIManager : public SingletonTemplate<UIManager>
{
	std::map<std::string, Panel*> UIElements;

public:
	void render();
	void clear();

	// TODO: Make this only work for classes that inherit from Panel
	template<typename T, typename... Args>
	T* createUIElement(const std::string& name, Args... args)
	{
		if (std::derived_from<T, Panel>)
		{
			UIElements[name] = new T(args...);
			return static_cast<T*>(UIElements[name]);
		}
		else
		{
			std::cout << "ERROR: Trying to create UI element that is not a panel\n";
		}
	}
};

