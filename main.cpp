#include <iostream>
#include "LuaCppAPI/LuaCppAPI.h"

/**
 * A small demo of how to get a 'data string' from a lua script, and push it to another script
 * @param path_lua_get - Path to a Lua script that implements a 'GetDataStr()' function
 * @param path_lua_push - Path to a lua script that implements a 'PushDataStr(datastr)' function
 * @return 0 on success, 1 on failure
 */
int demo_get_then_push(const LuaCppAPI::LuaScriptPath &path_lua_get,
                       const LuaCppAPI::LuaScriptPath &path_lua_push) {
    std::cout << "[main.cpp] Running demo_get_then_push('"
              << path_lua_get << "', '"
              << path_lua_push << "')... " << std::endl;
    LuaCppAPI::DataStr datastr;
    LuaCppAPI lua_get(path_lua_get);
    LuaCppAPI lua_push(path_lua_push);

    std::cout << "[main.cpp] Calling GetDataStr('" << path_lua_get << "')..." << std::endl;
    if (!lua_get.GetDataStr(&datastr)) {
        std::cerr << "Error: Failed to execute GetDataStr('" << path_lua_get << "')" << std::endl;
        return -1;
    }
    std::cout << "[main.cpp] DataStr = '" << datastr << "'" << std::endl;

    std::cout << "[main.cpp] Calling PushDataStr('" << path_lua_push << "', " << datastr << ")..."
              << std::endl;
    if (!lua_push.PushDataStr(datastr)) {
        std::cerr << "Error: Failed to execute PushDataStr('" << path_lua_push << "')" << std::endl;
        return -1;
    }
    std::cout << "[main.cpp] Done!\r\n" << std::endl;
    return 0;
}

int demo_get_multiple(const LuaCppAPI::LuaScriptPath &path_lua_get, int n) {
    std::cout << "[main.cpp] Running demo_get_multiple('" << path_lua_get << "')"
              << std::endl;
    LuaCppAPI::DataStr datastr;
    LuaCppAPI lua_get(path_lua_get);

    for (int i = 0; i < n; i++) {
        std::cout << "[main.cpp] Calling GetDataStr('" << path_lua_get << "')..." << std::endl;
        if (!lua_get.GetDataStr(&datastr)) {
            std::cerr << "Error: Failed to execute GetDataStr('" << path_lua_get << "')" << std::endl;
            return -1;
        }
        std::cout << "[main.cpp] DataStr = '" << datastr << "'" << std::endl;
    }
    std::cout << "[main.cpp] Done!\r\n" << std::endl;
    return 0;
}

int demo_null_terminator_handling(const LuaCppAPI::LuaScriptPath &path_lua_get,
                                  const LuaCppAPI::LuaScriptPath &path_lua_push) {
    std::cout << "[main.cpp] Running demo_null_terminator_handling('"
            << path_lua_get << "', '"
            << path_lua_push << "')... " << std::endl;
    LuaCppAPI::DataStr datastr;
    LuaCppAPI lua_get(path_lua_get);
    LuaCppAPI lua_push(path_lua_push);


    std::cout << "[main.cpp] Calling GetDataStr('" << path_lua_get << "')..." << std::endl;
    if (!lua_get.GetDataStr(&datastr)) {
        std::cerr << "Error: Failed to execute GetDataStr('" << path_lua_get << "')" << std::endl;
        return -1;
    }
    std::cout << "[main.cpp] DataStr from Lua = '" << datastr << "'" << std::endl;

    std::cout << "[main.cpp] Calling PushDataStr('" << path_lua_push << "', '" << datastr << "')..."
              << std::endl;
    if (!lua_push.PushDataStr(datastr)) {
        std::cerr << "Error: Failed to execute PushDataStr('" << path_lua_push << "')" << std::endl;
        return -1;
    }

    const char string_with_embedded_null[] = "{\"message\":\"cyber --> \0 <-- victory!\", \"author\":\"main\"}";
    LuaCppAPI::DataStr cpp_null_terminated_str(string_with_embedded_null, string_with_embedded_null + sizeof(string_with_embedded_null)-1);
    std::cout << "[main.cpp] DataStr by C++ = '" << cpp_null_terminated_str << "'" << std::endl;
    std::cout << "[main.cpp] Calling PushDataStr('" << path_lua_push << "', '" << cpp_null_terminated_str << "')..."
              << std::endl;
    if (!lua_push.PushDataStr(cpp_null_terminated_str)) {
        std::cerr << "Error: Failed to execute PushDataStr('" << path_lua_push << "')" << std::endl;
        return -1;
    }

    std::cout << "[main.cpp] Done!\r\n" << std::endl;
    return 0;
}

int main() {
    LuaCppAPI::LuaScriptPath a_path = "../lua/a.lua";
    LuaCppAPI::LuaScriptPath b_path = "../lua/b.lua";
    LuaCppAPI::LuaScriptPath increment_path = "../lua/increment.lua";
    LuaCppAPI::LuaScriptPath null_terminator_path = "../lua/null_terminator.lua";
    demo_get_then_push(a_path, b_path);
    demo_get_multiple(increment_path, 5);
    demo_null_terminator_handling(null_terminator_path, a_path);
    return 1;
}
