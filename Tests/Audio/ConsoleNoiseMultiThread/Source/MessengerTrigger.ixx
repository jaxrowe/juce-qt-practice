module;

#include <juce_events.h>
#include <juce_core.h>
#include <iostream>

export module MessengerTrigger;

export
{
    
    class MessengerTrigger : public juce::Thread
    {

    public:

        MessengerTrigger() : juce::Thread("Messenger Thread")
        {
            std::cout << "Starting " << getThreadName() << std::endl;
            startThread();
        }

        void run() override
        {
            if (isThreadRunning())
            {
                std::cout << getThreadName() << " Running On Thread ID: " << getThreadId() << std::endl;
            }

            auto Messenger {juce::MessageManager::getInstance()};
            if (Messenger != nullptr)
            {
                std::cout << "MessageManager Successfully Created" << std::endl;
            }
            else
            {
                std::cout << "MessageManager Failed To Create" << std::endl;
            }

            std::cout << "Starting Messenger Dispatch Loop" << std::endl;
            Messenger->runDispatchLoop();
            std::cout << "Messenger Dispatch Loop Stopped" << std::endl;
            
            /*
            potentially add a function call here that replaces 'return app->shutdownApp();'
            from standard juce application setups, in the main() event loop in juce::JUCEApplicationBase::main()
            but instead of running shutdownApp() of a JUCEApplicationBase (that we are not using)
            just write somthing that deallocates objects from audio-only backend gradually, in a order that prevents any crashes, 
            for safe and clean application shutdown.
            */

        }
    };
}

module : private;