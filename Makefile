test: test.c render.c
	$(CC) -o $@ -lSDL2 -lGL -O0 -g -Wall -Werror $^

install: test
