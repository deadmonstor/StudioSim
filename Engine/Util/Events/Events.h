#pragma once
#include <map>
#include <typeindex>
#include "FunctionHandler.h"
#include "../Logger.h"
#include "../SingletonTemplate.h"

namespace Disunity
{
	class Events : public SingletonTemplate<Events>
	{
	public:
		typedef std::map<int, FunctionBase*> EventList;

		template<typename EventType>
		void invoke(EventType *event)
		{
			const EventList* list = internalEvents[typeid(EventType)];

			if (list == nullptr)
				return;

			for (const auto [id, function_base] : *list)
			{
				FunctionBase *handler = function_base;
				if (!handler)
				{
					continue;
				}
				
				handler->invoke(event);
			}
		}

		template<class T, class EventType>
		int subscribe(T* instance, void (T::*func)(EventType*))
		{
			EventList* list = internalEvents[typeid(EventType)];

			if (list == nullptr)
			{
				list = new EventList();
				internalEvents[typeid(EventType)] = list;
			}

			// TODO: Check if this is slow? 
			int nextID = 0;
			for (const auto [i, it] : *list)
			{
				if (i > nextID)
				{
					nextID = i;
				}
			}
			
			list->insert({nextID + 1, new FunctionHandler<T, EventType>(instance, func)});
			return nextID + 1;
		}

		template<class T, class EventType>
		void unsubscribe(T*, void (T::*)(EventType*), const int id)
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
			}
		}
	private:
		std::map<std::type_index, EventList*> internalEvents;
	};
}