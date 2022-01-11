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


class LuaCppAPI {
public:
    typedef std::string LuaScriptPath;
    typedef std::string DataStr;
    static bool GetDataStr(const LuaScriptPath &script_path, DataStr* out_datastr);
    static bool PushDataStr(const LuaScriptPath &script_path, const DataStr &datastr);

private:
    static bool CheckLua(lua_State *L, int r);
};


#endif //LUACPPDEMO_LUACPPAPI_H
