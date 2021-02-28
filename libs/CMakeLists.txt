cmake_minimum_required(VERSION 3.2)

add_library(joinServer STATIC joinServer.h joinServer.cpp)
set_target_properties(joinServer  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(joinServer PRIVATE ${CMAKE_BINARY_DIR})

add_library(assync STATIC asyncLib.cpp asyncLib.h )
set_target_properties(assync  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(assync PRIVATE ${CMAKE_BINARY_DIR})

add_library(clientServer STATIC Client.cpp Client.h Server.cpp Server.h)
set_target_properties(clientServer  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(clientServer PRIVATE ${CMAKE_BINARY_DIR})

if(MSVC)
	target_compile_options(clientServer PRIVATE /W4)
else()
	target_compile_options(clientServer PRIVATE -Wall -Wextra -Werror)
endif()
