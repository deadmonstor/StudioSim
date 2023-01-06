// ReSharper disable CppClangTidyBugproneMacroParentheses
#pragma once

namespace Griddy
{
	class Event
	{
		protected:
			Event() {}
	};
	
	class FunctionBase
	{
	public:
		virtual ~FunctionBase() = default;
		void invoke(Event* event) { call(event); }
	private:
		virtual void call(Event* event) = 0;
	};

	template<class T, class EventType>
	class FunctionHandler final : public FunctionBase
	{
	public:
		typedef void (T::*Func)(EventType*);

		FunctionHandler(T* instance, const Func func) : instance{instance}, func{func} {}

		void call(Event *event) override
		{
			(instance->*func)(static_cast<EventType*>(event));
		}
	private:
		T* instance;
		Func func;
	};

	#define NEW_EMPTY_EVENT(eventName) \
		class eventName : public Griddy::Event\
		{\
		}
}