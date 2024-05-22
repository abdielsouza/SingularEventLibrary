#ifndef B0CF720B_1902_49E8_BCD8_2B03496DAC70
#define B0CF720B_1902_49E8_BCD8_2B03496DAC70

#pragma once

#include <cstddef>
#include <type_traits>
#include <singular/Event.hpp>

namespace Singular
{
    using EventID = std::size_t;

    template <typename TEventBase>
    class EventIDGenerator
    {
        static_assert(std::is_base_of<Event, TEventBase>::value, "TEvent should be a derived class of Event");

        static EventID next_event_id;

    public:
        template <typename T>
        static EventID GetEventID();
    };
}

#include <singular/EventID.inl>

#endif /* B0CF720B_1902_49E8_BCD8_2B03496DAC70 */
