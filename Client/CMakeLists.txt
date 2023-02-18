cmake_minimum_required(VERSION 3.0.0)
project(myclientproject VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(myclientproject client.c)
target_link_libraries(myclientproject m)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
