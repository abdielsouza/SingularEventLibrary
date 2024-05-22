#ifndef A395D8B6_17F4_4F78_8C3B_678C5E070DDD
#define A395D8B6_17F4_4F78_8C3B_678C5E070DDD

#pragma once

#include <unordered_map>
#include <vector>
#include <functional>

#include <singular/EventID.hpp>
#include <singular/IEventListener.hpp>

namespace Singular
{
    template <typename TEvent>
    concept IsEventType = std::is_base_of_v<Event, TEvent>;

    class EventHandler
    {
        using IEventListenerPtrList = std::vector<IEventListener*>;

        std::unordered_map<EventID, IEventListenerPtrList> listeners;

    public:
        template <IsEventType TEvent>
        void RegisterListener(IEventListener* listener);

        template <IsEventType TEvent>
        void RemoveListener(IEventListener* listener);

        template <IsEventType TEvent, typename ...Args>
        void SendEvent(Args... args);

        template <IsEventType TEvent>
        void SendEvent(const TEvent& event);

        template <IsEventType TEvent>
        unsigned int GetListenerCount() const;

        void RemoveAll();
    };
}

#include <singular/EventHandler.inl>

#endif /* A395D8B6_17F4_4F78_8C3B_678C5E070DDD */
