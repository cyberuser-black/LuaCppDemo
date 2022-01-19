-- null_terminator.lua - A simple file implementing the lua-Cpp API:
-- GetDataStr() --> datastr (includes an embedded null terminator)
-- PushDataStr(datastr)

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
    data = {author="null_terminator", message="null terminator --> \0 <-- great success!" }
    datastr = serializer.TableToDataStr(data);
    print("[lua] [null_terminator.lua] GetDataStr() --> '" .. datastr .. "'")
    return datastr
end

-- API: PushDataStr
function PushDataStr(datastr)
    data = serializer.DataStrToTable(datastr)
    print("[lua] [null_terminator.lua]: PushDataStr('" .. utils.dump(data) .."')");
    return 1;
end
