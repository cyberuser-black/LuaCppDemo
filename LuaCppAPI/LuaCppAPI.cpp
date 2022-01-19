//
// Created by cyber on 1/10/22.
//

#include <iostream>
#include "LuaCppAPI.h"

const int STACK_TOP = -1; // Index of highest lua stack cell

bool LuaCppAPI::CheckLua(lua_State *L, int r) {
    if (r != LUA_OK) {
        std::string errormsg = lua_tostring(L, STACK_TOP);
        std::cout << "[C++] [LuaCppAPI::CheckLua] " << errormsg << std::endl;
        return false;
    }
    return true;
}

LuaCppAPI::LuaCppAPI(const LuaCppAPI::LuaScriptPath &script_path) : _script_path(script_path),
                                                                    _script_path_data(script_path.data()),
                                                                    _is_ready(false) {
    // Create lua State
    _L = luaL_newstate();
    // Add standard libraries to lua Virtual Machine
    luaL_openlibs(_L);

    // Run lua script and load all of its methods
    if (!CheckLua(_L, luaL_dofile(_L, _script_path_data))) {
        std::cout << "[C++] [LuaCppAPI::LuaCppAPI] Error: Failed to run '" << _script_path_data << "'" << std::endl;
    } else {
        _is_ready = true;
    }
}

bool LuaCppAPI::GetDataStr(DataStr *out_datastr) {
    // Validate the lua script is ready
    if (!_is_ready) {
        std::cout << "[C++] [LuaCppAPI::GetDataStr] Error: lua script is not ready!" << std::endl;
        return false;
    }

    // Push functions and arguments
    lua_getglobal(_L, "GetDataStr");

    // Do the call (0 arguments, 1 result - datastr)
    if (CheckLua(_L, lua_pcall(_L, 0, 1, 0))) {
        // retrieve result
        if (lua_isstring(_L, STACK_TOP)) {
            size_t len = 0;
            const char* datastr = lua_tolstring(_L, STACK_TOP, &len);
            out_datastr->assign(datastr, len);
            if (len ==0){
                out_datastr = nullptr;
                std::cout << "[C++] [LuaCppAPI::GetDataStr] Error: lua returned an lstring with len = 0" << std::endl;
                return false;
            }
            return true;
        } else {
            std::cout << "[C++] [LuaCppAPI::GetDataStr] Error: lua's stack top is not a string" << std::endl;
            return false;
        }
    } else {
        std::cout << "[C++] [LuaCppAPI::GetDataStr] Error: Failed to call '" << _script_path_data << ".GetDataStr()'" << std::endl;
        return false;
    }

}

bool LuaCppAPI::PushDataStr(const LuaCppAPI::DataStr &datastr) {
    // Validate script is ready
    if (!_is_ready) {
        std::cout << "[C++] [LuaCppAPI::PushDataStr] Error: lua script is not ready!" << std::endl;
        return false;
    }

    // Push functions and arguments
    lua_getglobal(_L, "PushDataStr");
    lua_pushlstring(_L, datastr.data(), datastr.length());

    // Do the call (1 argument - datastr, 1 result - boolean)
    if (CheckLua(_L, lua_pcall(_L, 1, 1, 0))) {
        // retrieve result
        if (lua_isinteger(_L, STACK_TOP)) {
            return lua_tointeger(_L, STACK_TOP);
        } else {
            std::cout << "[C++] [LuaCppAPI::PushDataStr] Error: lua returned a non-integer value" << std::endl;
            return false;
        }
    } else {
        std::cout << "[C++] [LuaCppAPI::PushDataStr] Error: Failed to call '" << _script_path_data << ".PushDataStr(datastr)'" << std::endl;
        return false;
    }

}
