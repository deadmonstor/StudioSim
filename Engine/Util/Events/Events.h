#pragma once
#include <map>
#include <ranges>
#include <typeindex>

#include "EngineEvents.h"
#include "FunctionHandler.h"
#include "../Logger.h"
#include "../SingletonTemplate.h"

namespace Griddy
{
	class Events : public SingletonTemplate<Events>
	{
	public:
		
		typedef std::map<int32_t, FunctionBase*> EventList;

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
		static int32_t subscribe(T* instance, void (T::*func)(EventType*))
		{
			return Instance()->subscribeInternal(instance, func);
		}

		template<class T, class EventType>
		static void unsubscribe(T* instance, void (T::*func)(EventType*), const int32_t id)
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
		void invokeInternal(EventType *event, bool withoutCleanup = false)
		{
			if (!internalEvents.contains(typeid(EventType)))
			{
				if (!withoutCleanup)
					delete event;
				
				return;
			}
			
			const EventList* list = internalEvents[typeid(EventType)];

			if (list == nullptr || !list || list->empty())
			{
#ifdef _DEBUG_ECS
				if (true && !isBlacklistedLog(typeid(EventType).name()))
					LOG_INFO("Invoking event: " + std::string(typeid(EventType).name()) + " with 0 subscribers");
#endif
				
				if (!withoutCleanup)
					delete event;
				
				return;
			}

#ifdef _DEBUG_ECS
			if (!isBlacklistedLog(typeid(EventType).name()))
				LOG_INFO("Invoking event: " + std::string(typeid(EventType).name()) + " with " + std::to_string(list->size()) + " subscribers");
#endif
			
			for (const auto t : *list)
			{
				FunctionBase* handler = t.second;
				
				if (!handler)
				{
					DebugBreak();
					continue;
				}
				
				handler->invoke(event);
			}

			if (!withoutCleanup)
				delete event;
		}
		
		struct UnsubscribeData
		{
			UnsubscribeData(const std::type_index& type, int32_t id)
				: type(type),
				  id(id) {}

			std::type_index type;
			int32_t id;
		};

		inline static std::vector<UnsubscribeData> reuseIDQueue = std::vector<UnsubscribeData>();
		
		template<class T, class EventType>
		int32_t subscribeInternal(T* instance, void (T::*func)(EventType*))
		{
			EventList* list = internalEvents[typeid(EventType)];
			
			if (list == nullptr)
			{
				list = new EventList();
				internalEvents[typeid(EventType)] = list;
			}
			
			int32_t nextID = 0;
			for (auto it = reuseIDQueue.begin(); it != reuseIDQueue.end(); ++it)
			{
				if (it->type == typeid(EventType))
				{
					nextID = it->id;
					reuseIDQueue.erase(it);
					break;
				}
			}

			if (nextID == 0)
			{
				for (const auto i : *list | std::views::keys)
				{
					if (i > nextID)
					{
						nextID = i;
					}
				}
				
				nextID = nextID + 1;
			}

#ifdef _DEBUG_ECS
			LOG_INFO("Subscribing to event: " + std::string(typeid(EventType).name()) + " with ID: " + std::to_string(nextID));
#endif
			
			list->insert({nextID, new FunctionHandler<T, EventType>(instance, func)});
			return nextID;
		}
		
		inline static std::vector<UnsubscribeData> unsubscribeQueue = std::vector<UnsubscribeData>();

		void unsubscribeInternalQueue()
		{
			for (const auto& data : unsubscribeQueue)
			{
				unsubscribeInternal(data.type, data.id);
				reuseIDQueue.push_back(data);
			}
			
			unsubscribeQueue.clear();
		}

		void unsubscribeInternal(const std::type_index type, const int32_t id)
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
				abort();
			}
		}

		template<class T, class EventType>
		static void unsubscribeInternalQueue(T*, void (T::*)(EventType*), const int32_t id)
		{
			unsubscribeQueue.push_back(UnsubscribeData(typeid(EventType), id));
		}
	};
}