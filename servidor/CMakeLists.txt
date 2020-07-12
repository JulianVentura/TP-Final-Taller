cmake_minimum_required(VERSION 2.8)

project(TP-Final-Taller)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -pedantic -pedantic-errors -O3 -std=c++17")
set (CMAKE_EXE_LINKER_FLAGS  "-pthread")
set (CMAKE_BUILD_TYPE "Debug")

add_executable(server servidor_main.cpp ../common/commonSocket.cpp ../common/commonProtocolo.cpp ../common/FallaConexionException.cpp)

add_subdirectory(Clases)

target_link_libraries(server misClases)
