CC = gcc
INCLUDE = ./include
CFLAGS = -I ${INCLUDE}
OBJ = main.o greet.o add.o

greet: ${OBJ} 
	${CC} -o $@ $^

main.o : main.c  ${INCLUDE}/*.h
	${CC} -c -o $@ ${CFLAGS} $<

%.o: ./src/%.c ${INCLUDE}/%.h
	${CC} -c $< 

run: greet
	./greet

clean:
	rm greet *.o

.PHONY: clean run

