cmake_minimum_required(VERSION 3.2) 

add_executable(jServer main.cpp)
set_target_properties(jServer PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQIRED ON)
target_link_libraries(jServer PRIVATE pthread boost_system clientServer joinServerLib)

if(MSVC)
	target_compile_options(jServer PRIVATE /W4)
else()
	target_compile_options(jServer PRIVATE -Wall -Wextra -Werror)
endif()

install(TARGETS jServer RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_CONTACT gavl.andr96@gmail.com)

include(CPack)