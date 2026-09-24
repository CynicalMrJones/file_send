
main:
	gcc -Wall -Wextra -o main main.c

server: src/server.c
	gcc -g -Wall -Wextra -o server lib/lib.c src/server.c

client: src/client.c
	gcc -g -Wall -Wextra -o client lib/lib.c src/client.c
