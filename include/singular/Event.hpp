#ifndef D8946220_7FBE_41E9_8EE8_B1619D77665C
#define D8946220_7FBE_41E9_8EE8_B1619D77665C

#pragma once

namespace Singular
{
    class EventHandler;

    class Event
    {
        EventHandler* event_handler = nullptr;

        friend class EventHandler;
        
    public:
        EventHandler* GetSender() const;
    };
}

#endif /* D8946220_7FBE_41E9_8EE8_B1619D77665C */
