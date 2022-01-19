//
// Created by cyber on 1/16/22.
//

#ifndef LUACPPDEMO_GET_THEN_PUSH_H
#define LUACPPDEMO_GET_THEN_PUSH_H

#include <iostream>
#include "../../LuaCppAPI/LuaCppAPI.h"

/**
 * A small demo of how to get a 'data string' from a lua script, and push it to another script
 * @param path_lua_get - Path to a lua script that implements a 'GetDataStr()' function
 * @param path_lua_push - Path to a lua script that implements a 'PushDataStr(datastr)' function
 * @return 0 on success, 1 on failure
 */
int demo_get_then_push(const LuaCppAPI::LuaScriptPath &path_lua_get,
                       const LuaCppAPI::LuaScriptPath &path_lua_push) {
    std::cout << "[C++] [demo_get_then_push] Running demo_get_then_push('"
              << path_lua_get << "', '"
              << path_lua_push << "')... " << std::endl;
    LuaCppAPI::DataStr datastr;
    LuaCppAPI lua_get(path_lua_get);
    LuaCppAPI lua_push(path_lua_push);

    std::cout << "[C++] [demo_get_then_push] Calling GetDataStr('" << path_lua_get << "')..." << std::endl;
    if (!lua_get.GetDataStr(&datastr)) {
        std::cout << "[C++] [demo_get_then_push] Error: Failed to execute GetDataStr('" << path_lua_get << "')" << std::endl;
        return -1;
    }
    std::cout << "[C++] [demo_get_then_push] DataStr = '" << datastr << "'" << std::endl;

    std::cout << "[C++] [demo_get_then_push] Calling PushDataStr('" << path_lua_push << "', '" << datastr << "')..."
              << std::endl;
    if (!lua_push.PushDataStr(datastr)) {
        std::cout << "[C++] [demo_get_then_push] Error: Failed to execute PushDataStr('" << path_lua_push << "')" << std::endl;
        return -1;
    }
    std::cout << "[C++] [demo_get_then_push] Done!\r\n" << std::endl;
    return 0;
}

#endif // LUACPPDEMO_GET_THEN_PUSH_H
