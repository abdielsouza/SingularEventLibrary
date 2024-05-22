#include <singular/EventID.hpp>

namespace Singular
{
    template <typename TEventBase>
    EventID EventIDGenerator<TEventBase>::next_event_id = 0;

    template <typename TEventBase>
    template <typename TEvent>
    inline EventID EventIDGenerator<TEventBase>::GetEventID()
    {
        static const EventID id = next_event_id++;
        return id;
    }
}