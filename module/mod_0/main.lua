mymod = require("my_mod/mod")

function main()
    mymod.greet("Aki")
    local res_add = mymod.my_add(11,100)
    print("res_add = "..res_add)
end

main()
