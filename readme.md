# About the library

This is a simple event handling library written with **C++ 20** _(note the specification)_ I created to be used mainly on game development. However, I want to
make the library **asynchronous** and **"message-driven"**, since I just released now a first version of this.

# How to use it

To use this library, you can take this code as example:

```cpp
// First of all, import the needed libraries.
#include <singular/Event.hpp>
#include <singular/EventHandler.hpp>
#include <iostream> // this is just for printing in the example below.

// Create your own event class (it could be a struct too)
struct CustomEvent : Singular::Event {};

// Create your own event listener.
class CustomEventListener : public IEventListener
{
    void OnEvent(const Singular::Event& event) override
    {
        std::cout << "CustomEvent listened!\n";
    }
};

int main(void)
{
    // Create an instance of the listener and an instance for the handler.
    CustomEventListener listener;
    Singular::EventHandler handler;

    /* Register the listener on the handler. 
     * The listener must be coherent with the event type to be handled.
     */
    handler.RegisterListener<CustomEvent>(&listener);

    // Now we can send the event to its respective listener and it will return a response.
    handler.SendEvent<CustomEvent>();

    // We can also remove the listener from the handler.
    handler.RemoveListener<CustomEvent>(&listener);
    // Or clear the entire listener container.
    handler.RemoveAll();
}
```

# Future features
- Asynchronous programming support
- Templated listeners (to define the events to be listened at compile-time)
- "message-driven" architecture

# How to build and install it

To use this library, the easier way is installing it on your system with the instructions below:

1. First of all, clone this repository, go to the root directory and run these commands:
```bash
mkdir build && cd build
sudo cmake ..
```

2. Inside the "build" directory, run this command to install Singular on your system:
```bash
sudo make install
```

After that, the library should be installed on your system and you are
ready to use it on your projects.