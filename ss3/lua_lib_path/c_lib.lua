package.cpath = "./mylib/?.so;" -- set path to C library
my_lib = require("libmy_lib") -- load C (shared) library (./mylib/libmy_lib.so) 

res_ls = my_lib.dir("./") 
for _,v in pairs(res_ls) do
    print(v)
end

res_add = my_lib.c_add(1,2);
print("res_add = "..res_add);

my_lib.greet("aki")
