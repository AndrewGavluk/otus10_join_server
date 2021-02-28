# pragma once
#include <cstdint>
#include <cstdio>
#include <map>
#include <memory>

#include "joinServer.h"

class assyncLib
{
    public:
        assyncLib();
        void receive(const char *);
    private:
        JoinServer m_JoinServer;
        uint64_t m_counter;
};