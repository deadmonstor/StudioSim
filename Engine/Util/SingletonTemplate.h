#pragma once
#include <memory>

template<typename T>

class SingletonTemplate
{
public:
	static T* GetInstance()
	{
		static std::unique_ptr<T> instance = std::make_unique<T>();
		return instance.get();
	}
	
protected:
	SingletonTemplate() {}
	~SingletonTemplate() {}
	
private:
	SingletonTemplate(const SingletonTemplate&) = delete;
	SingletonTemplate* operator=(const SingletonTemplate*) = delete;
	SingletonTemplate& operator=(const SingletonTemplate&) = delete;
};
