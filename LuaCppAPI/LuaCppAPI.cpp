//
// Created by cyber on 1/10/22.
//

#include <iostream>
#include "LuaCppAPI.h"

const int STACK_TOP = -1; // Index of highest lua stack cell

bool LuaCppAPI::CheckLua(lua_State *L, int r) {
    if (r != LUA_OK) {
        std::string errormsg = lua_tostring(L, STACK_TOP);
        std::cerr << errormsg << std::endl;
        return false;
    }
    return true;
}

bool LuaCppAPI::GetDataStr(const LuaCppAPI::LuaScriptPath &script_path,
                           DataStr *out_datastr) {
    // Create Lua State
    lua_State *L = luaL_newstate();
    // Add standard libraries to Lua Virtual Machine
    luaL_openlibs(L);

    // Run Lua script and call its 'GetDataStr()' function
    if (CheckLua(L, luaL_dofile(L, script_path.c_str()))) {
        // Push functions and arguments
        lua_getglobal(L, "GetDataStr");

        // Do the call (0 arguments, 1 result - datastr)
        if (CheckLua(L, lua_pcall(L, 0, 1, 0))) {
            // retrieve result
            if (lua_isstring(L, STACK_TOP)) {
                *out_datastr = lua_tostring(L, STACK_TOP);
                return true;
            } else {
                std::cerr << "Error: Lua's stack top is not a string" << std::endl;
                return false;
            }
        } else {
        std::cerr << "Error: Failed to call '" << script_path.c_str() << ".GetDataStr()'" << std::endl;
        return false;
    }
    } else {
        std::cerr << "Error: Failed to run '" << script_path.c_str() << "'" << std::endl;
        return false;
    }
}

bool LuaCppAPI::PushDataStr(const LuaCppAPI::LuaScriptPath &script_path,
                            const LuaCppAPI::DataStr &datastr) {
    // Create Lua State
    lua_State *L = luaL_newstate();
    // Add standard libraries to Lua Virtual Machine
    luaL_openlibs(L);

    // Run Lua script and call its 'PushDataStr(datastr)' function
    if (CheckLua(L, luaL_dofile(L, script_path.c_str()))) {
        // Push functions and arguments
        lua_getglobal(L, "PushDataStr");
        lua_pushstring(L, datastr.c_str());

        // Do the call (1 argument - datastr, 1 result - boolean)
        if (CheckLua(L, lua_pcall(L, 1, 1, 0))) {
            // retrieve result
            if (lua_isinteger(L, STACK_TOP)) {
                return lua_tointeger(L, STACK_TOP);
            } else {
                std::cerr << "Error: Lua returned a non-integer value" << std::endl;
                return false;
            }
        } else {
            std::cerr << "Error: Failed to call '" << script_path.c_str() << ".PushDataStr(datastr)'" << std::endl;
            return false;
        }
    } else {
        std::cerr << "Error: Failed to execute '" << script_path.c_str() << "'" << std::endl;
        return false;
    }
}
