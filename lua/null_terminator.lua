-- increment.lua - A simple file implementing the Lua-Cpp API:
-- GetDataStr() --> datastr (includes a global counter)
-- PushDataStr(datastr)
-- Has a global counter that increments on each call

-- Add LuaCppAPI to Lua path
package.path = package.path .. ";../LuaCppAPI/?.lua"
serializer = require("Serializer")

-- Add Utils to Lua path
package.path = package.path .. ";../lua/?.lua"
utils = require("utils")

-------------------------------------------------------------------------------
--                               Globals                                     --
-------------------------------------------------------------------------------

-- Global variable that will be incremented on each call
counter = 0


-------------------------------------------------------------------------------
--                             Lua Cpp API                                   --
-------------------------------------------------------------------------------

-- API: GetDataStr
function GetDataStr()
    counter = counter +1 -- Increment on each call to GetDataStr()
    data = {author="null_terminator", message="null terminator --> \0 <-- great success!" }
    datastr = serializer.TableToDataStr(data);
    print("[null_terminator.lua] GetDataStr() --> '" .. datastr .. "'")
    return datastr
end

-- API: PushDataStr
function PushDataStr(datastr)
    data = serializer.DataStrToTable(datastr)
    print("[null_terminator.lua]: PushDataStr('" .. utils.dump(data) .."')");
    return 1;
end
