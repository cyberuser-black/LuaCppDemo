-- Serialize a Lua table into a string ('DataStr')
local lunajson = require ('lunajson') -- from /usr/local/share/lua/5.3/lunajson.lua

Serializer = {}

-- Serialize a Lua table to a string
function Serializer.TableToDataStr(table)
    return lunajson.encode(table)
end

-- Deserialize a string into a Lua table
function Serializer.DataStrToTable(datastr)
    return lunajson.decode(datastr)
end

return Serializer