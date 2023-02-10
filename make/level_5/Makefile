CC = gcc
INCLUDE = ./include
LIB_NAME = my_tool
OBJ = greet.o add.o

greet: main.o lib${LIB_NAME}.so
	${CC} -o $@ $< -L ./ -l${LIB_NAME}

main.o : main.c  ${INCLUDE}/*.h
	${CC} -c -o $@ -I ${INCLUDE} $<

lib${LIB_NAME}.so : ${OBJ} 
	${CC} -shared -o $@  $^

%.o: ./src/%.c ${INCLUDE}/%.h
	${CC} -fpic -Wall -c $< 

run: greet
	./greet

clean:
	rm greet *.o *.so

.PHONY: clean run

