CC = gcc
OBJ = c_lib.o
LIB_NAME = mylib

# 生成する共有ライブラリ名<lib_name>はC言語側の\
int  luaopen_<lib_name>(lua_State)の<lib_name>と共通でなけらばならない\

lib${LIB_NAME}.so : ${OBJ}
	${CC} -shared -o $@ $^

%.o : %.c
	${CC} -fpic -Wall -c $<

run: lib${LIB_NAME}.so
	lua c_lib.lua

clean:
	rm *.o *.so

.PHONY: clean run
