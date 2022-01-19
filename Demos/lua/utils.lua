local utils = {}

-- Convert lua objects to printable strings
-- Based on https://stackoverflow.com/questions/9168058/how-to-dump-a-table-to-console
function utils.dump(o)
    if type(o) == 'table' then
        local s = '{ '
        for k,v in pairs(o) do
            if type(k) ~= 'number' then k = '"'..k..'"' end
            if (type(v) ~= 'number') and (type(v) ~= 'table') then v = "'"..v.."'" end
            s = s .. '['..k..'] = ' .. utils.dump(v) .. ','
        end
        return s .. '} '
    else
        return tostring(o)
    end
end

return utils