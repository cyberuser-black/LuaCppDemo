---------------------------
-- ExampleSerializer.lua --
---------------------------

-- Serialize a lua table into a string ('DataStr')
local lunajson = require ('lunajson') -- from /usr/local/share/lua/5.3/lunajson.lua

Serializer = {}

-- Serialize a lua table to a string
function Serializer.TableToDataStr(table)
    return table["message"] --lunajson.encode(table)
end

-- Deserialize a string into a lua table
function Serializer.DataStrToTable(datastr)
    return datastr --lunajson.decode(datastr)
end

return Serializer