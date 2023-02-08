#pragma once
#include <algorithm>
#include <map>
#include <string>
#include "Util/SingletonTemplate.h"
#include <type_traits>
#include <vector>

class Panel;

class UIManager : public SingletonTemplate<UIManager>
{
	std::map<std::string, Panel*> UIElements;
	std::vector<Panel*> renderPanels;
	
public:
	void render();
	void clear();
	void sortOrder();
	void update();

	template<typename T, typename... Args>
	std::enable_if_t<std::is_base_of_v<Panel, T>, T*> createUIElement(const std::string& name, Args... args)
	{
		UIElements[name] = new T(args...);
		sortOrder();
		
		return static_cast<T*>(UIElements[name]);
	}
};

