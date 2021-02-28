#include <iostream>
#include <string.h>
#include <thread>

#include "queue.h"

class JoinServer
{
    public:
        JoinServer();
        ~JoinServer();
        void pushBack(std::string&);
        
    private:
        void process();
        queueLists<std::string> m_queue;
        std::thread m_thread;
};

