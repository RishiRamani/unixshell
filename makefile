CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = src/main.c src/parser.c src/executor.c src/builtins.c src/redirection.c
OUT = unixshell

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)