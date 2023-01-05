#pragma once


namespace Disunity
{
	class Event {};
	
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

		FunctionHandler(T* handler, const Func func) : instance{instance}, func{func} {}

		void call(Event *event) override
		{
			(instance->*func)(static_cast<EventType*>(event));
		}
	private:
		T* instance;
		Func func;
	};
}