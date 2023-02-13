# 26 

## ハマったポイント

### FFI

- 課題

簡易的なls関数をCで実装して、Luaから呼び出す。

ディレクトリ構造


```
.
├── c_lib.c
├── c_lib.lua
└── Makefile
```

ls関数
```C

/* function for C library of Lua */
static int lua_dir(lua_State *L){
    DIR* dir;
    struct dirent *entry;
    const char* path = luaL_checkstring(L, 1);

    /* opent directory */
    dir = opendir(path);
    if(dir == NULL) {
        lua_pushnil(L); /* error openign the directory? */
        lua_pushstring(L, strerror(errno)); /* error message */
        return 2;
    }

    /* careate result table */
    lua_newtable(L);
    int i = 1;
    while((entry = readdir(dir))) {
        lua_pushnumber(L, i++); /* push key */
        lua_pushstring(L, entry->d_name);
        lua_settable(L, -3);
    }

    closedir(dir);
    return 1;
}

```

これをLuaにおける関数名,呼び出したい関数のポインタの順に以下の配列に登録する。
なお、配列の末尾は{NULL,NULL}としておく。

```C

/* this array store list of function */
static const struct luaL_Reg my_lib[] = {
    {"dir", lua_dir},
    {NULL, NULL} /* setntinel */
};

```

main関数としてlua_open_\<lib name\>(lua_State\* L)を以下のように実装する。

```C
/* main function */
int luaopen_libmylib(lua_State* L) {
    luaL_newlib(L, my_lib);
    return 1;
}
```

ソースコードは共有ライブラリ(\*.so)としてビルドする。
ここでは以下のMakefileを使った。
ここで生成する共有ライブラリの名前とmain関数の\<lib name\>は揃えなければならない。


```Makefile

CC = gcc
OBJ = c_lib.o
LIB_NAME = mylib

lib${LIB_NAME}.so : ${OBJ}
	${CC} -shared -o $@ $^

%.o : %.c
	${CC} -fpic -Wall -c $<

run: lib${LIB_NAME}.so
	lua c_lib.lua

clean:
	rm *.o *.so

.PHONY: clean run
```

生成した共有ライブラリを以下のLuaのコードから呼び出す

```Lua

my_lib = require("libmylib") 
res = my_lib.dir("./") 

for _,v in pairs(res) do
    print(v)
end
```

ここで、共有ライブラリが以下のように呼び出し元のLuaのソースコードとは別のディレクトリにある場合は

```
.
├── c_lib.lua
└── mylib
    ├── c_lib.c
    ├── c_lib.o
    ├── libmy_lib.so
    └── Makefile
```

以下のようにpackage.cpathを設定する必要がある。

```Lua

package.cpath = "./mylib/?.so;" -- set "./path/to/C_library/?.so;"
my_lib = require("libmy_lib") -- load C (shared) library (./mylib/libmy_lib.so) 
```

