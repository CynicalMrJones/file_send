server: src/server.c lib/lib.c
	gcc -g -Wall -Wextra -o server lib/lib.c src/server.c

client: src/client.c lib/lib.c
	gcc -g -Wall -Wextra -o client lib/lib.c src/client.c

testing:
	gcc -o test1 tests/test.c lib/lib.c -Wall -Wextra
	./test1
	rm test1

