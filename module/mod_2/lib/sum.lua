function sum(array)
    local sum = 0
    for _, v in pairs(array) do
        sum = sum + v
    end
    return sum
end

return sum
