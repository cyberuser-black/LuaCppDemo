-- a.lua - A simple file implementing the Lua-Cpp API:
-- GetDataStr() --> datastr
-- PushDataStr(datastr)

-- Add LuaCppAPI to Lua path
package.path = package.path .. ";../LuaCppAPI/?.lua"
serializer = require("Serializer")

-- Add Utils to Lua path
package.path = package.path .. ";../lua/?.lua"
utils = require("utils")


-------------------------------------------------------------------------------
--                             Lua Cpp API                                   --
-------------------------------------------------------------------------------

-- API: GetDataStr
function GetDataStr()
    data = { author = "a", message = "how you doin'?" }
    datastr = serializer.TableToDataStr(data);
    print("[a.lua] GetDataStr() --> " .. datastr)
    return datastr
end

-- API: PushDataStr
function PushDataStr(datastr)
    data = serializer.DataStrToTable(datastr)
    print("[a.lua]: PushDataStr(" .. utils.dump(data) .. ")");
    return 1;
end

-------------------------------------------------------------------------------