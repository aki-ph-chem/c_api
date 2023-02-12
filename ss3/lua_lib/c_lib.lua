my_lib = require("libmylib") 
res = my_lib.dir("./") 

for _,v in pairs(res) do
    print(v)
end
