﻿#pragma once
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

		template<class T, class EventType>
		static int8_t subscribe(T* instance, void (T::*func)(EventType*))
		{
			return Instance()->subscribeInternal(instance, func);
		}

		template<class T, class EventType>
		static void unsubscribe(T* instance, void (T::*func)(EventType*), const int8_t id)
		{
			Instance()->unsubscribeInternalQueue(instance, func, id);
		}
		
		static void unsubscribeQueueFunc()
		{
			Instance()->unsubscribeInternalQueue();
		}
		
	private:
		std::map<std::type_index, EventList*> internalEvents;

#ifdef _DEBUG_ECS
		inline static std::vector<std::string> blacklist = {typeid(OnEngineUpdate).name(), typeid(OnEngineRender).name()};

		static bool isBlacklistedLog(const std::string name)
		{
			return std::ranges::find(blacklist, name) != blacklist.end();
		}

#endif

		template<typename EventType>
		void invokeInternal(EventType *event)
		{
			const EventList* list = internalEvents[typeid(EventType)];

			if (list == nullptr || !list || list->empty())
			{
#ifdef _DEBUG_ECS
				if (false && !isBlacklistedLog(typeid(EventType).name()))
					LOG_INFO("Invoking event: " + std::string(typeid(EventType).name()) + " with 0 subscribers");
#endif
				
				delete event;
				return;
			}

#ifdef _DEBUG_ECS
			if (!isBlacklistedLog(typeid(EventType).name()))
				LOG_INFO("Invoking event: " + std::string(typeid(EventType).name()) + " with " + std::to_string(list->size()) + " subscribers");
#endif
			
			for (const auto t : *list)
			{
				int8_t id = t.first;
				FunctionBase* handler = t.second;
				
				if (!handler)
				{
					continue;
				}
				
				handler->invoke(event);
			}

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

			// TODO: Check if this is slow? 
			int8_t nextID = 0;
			for (const auto [i, it] : *list)
			{
				if (i > nextID)
				{
					nextID = i;
				}
			}

#ifdef _DEBUG_ECS
			if (!isBlacklistedLog(typeid(EventType).name()))
				LOG_INFO("Subscribing to event: " + std::string(typeid(EventType).name()) + " with ID: " + std::to_string(nextID + 1));
#endif
			
			list->insert({nextID + 1, new FunctionHandler<T, EventType>(instance, func)});
			return nextID + 1;
		}

		struct UnsubscribeData
		{
			UnsubscribeData(const std::type_index& type, int8_t id)
				: type(type),
				  id(id) {}

			std::type_index type;
			int8_t id;
		};
		
		inline static std::vector<UnsubscribeData> unsubscribeQueue = std::vector<UnsubscribeData>();

		void unsubscribeInternalQueue()
		{
			for (const auto& data : unsubscribeQueue)
			{
				unsubscribeInternal(data.type, data.id);
			}

			unsubscribeQueue.clear();
		}

		void unsubscribeInternal(const std::type_index type, const int8_t id)
		{
			EventList* list = internalEvents[type];

			if (list == nullptr)
			{
				return;
			}

			if (const auto it = list->find(id); it != list->end())
			{
#ifdef _DEBUG_ECS
				if (!isBlacklistedLog(type.name()))
					LOG_INFO("Unsubscribing from event: " + std::string(type.name()) + " with ID: " + std::to_string(id));
#endif
				
				delete it->second;
				list->erase(it);
			}
			else
			{
				LOG_ERROR("Event not found");
			}
		}

		template<class T, class EventType>
		static void unsubscribeInternalQueue(T*, void (T::*)(EventType*), const int8_t id)
		{
			unsubscribeQueue.push_back(UnsubscribeData(typeid(EventType), id));
		}
	};
}