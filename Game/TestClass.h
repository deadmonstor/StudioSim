#pragma once
#include "Util/Logger.h"
#include "Util/SingletonTemplate.h"

class TestClass : public SingletonTemplate<TestClass>
{
public:
	void TestFunc(testName*)
	{
		LOG_INFO("TestFunc");
	}
};
