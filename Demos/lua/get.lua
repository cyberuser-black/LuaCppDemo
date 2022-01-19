-- get.lua - A simple file implementing the lua-Cpp API:
-- GetDataStr() --> datastr
-- PushDataStr(datastr)  // NOT IMPLEMENTED HERE (see push.lua)

-- Add the serializer to lua path
package.path = package.path .. ";../Serialization/?.lua"
serializer = require("ExampleSerializer")

-- Add Utils to lua path
package.path = package.path .. ";../Demos/lua/?.lua"
utils = require("utils")


-------------------------------------------------------------------------------
--                             lua Cpp API                                   --
-------------------------------------------------------------------------------

-- API: GetDataStr
function GetDataStr()
    data = { author = "a", message = "how you doin'?" }
    datastr = serializer.TableToDataStr(data);
    print("[lua] [get.lua] GetDataStr() --> '" .. datastr .. "'")
    return datastr
end