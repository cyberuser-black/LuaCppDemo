#include <iostream>
#include "LuaCppAPI/LuaCppAPI.h"

/**
 * A small demo of how to get a 'data string' from a lua script, and push it to another script
 * @param lua_get - Path to a Lua script that implements a 'GetDataStr()' function
 * @param lua_push - Path to a lua script that implements a 'PushDataStr(datastr)' function
 * @return 0 on success, 1 on failure
 */
int demo_get_then_push(const LuaCppAPI::LuaScriptPath &lua_get,
                       const LuaCppAPI::LuaScriptPath &lua_push) {
    std::cout << "[main.cpp] Running demo_get_then_push('" << lua_get.c_str() << "', '" << lua_push.c_str() << "')... "
              << std::endl;
    LuaCppAPI::DataStr datastr;

    std::cout << "[main.cpp] Calling LuaCppAPI::GetDataStr('" << lua_get.c_str() << "')..." << std::endl;
    if (!LuaCppAPI::GetDataStr(lua_get, &datastr)) {
        std::cerr << "Error: Failed to execute LuaCppAPI::GetDataStr('" << lua_get << "')" << std::endl;
        return -1;
    }
    std::cout << "[main.cpp] DataStr = '" << datastr.c_str() << "'" << std::endl;

    std::cout << "[main.cpp] Calling LuaCppAPI::PushDataStr('" << lua_push.c_str() << "', " << datastr.c_str() << ")..."
              << std::endl;
    if (!LuaCppAPI::PushDataStr(lua_push, datastr)) {
        std::cerr << "Error: Failed to execute LuaCppAPI::PushDataStr('" << lua_push << "')" << std::endl;
        return -1;
    }
    std::cout << "[main.cpp] Done!" << std::endl;
    return 0;
}

int main() {
    LuaCppAPI::LuaScriptPath lua_a = "../lua/a.lua";
    LuaCppAPI::LuaScriptPath lua_b = "../lua/b.lua";
    demo_get_then_push(lua_a, lua_b);
    demo_get_then_push(lua_b, lua_a);
    return 1;
}
