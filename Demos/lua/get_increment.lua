-- get_increment.lua - A simple file implementing the lua-Cpp API:
-- GetDataStr() --> datastr (includes a global counter)
-- PushDataStr(datastr)
-- Has a global counter that increments on each call

-- Add the serializer to lua path
package.path = package.path .. ";../Serialization/?.lua"
serializer = require("ExampleSerializer")

-- Add Utils to lua path
package.path = package.path .. ";../Demos/lua/?.lua"
utils = require("utils")

-------------------------------------------------------------------------------
--                               Globals                                     --
-------------------------------------------------------------------------------

-- Global variable that will be incremented on each call
counter = 0


-------------------------------------------------------------------------------
--                             lua Cpp API                                   --
-------------------------------------------------------------------------------

-- API: GetDataStr
function GetDataStr()
    counter = counter +1 -- Increment on each call to GetDataStr()
    data = {author="increment", message="counter = " .. counter }
    datastr = serializer.TableToDataStr(data);
    print("[lua] [get_increment.lua] GetDataStr() --> '" .. datastr .. "'")
    return datastr
end

-- API: PushDataStr
function PushDataStr(datastr)
    data = serializer.DataStrToTable(datastr)
    print("[lua] [get_increment.lua]: PushDataStr('" .. utils.dump(data) .."')");
    return 1;
end
