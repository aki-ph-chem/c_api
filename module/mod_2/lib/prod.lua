function prod(array)
    local prod = 1
    for _, v in pairs(array) do
        prod = v * prod
    end
    return prod
end

return prod
