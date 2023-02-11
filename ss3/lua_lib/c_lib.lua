path = "./libc_lib.so"
my_lib = package.loadlib(path,"luaopen_mylib")
--my_lib = package.loadlib(path,"lua_dir")
print(my_lib)
my_lib("./")
