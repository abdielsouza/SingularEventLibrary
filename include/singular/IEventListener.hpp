#ifndef D8FF8E0B_709A_4604_9592_C6004D08049C
#define D8FF8E0B_709A_4604_9592_C6004D08049C

#pragma once

#include <singular/Event.hpp>

namespace Singular
{
    class IEventListener
    {
    public:
        virtual void OnEvent(const Event& event) = 0;
    };
}

#endif /* D8FF8E0B_709A_4604_9592_C6004D08049C */
