CC = gcc
INCLUDE = ./include
LIB_NAME = my_tool
OBJ = greet.o add.o

greet: main.o lib${LIB_NAME}.a
	${CC} -o $@ $< -L ./ -l${LIB_NAME}

main.o : main.c  ${INCLUDE}/*.h
	${CC} -c -o $@ -I ${INCLUDE} $<

lib${LIB_NAME}.a : ${OBJ} 
	ar rcs $@ -o $^

%.o: ./src/%.c ${INCLUDE}/%.h
	${CC} -c $< 

run: greet
	./greet

clean:
	rm greet *.o *.a

.PHONY: clean run

