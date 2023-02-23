package.cpath = "./mylib/?.so;" -- set path to C library
my_lib = require("libmy_lib") -- load C (shared) library (./mylib/libmy_lib.so) 

res_ls = my_lib.dir("/") 
for _,v in pairs(res_ls) do
    print(v)
end

for i,v in pairs(res_ls) do
    print(string.format("res_ls[%d] = %s", i, v))
end
