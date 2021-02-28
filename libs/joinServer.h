#include <iostream>
#include <string.h>
#include <sstream>
#include <thread>

#include <boost/algorithm/string.hpp>

#include "queue.h"

class JoinServer
{
    public:
        JoinServer();
        ~JoinServer();
        void pushBack(const char*, size_t& size);
        
    private:
        void process();
        queueLists<std::string> m_queue;
        std::thread m_thread;
};

