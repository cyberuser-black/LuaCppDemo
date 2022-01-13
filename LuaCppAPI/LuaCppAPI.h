//
// Created by cyber on 1/10/22.
//

#ifndef LUACPPDEMO_LUACPPAPI_H
#define LUACPPDEMO_LUACPPAPI_H


#include <string>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace std::literals::string_literals;

class LuaCppAPI {
public:
    typedef std::string LuaScriptPath;
    typedef std::string DataStr;

    // Generate an API for the given Lua script path.
    LuaCppAPI(const LuaScriptPath &script_path);

    ~LuaCppAPI() = default;

public:
    // Call Lua's GetDataStr function, set out_datastr to the returned value.
    bool GetDataStr(DataStr *out_datastr);

    // Push the given datastr to Lua's PushDataStr function.
    bool PushDataStr(const DataStr &datastr);

public:
    const LuaScriptPath &_script_path;
    const char *_script_path_data;

private:
    // Check the if Lua returned OK or print the error otherwise.
    static bool CheckLua(lua_State *L, int r);

    bool _is_ready; // Flag if the Lua virtual machine was properly initialized
    lua_State *_L; // The Lua virtual machine to API with
};


#endif //LUACPPDEMO_LUACPPAPI_H
