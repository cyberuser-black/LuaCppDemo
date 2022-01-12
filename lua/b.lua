-- b.lua - A simple file implementing the Lua-Cpp API:
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
    data = {author="b", message="hello there!"}
    datastr = serializer.TableToDataStr(data);
    print("[b.lua] GetDataStr() --> " .. datastr)
    return datastr
end

-- API: PushDataStr
function PushDataStr(datastr)
    data = serializer.DataStrToTable(datastr)
    print("[b.lua]: PushDataStr(" .. utils.dump(data) ..")");
    return 1;
end

-------------------------------------------------------------------------------