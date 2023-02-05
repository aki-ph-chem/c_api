## 24

- Luaの値
    - lua_valueという型(union)の値で表す

## stack周りのAPI

- void lua_pushnil(lua_State \*L) 
    - nilの値をstackにpushする
- void lua_pushboolean(lua_State \*L, int bool)
    - bool(int で0かそれ以外か)をstackにpush 
- void lua_pushlstring(lua_State \*L, const char \*s, size_t longth)
    - ヌル終端されていない長さlengthのchar\*型の値をstackにpushする
- void lua_pushstring(lua_State \*L, const char \*s)
    - ヌル終端されている長さlengthのchar\*型の値をstackにpushする

stackのサイズはlua.hにて

```C
#define LUA_MINSTACK	20
```

と定義されている。これは普通に使うにあは十分な大きさであるがもしより多くの容量が必要ならば以下の関数を用いる。

- int lua_checkstack(lua_Stack \*L, int sz)

stackから値を取り出す関数はlua_to\<type\>(lua_State \*L, int index)であるが、
型のチェックを挟みたい場合はlua_is\<type\>(lua_State \*L, int index)を用いる(lua_is\<type\>はマクロ)。

例としては以下がある

- int lua_toboolean(lua_State \*L, int index) 
   - bool値をintして得る 
- double lua_tonumber(lua_State \*L, int index)
   - double値を得る 
- const char\* lua_tostring(lus_State \*L, int index)
   - const char\*を得る 
- size_t lua_strlen(lus_State \*L, int index) 
   - 文字列のサイズを得る 

呼び出す型とstackにある型が一致しなくてもlua_to\<type\>を呼び出すことが可能である。
しかし、lua_toboolean,lua_tonumber, lua_strlenは0を返し、他の関数はNULLを返す。

Lua_is\<type\>を呼ばなくてもLua_to\<type\>を呼び出して、返り値のNULLチェックをすればok

Cの関数の呼び出しが終わるとLuaはstackの中身をクリアするのでLuaのstringへのポインタを関数の外部に保存してはならない。

lua_tostringが返す文字列はヌル終端されている。

## 他のstackの操作

- int lua_gettop(lua_State \*L)
    - topの値のindexを得る

- void lua_settop(lua_State \*L, int index)
    - topの値のindexを特定の値に変更する。新しい値が古い値よりも大きければtopの値は破棄される

- void lua_pushvalue(lua_State \*L, int index)
- void lua_remove(lua_State \*L, int index)
- void lua_insert(lua_State \*L, int index)
- void lua_replace(lua_State \*L, int index)



