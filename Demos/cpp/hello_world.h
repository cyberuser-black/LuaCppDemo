//
// Created by cyber on 1/16/22.
//

#ifndef LUACPPDEMO_HELLO_WORLD_H
#define LUACPPDEMO_HELLO_WORLD_H

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
    LuaCppAPI lua_get(path_lua_get);
    LuaCppAPI lua_push(path_lua_push);

    LuaCppAPI::DataStr datastr;
    lua_get.GetDataStr(&datastr);
    lua_push.PushDataStr(datastr);

    return 0;
}

#endif //LUACPPDEMO_HELLO_WORLD_H
