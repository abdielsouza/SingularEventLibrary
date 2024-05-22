#include <singular/EventHandler.hpp>

namespace Singular
{
    template <IsEventType TEvent>
    inline void EventHandler::RegisterListener(IEventListener* listener)
    {
        EventID id = EventIDGenerator<Event>::GetEventID<TEvent>();
        listeners[id].push_back(listener);
    }

    template<IsEventType TEvent>
    inline void EventHandler::RemoveListener(IEventListener* listener)
    {
        EventID id = EventIDGenerator<Event>::GetEventID<TEvent>();
        IEventListenerPtrList& listeners = this->listeners[id];

        for (auto it = listeners.begin(); it != listeners.end(); ++it)
        {
            if (*it == listener)
            {
                listeners.erase(it);
                break;
            }
        }
    }

    template<IsEventType TEvent, typename ...Args>
    inline void EventHandler::SendEvent(Args ...args)
    {
        TEvent event(args...);
        SendEvent(event);
    }

    template<IsEventType TEvent>
    inline void EventHandler::SendEvent(const TEvent& event)
    {
        const_cast<TEvent&>(event).event_handler = this;
        EventID id = EventIDGenerator<Event>::GetEventID<TEvent>();
        
        if (listeners.find(id) != listeners.end())
        {
            for (IEventListener* listener : listeners.at(id))
            {
                listener->OnEvent(event);
            }
        }
    }

    template <IsEventType TEvent>
    inline unsigned int EventHandler::GetListenerCount() const
    {
        EventID id = EventIDGenerator<Event>::GetEventID<TEvent>();

        if (listeners.find(id) != listeners.end())
        {
            return listeners.at(id).size();
        }

        return 0u;
    }

    void EventHandler::RemoveAll()
    {
        listeners.clear();
    }
}