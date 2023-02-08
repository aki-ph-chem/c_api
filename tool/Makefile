CC = gcc
name = tool
OBJ = dump.o error.o

lib${name}.a :${OBJ} 
	ar rcs $@ -o $^

%.o: ./src/%.c
	${CC} -c $<

clean:
	rm lib${name}.a *.o

.PHONY: clean
