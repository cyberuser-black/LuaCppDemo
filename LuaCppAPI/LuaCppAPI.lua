-------------------
-- LuaCppAPI.lua --
-------------------
--
-- This file is a reference for writing lua scripts that adhere to the LuaCppAPI interface.
-- Essentially, the interface requires the script to implement the following functions:
--   *  GetDataStr() --> DataStr
--   *  PushDataStr(datastr) --> Boolean (1=Success, 0=Error)
--
-- These functions exchange data with C++ through the lua stack, which is accessible to C++
-- through the _L struct and other methods defined in "lua.h", like lua_getglobal() for example.
-- The data is serialized and transferred from lua to C++ and vice versa as an std::string.
-- See lua_tolstring() and lua_pushlstring() for details.

package.path = package.path .. ";../Serialization/?.lua"
serializer = require("ExampleSerializer")

-- Returns serialized data from lua
function GetDataStr() --> DataStr
    data = {} -- Get the data somehow
    return serializer.TableToDataStr(data)
end

-- Handles serialized data in lua
function PushDataStr(datastr) --> Boolean (1=Success, 0=Error)
    data = serializer.DataStrToTable(datastr)
    print(data) -- Handle the data somehow
    return 1
end