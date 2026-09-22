
main:
	gcc -Wall -Wextra -o main main.c

server: src/server.c
	gcc -Wall -Wextra -o server src/server.c

client: src/client.c
	gcc -Wall -Wextra -o client src/client.c
