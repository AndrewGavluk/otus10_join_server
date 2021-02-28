
#include "Client.h"

ClientSession::ClientSession(assyncLib& _assync, ip::tcp::socket sock) : 
    m_assync{_assync},  m_sock{std::move(sock)} {}

void ClientSession::start()
{
    m_handle = 0;//m_assync.connect(m_bulkSize);
    m_self = shared_from_this();
    handle_read();
}

void ClientSession::handle_read()
{
    auto interpreter = [this](const boost::system::error_code& ec, 
                            std::size_t len){
        if (!ec){
            (void)(len);
            m_assync.receive(m_buf.data());
            handle_read();
        }
        else{
            m_sock.close();
            m_self.reset();
        }
    };
    m_sock.async_read_some(buffer(m_buf),interpreter );
}