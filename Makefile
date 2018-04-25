test: test.c render.c
	$(CC) -o $@ -lSDL2 -O0 -g -Wall -Werror $^

install: test
