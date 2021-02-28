#include "asyncLib.h"

assyncLib::assyncLib() : m_counter{0} {}

void assyncLib::receive(const char * buff) {
   std::string str {buff};
   m_JoinServer.pushBack(str);
}

