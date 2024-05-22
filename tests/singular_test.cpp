#include <gtest/gtest.h>
#include <singular/IEventListener.hpp>
#include <singular/EventHandler.hpp>
#include <iostream>
#include <typeinfo>

TEST(singular_test, test_event_handler)
{
    struct MutationEvent : Singular::Event
    {

    };

    struct MutationEventListener : Singular::IEventListener
    {
        void OnEvent(const Singular::Event& event) override
        {
            std::cout << "Mutation event tested!\n";
        }
    } mutation_event_listener;

    Singular::EventHandler handler;

    ASSERT_NO_THROW(handler.RegisterListener<MutationEvent>(&mutation_event_listener));
    ASSERT_NO_THROW(handler.SendEvent<MutationEvent>());
    ASSERT_NO_THROW(handler.RemoveListener<MutationEvent>(&mutation_event_listener));
}

TEST(singular_test, test_multiple_handler_insertion_and_remove)
{
    struct FirstEvent : Singular::Event {};
    struct SecondEvent : Singular::Event {};

    struct AnyEventListener : Singular::IEventListener
    {
        void OnEvent(const Singular::Event& event) override
        {
            if (typeid(event) == typeid(FirstEvent))
                std::cout << "First event tested!\n";
            else if (typeid(event) == typeid(SecondEvent))
                std::cout << "Second event tested!\n";
            else
                std::cout << "Any event tested!\n";
        }
    } any_event_listener;

    Singular::EventHandler handler;

    ASSERT_NO_THROW({
        handler.RegisterListener<FirstEvent>(&any_event_listener);
        handler.RegisterListener<SecondEvent>(&any_event_listener);
    });
    ASSERT_NO_THROW({
        handler.SendEvent<FirstEvent>();
        handler.SendEvent<SecondEvent>();
    });
    ASSERT_NO_THROW(handler.RemoveAll());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
