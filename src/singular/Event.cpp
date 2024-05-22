#include <singular/Event.hpp>

namespace Singular
{
    EventHandler* Event::GetSender() const
    {
        return event_handler;
    }
}