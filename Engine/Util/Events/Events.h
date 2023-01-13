#pragma once
#include <map>
#include <typeindex>
#include "FunctionHandler.h"
#include "../Logger.h"
#include "../SingletonTemplate.h"

namespace Griddy
{
	class Events : public SingletonTemplate<Events>
	{
	public:
		typedef std::map<int8_t, FunctionBase*> EventList;

		template<typename T, typename... Args>
		static void invoke(Args... args)
		{
			Instance()->invokeInternal(new T(args...));
		}

		template<typename T, typename... Args>
		static void invokeWithoutCleanup(Args... args)
		{
			Instance()->invokeInternal(new T(args...), true);
		}

		template<class T, class EventType>
		static int8_t subscribe(T* instance, void (T::*func)(EventType*))
		{
			return Instance()->subscribeInternal(instance, func);
		}

		template<class T, class EventType>
		static void unsubscribe(T* instance, void (T::*func)(EventType*), const int8_t id)
		{
			Instance()->unsubscribeInternal(instance, func, id);
		}
		
	private:
		std::map<std::type_index, EventList*> internalEvents;

		template<typename EventType>
		void invokeInternal(EventType *event, bool withoutCleanup = false)
		{
			const EventList* list = internalEvents[typeid(EventType)];

			if (list == nullptr)
				return;

			for (const auto [id, function_base] : *list)
			{
				FunctionBase* handler = function_base;
				if (handler == nullptr)
				{
					continue;
				}
				
				handler->invoke(event);
			}

			if (!withoutCleanup)
				delete event;
		}

		template<class T, class EventType>
		int8_t subscribeInternal(T* instance, void (T::*func)(EventType*))
		{
			EventList* list = internalEvents[typeid(EventType)];

			if (list == nullptr)
			{
				list = new EventList();
				internalEvents[typeid(EventType)] = list;
			}

			int8_t nextID = 0;
			// TODO: Check if this is slow? 
			for (const auto [i, it] : *list)
			{
				if (i > nextID)
				{
					nextID = i;
				}
			}

			nextID = nextID + 1;
			list->insert({nextID, new FunctionHandler<T, EventType>(instance, func)});
			return nextID;
		}

		template<class T, class EventType>
		void unsubscribeInternal(T*, void (T::*)(EventType*), const int8_t id)
		{
			EventList* list = internalEvents[typeid(EventType)];

			if (list == nullptr)
			{
				return;
			}

			if (const auto it = list->find(id); it != list->end())
			{
				delete it->second;
				list->erase(it);
			}
			else
			{
				LOG_ERROR("Event not found");
				abort();
			}
		}
	};
}