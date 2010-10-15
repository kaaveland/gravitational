
CFLAGS = -std=gnu99 -Wall -Wextra -lm
OBJECTS = particle.o gravity.o

lib: ${OBJECTS}
	ar rcs libgravity.a ${OBJECTS}

clean:
	rm ${OBJECTS}
	rm libgravity.a