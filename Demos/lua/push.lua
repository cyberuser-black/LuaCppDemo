-- push.lua - A simple file implementing the lua-Cpp API:
-- GetDataStr() --> datastr
-- PushDataStr(datastr)

-- Add LuaCppAPI to lua path
package.path = package.path .. ";../Serialization/?.lua"
serializer = require("ExampleSerializer")

-- Add Utils to lua path
package.path = package.path .. ";../Demos/lua/?.lua"
utils = require("utils")


-------------------------------------------------------------------------------
--                             lua Cpp API                                   --
-------------------------------------------------------------------------------

-- API: PushDataStr
function PushDataStr(datastr)
    data = serializer.DataStrToTable(datastr)
    print("[lua] [push.lua] PushDataStr('" .. utils.dump(data) .."')");
    return 1;
end
