cmake_minimum_required(VERSION 3.21)
project(LuaCppDemo)

set(CMAKE_CXX_STANDARD 14)

add_executable(LuaCppDemo main.cpp LuaCppAPI/LuaCppAPI.cpp LuaCppAPI/LuaCppAPI.h)
target_link_libraries(${PROJECT_NAME} lua5.3)
