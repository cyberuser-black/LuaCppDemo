//
// Created by cyber on 1/16/22.
//

#ifndef LUACPPDEMO_GET_NULL_TERMINATOR_H
#define LUACPPDEMO_GET_NULL_TERMINATOR_H

#include <iostream>
#include "../../LuaCppAPI/LuaCppAPI.h"

int demo_null_terminator(const LuaCppAPI::LuaScriptPath &path_lua_get,
                         const LuaCppAPI::LuaScriptPath &path_lua_push) {
    std::cout << "[C++] [demo_null_terminator] Running demo_null_terminator('"
              << path_lua_get << "', '"
              << path_lua_push << "')... " << std::endl;
    LuaCppAPI::DataStr datastr;
    LuaCppAPI lua_get(path_lua_get);
    LuaCppAPI lua_push(path_lua_push);


    std::cout << "[C++] [demo_null_terminator] Calling GetDataStr('" << path_lua_get << "')..." << std::endl;
    if (!lua_get.GetDataStr(&datastr)) {
        std::cout << "[C++] [demo_null_terminator] Error: Failed to execute GetDataStr('" << path_lua_get << "')" << std::endl;
        return -1;
    }
    std::cout << "[C++] [demo_null_terminator] DataStr from lua = '" << datastr << "'" << std::endl;

    std::cout << "[C++] [demo_null_terminator] Calling PushDataStr('" << path_lua_push << "', '" << datastr << "')..."
              << std::endl;
    if (!lua_push.PushDataStr(datastr)) {
        std::cout << "[C++] [demo_null_terminator] Error: Failed to execute PushDataStr('" << path_lua_push << "')" << std::endl;
        return -1;
    }

    const char string_with_embedded_null[] = "{\"message\":\"cyber --> \0 <-- victory!\", \"author\":\"main\"}";
    LuaCppAPI::DataStr cpp_null_terminated_str(string_with_embedded_null, string_with_embedded_null + sizeof(string_with_embedded_null)-1);
    std::cout << "[C++] [demo_null_terminator] DataStr by C++ = '" << cpp_null_terminated_str << "'" << std::endl;
    std::cout << "[C++] [demo_null_terminator] Calling PushDataStr('" << path_lua_push << "', '" << cpp_null_terminated_str << "')..."
              << std::endl;
    if (!lua_push.PushDataStr(cpp_null_terminated_str)) {
        std::cout << "[C++] [demo_null_terminator] Error: Failed to execute PushDataStr('" << path_lua_push << "')" << std::endl;
        return -1;
    }

    std::cout << "[C++] [demo_null_terminator] Done!\r\n" << std::endl;
    return 0;
}

#endif // LUACPPDEMO_GET_NULL_TERMINATOR_H