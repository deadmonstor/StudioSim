#pragma once
#include <chrono>

#include "SingletonTemplate.h"

class Time : public SingletonTemplate<Time>
{
public:
	Time();
	static void update();

	double static getDeltaTime() { return Instance()->m_deltaTime; }
	double static getTime() { return Instance()->m_time; }
	
private:
	void internalUpdate();

	double m_time = 0;
	double m_deltaTime = 0;

	std::chrono::steady_clock::time_point m_start;
	std::chrono::steady_clock::time_point m_end;
};
