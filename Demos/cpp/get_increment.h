//
// Created by cyber on 1/16/22.
//

#ifndef LUACPPDEMO_GET_INCREMENT_H
#define LUACPPDEMO_GET_INCREMENT_H

#include <iostream>
#include "../../LuaCppAPI/LuaCppAPI.h"

int demo_get_increment(const LuaCppAPI::LuaScriptPath &path_lua_get, int n) {
    std::cout << "[C++] [demo_get_increment] Running demo_get_increment('" << path_lua_get << "')"
              << std::endl;
    LuaCppAPI::DataStr datastr;
    LuaCppAPI lua_get(path_lua_get);

    for (int i = 0; i < n; i++) {
        std::cout << "[C++] [demo_get_increment] Calling GetDataStr('" << path_lua_get << "')..." << std::endl;
        if (!lua_get.GetDataStr(&datastr)) {
            std::cout << "[C++] [demo_get_increment] Error: Failed to execute GetDataStr('" << path_lua_get << "')" << std::endl;
            return -1;
        }
        std::cout << "[C++] [demo_get_increment] DataStr = '" << datastr << "'" << std::endl;
    }
    std::cout << "[C++] [demo_get_increment] Done!\r\n" << std::endl;
    return 0;
}

#endif // LUACPPDEMO_GET_INCREMENT_H