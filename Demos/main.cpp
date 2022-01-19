#include <iostream>
#include "../LuaCppAPI/LuaCppAPI.h"
#include "cpp/get_then_push.h"
#include "cpp/get_increment.h"
#include "cpp/null_terminator.h"

int main() {
    LuaCppAPI::LuaScriptPath lua_path_get = "../Demos/lua/get.lua";
    LuaCppAPI::LuaScriptPath lua_path_push = "../Demos/lua/push.lua";
    LuaCppAPI::LuaScriptPath lua_path_get_increment = "../Demos/lua/get_increment.lua";
    LuaCppAPI::LuaScriptPath lua_path_null_terminator = "../Demos/lua/null_terminator.lua";
    demo_get_then_push(lua_path_get, lua_path_push);
    demo_get_increment(lua_path_get_increment, 5);
    demo_null_terminator(lua_path_null_terminator, lua_path_push);
    return 1;
}
