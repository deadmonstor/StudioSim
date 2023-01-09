#pragma once

#include <string>

class SortingLayer
{
public:
	const std::string& getName() const { return name; }
	const int& getOrder() const { return order; }

private:
	SortingLayer(std::string layerName, const int order)
		: name(std::move(layerName)),
		order(order)
	{}

private:
	std::string name;
	int order;

	friend class Renderer;
};