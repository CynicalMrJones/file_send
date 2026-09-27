server: src/server.c lib/lib.c
	gcc -g -Wall -Wextra -o server lib/lib.c src/server.c

client: src/client.c lib/lib.c
	gcc -g -Wall -Wextra -o client lib/lib.c src/client.c

test:
	gcc -g -Wall -Wextra -o client lib/lib.c src/client.c
	gcc -g -Wall -Wextra -o server lib/lib.c src/server.c
	mv server tests/
	mv client tests/test_dir

