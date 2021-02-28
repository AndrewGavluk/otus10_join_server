#include "joinServer.h"

JoinServer::JoinServer()
{
    m_thread = std::thread(&JoinServer::process, std::ref(*this));
}

JoinServer::~JoinServer()
{
    if (m_thread.joinable())
        m_thread.join();
}

void JoinServer::process()
{
    std::string stringToProcess;
    while (m_queue.pop(stringToProcess))
        std::cout << stringToProcess << std::endl;
}

void JoinServer::pushBack(const char* buf, size_t& size)
{
    m_queue.push(std::string{buf, size});
}