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

LuaCppAPI::LuaCppAPI(const LuaCppAPI::LuaScriptPath &script_path) : _script_path(script_path),
                                                                    _script_path_cstr(script_path.c_str()),
                                                                    _is_ready(false) {
    // Create Lua State
    _L = luaL_newstate();
    // Add standard libraries to Lua Virtual Machine
    luaL_openlibs(_L);

    // Run Lua script and load all of its methods
    if (!CheckLua(_L, luaL_dofile(_L, _script_path_cstr))) {
        std::cerr << "Error: Failed to run '" << _script_path_cstr << "'" << std::endl;
    } else {
        _is_ready = true;
    }
}

bool LuaCppAPI::GetDataStr(DataStr *out_datastr) {
    // Validate script is ready
    if (!_is_ready) {
        std::cerr << "Error: Lua script is not ready!";
        return false;
    }

    // Push functions and arguments
    lua_getglobal(_L, "GetDataStr");

    // Do the call (0 arguments, 1 result - datastr)
    if (CheckLua(_L, lua_pcall(_L, 0, 1, 0))) {
        // retrieve result
        if (lua_isstring(_L, STACK_TOP)) {
            *out_datastr = lua_tostring(_L, STACK_TOP);
            return true;
        } else {
            std::cerr << "Error: Lua's stack top is not a string" << std::endl;
            return false;
        }
    } else {
        std::cerr << "Error: Failed to call '" << _script_path_cstr << ".GetDataStr()'" << std::endl;
        return false;
    }

}

bool LuaCppAPI::PushDataStr(const LuaCppAPI::DataStr &datastr) {
    // Validate script is ready
    if (!_is_ready) {
        std::cerr << "Error: Lua script is not ready!";
        return false;
    }

    // Push functions and arguments
    lua_getglobal(_L, "PushDataStr");
    lua_pushstring(_L, datastr.c_str());

    // Do the call (1 argument - datastr, 1 result - boolean)
    if (CheckLua(_L, lua_pcall(_L, 1, 1, 0))) {
        // retrieve result
        if (lua_isinteger(_L, STACK_TOP)) {
            return lua_tointeger(_L, STACK_TOP);
        } else {
            std::cerr << "Error: Lua returned a non-integer value" << std::endl;
            return false;
        }
    } else {
        std::cerr << "Error: Failed to call '" << _script_path_cstr << ".PushDataStr(datastr)'" << std::endl;
        return false;
    }

}
