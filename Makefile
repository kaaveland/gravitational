CFLAGS = -std=gnu99 -Wall -Wextra -lm -DDEBUG=1
OBJECTS = particle.o gravity.o

test: lib
	cc ${CFLAGS} test.c libgravity.a -o test

lib: ${OBJECTS}
	ar rcs libgravity.a ${OBJECTS}

clean:
	rm ${OBJECTS}
	rm libgravity.a
	rm test