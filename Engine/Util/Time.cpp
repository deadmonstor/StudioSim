#include "Time.h"

Time::Time()
{
	m_start = std::chrono::steady_clock::now();
}

void Time::update()
{
	Instance()->internalUpdate();
}

void Time::internalUpdate()
{
	m_end = std::chrono::steady_clock::now();
	const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start);
	
	m_deltaTime = static_cast<double>(duration.count()) / 1000000.0;
	m_start = std::chrono::steady_clock::now();

	// 0.4 seems to be unreal engine 5's magic number
	if (m_deltaTime > 0.4)
	{
		m_deltaTime = 0.4;
	}
	
	m_time += m_deltaTime;
}