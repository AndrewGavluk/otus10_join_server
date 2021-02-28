#include "joinServer.h"

JoinServer::JoinServer():m_words{4}
{
    m_thread = std::thread(&JoinServer::process, std::ref(*this));
    
    m_trigers.emplace(std::make_pair(messType::INSERT,                  "INSERT"));
    m_trigers.emplace(std::make_pair(messType::TRUNCATE,                "TRUNCATE"));
    m_trigers.emplace(std::make_pair(messType::INTERSECTION,            "INTERSECTION\n"));
    m_trigers.emplace(std::make_pair(messType::SYMMETRIC_DIFFERENCE,    "SYMMETRIC_DIFFERENCE\n"));
}

JoinServer::~JoinServer()
{
    if (m_thread.joinable())
        m_thread.join();
}

void JoinServer::insert(std::map<int, std::string>& tab)
{
    int index = std::stoi(m_words[2]);
    auto find = tab.find(index);
        if (find==tab.end())
        {
            try
            {
                tab.emplace(std::make_pair(index, m_words[3]));
                std::cout << "OK. Insertion complete" << std::endl;
            }
            catch(const std::exception& e){
                std::cerr << e.what() << '\n';}
        }
        else
            std::cerr << "ERR duplicate " << m_words[2] << std::endl;
}

// chain of responsibility
void JoinServer::processINSERT(){
    if (m_words[0] != m_trigers[messType::INSERT])
    {
        processTRUNCATE();
        return;
    };

    if (m_words.size() != 4)
    {
        std::cerr << "wrong number of parametrs : " << " INSERT tabName index value " << std::endl;
        return;
    }

    if (m_words[1] == "A")
        insert(m_tabA);
    else if (m_words[1] == "B")
        insert(m_tabB);
    else
        std::cerr << "unknown tabName parametr : " << m_words[1] << std::endl;
}



void JoinServer::processTRUNCATE(){
    if (m_words[0] != m_trigers[messType::TRUNCATE])
    {
        processINTERSECTION();
        return;
    };

    if (m_words[1] == "A")
        m_tabA.clear();
    else if (m_words[1] == "B")
        m_tabB.clear();
    else
        std::cerr << "unknown tabName parametr : " << m_words[1] << std::endl;

    std::cout << "process TRUNCATE\n"; 
}

bool compareNoCase( const std::string& s1, const std::string& s2 ) {
    return strcasecmp( s1.c_str(), s2.c_str() ) <= 0;
}

void JoinServer::processINTERSECTION(){
    if (m_words[0] != m_trigers[messType::INTERSECTION])
    {
        processSYMMETRIC_DIFFERENCE();
        return;
    };

    m_results.clear();
    //std::sort (m_tabA.begin(), m_tabA.end(), compareNoCase);

    std::cout << "process INTERSECTION\n"; 
}

void JoinServer::processSYMMETRIC_DIFFERENCE(){
    if (m_words[0] != m_trigers[messType::SYMMETRIC_DIFFERENCE]){
        std::cout << "unknown command : " << m_words[0] << std::endl;
        return;
    };
    std::cout << "process SYMMETRIC_DIFFERENCE\n"; 
}


void JoinServer::process()
{
    std::string stringToProcess;
    
    // pop 1 comand, and split into words
    while (m_queue.pop(stringToProcess))
    {   
        boost::split(m_words, stringToProcess, [](char c){return c == ' ';});
        processINSERT();
    }
}

void JoinServer::pushBack(std::string& buf)
{
    // push one command contain more than 1 word
    m_queue.push(buf);
}