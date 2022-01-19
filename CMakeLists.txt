cmake_minimum_required(VERSION 3.21)
project(LuaCppDemo)

set(CMAKE_CXX_STANDARD 14)

add_executable(LuaCppDemo
        Demos/main.cpp
        Demos/cpp/get_then_push.h
        Demos/cpp/get_increment.h
        Demos/cpp/null_terminator.h
        LuaCppAPI/LuaCppAPI.cpp LuaCppAPI/LuaCppAPI.h Demos/cpp/hello_world.h)
target_link_libraries(${PROJECT_NAME} lua5.3)
