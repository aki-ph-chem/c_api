CC = gcc
OBJ = c_lib.o
LIB_NAME = libmy_lib

${LIB_NAME}.so : ${OBJ}
	${CC} -shared -o $@ $^ 
%.o : %.c
	${CC} -fpic -Wall -c $< 
run:
	lua c_lib.lua

clean:
	rm *.o *.so

.PHONY: clean run

# gcc c_lib.c -shared -o mylib.so -fPIC -llua
